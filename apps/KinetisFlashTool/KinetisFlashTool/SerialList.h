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
#include <vector>
#include <cstring>

/*!
* \brief SerialDevice class represent a COM port hardware on host
*/
class SerialDevice
{
public:
    //! \brief Generated standard constructor.
    SerialDevice()
        : m_port(_T("")){};

    //! \brief Generated standard constructor with a parameter.
    SerialDevice(LPCTSTR port)
        : m_port(port){};

    //! \brief Generated standard destructor.
    virtual ~SerialDevice(){};

    //! \brief Get the string containing COM port.(COMxx)
    virtual CString GetString() { return (m_port); };
    //! \brief Get the port number only.
    virtual uint32_t GetNum() { return _ttoi(m_port.Mid(3)); };
private:
    CString m_port; //!< A string variable contains COM port string.
};

/*!
* \brief SerialList class contains all serial devices on host
*/
class SerialList
{
public:
    //! \brief Generated standard constructor.
    SerialList(){};

    //! \brief Generated standard destructor.
    virtual ~SerialList(){};

    //! \brief Get SerialDevice variable at specified index.
    SerialDevice GetDevice(int index) { return m_serialDevices.at(index); };
    //! \brief Get the number of devices in the list.
    size_t GetDeviceCount() { return m_serialDevices.size(); };
    //! \brief Find whether the specified device is in the list.
    int FindSerialDevice(SerialDevice device)
    {
        std::vector<SerialDevice>::iterator it;
        for (it = m_serialDevices.begin(); it != m_serialDevices.end(); it++)
        {
            // Check next index.
            if (device.GetNum() > it->GetNum())
            {
                continue;
            }
            // The same COM device in the list, return the index
            else if (device.GetNum() == it->GetNum())
            {
                return it - m_serialDevices.begin();
            }
            // No matched, return negative.
            else
            {
                return -1;
            }
        }
        return -1;
    }

    //! \brief Scan all COM port hardware on the host.
    void ScanSerialDevices();

    //! \brief Sort all devices in the list as ascending order
    void SortSerialDevices();

private:
    std::vector<SerialDevice> m_serialDevices; //!< Serial Device list.
};

extern SerialList *g_pAllComDevices; //!< Global point to SerialList class.
