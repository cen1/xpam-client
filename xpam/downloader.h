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

#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include "QUrl"
#include "QByteArray"
#include "QNetworkAccessManager"
#include "QNetworkReply"
#include "QFile"
#include "config.h"

class Downloader : public QObject
{
    Q_OBJECT
public:
    Downloader(QUrl u, Config* c);
    ~Downloader();

    QNetworkReply * reply;

private:
    QUrl url;
    QNetworkAccessManager nam;
    bool erroremitted;              //if error() and finished() are both emitted with errors, we only emit one signal to updater thread
    QByteArray tmpBuffer;
    QFile* file;
    Config* config;

signals:
    void progress(qint64 bytesReceived, qint64 bytesTotal);
    void finisheddl();
    void sendInfo(QString info);

public slots:
    void progressSlot(qint64 bytesReceived, qint64 bytesTotal);
    void writeToFileSlot();
    void finishedSlot();
    void errorSlot(QNetworkReply::NetworkError code);
    void startDl();
};

#endif // DOWNLOADER_H
