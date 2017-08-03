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
#include "QDir"

Downloader::Downloader(QUrl u, Config* c) {
    url=u;
    reply=nullptr;
    erroremitted=false;
    file = nullptr;
    config = c;
}

Downloader::~Downloader(){
    delete reply;
    if (file!=nullptr)
        delete file;
}

// Slot to be triggered from the updater thread
void Downloader::startDl() {
    if (reply==nullptr) {

        //Prep appdata file
        if (!QDir(config->APPDATA).exists()) {
            QDir().mkpath(config->APPDATA);
        }
        file = new QFile(config->APPDATA+"\\patch.zip");
        file->open(QFile::WriteOnly | QFile::Truncate);

        //nam.setNetworkAccessible(QNetworkAccessManager::Accessible);
        reply = nam.get(QNetworkRequest(url));

        emit sendInfo("Starting download");
        emit sendInfo(""); //empty line which will be removed for the progress text

        QObject::connect(reply, SIGNAL(finished()), this, SLOT(finishedSlot()));
        QObject::connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorSlot(QNetworkReply::NetworkError)));
        QObject::connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(progressSlot(qint64, qint64)));
        QObject::connect(reply, SIGNAL(readyRead()), this, SLOT(writeToFileSlot()));
    }
    else {
        emit sendInfo("You can't start the same download several times!!!");
    }
}

//intermediate slot for sending progress info to updater thread
void Downloader::progressSlot(qint64 bytesReceived, qint64 bytesTotal){
    emit progress(bytesReceived, bytesTotal);
}

void Downloader::writeToFileSlot(){
    tmpBuffer.append(reply->read(1000000));
    if (tmpBuffer.size()>1000000 && !reply->isFinished()) {
        if (file->isOpen() && file->isWritable()){
            file->write(tmpBuffer);
            tmpBuffer.clear();
        }
    }
}

//reply finished
void Downloader::finishedSlot(){

    if (reply->error() == QNetworkReply::NoError){
        QVariant possibleRedirectUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

        if (!possibleRedirectUrl.toUrl().isEmpty()) {
            //there is redirect
            //make new request
            //emit sendInfo("Redirected to "+possibleRedirectUrl.toUrl().toString());

            reply->deleteLater();
            reply = nam.get(QNetworkRequest(possibleRedirectUrl.toUrl())); //when this reply is finished this slot will get re-triggered

            emit sendInfo("Redirecting...");
            emit sendInfo("");
            tmpBuffer.clear(); //CLEAR THE GODDAMN BUFFER!!!!
            file->resize(0);

            //reconnect since deleting reply disconnects all slots
            QObject::connect(reply, SIGNAL(finished()), this, SLOT(finishedSlot()));
            QObject::connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorSlot(QNetworkReply::NetworkError)));
            QObject::connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(progressSlot(qint64, qint64)));
        }
        else {
            //all ok
            emit sendInfo("Downloader exiting with no errors");

            //Read whatever is left
            tmpBuffer.append(reply->readAll());
            file->write(tmpBuffer);
            file->close();

            emit sendInfo("Handing off work to updater");
            emit finisheddl();
        }
    }
    else {
        if (!erroremitted) {
            emit sendInfo("Network err code: "+reply->errorString());
            erroremitted=true;
            emit finisheddl();
        }
    }
}

void Downloader::errorSlot(QNetworkReply::NetworkError code) {
    if (!erroremitted) {
        emit sendInfo("Network error: "+QString::number(code));
        erroremitted=true;
        emit finisheddl();
    }
}
