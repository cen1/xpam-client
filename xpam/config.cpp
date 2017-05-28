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


#include "config.h"
#include "registry.h"
#include "winutils.h"
#include <QStandardPaths>

Config::Config()
{
    VERSION = "0.8.0.0";
    W3VERSION = "1.28.2.7395";
    BETAPIN = "1377";

    EUROPATH = Registry::getEuroPath();
    SOUNDPATH= EUROPATH+"\\sounds";
    W3PATH   = Registry::getW3dir();
    DOCPATH  = QStandardPaths::locate(QStandardPaths::DocumentsLocation, QString(), QStandardPaths::LocateDirectory)+"Warcraft III";
    DOCMAPPATH  = QStandardPaths::locate(QStandardPaths::DocumentsLocation, QString(), QStandardPaths::LocateDirectory)+"Warcraft III/Maps";
    MAPPATH  = QStandardPaths::locate(QStandardPaths::DocumentsLocation, QString(), QStandardPaths::LocateDirectory)+"Warcraft III/Maps/Download";
    PATCH    = Registry::getPatchVersion();
    APPDATA  = Winutils::getAppData()+"\\Eurobattle.net";
    SYSTEM   = Winutils::getSystem32();

    json1 = "http://xpam.pl/update/update.json";
    json2 = "http://tools.eurobattle.net/update/update.json";
    json3 = "http://leaguebots.com/cen/update/update.json";
}

bool Config::SetOption(QString file, QString option, QString value) {
    QFile conf(file);
    if (!conf.open(QFile::ReadOnly)) return false;

    QStringList lines;
    while(!conf.atEnd())
        lines.append(conf.readLine());

    bool optionWasUpdated=false;

    conf.close();
    for (auto i = lines.begin(); i!=lines.end(); i++) {
        if ((*i).startsWith("#")) continue;
        QStringList l = (*i).split("=");
        if (l[0].simplified()==option) {
            l[1]=" "+value+"\r\n";
            (*i)=l[0]+"="+l[1];
            optionWasUpdated=true;
        }
    }
    QFile conf2(file);
    if (!conf2.open(QFile::WriteOnly)) {
        return false;
    }

    if (!optionWasUpdated) {
        lines.append(option+"="+value);
    }

    for (auto i = lines.begin(); i!=lines.end(); i++) {
        QByteArray ba = (*i).toLocal8Bit();
        conf2.write(ba.data());
    }
    conf2.close();
    return true;
}
