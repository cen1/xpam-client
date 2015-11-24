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

#include "gproxy.h"
#ifndef QTHREAD_H
    #include "QThread"
#endif
#ifndef QBYTEARRAY_H
    #include "QByteArray"
#endif
#include "winutils.h"

GProxy::GProxy(QString w, QString e)
{
    abort=false;
    workdir=w;
    exedir=e;
}

GProxy::~GProxy() {
    //emit sendLine("Destructing gproxy object");
}

void GProxy::readStdout() {
    QProcess p;
    p.setWorkingDirectory(workdir);
    p.start(exedir);
    if (!p.waitForStarted()) {
        emit sendLine("Could not start GProxy: "+p.errorString());
        emit gproxyExiting();
        return;
    }
    if (!p.isOpen()) emit sendLine("Console stream is not open");
    if (!p.isReadable()) emit sendLine("Console stream is not readable");

    while(!abort) {
        p.waitForReadyRead(100);

        if (p.canReadLine()) {
            QString line(p.readLine());
            line=line.simplified(); //mostly for removing newline
            QStringList tokens = parseTokens(line);

            emit sendLine(line);
            //if (tokens.count() >= 4) emit sendLine(tokens[1]+"---"+tokens[2]+"---"+tokens[3]);
            //general
            if (tokens[1] == "SYSTEM" && tokens[2] == "LOG_INFO" && tokens[3] == "GPROXY READY") {
                emit gproxyReady();
            }
            else if (tokens[1] == "SYSTEM" && tokens[2] == "LOG_INFO" && tokens[3] == "GPROXY EXITING") {
                emit sendLine("Received the EXIT signal");
                abort=true;
            }
            else if (tokens[2]=="ERROR") {
                abort=true;
            }

            if (p.state() != QProcess::Running) {
                emit sendLine("GProxy process exited");
                abort=true;
            }
        }
    }
    emit gproxyExiting();
}

QStringList GProxy::parseTokens(QString s) {
    //example [24-11-2015 16:38:54][SYSTEM][LOG_INFO] GPROXY READY
    QStringList tokens = s.split("]");
    for (unsigned int i = 0; i<tokens.count(); i++) {
        tokens[i] = tokens[i].remove("[");
        tokens[i] = tokens[i].simplified();
    }
    return tokens;
}
