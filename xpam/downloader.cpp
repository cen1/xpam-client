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

#include "downloader.h"

Downloader::Downloader(QUrl u) {
    url=u;
    reply=NULL;
    nam=NULL;
}

Downloader::~Downloader(){
    delete reply;
    delete nam;
}

// Slot to be triggered from the updater thread
void Downloader::startDl() {
    nam = new QNetworkAccessManager();
    reply = nam->get(QNetworkRequest(url));

    emit sendInfo("Starting download");
    emit sendInfo("");
    QObject::connect(reply, SIGNAL(finished()), this, SLOT(finishedSlot()));
    QObject::connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(progressSlot(qint64, qint64)));
}

//intermediate slot for sending progress info to updater thread
void Downloader::progressSlot(qint64 bytesReceived, qint64 bytesTotal){
    emit progress(bytesReceived, bytesTotal);
}

//reply finished
void Downloader::finishedSlot(){
    emit sendInfo("Network reply finished");

    if (reply->error() == QNetworkReply::NoError){
        QVariant possibleRedirectUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

        if (!possibleRedirectUrl.toUrl().isEmpty()) {
            //there is redirect
            //make new request
            //emit sendInfo("Redirected to "+possibleRedirectUrl.toUrl().toString());
            delete reply;
            reply = nam->get(QNetworkRequest(possibleRedirectUrl.toUrl())); //when this reply is finished this slot will get re-triggered

            emit sendInfo("Starting download");
            emit sendInfo("");
            QObject::connect(reply, SIGNAL(finished()), this, SLOT(finishedSlot()));
            QObject::connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(progressSlot(qint64, qint64)));
        }
        else {
            //all ok
            emit sendInfo("Downloader exiting");
            emit finisheddl(reply->readAll());
        }
    }
    else{
        emit sendInfo("Network error: "+reply->errorString());
        QByteArray ba;
        emit finisheddl(ba);
    }
}
