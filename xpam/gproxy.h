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

#ifndef GPROXY_H
#define GPROXY_H

#ifndef QPROCESS_H
    #include "QProcess"
#endif

class GProxy : public QObject
{
    Q_OBJECT
signals:
    void sendLine(QString line);
    void gproxyReady(QString w3Exename);
    void gproxyExiting(bool killedForcefully);
private:
    QStringList parseTokens(QString s);
    bool killedForcefully;
public:
    GProxy(QString gpDir, QString gpExe, QString gpMode, QString gpServer, QString w3exe, QString w3p);
    ~GProxy();

    bool abort;
    QString workdir;
    QString exedir;
    QString w3Exename;
    QString mode;
    QString w3Path;
    QString server;
    QProcess *process;
public slots:
    void readStdout();
    void kill();
};

#endif // GPROXY_H
