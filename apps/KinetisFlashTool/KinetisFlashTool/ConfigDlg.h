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

// ConfigDlg Dialog
/*!
* \brief ConfigDlg class is the UI Dialog class for the
*  BCA utilities tab page
*/
class ConfigDlg : public CDialogEx
{
    DECLARE_DYNAMIC(ConfigDlg)

public:
    //! \brief Generated standard constructor.
    ConfigDlg(CWnd *pParent = NULL); // standard constructor

    //! \brief Generated standard destructor.
    virtual ~ConfigDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
    enum
    {
        IDD = IDD_DIALOG_CONFIG
    };
#endif

    //! \brief Generated message map functions.
protected:
    virtual void DoDataExchange(CDataExchange *pDX); // DDX/DDV support

    DECLARE_MESSAGE_MAP()
    virtual void OnOK();
    virtual void OnCancel();

public:
    virtual BOOL OnInitDialog();
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void OnSelchangeComboFile();
    afx_msg void OnKillfocusComboFile();
    afx_msg void OnBnClickedButtonBrowse();
    afx_msg void OnChangeEditBcaData();
    afx_msg void OnBnClickedButtonConfigBca();
    afx_msg void OnBnClickedButtonSaveBca();

public:
    //! \brief  Refresh the image file list.
    void RefreshImageFileList();

    //! \brief  Read BCA data from image file to memory region(m_bcaData).
    BOOL ReadBootloaderConfigureArea();

    //! \brief  Update BCA data between memory region and UI
    //!
    //! \param direction    The update direction between UI and memory.
    //!                     TRUE:   from UI to memory
    //!                     FALSE:  from memory to UI
    void UpdateDataOfBootloaderConfigureArea(BOOL direction);

    //! \brief  Write BCA data to image file.
    void WriteBootloaderConfigureArea();

    //! \brief  Reset BCA data to all 0xFFs.
    void ResetBootloaderConfigureArea();

public:
    CComboBox m_ctrlImageFile; //!< A control variable for the Combox, IDC_COMBO_FILE2.
    CString m_bcaBinaries;     //!< A string variable for the Edit Control, IDC_EDIT_BCA_BINARY.
    char *m_bcaData;           //!< A pointer, pointing to a memory region that contains BCA binaries.
};