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
#include <QDir>
#ifndef QTHREAD_H
    #include "QThread"
#endif
#ifndef QBYTEARRAY_H
    #include "QByteArray"
#endif
#include "winutils.h"

GProxy::GProxy(QString gpDir, QString gpExe, QString gpMode, QString gpServer, QString w3exe, QString w3p)
{
    abort=false;
    workdir=gpDir;
    exedir=gpExe;
    mode=gpMode;
    server=gpServer;
    w3Exename=w3exe;
    w3Path=w3p;
}

GProxy::~GProxy() {
    //emit sendLine("Destructing gproxy object");
}

void GProxy::readStdout() {

    QStringList args;
    // @todo add more clean and flexible way to provide arguments
    args << exedir;
    args << "--w3exe=\"" + QDir::toNativeSeparators(w3Path + "/" + w3Exename) + "\"";
    args << "--mode=" + mode;
    args << "--server=" + server;
    process.setWorkingDirectory(workdir);
    process.start(args.join(" "));

    if (!process.waitForStarted()) {
        emit sendLine("Could not start GProxy: "+process.errorString());
        emit gproxyExiting();
        return;
    }
    if (!process.isOpen()) emit sendLine("Console stream is not open");
    if (!process.isReadable()) emit sendLine("Console stream is not readable");

    while(!abort) {
        process.waitForReadyRead(100);

        while (process.canReadLine()) {
            QString line(process.readLine());
            line=line.simplified(); //mostly for removing newline

            QStringList tokens = parseTokens(line);

            emit sendLine(line);
            //if (tokens.count() >= 4) emit sendLine(tokens[1]+"---"+tokens[2]+"---"+tokens[3]);
            //general
            if (tokens.size() >= 4 && tokens[1] == "SYSTEM" && tokens[2] == "LOG_INFO" && tokens[3] == "GPROXY READY") {
                emit gproxyReady(w3Exename);
            }
            else if (tokens.size() >= 4 && tokens[1] == "SYSTEM" && tokens[2] == "LOG_INFO" && tokens[3] == "GPROXY EXITING") {
                emit sendLine("Received the EXIT signal");
                abort=true;
            }
            else if (tokens.size() >= 3 && tokens[2]=="ERROR") {
                abort=true;
            }

            if (process.state() != QProcess::Running) {
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
    for (unsigned int i = 0; i<tokens.size(); i++) {
        tokens[i] = tokens[i].remove("[");
        tokens[i] = tokens[i].simplified();
    }
    return tokens;
}
