/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "usb_device_config.h"
#include "usb.h"

#include "usb_device.h"

#include "fsl_device_registers.h"

#if ((defined(USB_DEVICE_CONFIG_EHCI)) && (USB_DEVICE_CONFIG_EHCI > 0U))

#include "usb_device_dci.h"

#include "usb_device_ehci.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static void USB_DeviceEhciSetDefaultState(usb_device_ehci_state_struct_t *ehciState);
static usb_status_t USB_DeviceEhciEndpointInit(usb_device_ehci_state_struct_t *ehciState,
                                               usb_device_endpoint_init_struct_t *epInit);
static usb_status_t USB_DeviceEhciEndpointDeinit(usb_device_ehci_state_struct_t *ehciState, uint8_t ep);
static usb_status_t USB_DeviceEhciEndpointStall(usb_device_ehci_state_struct_t *ehciState, uint8_t ep);
static usb_status_t USB_DeviceEhciEndpointUnstall(usb_device_ehci_state_struct_t *ehciState, uint8_t ep);
static void USB_DeviceEhciFillSetupBuffer(usb_device_ehci_state_struct_t *ehciState, uint8_t ep);
static void USB_DeviceEhciCancelControlPipe(usb_device_ehci_state_struct_t *ehciState,
                                            uint8_t endpoint,
                                            uint8_t direction);
static void USB_DeviceEhciInterruptTokenDone(usb_device_ehci_state_struct_t *ehciState);
static void USB_DeviceEhciInterruptPortChange(usb_device_ehci_state_struct_t *ehciState);
static void USB_DeviceEhciInterruptReset(usb_device_ehci_state_struct_t *ehciState);
static void USB_DeviceEhciInterruptSof(usb_device_ehci_state_struct_t *ehciState);
#if ((defined(USB_DEVICE_CONFIG_LOW_POWER_MODE) && (USB_DEVICE_CONFIG_LOW_POWER_MODE > 0U)) || \
     (defined(USB_DEVICE_CONFIG_REMOTE_WAKEUP) && (USB_DEVICE_CONFIG_REMOTE_WAKEUP > 0U)))
static void USB_DeviceEhciInterruptSuspend(usb_device_ehci_state_struct_t *ehciState);
#endif
static usb_status_t USB_DeviceEhciTransfer(usb_device_ehci_state_struct_t *ehciState,
                                           uint8_t endpointAddress,
                                           uint8_t *buffer,
                                           uint32_t length);

extern usb_status_t USB_DeviceNotificationTrigger(void *handle, void *msg);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Apply for QH buffer, 2048-byte alignment */
#if defined(__ICCARM__)
#pragma data_alignment = 2048U
static __no_init usb_device_ehci_qh_struct_t s_UsbDeviceEhciQh[USB_DEVICE_CONFIG_EHCI][USB_DEVICE_CONFIG_ENDPOINTS * 2];
#elif defined(__CC_ARM) || defined(__GNUC__)
__attribute__((aligned(2048U))) static usb_device_ehci_qh_struct_t
    s_UsbDeviceEhciQh[USB_DEVICE_CONFIG_EHCI][USB_DEVICE_CONFIG_ENDPOINTS * 2];
#else
#error The tool-chain is not supported.
#endif

/* Apply for DTD buffer, 32-byte alignment */
#if defined(__ICCARM__)
#pragma data_alignment = 32U
static __no_init usb_device_ehci_dtd_struct_t
    s_UsbDeviceEhciDtd[USB_DEVICE_CONFIG_EHCI][USB_DEVICE_CONFIG_EHCI_MAX_DTD];
#elif defined(__CC_ARM) || defined(__GNUC__)
__attribute__((aligned(32U))) static usb_device_ehci_dtd_struct_t
    s_UsbDeviceEhciDtd[USB_DEVICE_CONFIG_EHCI][USB_DEVICE_CONFIG_EHCI_MAX_DTD];
#else
#error The tool-chain is not supported.
#endif

/* Apply for ehci device state structure */
static usb_device_ehci_state_struct_t g_UsbDeviceEhciSate[USB_DEVICE_CONFIG_EHCI];

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Set device controller state to default state.
 *
 * The function is used to set device controller state to default state.
 * The function will be called when USB_DeviceEhciInit called or the control type kUSB_DeviceControlGetEndpointStatus
 * received in USB_DeviceEhciControl.
 *
 * @param ehciState       Pointer of the device EHCI state structure.
 *
 */
static void USB_DeviceEhciSetDefaultState(usb_device_ehci_state_struct_t *ehciState)
{
    usb_device_ehci_dtd_struct_t *p;

    /* Initialize the dtd free queue */
    ehciState->dtdFree = ehciState->dtd;
    p = ehciState->dtdFree;
    for (uint32_t i = 1U; i < USB_DEVICE_CONFIG_EHCI_MAX_DTD; i++)
    {
        p->nextDtdPointer = (uint32_t)&ehciState->dtd[i];
        p = (usb_device_ehci_dtd_struct_t *)p->nextDtdPointer;
    }
    p->nextDtdPointer = 0U;
    ehciState->dtdCount = USB_DEVICE_CONFIG_EHCI_MAX_DTD;

    /* Not use interrupt threshold. */
    ehciState->registerBase->USBCMD &= ~USBHS_USBCMD_ITC_MASK;
    ehciState->registerBase->USBCMD |= USBHS_USBCMD_ITC(0U);

    /* Disable setup lockout, please refer to "Control Endpoint Operation" section in RM. */
    ehciState->registerBase->USBMODE |= USBHS_USBMODE_SLOM_MASK;

/* Set the endian by using CPU's endian */
#if (ENDIANNESS == BIG_ENDIAN)
    ehciState->registerBase->USBMODE |= USBHS_USBMODE_ES_MASK;
#else
    ehciState->registerBase->USBMODE &= ~USBHS_USBMODE_ES_MASK;
#endif
    /* Initialize the QHs of endpoint. */
    for (uint32_t i = 0U; i < (USB_DEVICE_CONFIG_ENDPOINTS * 2U); i++)
    {
        ehciState->qh[i].nextDtdPointer = USB_DEVICE_ECHI_DTD_TERMINATE_MASK;
        ehciState->qh[i].capabilttiesCharacteristicsUnion.capabilttiesCharacteristicsBitmap.maxPacketSize =
            USB_CONTROL_MAX_PACKET_SIZE;
        ehciState->dtdHard[i] = NULL;
        ehciState->dtdTail[i] = NULL;
        ehciState->qh[i].endpointStatusUnion.endpointStatusBitmap.isOpened = 0U;
    }

    /* Add QH buffer address to USBHS_EPLISTADDR_REG */
    ehciState->registerBase->EPLISTADDR = (uint32_t)ehciState->qh;

    /* Clear device address */
    ehciState->registerBase->DEVICEADDR = 0U;

    /* Enable reset, sof, token, stall interrupt */
    ehciState->registerBase->USBINTR =
        (USBHS_USBINTR_UE_MASK | USBHS_USBINTR_UEE_MASK | USBHS_USBINTR_PCE_MASK | USBHS_USBINTR_URE_MASK
#if ((defined(USB_DEVICE_CONFIG_LOW_POWER_MODE) && (USB_DEVICE_CONFIG_LOW_POWER_MODE > 0U)) || \
     (defined(USB_DEVICE_CONFIG_REMOTE_WAKEUP) && (USB_DEVICE_CONFIG_REMOTE_WAKEUP > 0U)))
         | USBHS_USBINTR_SLE_MASK
#endif /* USB_DEVICE_CONFIG_LOW_POWER_MODE || USB_DEVICE_CONFIG_REMOTE_WAKEUP */
         );

    /* Clear reset flag */
    ehciState->isResetting = 0U;
}

/*!
 * @brief Initialize a specified endpoint.
 *
 * The function is used to initialize a specified endpoint.
 *
 * @param ehciState       Pointer of the device EHCI state structure.
 * @param epInit          The endpoint initialization structure pointer.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
static usb_status_t USB_DeviceEhciEndpointInit(usb_device_ehci_state_struct_t *ehciState,
                                               usb_device_endpoint_init_struct_t *epInit)
{
    uint32_t primeBit = 1U << ((epInit->endpointAddress & USB_ENDPOINT_NUMBER_MASK) +
                               ((epInit->endpointAddress & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >> 0x03U));
    uint16_t maxPacketSize = epInit->maxPacketSize & USB_DESCRIPTOR_ENDPOINT_MAXPACKETSIZE_SIZE_MASK;
    uint8_t endpoint = (epInit->endpointAddress & USB_ENDPOINT_NUMBER_MASK);
    uint8_t direction = (epInit->endpointAddress & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >>
                        USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT;
    uint8_t index = ((uint8_t)((uint32_t)endpoint << 1U)) | direction;
    uint8_t transferType = epInit->transferType & USB_DESCRIPTOR_ENDPOINT_ATTRIBUTE_TYPE_MASK;

    /* Cancel pending transfer of the endpoint */
    USB_DeviceEhciCancel(ehciState, epInit->endpointAddress);

    if ((ehciState->registerBase->EPPRIME & primeBit) || (ehciState->registerBase->EPSR & primeBit))
    {
        return kStatus_USB_Busy;
    }

    /* Make the endpoint max packet size align with USB Specification 2.0. */
    if (USB_ENDPOINT_ISOCHRONOUS == transferType)
    {
        if (maxPacketSize > USB_DEVICE_MAX_HS_ISO_MAX_PACKET_SIZE)
        {
            maxPacketSize = USB_DEVICE_MAX_HS_ISO_MAX_PACKET_SIZE;
        }
        ehciState->qh[index].capabilttiesCharacteristicsUnion.capabilttiesCharacteristicsBitmap.mult =
            1U + ((maxPacketSize & USB_DESCRIPTOR_ENDPOINT_MAXPACKETSIZE_MULT_TRANSACTIONS_MASK) >>
                  USB_DESCRIPTOR_ENDPOINT_MAXPACKETSIZE_MULT_TRANSACTIONS_SHFIT);
    }
    else
    {
        ehciState->qh[index].capabilttiesCharacteristicsUnion.capabilttiesCharacteristicsBitmap.mult = 0U;
    }

    /* Save the max packet size of the endpoint */
    ehciState->qh[index].capabilttiesCharacteristicsUnion.capabilttiesCharacteristicsBitmap.maxPacketSize =
        maxPacketSize;
    /* Set ZLT bit. */
    ehciState->qh[index].capabilttiesCharacteristicsUnion.capabilttiesCharacteristicsBitmap.zlt = !epInit->zlt;

    /* Enable the endpoint. */
    if (USB_ENDPOINT_CONTROL == transferType)
    {
        ehciState->qh[index].capabilttiesCharacteristicsUnion.capabilttiesCharacteristicsBitmap.ios = 1U;
        ehciState->registerBase->EPCR0 |=
            (direction ?
                 (USBHS_EPCR_TXE_MASK | USBHS_EPCR_TXR_MASK | ((uint32_t)transferType << USBHS_EPCR_TXT_SHIFT)) :
                 (USBHS_EPCR_RXE_MASK | USBHS_EPCR_RXR_MASK | ((uint32_t)transferType << USBHS_EPCR_RXT_SHIFT)));
    }
    else
    {
        ehciState->qh[index].capabilttiesCharacteristicsUnion.capabilttiesCharacteristicsBitmap.ios = 0U;
        ehciState->registerBase->EPCR[endpoint - 1U] |=
            (direction ?
                 (USBHS_EPCR_TXE_MASK | USBHS_EPCR_TXR_MASK | ((uint32_t)transferType << USBHS_EPCR_TXT_SHIFT)) :
                 (USBHS_EPCR_RXE_MASK | USBHS_EPCR_RXR_MASK | ((uint32_t)transferType << USBHS_EPCR_RXT_SHIFT)));
    }

    ehciState->qh[index].endpointStatusUnion.endpointStatusBitmap.isOpened = 1U;
    return kStatus_USB_Success;
}

/*!
 * @brief De-initialize a specified endpoint.
 *
 * The function is used to de-initialize a specified endpoint.
 * Current transfer of the endpoint will be cancelled and the specified endpoint will be disabled.
 *
 * @param ehciState       Pointer of the device EHCI state structure.
 * @param ep               The endpoint address, Bit7, 0U - USB_OUT, 1U - USB_IN.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
static usb_status_t USB_DeviceEhciEndpointDeinit(usb_device_ehci_state_struct_t *ehciState, uint8_t ep)
{
    uint32_t primeBit =
        1U << ((ep & USB_ENDPOINT_NUMBER_MASK) + ((ep & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >> 0x03U));
    uint8_t endpoint = (ep & USB_ENDPOINT_NUMBER_MASK);
    uint8_t direction =
        (ep & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >> USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT;
    uint8_t index = ((uint8_t)((uint32_t)endpoint << 1U)) | direction;

    ehciState->qh[index].endpointStatusUnion.endpointStatusBitmap.isOpened = 0U;

    /* Cancel the transfer of the endpoint */
    USB_DeviceEhciCancel(ehciState, ep);

    if ((ehciState->registerBase->EPPRIME & primeBit) || (ehciState->registerBase->EPSR & primeBit))
    {
        return kStatus_USB_Busy;
    }

    /* Clear endpoint state */
    ehciState->qh[index].capabilttiesCharacteristicsUnion.capabilttiesCharacteristics = 0U;
    /* Disable the endpoint */
    if (!endpoint)
    {
        ehciState->registerBase->EPCR0 &=
            ~(direction ? (USBHS_EPCR_TXE_MASK | USBHS_EPCR_TXT_MASK) : (USBHS_EPCR_RXE_MASK | USBHS_EPCR_RXT_MASK));
    }
    else
    {
        ehciState->registerBase->EPCR[endpoint - 1U] &=
            ~(direction ? (USBHS_EPCR_TXE_MASK | USBHS_EPCR_TXT_MASK) : (USBHS_EPCR_RXE_MASK | USBHS_EPCR_RXT_MASK));
    }

    return kStatus_USB_Success;
}

/*!
 * @brief Stall a specified endpoint.
 *
 * The function is used to stall a specified endpoint.
 * Current transfer of the endpoint will be cancelled and the specified endpoint will be stalled.
 *
 * @param ehciState       Pointer of the device EHCI state structure.
 * @param ep               The endpoint address, Bit7, 0U - USB_OUT, 1U - USB_IN.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
static usb_status_t USB_DeviceEhciEndpointStall(usb_device_ehci_state_struct_t *ehciState, uint8_t ep)
{
    uint8_t endpoint = ep & USB_ENDPOINT_NUMBER_MASK;
    uint8_t direction =
        (ep & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >> USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT;
    uint8_t index = ((uint8_t)((uint32_t)endpoint << 1U)) | direction;

    /* Cancel the transfer of the endpoint */
    USB_DeviceEhciCancel(ehciState, ep);

    /* Set endpoint stall flag. */
    if (ehciState->qh[index].capabilttiesCharacteristicsUnion.capabilttiesCharacteristicsBitmap.ios)
    {
        if (!endpoint)
        {
            ehciState->registerBase->EPCR0 |= (USBHS_EPCR_TXS_MASK | USBHS_EPCR_RXS_MASK);
        }
        else
        {
            ehciState->registerBase->EPCR[endpoint - 1U] |= (USBHS_EPCR_TXS_MASK | USBHS_EPCR_RXS_MASK);
        }
    }
    else
    {
        if (!endpoint)
        {
            ehciState->registerBase->EPCR0 |= (direction ? USBHS_EPCR_TXS_MASK : USBHS_EPCR_RXS_MASK);
        }
        else
        {
            ehciState->registerBase->EPCR[endpoint - 1U] |= (direction ? USBHS_EPCR_TXS_MASK : USBHS_EPCR_RXS_MASK);
        }
    }

    return kStatus_USB_Success;
}

/*!
 * @brief Un-stall a specified endpoint.
 *
 * The function is used to un-stall a specified endpoint.
 * Current transfer of the endpoint will be cancelled and the specified endpoint will be un-stalled.
 *
 * @param ehciState       Pointer of the device EHCI state structure.
 * @param ep               The endpoint address, Bit7, 0U - USB_OUT, 1U - USB_IN.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
static usb_status_t USB_DeviceEhciEndpointUnstall(usb_device_ehci_state_struct_t *ehciState, uint8_t ep)
{
    uint8_t endpoint = ep & USB_ENDPOINT_NUMBER_MASK;
    uint8_t direction =
        (ep & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >> USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT;

    /* Clear the endpoint stall state */
    if (!endpoint)
    {
        ehciState->registerBase->EPCR0 &= ~(direction ? USBHS_EPCR_TXS_MASK : USBHS_EPCR_RXS_MASK);
    }
    else
    {
        ehciState->registerBase->EPCR[endpoint - 1U] &= ~(direction ? USBHS_EPCR_TXS_MASK : USBHS_EPCR_RXS_MASK);
        ehciState->registerBase->EPCR[endpoint - 1U] |= (direction ? USBHS_EPCR_TXR_MASK : USBHS_EPCR_RXR_MASK);
    }

    return kStatus_USB_Success;
}

/*!
 * @brief Get setup packet data.
 *
 * The function is used to get setup packet data and copy to a backup buffer.
 *
 * @param ehciState       Pointer of the device EHCI state structure.
 * @param ep               The endpoint number.
 *
 */
static void USB_DeviceEhciFillSetupBuffer(usb_device_ehci_state_struct_t *ehciState, uint8_t ep)
{
    uint8_t waitingSafelyAccess = 1U;
    uint8_t index = (ep * 2U) | USB_OUT;

    /* Write 1U to clear corresponding bit in EPSETUPSR. */
    ehciState->registerBase->EPSETUPSR = 1U << ep;

    while (waitingSafelyAccess)
    {
        /* Set the setup tripwire bit. */
        ehciState->registerBase->USBCMD |= USBHS_USBCMD_SUTW_MASK;

        /* Copy setup packet data to backup buffer */
        ehciState->qh[index].setupBufferBack[0] = ehciState->qh[index].setupBuffer[0];
        ehciState->qh[index].setupBufferBack[1] = ehciState->qh[index].setupBuffer[1];

        /* Read the USBCMD[SUTW] bit. If set, jump out from the while loop; if cleared continue */
        if (ehciState->registerBase->USBCMD & USBHS_USBCMD_SUTW_MASK)
        {
            waitingSafelyAccess = 0U;
        }
    }
    /* Clear the setup tripwire bit */
    ehciState->registerBase->USBCMD &= ~USBHS_USBCMD_SUTW_MASK;

    /* Poll until the EPSETUPSR bit clearred */
    while (ehciState->registerBase->EPSETUPSR & (1U << ep))
    {
    }
}

/*!
 * @brief Cancel the transfer of the control pipe.
 *
 * The function is used to cancel the transfer of the control pipe.
 *
 * @param ehciState       Pointer of the device EHCI state structure.
 * @param endpoint         The endpoint number.
 * @param direction        The direction of the endpoint.
 *
 */
static void USB_DeviceEhciCancelControlPipe(usb_device_ehci_state_struct_t *ehciState,
                                            uint8_t endpoint,
                                            uint8_t direction)
{
    usb_device_ehci_dtd_struct_t *currentDtd;
    uint32_t index = ((uint32_t)endpoint << 1U) + (uint32_t)direction;
    usb_device_callback_message_struct_t message;

    message.buffer = NULL;
    message.length = 0U;
    /* Get the dtd of the control pipe */
    currentDtd = ehciState->dtdHard[index];
    while (currentDtd)
    {
        /* Pass the transfer buffer address */
        if (NULL == message.buffer)
        {
            uint32_t bufferAddress = currentDtd->bufferPointerPage[0];
            message.buffer = (uint8_t *)((bufferAddress & USB_DEVICE_ECHI_DTD_PAGE_MASK) |
                                         (currentDtd->reservedUnion.originalBufferInfo.originalBufferOffest));
        }
        /* If the dtd is active, set the message length to USB_UNINITIALIZED_VAL_32. Or set the length by using finished
         * length. */
        if (currentDtd->dtdTokenUnion.dtdTokenBitmap.status & USB_DEVICE_ECHI_DTD_STATUS_ACTIVE)
        {
            message.length = USB_UNINITIALIZED_VAL_32;
        }
        else
        {
            message.length += (currentDtd->reservedUnion.originalBufferInfo.originalBufferLength -
                               currentDtd->dtdTokenUnion.dtdTokenBitmap.totalBytes);
        }

        /* Move the dtd head pointer to next. */
        /* If the pointer of the head equals to the tail, set the dtd queue to null. */
        if (ehciState->dtdHard[index] == ehciState->dtdTail[index])
        {
            ehciState->dtdHard[index] = NULL;
            ehciState->dtdTail[index] = NULL;
            ehciState->qh[index].nextDtdPointer = USB_DEVICE_ECHI_DTD_TERMINATE_MASK;
            ehciState->qh[index].dtdTokenUnion.dtdToken = 0U;
        }
        else
        {
            ehciState->dtdHard[index] = (usb_device_ehci_dtd_struct_t *)ehciState->dtdHard[index]->nextDtdPointer;
        }

        /* When the ioc is set or the dtd queue is empty, the up layer will be notified. */
        if ((currentDtd->dtdTokenUnion.dtdTokenBitmap.ioc) || (NULL == ehciState->dtdHard[index]))
        {
            message.code = endpoint | (uint8_t)((uint32_t)direction << 0x07U);
            message.isSetup = 0U;
            USB_DeviceNotificationTrigger(ehciState->deviceHandle, &message);
            message.buffer = NULL;
            message.length = 0U;
        }

        /* Clear the token field of the dtd. */
        currentDtd->dtdTokenUnion.dtdToken = 0U;
        /* Add the dtd to the free dtd queue. */
        currentDtd->nextDtdPointer = (uint32_t)ehciState->dtdFree;
        ehciState->dtdFree = currentDtd;
        ehciState->dtdCount++;

        /* Get the next in-used dtd. */
        currentDtd = ehciState->dtdHard[index];
    }
}

/*!
 * @brief Handle the endpoint token done interrupt.
 *
 * The function is used to handle the endpoint token done interrupt.
 *
 * @param ehciState       Pointer of the device EHCI state structure.
 *
 */
static void USB_DeviceEhciInterruptTokenDone(usb_device_ehci_state_struct_t *ehciState)
{
    uint32_t status;
    uint32_t primeBit;
    usb_device_ehci_dtd_struct_t *currentDtd;
    usb_device_callback_message_struct_t message;
    uint8_t endpoint;
    uint8_t direction;
    uint8_t count;
    uint8_t index;

    /* Get the EPSETUPSR to check the setup packect received in which one endpoint. */
    status = ehciState->registerBase->EPSETUPSR;

    if (status)
    {
        for (endpoint = 0U; endpoint < USB_DEVICE_CONFIG_ENDPOINTS; endpoint++)
        {
            /* Check the endpoint receive the setup packet. */
            if (status & (1U << endpoint))
            {
                /* Get last setup packet */
                usb_setup_struct_t *deviceSetup =
                    (usb_setup_struct_t *)&ehciState->qh[(uint8_t)((uint32_t)endpoint << 1U) + USB_OUT].setupBufferBack;

                /* Check the direction of the data phase. */
                direction = (deviceSetup->bmRequestType & USB_REQUEST_TYPE_DIR_IN) >> USB_REQUSET_TYPE_DIR_SHIFT;
                /* Cancel the data phase transfer */
                USB_DeviceEhciCancelControlPipe(ehciState, endpoint, direction);
                /* Cancel the status phase transfer */
                USB_DeviceEhciCancelControlPipe(ehciState, endpoint, 1U ^ direction);
                message.code = (endpoint) | (USB_OUT << 0x07U);
                message.buffer = (uint8_t *)deviceSetup;
                message.length = USB_SETUP_PACKET_SIZE;
                message.isSetup = 1U;
                /* Fill the setup packet to the backup buffer */
                USB_DeviceEhciFillSetupBuffer(ehciState, endpoint);
                /* Notify the up layer the EHCI status changed. */
                USB_DeviceNotificationTrigger(ehciState->deviceHandle, &message);
            }
        }
    }
    /* Read the USBHS_EPCOMPLETE_REG to get the endpoint transfer done status */
    status = ehciState->registerBase->EPCOMPLETE;
    /* Clear the endpoint transfer done status */
    ehciState->registerBase->EPCOMPLETE = status;

    if (status)
    {
        for (count = 0U; count < 32U; count++)
        {
            /* Check the transfer is done or not in the specified endpoint. */
            if (status & ((uint32_t)(1U << count)))
            {
                if (count > 15U)
                {
                    endpoint = count - 16U;
                    direction = USB_IN;
                }
                else
                {
                    endpoint = count;
                    direction = USB_OUT;
                }
                if (endpoint >= USB_DEVICE_CONFIG_ENDPOINTS)
                {
                    continue;
                }
                index = (endpoint << 1U) + direction;
                message.buffer = NULL;
                message.length = 0U;
                /* Get the in-used dtd of the specified endpoint. */
                currentDtd = ehciState->dtdHard[endpoint * 2U + direction];

                while (currentDtd)
                {
                    /* Don't handle the active dtd. */
                    if (currentDtd->dtdTokenUnion.dtdTokenBitmap.status & USB_DEVICE_ECHI_DTD_STATUS_ACTIVE)
                    {
                        break;
                    }
                    /* Save the transfer buffer address */
                    if (NULL == message.buffer)
                    {
                        message.buffer =
                            (uint8_t *)((currentDtd->bufferPointerPage[0] & USB_DEVICE_ECHI_DTD_PAGE_MASK) |
                                        (currentDtd->reservedUnion.originalBufferInfo.originalBufferOffest));
                    }
                    /* Save the transferred data length */
                    message.length += (currentDtd->reservedUnion.originalBufferInfo.originalBufferLength -
                                       currentDtd->dtdTokenUnion.dtdTokenBitmap.totalBytes);

                    /* Move the dtd queue head pointer to next */
                    if (ehciState->dtdHard[index] == ehciState->dtdTail[index])
                    {
                        ehciState->dtdHard[index] = NULL;
                        ehciState->dtdTail[index] = NULL;
                        ehciState->qh[index].nextDtdPointer = USB_DEVICE_ECHI_DTD_TERMINATE_MASK;
                        ehciState->qh[index].dtdTokenUnion.dtdToken = 0U;
                    }
                    else
                    {
                        ehciState->dtdHard[index] =
                            (usb_device_ehci_dtd_struct_t *)ehciState->dtdHard[index]->nextDtdPointer;
                    }

                    /* When the ioc is set or the dtd queue is empty, the up layer will be notified. */
                    if ((currentDtd->dtdTokenUnion.dtdTokenBitmap.ioc) || (NULL == ehciState->dtdHard[index]))
                    {
                        message.code = endpoint | (uint8_t)((uint32_t)direction << 0x07U);
                        message.isSetup = 0U;
                        USB_DeviceNotificationTrigger(ehciState->deviceHandle, &message);
                        message.buffer = NULL;
                        message.length = 0U;
                    }
                    /* Clear the token field of the dtd */
                    currentDtd->dtdTokenUnion.dtdToken = 0U;
                    currentDtd->nextDtdPointer = (uint32_t)ehciState->dtdFree;
                    ehciState->dtdFree = currentDtd;
                    ehciState->dtdCount++;
                    /* Get the next in-used dtd */
                    currentDtd = ehciState->dtdHard[index];

                    if ((NULL != currentDtd) &&
                        (currentDtd->dtdTokenUnion.dtdTokenBitmap.status & USB_DEVICE_ECHI_DTD_STATUS_ACTIVE))
                    {
                        primeBit = 1U << (endpoint + 16U * direction);

                        /* Try to prime the next dtd. */
                        ehciState->registerBase->EPPRIME = primeBit;

                        /* Whether the endpoint transmit/receive buffer is ready or not. If not, wait for prime bit
                         * cleared and prime the next dtd. */
                        if (!(ehciState->registerBase->EPSR & primeBit))
                        {
                            /* Wait for the endpoint prime bit cleared by HW */
                            while (ehciState->registerBase->EPPRIME & primeBit)
                            {
                            }

                            /* If the endpoint transmit/receive buffer is not ready */
                            if (!(ehciState->registerBase->EPSR & primeBit))
                            {
                                /* Prime next dtd and prime the transfer */
                                ehciState->qh[index].nextDtdPointer = (uint32_t)currentDtd;
                                ehciState->qh[index].dtdTokenUnion.dtdToken = 0U;
                                ehciState->registerBase->EPPRIME = primeBit;
                            }
                        }
                    }
                }
            }
        }
    }
}

/*!
 * @brief Handle the port status change interrupt.
 *
 * The function is used to handle the port status change interrupt.
 *
 * @param ehciState       Pointer of the device EHCI state structure.
 *
 */
static void USB_DeviceEhciInterruptPortChange(usb_device_ehci_state_struct_t *ehciState)
{
    usb_device_callback_message_struct_t message;

    message.buffer = (uint8_t *)NULL;
    message.length = 0U;
    message.isSetup = 0U;

    /* Whether the port is doing reset. */
    if (!(ehciState->registerBase->PORTSC1 & USBHS_PORTSC1_PR_MASK))
    {
        /* If not, update the USB speed. */
        if (ehciState->registerBase->PORTSC1 & USBHS_PORTSC1_HSP_MASK)
        {
            ehciState->speed = USB_SPEED_HIGH;
        }
        else
        {
            ehciState->speed = USB_SPEED_FULL;
        }

        /* If the device reset flag is non-zero, notify the up layer the device reset finished. */
        if (ehciState->isResetting)
        {
            message.code = kUSB_DeviceNotifyBusReset;
            USB_DeviceNotificationTrigger(ehciState->deviceHandle, &message);
            ehciState->isResetting = 0U;
        }
    }

#if defined(USB_DEVICE_CONFIG_DETACH_ENABLE) && (USB_DEVICE_CONFIG_DETACH_ENABLE > 0U)
    if ((!(ehciState->registerBase->PORTSC1 & USBHS_PORTSC1_CCS_MASK)) &&
        (ehciState->registerBase->PORTSC1 & USBHS_PORTSC1_CSC_MASK))
    {
        /* Device is disconnected from a host. */
        message.code = kUSB_DeviceNotifyDetach;
        USB_DeviceNotificationTrigger(ehciState->deviceHandle, &message);
    }
    if ((ehciState->registerBase->PORTSC1 & USBHS_PORTSC1_CCS_MASK) &&
        (ehciState->registerBase->PORTSC1 & USBHS_PORTSC1_CSC_MASK))
    {
        /* Device is connected to a host. */
        message.code = kUSB_DeviceNotifyAttach;
        USB_DeviceNotificationTrigger(ehciState->deviceHandle, &message);
    }
#endif /* USB_DEVICE_CONFIG_DETACH_ENABLE */

#if ((defined(USB_DEVICE_CONFIG_LOW_POWER_MODE) && (USB_DEVICE_CONFIG_LOW_POWER_MODE > 0U)) || \
     (defined(USB_DEVICE_CONFIG_REMOTE_WAKEUP) && (USB_DEVICE_CONFIG_REMOTE_WAKEUP > 0U)))
    if ((ehciState->isSuspending) && (!(ehciState->registerBase->PORTSC1 & USBHS_PORTSC1_SUSP_MASK)))
    {
        /* Set the resume flag */
        ehciState->isSuspending = 0U;

        message.code = kUSB_DeviceNotifyResume;
        USB_DeviceNotificationTrigger(ehciState->deviceHandle, &message);
    }
#endif /* USB_DEVICE_CONFIG_LOW_POWER_MODE || USB_DEVICE_CONFIG_REMOTE_WAKEUP */
}

/*!
 * @brief Handle the reset interrupt.
 *
 * The function is used to handle the reset interrupt.
 *
 * @param ehciState       Pointer of the device EHCI state structure.
 *
 */
static void USB_DeviceEhciInterruptReset(usb_device_ehci_state_struct_t *ehciState)
{
    uint32_t status = 0U;

    /* Clear the setup flag */
    status = ehciState->registerBase->EPSETUPSR;
    ehciState->registerBase->EPSETUPSR = status;
    /* Clear the endpoint complete flag */
    status = ehciState->registerBase->EPCOMPLETE;
    ehciState->registerBase->EPCOMPLETE = status;

    do
    {
        /* Flush the pending transfers */
        ehciState->registerBase->EPFLUSH = USBHS_EPFLUSH_FERB_MASK | USBHS_EPFLUSH_FETB_MASK;
    } while (ehciState->registerBase->EPPRIME & (USBHS_EPPRIME_PERB_MASK | USBHS_EPPRIME_PETB_MASK));

    /* Whether is the port reset. If yes, set the isResetting flag. Or, notify the up layer. */
    if (ehciState->registerBase->PORTSC1 & USBHS_PORTSC1_PR_MASK)
    {
        ehciState->isResetting = 1U;
    }
    else
    {
        usb_device_callback_message_struct_t message;
        message.buffer = (uint8_t *)NULL;
        message.code = kUSB_DeviceNotifyBusReset;
        message.length = 0U;
        message.isSetup = 0U;

        USB_DeviceNotificationTrigger(ehciState->deviceHandle, &message);
    }
}

/*!
 * @brief Handle the sof interrupt.
 *
 * The function is used to handle the sof interrupt.
 *
 * @param ehciState       Pointer of the device EHCI state structure.
 *
 */
static void USB_DeviceEhciInterruptSof(usb_device_ehci_state_struct_t *ehciState)
{
}

#if ((defined(USB_DEVICE_CONFIG_LOW_POWER_MODE) && (USB_DEVICE_CONFIG_LOW_POWER_MODE > 0U)) || \
     (defined(USB_DEVICE_CONFIG_REMOTE_WAKEUP) && (USB_DEVICE_CONFIG_REMOTE_WAKEUP > 0U)))
/*!
 * @brief Handle the suspend interrupt.
 *
 * The function is used to handle the suspend interrupt.
 *
 * @param ehciState       Pointer of the device EHCI state structure.
 *
 */
static void USB_DeviceEhciInterruptSuspend(usb_device_ehci_state_struct_t *ehciState)
{
    usb_device_callback_message_struct_t message;
    message.buffer = (uint8_t *)NULL;
    message.length = 0U;
    message.isSetup = 0U;

    /* If the port is in suspend state, notify the up layer */
    if (ehciState->registerBase->PORTSC1 & USBHS_PORTSC1_SUSP_MASK)
    {
        ehciState->isSuspending = 1U;
        message.code = kUSB_DeviceNotifySuspend;
        USB_DeviceNotificationTrigger(ehciState->deviceHandle, &message);
    }
}
#endif /* USB_DEVICE_CONFIG_LOW_POWER_MODE || USB_DEVICE_CONFIG_REMOTE_WAKEUP */

/*!
 * @brief Get dtds and link to QH.
 *
 * The function is used to get dtds and link to QH.
 *
 * @param ehciState       Pointer of the device EHCI state structure.
 * @param endpointAddress The endpoint address, Bit7, 0U - USB_OUT, 1U - USB_IN.
 * @param buffer           The memory address needed to be transferred.
 * @param length           Data length.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
static usb_status_t USB_DeviceEhciTransfer(usb_device_ehci_state_struct_t *ehciState,
                                           uint8_t endpointAddress,
                                           uint8_t *buffer,
                                           uint32_t length)
{
    usb_device_ehci_dtd_struct_t *dtd;
    usb_device_ehci_dtd_struct_t *dtdHard;
    uint32_t index = ((endpointAddress & USB_ENDPOINT_NUMBER_MASK) << 1U) |
                     ((endpointAddress & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >>
                      USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT);
    uint32_t primeBit = 1U << ((endpointAddress & USB_ENDPOINT_NUMBER_MASK) +
                               ((endpointAddress & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >> 0x03U));
    uint8_t epStatus = primeBit;
    uint32_t sendLength;
    uint32_t currentIndex = 0U;
    uint32_t dtdRequestCount = (length + USB_DEVICE_ECHI_DTD_TOTAL_BYTES - 1U) / USB_DEVICE_ECHI_DTD_TOTAL_BYTES;
    uint8_t qhIdle = 0U;
    uint8_t waitingSafelyAccess = 1U;
    USB_OSA_SR_ALLOC();

    if (!ehciState)
    {
        return kStatus_USB_InvalidHandle;
    }

    if (0U == ehciState->qh[index].endpointStatusUnion.endpointStatusBitmap.isOpened)
    {
        return kStatus_USB_Error;
    }
    /* Return error when ehci is doing reset */
    if (ehciState->isResetting)
    {
        return kStatus_USB_Error;
    }

    if (!dtdRequestCount)
    {
        dtdRequestCount = 1U;
    }

    USB_OSA_ENTER_CRITICAL();
    /* The free dtd count need to not less than the transfer requests. */
    if (dtdRequestCount > (uint32_t)ehciState->dtdCount)
    {
        USB_OSA_EXIT_CRITICAL();
        return kStatus_USB_Busy;
    }

    do
    {
        /* The transfer length need to not more than USB_DEVICE_ECHI_DTD_TOTAL_BYTES for each dtd. */
        if (length > USB_DEVICE_ECHI_DTD_TOTAL_BYTES)
        {
            sendLength = USB_DEVICE_ECHI_DTD_TOTAL_BYTES;
        }
        else
        {
            sendLength = length;
        }
        length -= sendLength;

        /* Get a free dtd */
        dtd = ehciState->dtdFree;

        ehciState->dtdFree = (usb_device_ehci_dtd_struct_t *)dtd->nextDtdPointer;
        ehciState->dtdCount--;

        /* Save the dtd head when current active buffer offset is zero. */
        if (!currentIndex)
        {
            dtdHard = dtd;
        }

        /* Set the dtd field */
        dtd->nextDtdPointer = USB_DEVICE_ECHI_DTD_TERMINATE_MASK;
        dtd->dtdTokenUnion.dtdToken = 0U;
        dtd->bufferPointerPage[0] = (uint32_t)(buffer + currentIndex);
        dtd->bufferPointerPage[1] =
            (dtd->bufferPointerPage[0] + USB_DEVICE_ECHI_DTD_PAGE_BLOCK) & USB_DEVICE_ECHI_DTD_PAGE_MASK;
        dtd->bufferPointerPage[2] = dtd->bufferPointerPage[1] + USB_DEVICE_ECHI_DTD_PAGE_BLOCK;
        dtd->bufferPointerPage[3] = dtd->bufferPointerPage[2] + USB_DEVICE_ECHI_DTD_PAGE_BLOCK;
        dtd->bufferPointerPage[4] = dtd->bufferPointerPage[3] + USB_DEVICE_ECHI_DTD_PAGE_BLOCK;

        dtd->dtdTokenUnion.dtdTokenBitmap.totalBytes = sendLength;

        /* Save the data length needed to be transferred. */
        dtd->reservedUnion.originalBufferInfo.originalBufferLength = sendLength;
        /* Save the original buffer address */
        dtd->reservedUnion.originalBufferInfo.originalBufferOffest =
            dtd->bufferPointerPage[0] & USB_DEVICE_ECHI_DTD_PAGE_OFFSET_MASK;

        /* Set the IOC field in last dtd. */
        if (!length)
        {
            dtd->dtdTokenUnion.dtdTokenBitmap.ioc = 1U;
        }

        /* Set dtd active */
        dtd->dtdTokenUnion.dtdTokenBitmap.status = USB_DEVICE_ECHI_DTD_STATUS_ACTIVE;

        /* Move the buffer offset index */
        currentIndex += sendLength;

        /* Add dtd to the in-used dtd queue */
        if (ehciState->dtdTail[index])
        {
            ehciState->dtdTail[index]->nextDtdPointer = (uint32_t)dtd;
            ehciState->dtdTail[index] = dtd;
        }
        else
        {
            ehciState->dtdHard[index] = dtd;
            ehciState->dtdTail[index] = dtd;
            qhIdle = 1U;
        }
    } while (length);

    /* If the QH is not empty */
    if (!qhIdle)
    {
        /* If the prime bit is set, nothing need to do. */
        if (ehciState->registerBase->EPPRIME & primeBit)
        {
            USB_OSA_EXIT_CRITICAL();
            return kStatus_USB_Success;
        }

        /* To safely a dtd */
        while (waitingSafelyAccess)
        {
            /* set the ATDTW flag to USBHS_USBCMD_REG. */
            ehciState->registerBase->USBCMD |= USBHS_USBCMD_ATDTW_MASK;
            /* Read EPSR */
            epStatus = ehciState->registerBase->EPSR;
            /* Wait the ATDTW bit set */
            if (ehciState->registerBase->USBCMD & USBHS_USBCMD_ATDTW_MASK)
            {
                waitingSafelyAccess = 0U;
            }
        }
        /* Clear the ATDTW bit */
        ehciState->registerBase->USBCMD &= ~USBHS_USBCMD_ATDTW_MASK;
    }

    /* If QH is empty or the endpoint is not primed, need to link current dtd head to the QH. */
    /* When the endpoint is not primed if qhIdle is zero, it means the QH is empty. */
    if ((qhIdle) || (!(epStatus & primeBit)))
    {
        ehciState->qh[index].nextDtdPointer = (uint32_t)dtdHard;
        ehciState->qh[index].dtdTokenUnion.dtdToken = 0U;
        ehciState->registerBase->EPPRIME = primeBit;
    }

    USB_OSA_EXIT_CRITICAL();
    return kStatus_USB_Success;
}

/*!
 * @brief Initialize the USB device EHCI instance.
 *
 * This function initializes the USB device EHCI module specified by the controllerId.
 *
 * @param controllerId The controller id of the USB IP. Please refer to enumeration type usb_controller_index_t.
 * @param handle        Pointer of the device handle, used to identify the device object is belonged to.
 * @param ehciHandle   It is out parameter, is used to return pointer of the device EHCI handle to the caller.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceEhciInit(uint8_t controllerId,
                                usb_device_handle handle,
                                usb_device_controller_handle *ehciHandle)
{
    usb_device_ehci_state_struct_t *ehciState;
    uint32_t ehci_base[] = USBHS_BASE_ADDRS;

    if ((controllerId < kUSB_ControllerEhci0) ||
        ((uint32_t)(controllerId - kUSB_ControllerEhci0) >= USB_DEVICE_CONFIG_EHCI) ||
        ((uint32_t)(controllerId - kUSB_ControllerEhci0) >= (sizeof(ehci_base) / sizeof(uint32_t))))
    {
        return kStatus_USB_ControllerNotFound;
    }

    ehciState = &g_UsbDeviceEhciSate[controllerId - kUSB_ControllerEhci0];

    ehciState->dtd = s_UsbDeviceEhciDtd[controllerId - kUSB_ControllerEhci0];
    ehciState->qh = s_UsbDeviceEhciQh[controllerId - kUSB_ControllerEhci0];
    ehciState->controllerId = controllerId;

    ehciState->registerBase = (USBHS_Type *)ehci_base[controllerId - kUSB_ControllerEhci0];

    /* Get the HW's endpoint count */
    ehciState->endpointCount =
        (uint8_t)((ehciState->registerBase->DCCPARAMS & USBHS_DCCPARAMS_DEN_MASK) >> USBHS_DCCPARAMS_DEN_SHIFT);

    if (ehciState->endpointCount < USB_DEVICE_CONFIG_ENDPOINTS)
    {
        return kStatus_USB_Error;
    }
    ehciState->deviceHandle = (usb_device_struct_t *)handle;

    /* Clear the controller mode field and set to device mode. */
    ehciState->registerBase->USBMODE &= ~USBHS_USBMODE_CM_MASK;
    ehciState->registerBase->USBMODE |= USBHS_USBMODE_CM(0x02U);

    /* Set the EHCI to default status. */
    USB_DeviceEhciSetDefaultState(ehciState);
    *ehciHandle = (usb_device_controller_handle)ehciState;

    return kStatus_USB_Success;
}

/*!
 * @brief De-initialize the USB device EHCI instance.
 *
 * This function de-initializes the USB device EHCI module.
 *
 * @param ehciHandle   Pointer of the device EHCI handle.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceEhciDeinit(usb_device_controller_handle ehciHandle)
{
    usb_device_ehci_state_struct_t *ehciState = (usb_device_ehci_state_struct_t *)ehciHandle;

    if (!ehciHandle)
    {
        return kStatus_USB_InvalidHandle;
    }

    /* Disable all interrupt. */
    ehciState->registerBase->USBINTR = 0U;
    /* Stop the device functionality. */
    ehciState->registerBase->USBCMD &= ~USBHS_USBCMD_RS_MASK;
    /* Reset the controller. */
    ehciState->registerBase->USBCMD |= USBHS_USBCMD_RST_MASK;

    return kStatus_USB_Success;
}

/*!
 * @brief Send data through a specified endpoint.
 *
 * This function sends data through a specified endpoint.
 *
 * @param ehciHandle      Pointer of the device EHCI handle.
 * @param endpointAddress Endpoint index.
 * @param buffer           The memory address to hold the data need to be sent.
 * @param length           The data length need to be sent.
 *
 * @return A USB error code or kStatus_USB_Success.
 *
 * @note The return value just means if the sending request is successful or not; the transfer done is notified by the
 * corresponding callback function.
 * Currently, only one transfer request can be supported for one specific endpoint.
 * If there is a specific requirement to support multiple transfer requests for one specific endpoint, the application
 * should implement a queue in the application level.
 * The subsequent transfer could begin only when the previous transfer is done (get notification through the endpoint
 * callback).
 */
usb_status_t USB_DeviceEhciSend(usb_device_controller_handle ehciHandle,
                                uint8_t endpointAddress,
                                uint8_t *buffer,
                                uint32_t length)
{
    /* Add dtd to the QH */
    return USB_DeviceEhciTransfer(
        (usb_device_ehci_state_struct_t *)ehciHandle,
        (endpointAddress & USB_ENDPOINT_NUMBER_MASK) | (USB_IN << USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT),
        buffer, length);
}

/*!
 * @brief Receive data through a specified endpoint.
 *
 * This function Receives data through a specified endpoint.
 *
 * @param ehciHandle      Pointer of the device EHCI handle.
 * @param endpointAddress Endpoint index.
 * @param buffer           The memory address to save the received data.
 * @param length           The data length want to be received.
 *
 * @return A USB error code or kStatus_USB_Success.
 *
 * @note The return value just means if the receiving request is successful or not; the transfer done is notified by the
 * corresponding callback function.
 * Currently, only one transfer request can be supported for one specific endpoint.
 * If there is a specific requirement to support multiple transfer requests for one specific endpoint, the application
 * should implement a queue in the application level.
 * The subsequent transfer could begin only when the previous transfer is done (get notification through the endpoint
 * callback).
 */
usb_status_t USB_DeviceEhciRecv(usb_device_controller_handle ehciHandle,
                                uint8_t endpointAddress,
                                uint8_t *buffer,
                                uint32_t length)
{
    /* Add dtd to the QH */
    return USB_DeviceEhciTransfer(
        (usb_device_ehci_state_struct_t *)ehciHandle,
        (endpointAddress & USB_ENDPOINT_NUMBER_MASK) | (USB_OUT << USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT),
        buffer, length);
}

/*!
 * @brief Cancel the pending transfer in a specified endpoint.
 *
 * The function is used to cancel the pending transfer in a specified endpoint.
 *
 * @param ehciHandle      Pointer of the device EHCI handle.
 * @param ep               Endpoint address, bit7 is the direction of endpoint, 1U - IN, 0U - OUT.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceEhciCancel(usb_device_controller_handle ehciHandle, uint8_t ep)
{
    usb_device_ehci_state_struct_t *ehciState = (usb_device_ehci_state_struct_t *)ehciHandle;
    usb_device_callback_message_struct_t message;
    usb_device_ehci_dtd_struct_t *currentDtd;
    uint32_t primeBit =
        1U << ((ep & USB_ENDPOINT_NUMBER_MASK) + ((ep & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >> 0x03U));
    uint8_t index =
        ((ep & USB_ENDPOINT_NUMBER_MASK) << 1U) | ((ep & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >> 0x07U);

    USB_OSA_SR_ALLOC();

    if (!ehciHandle)
    {
        return kStatus_USB_InvalidHandle;
    }

    USB_OSA_ENTER_CRITICAL();

    message.buffer = NULL;
    message.length = USB_UNINITIALIZED_VAL_32;
    /* Get the first dtd */
    currentDtd = ehciState->dtdHard[index];
    while (currentDtd)
    {
        if (currentDtd->dtdTokenUnion.dtdTokenBitmap.status & USB_DEVICE_ECHI_DTD_STATUS_ACTIVE)
        {
            /* Flush the endpoint to stop a transfer. */
            do
            {
                /* Set the corresponding bit(s) in the EPFLUSH register */
                ehciState->registerBase->EPFLUSH |= primeBit;

                /* Wait until all bits in the EPFLUSH register are cleared. */
                while (ehciState->registerBase->EPFLUSH & primeBit)
                {
                }
                /*
                 * Read the EPSR register to ensure that for all endpoints
                 * commanded to be flushed, that the corresponding bits
                 * are now cleared.
                 */
            } while (ehciState->registerBase->EPSR & primeBit);
        }

        /* Save the original buffer address. */
        if (NULL == message.buffer)
        {
            message.buffer = (uint8_t *)((currentDtd->bufferPointerPage[0] & USB_DEVICE_ECHI_DTD_PAGE_MASK) |
                                         (currentDtd->reservedUnion.originalBufferInfo.originalBufferOffest));
        }

        /* Remove the dtd from the dtd in-used queue. */
        if (ehciState->dtdHard[index] == ehciState->dtdTail[index])
        {
            ehciState->dtdHard[index] = NULL;
            ehciState->dtdTail[index] = NULL;
        }
        else
        {
            ehciState->dtdHard[index] = (usb_device_ehci_dtd_struct_t *)ehciState->dtdHard[index]->nextDtdPointer;
        }

        /* When the ioc is set or the dtd queue is empty, the up layer will be notified. */
        if ((currentDtd->dtdTokenUnion.dtdTokenBitmap.ioc) || (NULL == ehciState->dtdHard[index]))
        {
            message.code = ep;
            message.isSetup = 0U;
            USB_DeviceNotificationTrigger(ehciState->deviceHandle, &message);
            message.buffer = NULL;
        }
        /* Clear the token field. */
        currentDtd->dtdTokenUnion.dtdToken = 0U;
        /* Save the dtd to the free queue. */
        currentDtd->nextDtdPointer = (uint32_t)ehciState->dtdFree;
        ehciState->dtdFree = currentDtd;
        ehciState->dtdCount++;
        /* Get the next dtd. */
        currentDtd = ehciState->dtdHard[index];
    }
    /* Set the QH to empty. */
    ehciState->qh[index].nextDtdPointer = USB_DEVICE_ECHI_DTD_TERMINATE_MASK;
    ehciState->qh[index].dtdTokenUnion.dtdToken = 0U;
    USB_OSA_EXIT_CRITICAL();
    return kStatus_USB_Success;
}

/*!
 * @brief Control the status of the selected item.
 *
 * The function is used to control the status of the selected item.
 *
 * @param ehciHandle      Pointer of the device EHCI handle.
 * @param type             The selected item. Please refer to enumeration type usb_device_control_type_t.
 * @param param            The param type is determined by the selected item.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceEhciControl(usb_device_controller_handle ehciHandle, usb_device_control_type_t type, void *param)
{
    usb_device_ehci_state_struct_t *ehciState = (usb_device_ehci_state_struct_t *)ehciHandle;
    usb_status_t error = kStatus_USB_Error;
    uint16_t *temp16;
    uint8_t *temp8;
#if USB_DEVICE_CONFIG_REMOTE_WAKEUP
    USB_OSA_SR_ALLOC();
#endif

    if (!ehciHandle)
    {
        return kStatus_USB_InvalidHandle;
    }

    switch (type)
    {
        case kUSB_DeviceControlRun:
            ehciState->registerBase->USBCMD |= USBHS_USBCMD_RS_MASK;
            error = kStatus_USB_Success;
            break;
        case kUSB_DeviceControlStop:
            ehciState->registerBase->USBCMD &= ~USBHS_USBCMD_RS_MASK;
            error = kStatus_USB_Success;
            break;
        case kUSB_DeviceControlEndpointInit:
            if (param)
            {
                error = USB_DeviceEhciEndpointInit(ehciState, (usb_device_endpoint_init_struct_t *)param);
            }
            break;
        case kUSB_DeviceControlEndpointDeinit:
            if (param)
            {
                temp8 = (uint8_t *)param;
                error = USB_DeviceEhciEndpointDeinit(ehciState, *temp8);
            }
            break;
        case kUSB_DeviceControlEndpointStall:
            if (param)
            {
                temp8 = (uint8_t *)param;
                error = USB_DeviceEhciEndpointStall(ehciState, *temp8);
            }
            break;
        case kUSB_DeviceControlEndpointUnstall:
            if (param)
            {
                temp8 = (uint8_t *)param;
                error = USB_DeviceEhciEndpointUnstall(ehciState, *temp8);
            }
            break;
        case kUSB_DeviceControlGetDeviceStatus:
            if (param)
            {
                temp16 = (uint16_t *)param;
                *temp16 =
                    (USB_DEVICE_CONFIG_SELF_POWER << (USB_REQUSET_STANDARD_GET_STATUS_DEVICE_SELF_POWERED_SHIFT)) |
                    (USB_DEVICE_CONFIG_REMOTE_WAKEUP << (USB_REQUSET_STANDARD_GET_STATUS_DEVICE_REMOTE_WARKUP_SHIFT));
                error = kStatus_USB_Success;
            }
            break;
        case kUSB_DeviceControlGetEndpointStatus:
            if (param)
            {
                usb_device_endpoint_status_struct_t *endpointStatus = (usb_device_endpoint_status_struct_t *)param;
                uint8_t ep = (endpointStatus->endpointAddress) & USB_ENDPOINT_NUMBER_MASK;
                uint8_t direction =
                    ((endpointStatus->endpointAddress) & USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_MASK) >>
                    USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT;

                if (ep < USB_DEVICE_CONFIG_ENDPOINTS)
                {
                    if (ep)
                    {
                        endpointStatus->endpointStatus = (ehciState->registerBase->EPCR[ep - 1U] &
                                                          (direction ? USBHS_EPCR_TXS_MASK : USBHS_EPCR_RXS_MASK)) ?
                                                             kUSB_DeviceEndpointStateStalled :
                                                             kUSB_DeviceEndpointStateIdle;
                    }
                    else
                    {
                        endpointStatus->endpointStatus =
                            (ehciState->registerBase->EPCR0 & (direction ? USBHS_EPCR_TXS_MASK : USBHS_EPCR_RXS_MASK)) ?
                                kUSB_DeviceEndpointStateStalled :
                                kUSB_DeviceEndpointStateIdle;
                    }
                    error = kStatus_USB_Success;
                }
            }
            break;
        case kUSB_DeviceControlSetDeviceAddress:
            if (param)
            {
                temp8 = (uint8_t *)param;
                ehciState->registerBase->DEVICEADDR = (((uint32_t)(*temp8)) << USBHS_DEVICEADDR_USBADR_SHIFT);
                error = kStatus_USB_Success;
            }
            break;
        case kUSB_DeviceControlGetSynchFrame:
            break;
        case kUSB_DeviceControlResume:
#if defined(USB_DEVICE_CONFIG_REMOTE_WAKEUP) && (USB_DEVICE_CONFIG_REMOTE_WAKEUP > 0U)
            USB_OSA_ENTER_CRITICAL();
            ehciState->registerBase->PORTSC1 |= USBHS_PORTSC1_FPR_MASK;
            for (int i = 500U; i > 0U; i--)
            {
                __ASM("nop");
            }
            ehciState->registerBase->PORTSC1 &= ~USBHS_PORTSC1_FPR_MASK;
            USB_OSA_EXIT_CRITICAL();
            error = kStatus_USB_Success;
#endif /* USB_DEVICE_CONFIG_REMOTE_WAKEUP */
            break;
        case kUSB_DeviceControlSetDefaultStatus:
            for (uint8_t count = 0U; count < USB_DEVICE_CONFIG_ENDPOINTS; count++)
            {
                USB_DeviceEhciEndpointDeinit(ehciState, (count | (USB_IN << 0x07U)));
                USB_DeviceEhciEndpointDeinit(ehciState, (count | (USB_OUT << 0x07U)));
            }
            USB_DeviceEhciSetDefaultState(ehciState);
            error = kStatus_USB_Success;
            break;
        case kUSB_DeviceControlGetSpeed:
            if (param)
            {
                temp8 = (uint8_t *)param;
                *temp8 = ehciState->speed;
                error = kStatus_USB_Success;
            }
            break;
        case kUSB_DeviceControlGetOtgStatus:
            break;
        case kUSB_DeviceControlSetOtgStatus:
            break;
#if (defined(USB_DEVICE_CONFIG_EHCI_TEST_MODE) && (USB_DEVICE_CONFIG_EHCI_TEST_MODE > 0U))
        case kUSB_DeviceControlSetTestMode:
            if (param)
            {
                temp8 = (uint8_t *)param;
                ehciState->registerBase->PORTSC1 |= ((uint32_t)(*temp8) << 16U);
                error = kStatus_USB_Success;
            }
            break;
#endif
        default:
            break;
    }

    return error;
}

/*!
 * @brief Handle the EHCI device interrupt.
 *
 * The function is used to handle the EHCI device interrupt.
 *
 * @param deviceHandle    The device handle got from USB_DeviceInit.
 *
 */
void USB_DeviceEhciIsrFunction(void *deviceHandle)
{
    usb_device_struct_t *handle = (usb_device_struct_t *)deviceHandle;
    usb_device_ehci_state_struct_t *ehciState;
    uint32_t status;

    if (NULL == deviceHandle)
    {
        return;
    }

    ehciState = (usb_device_ehci_state_struct_t *)(handle->controllerHandle);

    status = ehciState->registerBase->USBSTS;
    status &= ehciState->registerBase->USBINTR;

    ehciState->registerBase->USBSTS = status;

#if defined(USB_DEVICE_CONFIG_KHCI_ERROR_HANDLING) && (USB_DEVICE_CONFIG_KHCI_ERROR_HANDLING > 0U)
    if (status & USBHS_USBSTS_UEI_MASK)
    {
        /* Error interrupt */
        USB_DeviceEhciInterruptError(ehciState);
    }
#endif /* USB_DEVICE_CONFIG_KHCI_ERROR_HANDLING */

    if (status & USBHS_USBSTS_URI_MASK)
    {
        /* Reset interrupt */
        USB_DeviceEhciInterruptReset(ehciState);
    }

    if (status & USBHS_USBSTS_UI_MASK)
    {
        /* Token done interrupt */
        USB_DeviceEhciInterruptTokenDone(ehciState);
    }

    if (status & USBHS_USBSTS_PCI_MASK)
    {
        /* Port status change interrupt */
        USB_DeviceEhciInterruptPortChange(ehciState);
    }

#if ((defined(USB_DEVICE_CONFIG_LOW_POWER_MODE) && (USB_DEVICE_CONFIG_LOW_POWER_MODE > 0U)) || \
     (defined(USB_DEVICE_CONFIG_REMOTE_WAKEUP) && (USB_DEVICE_CONFIG_REMOTE_WAKEUP > 0U)))
    if (status & USBHS_USBSTS_SLI_MASK)
    {
        /* Suspend interrupt */
        USB_DeviceEhciInterruptSuspend(ehciState);
    }
#endif /* USB_DEVICE_CONFIG_LOW_POWER_MODE || USB_DEVICE_CONFIG_REMOTE_WAKEUP */

    if (status & USBHS_USBSTS_SRI_MASK)
    {
        /* Sof interrupt */
        USB_DeviceEhciInterruptSof(ehciState);
    }
}

#endif /* USB_DEVICE_CONFIG_EHCI */
