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

#ifndef REGISTRY_H
#define REGISTRY_H

#ifndef WINDOWS_H
    #include <windows.h>
#endif
#ifndef __ATLBASE_H__
    #include <atlbase.h>
#endif
#ifndef QSTRING_H
    #include <QString>
#endif

class Registry {
public:
    static QString getInstallPath();
    static QString getW3dir();
    static QString getEuroPath();
    static int getPatchVersion();
    static QString getGproxyReady();

    static QString getRegString(CRegKey * reg, QString name);
    static DWORD getRegDWORD(CRegKey reg, QString name);

    static bool setRegString(CRegKey reg, QString name, QString value);
    static bool setRegDWORD(CRegKey reg, QString name, DWORD value);

    static DWORD setGateways();
    static DWORD setGproxyGateways();
    static bool setPatchVersion(int version);

    bool setW3dir(QString w3dir);
    bool setInstallPath(QString w3dir);

    static bool delGM();

    Registry();
};

#endif // REGISTRY_H
