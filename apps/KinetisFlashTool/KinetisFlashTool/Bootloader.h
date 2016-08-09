/*
* Copyright (c) 2013-15, Freescale Semiconductor, Inc.
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

#pragma once
#include "afxwin.h"
#include <vector>
#include <array>
#include "../../common/blfwkdll/blfwkdll.h"

using namespace std;

/*!
* \brief Bootloader class.
*/
class Bootloader : public CWinThread
{
public:
    /*!
    * \brief TargetInformation struct contains devices information.
    */
    struct TargetInformation
    {
        UINT32 targetVersion;    //!< Bootloader version.
        UINT32 procotolVersion;  //!< Serial procotol version.
        UINT32 securityState;    //!< Security state.
        UINT32 flashSize;        //!< Flash memory size.
        UINT32 flashSectorSize;  //!< Flash memory sector size.
        UINT32 ramSize;          //!< RAM memory size.
        UINT32 rsvRgnFlashStart; //!< Start address of flash reserved region.
        UINT32 rsvRgnFlashEnd;   //!< End address of flash reserved region.
        UINT32 rsvRgnRamStart;   //!< Start address of RAM reserved region.
        UINT32 rsvRgnRamEnd;     //!< End address of RAM reserved region.
        UINT32 supportedCmd;     //!< Current device supported command.
    };

    /*!
    * \brief FlashFirmwareOption struct contains information for an update progress.
    */
    struct FlashFirmwareOption
    {
        BOOL autoConnect;          //!< Auto connect device after an update, if set TRUE.(Currently, not used)
        BOOL doErasetoUnlock;      //!< Execute flash-erase-all-unsecure to unlock the device.
        BOOL useKeytoUnlock;       //!< Execute flash-security-disable to unlock the device.
        std::string backdoorkey;   //!< Backdoor key
        std::string imageFilePath; //!< Absolute path for image file.
        uint32_t baseAddress;      //!< Base address where image file is written to.(Only used for binary file.)
    };

    /*!
    * \brief EraseOption struct contains information for an erase progress.
    */
    struct EraseOption
    {
        enum ERASE_OPERATION
        {
            erase_region = 0,          //!< Execute flash-erase-region.
            erase_all = 1,             //!< Execute flash-erase-all.
            erase_all_and_unsecure = 2 //!< Execute flash-erase-all-unsecure.
        };

        ERASE_OPERATION option; //!< Erase operation..
        uint32_t memoryID;      //!< Memory ID used for flash-erase-all command.
        uint32_t startAddress;  //!< Start address to erase.
        uint32_t length;        //!< Length in bytes to erase.
    };

    /*!
    * \brief ProgramOnceOption struct contains information for a program IFR progress.
    */
    struct ProgramOnceOption
    {
        uint32_t index;     //!< IFR index.
        uint32_t byteCount; //!< IFR length( should be 4 or 8).
        std::string data;   //!< IFR data to write. 4 or 8 hex digits with on leading "0x".
    };

public:
    //! \brief Generated standard constructor.
    Bootloader() { this->Open(); };
    //! \brief Generated standard destructor.
    virtual ~Bootloader() { this->Close(); };
    //! \brief Overrides.
    virtual BOOL InitInstance() { return CWinThread::InitInstance(); };
    //! \brief Overrides.
    virtual int ExitInstance() { return CWinThread::ExitInstance(); };
    /*!
    * \brief KibbleStatusCode struct contains two correct status code.
    */
    enum KibbleStatusCode
    {
        KBL_Status_Success = 0x0,           //!< Success status.
        KBL_Status_AbortDataPhase = 0x2712, //!< AbortDataPhase. This status will be received when executing RESET or
        //! EXECUTE command in a SB file successfully.
    };

    /*!
    * \brief Return whether currently a new operation can be processed.
    */
    bool CanRun();

    /*!
    * \brief Do initialization and create a child thread.
    */
    DWORD Open();

    /*!
    * \brief Do deinitialization and wait for child thread exit.
    */
    void Close();

    /*!
    * \brief the callback function to update the progress.
    */
    static void progressCallback(int percentage, int segmentIndex, int segmentCount);

    /*!
    * \brief Wait an event to be triggered.
    */
    DWORD WaitForEvents(DWORD time);

    /*!
    * \brief Reset the triggered event after the corresponding progress is done.
    */
    void ResetEvents(DWORD events);

    /*!
    * \brief Triggered a ping even to text the connection.
    */
    void Ping();

    /*!
    * \brief Triggered a reset even, and disconnect target device.
    */
    void Reset();

    /*!
    * \brief Triggered a connect even, and try to connect target device.
    */
    void Connect(blfwkdll::Updater::PeripheralConfig *config);

    /*!
    * \brief Triggered a updatestatue even to collect device information.
    */
    void UpdateStatus();

    /*!
    * \brief Triggered a update even to do a update progress.
    */
    void UpdateImage(blfwkdll::Updater::PeripheralConfig *config, FlashFirmwareOption *option);

    /*!
    * \brief Triggered an erase even.
    */
    void Erase(EraseOption *option);

    /*!
    * \brief Triggered an programming ifr even.
    */
    void ProgramOnce(ProgramOnceOption *option);

    HANDLE m_pingEvent;        //!< Ping event.
    HANDLE m_statusEvent;      //!< Update status event.
    HANDLE m_resetEvent;       //!< Reset event.
    HANDLE m_connectEvent;     //!< Connect event.
    HANDLE m_updateEvent;      //!< Update event.
    HANDLE m_eraseEvent;       //!< Erase event.
    HANDLE m_programOnceEvent; //!< Program IFR event.
    HANDLE m_exitEvent;        //!< Exit event to let child thread exit.
    CWinThread *m_pThread;     //!< Pointer to child thread.

    bool m_abort;                                 //!< Flag is set to abort the update progress.
    bool m_isRunning;                             //!< Flag is set when there is an operation under processing.
    bool m_isExiting;                             //!< Flag is set to let child thread exit.
    bool m_isConneted;                            //!< Flag is set when connect to a target device.
    TargetInformation m_targetInfo;               //!< Contains devices information.
    FlashFirmwareOption m_firmwareConfig;         //!< Contains information for a update operation.
    EraseOption m_eraseOption;                    //!< Contains information for an erase operation.
    ProgramOnceOption m_programOnceOption;        //!< Contains information for a programming-IFR operation.
    blfwkdll::Updater::PeripheralConfig m_config; //!< Contains information for peripheral configuration.
    blfwkdll::Updater *m_updater;                 //!< Pointer to a blfwkdll::Updater.
};

extern Bootloader *g_pBootloader; //!< Global pointer for bootloader.
