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

#include "w3.h"
#include <QProcess>
#include <QThread>
#include "winutils.h"
#include "logger.h"
#include "registry.h"

const QString W3::W3_126="126";
const QString W3::W3_LATEST="LATEST";

W3::W3(QString w, QString e, QStringList a, Config * c) {
    workdir=w;
    exedir=e;
    args=a;
    config = c;
}

W3::~W3() {

}

void W3::startW3() {
    QProcess p;
    p.setWorkingDirectory(workdir);
    p.start(exedir, args);
    if (!p.waitForStarted()) {
        emit w3Exited();
        return;
    }

    while(true) {
        QThread::sleep(1);
        if (p.state() != QProcess::Running) {
            break;
        }
    }
    emit w3Exited();
    return;
}

void W3::sanityCheck(Config * config) {

    //Add old registries back if they do not exist
    Registry reg;
    QString installPath = reg.getInstallPath();
    if (installPath=="ERROR" || installPath=="") {
        reg.setInstallPath(config->W3PATH_LATEST);
    }
    QString installPathX = reg.getInstallPathX();
    if (installPathX=="ERROR" || installPathX=="") {
        reg.setInstallPathX(config->W3PATH_LATEST);
    }
}
