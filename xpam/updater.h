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

#ifndef UPDATER_H
#define UPDATER_H

#include <QObject>
#include <QMessageBox>
#include "QThread"
#include "QJsonObject"
#include "QStringList"
#include "QByteArray"
#include "QTime"

#include "config.h"
#include "downloader.h"

class Updater : public QObject
{
    Q_OBJECT
public:
    Updater(Config * c, int t, QString w="");
    ~Updater();

    static QString Updater::moveToDocuments(Config *config);
    static void Updater::replaceCDKeys(Config *config);
    static void Updater::renamePatchMpqForLatestW3(Config *config);
    static QByteArray simpleDl(QUrl url);
    static QByteArray getUpdateJson(Config * config);
    
private:
    Config *        config;
    int             type;
    QString         jsonKey;
    QByteArray      archive;
    QThread *       dlthread;
    Downloader *    downloader;
    QString         zippath;
    int             mirrorno;
    QByteArray      jsonba;
    QJsonObject     real;
    QStringList     mirrors;
    QVector<int>    usedMirrors;
    QTime           progressTime;
    int             latestVersion;
    bool            restartNeeded;
    bool            isW3Update;

    bool extractZip();
    bool instructions();
    bool updateMPQ(QString w3path);

    int setCurrentPlusOneJson();
    int getRandomMirror();

signals:
    void updateFinished(bool restartNeeded, bool ok, bool isUpToDate, bool canceled, int type);
    void sendLine(QString line);
    void modifyLastLine(QString line);
    void startDl();
    void hideSplashScreen();

public slots:
    void startUpdate();
    void receiveProgress(qint64 bytesReceived, qint64 bytesTotal);
    void receiveFinishdl();
    void cancelUpdate();
};

#endif // UPDATER_H
