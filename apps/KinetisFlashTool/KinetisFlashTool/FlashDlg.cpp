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

#include "stdafx.h"
#include "KinetisFlashTool.h"
#include "FlashDlg.h"
#include "afxdialogex.h"
#include "Bootloader.h"
#include "utility.h"
// FlashDlg dialog

IMPLEMENT_DYNAMIC(FlashDlg, CDialogEx)

#define ERASE_REGION (_T("Erase Region"))
#define ERASE_ALL (_T("Erase All"))
#define ERASE_ALL_UNSECURE (_T("Erase All and Unsecure"))

#define INTERNAL_FLASH (_T("Internal Flash"))
#define QUADSPI_MEMORY (_T("QuadSPI 0 Memory"))

extern void PrintLog(const wchar_t *format, ...);

// See FlashDlg.h for documentation of this method.
FlashDlg::FlashDlg(CWnd *pParent /*=NULL*/)
    : CDialogEx(IDD_DIALOG_FLASH, pParent)
{
}

// See FlashDlg.h for documentation of this method.
FlashDlg::~FlashDlg()
{
}

// See FlashDlg.h for documentation of this method.
void FlashDlg::DoDataExchange(CDataExchange *pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_ERASE_OPT, m_comboEraseOpt);
    DDX_Control(pDX, IDC_COMBO_ERASE_MEMORYID, m_comboMemoryID);
}

BEGIN_MESSAGE_MAP(FlashDlg, CDialogEx)
ON_CBN_SELCHANGE(IDC_COMBO_ERASE_OPT, &FlashDlg::OnSelchangeComboEraseOpt)
ON_BN_CLICKED(IDC_BUTTON_ERASE, &FlashDlg::OnBnClickedButtonErase)
ON_BN_CLICKED(IDC_BUTTON_IFR, &FlashDlg::OnBnClickedButtonIfr)
END_MESSAGE_MAP()

// See ConfigDlg.h for documentation of this method.
void FlashDlg::OnOK()
{
    // CDialogEx::OnOK();
}

// See ConfigDlg.h for documentation of this method.
void FlashDlg::OnCancel()
{
    // CDialogEx::OnCancel();
}

// See FlashDlg.h for documentation of this method.
BOOL FlashDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  Add extra initialization here
    // Init the combo boxes
    m_comboEraseOpt.AddString(ERASE_REGION);
    m_comboEraseOpt.AddString(ERASE_ALL);
    m_comboEraseOpt.AddString(ERASE_ALL_UNSECURE);
    m_comboEraseOpt.SetCurSel(0);
    GetDlgItem(IDC_STATIC_ERASE_ID)->EnableWindow(false);
    GetDlgItem(IDC_COMBO_ERASE_MEMORYID)->EnableWindow(false);

    m_comboMemoryID.AddString(INTERNAL_FLASH);
    m_comboMemoryID.AddString(QUADSPI_MEMORY);
    m_comboMemoryID.SetCurSel(0);

    return TRUE; // return TRUE unless you set the focus to a control
}

// See FlashDlg.h for documentation of this method.
void FlashDlg::OnSelchangeComboEraseOpt()
{
    int eraseOpt = m_comboEraseOpt.GetCurSel();

    // Memory ID combox only is enabled when erase-all command is selected.
    GetDlgItem(IDC_STATIC_ERASE_ID)->EnableWindow(eraseOpt == 1);
    GetDlgItem(IDC_COMBO_ERASE_MEMORYID)->EnableWindow(eraseOpt == 1);

    // address and length only is enabled when erase-region command is selected.
    GetDlgItem(IDC_STATIC_ERASE_ADDR)->EnableWindow(!eraseOpt);
    GetDlgItem(IDC_EDIT_ERASE_ADDRESS)->EnableWindow(!eraseOpt);
    GetDlgItem(IDC_STATIC_ERASE_LENGTH)->EnableWindow(!eraseOpt);
    GetDlgItem(IDC_EDIT_ERASE_LENGTH)->EnableWindow(!eraseOpt);
}

// See FlashDlg.h for documentation of this method.
void FlashDlg::OnBnClickedButtonErase()
{
    if (!g_pBootloader->m_isConneted)
    {
        PrintLog(_T("No device is connected!\r\nPlease press Connect button to connect the device first.\r\n"));
        return;
    }

    Bootloader::EraseOption option;
    ZeroMemory(&option, sizeof(Bootloader::EraseOption));

    int eraseOpt = m_comboEraseOpt.GetCurSel();

    if (eraseOpt == 0) // erase region
    {
        option.option = Bootloader::EraseOption::ERASE_OPERATION::erase_region;

        CString startAddr;
        GetDlgItem(IDC_EDIT_ERASE_ADDRESS)->GetWindowTextW(startAddr);
        if (!cstringtoui(startAddr, option.startAddress))
        {
            PrintLog(_T("Error: Invalid Start Address.(%s)"), startAddr);
            return;
        }
        CString length;
        GetDlgItem(IDC_EDIT_ERASE_LENGTH)->GetWindowTextW(length);
        if (!cstringtoui(length, option.length))
        {
            PrintLog(_T("Error: Invalid Length.(%s)"), length);
            return;
        }
    }
    else if (eraseOpt == 1) // flash-erase-all
    {
        int memoryId = m_comboMemoryID.GetCurSel();
        if ((memoryId == 1) && (!(g_pBootloader->m_targetInfo.supportedCmd &
                                  blfwkdll::Updater::COMMAND_MASK::kCommandMask_ConfigureQuadSpi)))
        {
            PrintLog(_T("Current Device doesn't support QuadSPI.\r\n"));
            return;
        }

        option.option = Bootloader::EraseOption::ERASE_OPERATION::erase_all;
        option.memoryID = static_cast<uint32_t>(memoryId);
    }
    else if (eraseOpt == 2) // flash-erase-all-unsecure
    {
        if (!(g_pBootloader->m_targetInfo.supportedCmd &
              blfwkdll::Updater::COMMAND_MASK::kCommandMask_FlashEraseAllUnsecure))
        {
            PrintLog(_T("Current Device doesn't support FlashEraseAllUnsecure.\r\n"));
            return;
        }
        option.option = Bootloader::EraseOption::ERASE_OPERATION::erase_all_and_unsecure;
    }
    g_pBootloader->Erase(&option);
}

// See FlashDlg.h for documentation of this method.
void FlashDlg::OnBnClickedButtonIfr()
{
    if (!g_pBootloader->m_isConneted)
    {
        PrintLog(_T("No device is connected!\r\nPlease press Connect button to connect the device first.\r\n"));
        return;
    }

    if (!(g_pBootloader->m_targetInfo.supportedCmd & blfwkdll::Updater::COMMAND_MASK::kCommandMask_FlashProgramOnce))
    {
        PrintLog(_T("Current Device doesn't support FlashProgramOnce.\r\n"));
        return;
    }

    Bootloader::ProgramOnceOption option;

    CString strW;
    GetDlgItem(IDC_EDIT_IFR_INDEX)->GetWindowTextW(strW);
    if (!cstringtoui(strW, option.index))
    {
        PrintLog(_T("Error: Invalid index.(%s)"), strW);
        return;
    }

    GetDlgItem(IDC_EDIT_IFR_BYTECOUNT)->GetWindowTextW(strW);
    if (!cstringtoui(strW, option.byteCount))
    {
        PrintLog(_T("Error: Invalid byteCount.(%s)"), strW);
        return;
    }

    // Convert WCHAR to CHAR
    GetDlgItem(IDC_EDIT_IFR_DATA)->GetWindowTextW(strW);
    CStringA strA(strW.GetBuffer());
    strW.ReleaseBuffer();
    option.data = strA.GetBuffer();
    strA.ReleaseBuffer();

    g_pBootloader->ProgramOnce(&option);
}
