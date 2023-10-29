/*
Copyright (c) 2013, cen (imbacen@gmail.com)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met: 

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution. 
   
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef WINUTILS_H
#define WINUTILS_H

#pragma warning(disable: 4995)

#ifndef QSTRING_H
    #include <QString>
#endif
#ifndef WINDOWS_H
    #include <windows.h>
#endif
#ifndef _SHLOBJ_H_
    #include "Shlobj.h"
#endif
#ifndef __ATLBASE_H__
    #include <atlbase.h>
#endif
#ifndef __ATLSTR_H__
    #include <atlstr.h>
#endif
#ifndef _STRSAFE_H_INCLUDED_
    #include <strsafe.h>
#endif
#ifndef UTIL_H
    #include "util.h"
#endif

namespace Winutils
{
    inline bool IsWinXP32() {
        DWORD version = GetVersion();
        DWORD major = (DWORD) (LOBYTE(LOWORD(version)));
        DWORD minor = (DWORD) (HIBYTE(LOWORD(version)));
        return ((major == 5) && (minor == 1));
    }

    inline QString getProgramFiles()
    {
        TCHAR szPath[MAX_PATH];
        if (Winutils::IsWinXP32()) {
            if(SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PROGRAM_FILES, NULL, SHGFP_TYPE_DEFAULT, szPath))) {
                return QString::fromWCharArray(szPath);
            }
            else {
                return "";
            }
        }
        else {
            if(SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PROGRAM_FILESX86, NULL, SHGFP_TYPE_DEFAULT, szPath))) {
                return QString::fromWCharArray(szPath);
            }
            else {
                return "";
            }
        }
    }

    inline QString getDesktop()
    {
        TCHAR szPath[MAX_PATH];
        if(SUCCEEDED(SHGetFolderPath(NULL, CSIDL_DESKTOP, NULL, 0, szPath)))
        {
            return QString::fromWCharArray(szPath);
        }
        else
        {
            return "";
        }
    }

    inline QString getAppData()
    {
        TCHAR szPath[MAX_PATH];
        if(SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, szPath)))
        {
            return QString::fromWCharArray(szPath).replace('\\', '/');
        }
        else
        {
            return "";
        }
    }

    inline QString getAppDataLocal()
    {
        TCHAR szPath[MAX_PATH];
        if(SUCCEEDED(SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, szPath)))
        {
            return QString::fromWCharArray(szPath);
        }
        else
        {
            return "";
        }
    }

    inline QString getSystem32()
        {
            TCHAR szPath[MAX_PATH];
            if(SUCCEEDED(SHGetFolderPath(NULL, CSIDL_SYSTEM, NULL, 0, szPath)))
            {
                return QString::fromWCharArray(szPath);
            }
            else
            {
                return "";
            }
        }

    inline QString getFileVersion(QString filename)
    {
        DWORD verHandle=NULL;
        UINT size=0;
        LPBYTE lpBuffer=NULL;
        std::wstring t=filename.toStdWString();
        DWORD verSize=GetFileVersionInfoSize(t.c_str(), &verHandle);

        if (verSize != NULL)
        {
            LPSTR verData = new char[verSize];

            if (GetFileVersionInfo( t.c_str(), verHandle, verSize, verData))
            {
                if (VerQueryValue(verData, _T("\\"), (VOID FAR* FAR*)&lpBuffer,&size))
                {
                    if (size)
                    {
                        VS_FIXEDFILEINFO *verInfo = (VS_FIXEDFILEINFO *)lpBuffer;
                        if (verInfo->dwSignature == 0xfeef04bd)
                        {
                            int major = HIWORD(verInfo->dwFileVersionMS);
                            int minor = LOWORD(verInfo->dwFileVersionMS);
                            int revision = HIWORD(verInfo->dwFileVersionLS);
                            int build = LOWORD(verInfo->dwFileVersionLS);
                            TCHAR buffer[255];
                            wsprintf(buffer, _T("%d.%d.%d.%d"), major, minor, revision, build);
                            delete[] verData;
                            return QString::fromWCharArray(buffer);
                        }
                        else {
                            return "ERROR 5: "+Util::getLastErrorMsg()+" -- "+filename;
                        }
                    }
                    else {
                        return "ERROR 4: "+Util::getLastErrorMsg()+" -- "+filename;
                    }
                }
                else {
                    return "ERROR 3: "+Util::getLastErrorMsg()+" -- "+filename;
                }
            }
            else {
                delete[] verData;
                return "ERROR 2: "+Util::getLastErrorMsg()+" -- "+filename;
            }
        }
        else {
            return "ERROR 1: "+Util::getLastErrorMsg()+" -- "+filename;
        }
    }

    inline void GenerateKey( int vk )
    {
        INPUT ip;
        ip.type = INPUT_KEYBOARD;
        ip.ki.wScan = 0;
        ip.ki.time = 0;
        ip.ki.dwExtraInfo = 0;
        //press
        ip.ki.wVk = vk;
        ip.ki.dwFlags = 0; // 0 for key press
        SendInput(1, &ip, sizeof(INPUT));

        //release
        ip.ki.wVk = vk;
        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &ip, sizeof(INPUT));
    }

    inline void GenerateKeyCombo( int vk1 , int vk2)
    {
        INPUT ip;
        ip.type = INPUT_KEYBOARD;
        ip.ki.wScan = 0;
        ip.ki.time = 0;
        ip.ki.dwExtraInfo = 0;

        // Press the vk1 key
        ip.ki.wVk = vk1;
        ip.ki.dwFlags = 0; // 0 for key press
        SendInput(1, &ip, sizeof(INPUT));

        // Press the vk2 key
        ip.ki.wVk = vk2;
        ip.ki.dwFlags = 0; // 0 for key press
        SendInput(1, &ip, sizeof(INPUT));

        // Release the vk2 key
        ip.ki.wVk = vk2;
        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &ip, sizeof(INPUT));

        // Release the vk1 key
        ip.ki.wVk = vk1;
        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &ip, sizeof(INPUT));
    }

    inline QString getLastErrorMsg() {
        LPWSTR bufPtr = NULL;
        DWORD err = GetLastError();
        FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                       FORMAT_MESSAGE_FROM_SYSTEM |
                       FORMAT_MESSAGE_IGNORE_INSERTS,
                       NULL, err, 0, (LPWSTR)&bufPtr, 0, NULL);
        const QString result =
            (bufPtr) ? QString::fromUtf16((const ushort*)bufPtr).trimmed() :
                       QString("Unknown Error %1").arg(err);
        LocalFree(bufPtr);
        return result;
    }
}

#endif // WINUTILS_H
