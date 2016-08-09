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
#include "../../common/blfwkdll/blfwkdll.h"

// BootloaderConfigDlg dialog
/*!
* \brief BootloaderConfigDlg class is the UI Dialog class for the
*  bootloader configuration page
*/
class BootloaderConfigDlg : public CDialogEx
{
    DECLARE_DYNAMIC(BootloaderConfigDlg)

public:
    //! \brief Generated standard constructor.
    BootloaderConfigDlg(CWnd *pParent = NULL); // standard constructor

    //! \brief Custom constructor
    //!
    //! \param  config      A pointer to BCA data memory.
    //!                     (Must be specified)
    //!
    //! \param  file        A file pointer to the binary image, used for CRC calculation.
    //!                     (Must be specified.)
    //!
    //! \param  pParent     the father dialog pointer.
    BootloaderConfigDlg(blfwkdll::BootloaderConfigureAreaData *config, CFile *file, CWnd *pParent = NULL)
        : CDialogEx(IDD_DIALOG_BOOTLOADERCONFIG, pParent)
    {
        m_config = config;
        m_cFile = file;
    };

    //! \brief Generated standard destructor.
    virtual ~BootloaderConfigDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
    enum
    {
        IDD = IDD_DIALOG_BOOTLOADERCONFIG
    };
#endif
    //! \brief Generated message map functions.
protected:
    virtual void DoDataExchange(CDataExchange *pDX); // DDX/DDV support

    DECLARE_MESSAGE_MAP()
    virtual void OnOK();

public:
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedCheckCrc();
    afx_msg void OnBnClickedCheckI2cslaveAddress();
    afx_msg void OnBnClickedCheckTimeout();
    afx_msg void OnBnClickedCheckVid();
    afx_msg void OnBnClickedCheckPid();
    afx_msg void OnBnClickedCheckUsbstringPointer();
    afx_msg void OnBnClickedCheckDisableHighspeed();
    afx_msg void OnBnClickedCheckMmcauPointer();
    afx_msg void OnBnClickedCheckOtfadPointer();
    afx_msg void OnBnClickedCheckQspiPointer();
    afx_msg void OnBnClickedCheckCantxid();
    afx_msg void OnBnClickedCheckCanrxid();
    afx_msg void OnBnClickedCheckCanspeed();
    afx_msg void OnBnClickedRadioSpeedindex();
    afx_msg void OnBnClickedReload();
    afx_msg void OnBnClickedButtonConfigOk();
    afx_msg void OnBnClickedButtonConfigCancel();
    afx_msg void OnBnClickedButtonConfigGenerate();

public:
    //! \brief  Load BCA data to UI page.
    void LoadBootloaderConfigureArea();

    //! \brief  Save UI config data to BCA.
    //!
    //! \return OnOK for success, OnCancel for failure.
    int SaveBootloaderConfigureArea();

protected:
    blfwkdll::BootloaderConfigureAreaData *m_config; //!< A pointer to BCA data.
    CFile *m_cFile;                                  //!< A pointer to the binary file, used for crc calculation.
};
