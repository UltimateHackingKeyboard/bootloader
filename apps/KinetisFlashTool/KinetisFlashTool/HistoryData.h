/*
* Copyright (c) 2013-16, Freescale Semiconductor, Inc.
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
#include <vector>
#include <cstring>

/*!
* \brief HistoryData class stores the operation history.
* Save users operation steps.
*/
class HistoryData
{
public:
    //! \brief Generated standard constructor.
    HistoryData()
        : m_currentDevice(-1)
        , m_currentBaudRate(-1)
        , m_imageAddress(0){};

    //! \brief Generated standard destructor.
    virtual ~HistoryData(){};

    //! @brief File types.
    enum FileType
    {
        kBinary,     //!< Binary file.(.bin)
        kSBFile,     //!< SB file.(.sb)
        kIntelHex,   //!< Intel hex file.(.hex)
        kSRecord,    //!< Srecord file.(.srec, s19)
        kUnsupported //!< Unsupported file type.
    };

    //! \brief Get current selected device index at device list.
    //!
    //! \return negative: no device is selected.
    //!         non-negative: current selected device index at device list.
    int32_t GetCurrentDevice() { return m_currentDevice; };
    //! \brief Change the index of current selected device.
    //!
    //! \param index at device list.
    void SetCurrentDevice(int32_t index) { m_currentDevice = index; };
    //! \brief Get the baud rate at the specified index.
    //!
    //! \param index of the list.
    //!
    //! \return the value of the baud rate.
    int32_t GetBaudRate(size_t index) { return m_baudRate.at(index); };
    //! \brief Get count of the baud rates in the list.
    //!
    //! \return the count.
    size_t GetBaudRateCount() { return m_baudRate.size(); };
    //! \brief Get current selected baud rate index at the list.
    //!
    //! \return negative: no baud rate is selected.
    //!         non-negative: current selected baud rate index at the list.
    int32_t GetCurrentBaudRate() { return m_currentBaudRate; };
    //! \brief Change the index of current selected baud rate.
    //!
    //! \param index at baud rate list.
    void SetCurrentBaudRate(int32_t index) { m_currentBaudRate = index; };
    //! \brief Append a new baud rate at the end of the list.
    //!
    //! \param the value of baud rate.
    void AddBaudRate(int32_t baudrate)
    {
        // Find whether the new baudrate already exists in the list
        for (std::vector<int32_t>::iterator it = m_baudRate.begin(); it != m_baudRate.end(); it++)
        {
            // If find the matched baud rate, return.
            if (baudrate == *it)
            {
                return;
            }
        }
        // If no matched, add it to end of list.
        m_baudRate.push_back(baudrate);
    };

    //! \brief Insert a new baud rate, and change the current selected baud rate.
    //!        If the baud rate already exists in the list, only change the selected baud rate index
    //!
    //! \param the value of baud rate.
    void InsertBaudRate(int32_t baudrate)
    {
        // If find index of the baud rate to insert.
        for (std::vector<int32_t>::iterator it = m_baudRate.begin(); it != m_baudRate.end(); it++)
        {
            // Check next index.
            if (baudrate > *it)
            {
                continue;
            }
            // The same baudrate in the list, just set it as current selected baud rate.
            else if (baudrate == *it)
            {
                SetCurrentBaudRate(it - m_baudRate.begin());
                return;
            }
            // Find the correct index, insert it and set it as current selected baud rate.
            else
            {
                m_baudRate.insert(it, baudrate);
                SetCurrentBaudRate(it - m_baudRate.begin());
                return;
            }
        }
        // If baudrate is bigger than any one in the list, add it to list back.
        m_baudRate.push_back(baudrate);
        SetCurrentBaudRate(GetBaudRateCount());
        return;
    };

    //! \brief Get the VID at the specified index.
    //!
    //! \param index of the list.
    //!
    //! \return the value of the PID.
    uint16_t GetVid(size_t index) { return m_vids.at(index); };
    //! \brief Get count of the VID in the list .
    //!
    //! \return the count.
    size_t GetVidCount() { return m_vids.size(); };
    //! \brief Append a new VID at the end of the list.
    //!
    //! \param the value of VID.
    void AddVid(uint16_t vid)
    {
        // Find whether the new vid already exists in the list.
        for (std::vector<uint16_t>::iterator it = m_vids.begin(); it != m_vids.end(); it++)
        {
            // If find the matched vid, return.
            if (vid == *it)
            {
                return;
            }
        }
        // If no matched, add it to end of list.
        m_vids.push_back(vid);
    };

    //! \brief Insert a VID at the head of the list.
    //!        If the VID already exists in the list, only bubble that VID to list head.
    //!
    //! \param the value of VID.
    void InsertVid(uint16_t vid)
    {
        // Find whether the new vid already exists in the list.
        for (std::vector<uint16_t>::iterator it = m_vids.begin(); it != m_vids.end(); it++)
        {
            // If find the matched vid, bubble it to the head of list. Then return.
            if (vid == *it)
            {
                BubbleSelectedVid(it - m_vids.begin());
                return;
            }
        }
        // If no matched, add it to head of list.
        m_vids.insert(m_vids.begin(), vid);
    };

    //! \brief bubble the VID at the specified index to the head of the VID list
    //!
    //! \param the index of VID.
    void BubbleSelectedVid(size_t index)
    {
        uint16_t vid = m_vids.at(index);
        m_vids.erase(m_vids.begin() + index);
        m_vids.insert(m_vids.begin(), vid);
    }

    //! \brief Get the PID at the specified index.
    //!
    //! \param index of the list.
    //!
    //! \return the value of the PID.
    uint16_t GetPid(size_t index) { return m_pids.at(index); };
    //! \brief Get count of the PID in the list .
    //!
    //! \return the count.
    size_t GetPidCount() { return m_pids.size(); };
    //! \brief Append a new PID at the end of the list.
    //!
    //! \param the value of PID.
    void AddPid(uint16_t pid)
    {
        // Find whether the new pid already exists in the list.
        for (std::vector<uint16_t>::iterator it = m_pids.begin(); it != m_pids.end(); it++)
        {
            // If find the matched pid, return.
            if (pid == *it)
            {
                return;
            }
        }
        // If no matched, add it to end of list.
        m_pids.push_back(pid);
    };

    //! \brief Insert a PID at the head of the list.
    //!        If the PID already exists in the list, only bubble it to list head.
    //!
    //! \param the value of PID.
    void InsertPid(uint16_t pid)
    {
        // Find whether the new pid already exists in the list.
        for (std::vector<uint16_t>::iterator it = m_pids.begin(); it != m_pids.end(); it++)
        {
            // If find the matched pid, bubble it to the head of list. Then return.
            if (pid == *it)
            {
                BubbleSelectedPid(it - m_pids.begin());
                return;
            }
        }
        // If no matched, add it to head of list.
        m_pids.insert(m_pids.begin(), pid);
    };

    //! \brief bubble the PID at the specified index to the head of the PID list
    //!
    //! \param the index of PID.
    void BubbleSelectedPid(size_t index)
    {
        uint16_t pid = m_pids.at(index);
        m_pids.erase(m_pids.begin() + index);
        m_pids.insert(m_pids.begin(), pid);
    }

    //! \brief Get the file full path at the specified index of the file list.
    //!
    //! \param index of the list.
    //!
    //! \return full path string.
    CString GetFilePath(int index) { return m_imageFile.at(index); };
    //! \brief Get the file name at the specified index of the file list.
    //!
    //! \param index of the list.
    //!
    //! \return file name string.
    CString GetFileName(int index)
    {
        CString fullPath = m_imageFile.at(index);
        int pos = fullPath.ReverseFind(_T('\\'));
        return fullPath.Right(fullPath.GetLength() - pos - 1);
    };

    //! \brief Get the file type of the file at the specified index of the file list.
    //!
    //! \param index of the list.
    //!
    //! \return file type.
    FileType GetFileType(int index)
    {
        CString extension = PathFindExtension(m_imageFile.at(index));
        if (extension.CompareNoCase(_T(".bin")) == 0)
        {
            return kBinary;
        }
        else if (extension.CompareNoCase(_T(".sb")) == 0)
        {
            return kSBFile;
        }
        else if (extension.CompareNoCase(_T(".hex")) == 0)
        {
            return kIntelHex;
        }
        else if ((extension.CompareNoCase(_T(".srec")) == 0) || (extension.CompareNoCase(_T(".s19")) == 0))
        {
            return kSRecord;
        }
        else
        {
            return kUnsupported;
        }
    }
    //! \brief Get count of the files in the list .
    //!
    //! \return the count.
    size_t GetFileCount() { return m_imageFile.size(); };
    //! \brief Append a new file at the end of the list.
    //!
    //! \param the full path of the file.
    void AddFile(CString fullPath)
    {
        // Find whether this file already exists in the file list.
        for (std::vector<CString>::iterator it = m_imageFile.begin(); it != m_imageFile.end(); it++)
        {
            // If find the matched file, return.
            if (fullPath.Compare(*it) == 0)
            {
                return;
            }
        }
        // If no matched file, add it to end of file list.
        m_imageFile.push_back(fullPath);
    };

    //! \brief Insert a file at the head of the list.
    //!        If the file already exists in the list, only bubble that file to list head.
    //!
    //! \param the full path of the file.
    void InsertFile(CString fullPath)
    {
        // Find whether this file already exists in the file list.
        for (std::vector<CString>::iterator it = m_imageFile.begin(); it != m_imageFile.end(); it++)
        {
            // If find the matched file, bubble it to the head of file list. Then return.
            if (fullPath.Compare(*it) == 0)
            {
                BubbleSelectedFile(it - m_imageFile.begin());
                return;
            }
        }
        // If no matched file, add it to head of file list.
        m_imageFile.insert(m_imageFile.begin(), fullPath);
    };

    //! \brief bubble the file at the specified index to the head of the file list
    //!
    //! \param the index of file.
    void BubbleSelectedFile(int32_t index)
    {
        CString file = m_imageFile.at(index);
        m_imageFile.erase(m_imageFile.begin() + index);
        m_imageFile.insert(m_imageFile.begin(), file);
    }

    //! \brief Get image address previous used.
    //!
    //! \return value of the image address.
    uint32_t GetImageAddress() { return m_imageAddress; };
    //! \brief Change image address.
    //!
    //! \param value of the image address.
    void SetImageAddress(uint32_t imageAddress) { m_imageAddress = imageAddress; };
    //! \brief Get the string of backdoor key previous used.
    //!
    //! \return the string of backdoor key.
    CString GetBackdoorKey() { return m_backdoorKey; }
    //! \brief Change the string of backdoor key.
    //!
    //! \param the string of backdoor key.;
    void SetBackdoorKey(CString backdoorKey) { m_backdoorKey = backdoorKey; };
private:
    int32_t m_currentDevice;          //!< current selected device at device list.
    std::vector<int32_t> m_baudRate;  //!< baud rate list.
    int32_t m_currentBaudRate;        //!< current selected baud rate.
    std::vector<uint16_t> m_vids;     //!< vid list.
    std::vector<uint16_t> m_pids;     //!< pid list.
    std::vector<CString> m_imageFile; //!< image file list.
    uint32_t m_imageAddress;          //!< image address.
    CString m_backdoorKey;            //!< string of backdoor key.
};

extern HistoryData *g_pHistoryData; //!< Global point to HistoryData class.