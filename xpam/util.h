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

#ifndef UTIL_H
#define UTIL_H

#ifndef QUAZIP_STATIC
    #define QUAZIP_STATIC
#endif

#include "QMessageBox"
#include "Windows.h"
#include "Psapi.h"
#include "quazip.h"
#include "quazipfile.h"
#include "config.h"

#pragma comment(lib, "Psapi.lib")

namespace Util {
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

    inline void msgbox(QString q) {
        QMessageBox msgBox;
        msgBox.setText(q);
        msgBox.exec();
    }


    inline bool isRunning(QString pName) {
        unsigned long aProcesses[1024], cbNeeded, cProcesses;
        if(!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
            return false;

        cProcesses = cbNeeded / sizeof(unsigned long);
        for(unsigned int i = 0; i < cProcesses; i++)
        {
            if(aProcesses[i] == 0)
                continue;

            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, 0, aProcesses[i]);
            wchar_t buffer[MAX_PATH];
            GetModuleBaseName(hProcess, 0, buffer, sizeof(buffer)/sizeof(wchar_t));
            CloseHandle(hProcess);

            std::wstring tmp(buffer); //process base name

            if(tmp==pName.toStdWString()) {
                return true;
            }
        }
        return false;
    }

    inline int randInt(int low, int high) {
        return qrand() % ((high + 1) - low) + low;
    }

    inline QString getMiddleParam(QStringList list)
    {
        list.pop_front();
        list.pop_back();
        return list.join(" ");
    }
}

#endif //UTIL_H
