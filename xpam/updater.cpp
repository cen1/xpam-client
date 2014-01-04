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

#ifndef QUAZIP_STATIC
    #define QUAZIP_STATIC
#endif


#include "QThread"
#include "QJsonArray"
#include "QJsonDocument"
#include "QStringList"
#include "QDir"
#include "QFile"
#include "QCryptographicHash"
#include "QTextStream"
#include "QEventLoop"

#include "quazip.h"
#include "util.h"
#include "updater.h"
#include "registry.h"

Updater::Updater(Config * c, bool b) {
    config=c;
    beta=b;
    mirrorno=0;
    zippath=config->APPDATA+"\\patch.zip";
}

void Updater::startUpdate() {
    /*
     * XPAM CLIENT UPDATE PROCEDURE - DOCUMENTATION
     * 1. Access 3 different update.json mirrors. 2 out of 3 must be the same and avalible for the procedure to continue
     * 2. First object is latest stable patch, second object is beta patch. Each patch has current patch version,
     *    4 mirrors to the update zip archive and sha1 hash of the archive. Patches are full, not incremental.
     * 3. Mirrors are Google Drive, SkyDrive, Ubuntu ONE and files.eurobattle.net in that order
     * 4. If JSON patch version is bigger than your current in registry, download the archive.
     * 5. If you fail to download from the first mirror, fallback to the second etc
     * 6. When the archive is downloaded, compare the hash
     * 7. Download and extract the archive to %appdata%/Eurobattle.net
     * 8. Open instructions.txt and execute the commands
     * 9. COMMANDS
     *    MOVE <from> <to EUROPATH | W3PATH | MAPPATH>              //always overwrite
     *    DELETE <filename> <location EUROPATH | W3PATH | MAPPATH>  //deletes a file
     *
     * 10. Cleanup %appdata$ after update
     * 11. Start clientpatcher.exe, exit app. Clientpatcher removes xpam.exe and renames newxpam.exe (if it exists). Then starts xpam.exe
     *
     *
     * UPLOAD INSTRUCTIONS
     * -Google Drive: make sure you mark as public
     * -SkyDrive: ID from public link
     * -Ubuntu ONE: More->Publish
     */
    QByteArray j1=simpleDl(config->json1);
    QByteArray j2=simpleDl(config->json2);
    QByteArray j3=simpleDl(config->json3);

    if ((j1.isEmpty() && j2.isEmpty()) || (j1.isEmpty() && j3.isEmpty()) || (j2.isEmpty() && j3.isEmpty())){
        emit sendLine("Update info is empty. Update server are down or there might be a problem with your internet connection");
        emit updateFinished(false, false);
        return;
    }

    QByteArray jsonba;
    if (j1==j2){
        jsonba=j1;
    }
    else if (j1==j3){
        jsonba=j1;
    }
    else if (j2==j3){
        jsonba=j2;
    }
    else {
        emit sendLine("Update info mismatch");
        emit updateFinished(false, false);
        return;
    }

    //emit sendLine("Json received: "+QString(jsonba));

    QJsonDocument json = QJsonDocument::fromJson(jsonba);
    /*if (json.isEmpty()){
        emit sendLine("Json is empty");
        return;
    }
    if (json.isNull()){
        emit sendLine("Json is null");
        return;
    }
    if (json.isArray()){
        emit sendLine("Received an array instead of an object");
        return;
    }*/
    if (json.isObject()){
        emit sendLine("JSON build OK");
    }
    QJsonObject obj=json.object();

    QJsonObject latest_o = obj.value("latest").toObject();
    QJsonObject beta_o   = obj.value("beta").toObject();

    if (beta) {
        emit sendLine("Requested patch: beta");
        real=beta_o;
    }
    else {
        emit sendLine("Requested patch: stable");
        real=latest_o;
    }

    latestVersion = real.value("version").toInt();
    emit sendLine("Local version: "+QString::number(config->PATCH)+" Latest version: "+QString::number(latestVersion));
    if (latestVersion <= config->PATCH) {
        emit sendLine("Xpam is up to date");
        emit updateFinished(true, true);
        return;
    }
    //tell splash screen to hide, will only work on startup update
    //this means that we have an update so it'd be nice to see the progress
    emit hideSplashScreen();

    mirrors << real.value("mirror1").toString();
    mirrors << real.value("mirror2").toString();
    mirrors << real.value("mirror3").toString();
    mirrors << real.value("mirror4").toString();

    emit sendLine("Downloading from: mirror "+QString::number(mirrorno));
    QUrl url(mirrors[mirrorno]);
    dlthread=new QThread();
    downloader=new Downloader(url);

    QObject::connect(this, SIGNAL(startDl()), downloader, SLOT(startDl()));
    QObject::connect(downloader, SIGNAL(finisheddl(QByteArray)), this, SLOT(receiveFinishdl(QByteArray)));
    QObject::connect(downloader, SIGNAL(progress(qint64,qint64)), this, SLOT(receiveProgress(qint64,qint64)));
    QObject::connect(downloader, SIGNAL(sendInfo(QString)), this, SIGNAL(sendLine(QString)));

    downloader->moveToThread(dlthread);
    dlthread->start();
    emit startDl();

    progressTime = QTime().currentTime();
    progressTime.start();
}

/*
 * Extracts patch.zip
 */
bool Updater::extractZip() {

    QuaZip zip(zippath);
    zip.open(QuaZip::mdUnzip);

    if (zip.isOpen()) {
        for( bool f = zip.goToFirstFile(); f; f = zip.goToNextFile() ) {

            QString filePath = zip.getCurrentFileName();
            QuaZipFile zFile( zip.getZipName(), filePath );

            zFile.open(QIODevice::ReadOnly);
            qint64 size=zFile.size();
            char * buffer = (char *)malloc(size);
            qint64 ret = zFile.read(buffer, size);
            zFile.close();

            emit sendLine("Extracting "+filePath+" ("+QString::number(size)+") read "+QString::number(ret)+"-"+QString::number(sizeof(buffer)));

            if (QFile::exists(config->APPDATA+"\\"+filePath)) QFile::remove(config->APPDATA+"\\"+filePath);

            QFile dstFile(config->APPDATA+"\\"+filePath);

            dstFile.open(QIODevice::WriteOnly);
            if (dstFile.isOpen()){
                dstFile.write(buffer, size);
                dstFile.close();
            }
            else {
                emit sendLine("Could not extract file "+dstFile.errorString());
                return false;
            }
            delete buffer;
        }
    }
    else {
        emit sendLine("Could not open the zip file");
        return false;
    }
    zip.close();

    //cleanup
    QFile::remove(zippath);

    emit sendLine("...");
    emit sendLine("...");
    return true;
}

bool Updater::instructions() {
    //read instructions.txt and execute
    /*
     * MOVE or DELETE
     * Filename
     * EUROPATH, W3PATH or MAPS
    */
    QFile inst(config->APPDATA+"\\instructions.txt");
    if (inst.open(QIODevice::ReadOnly)) {
        QTextStream in(&inst);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList l = line.split(" ");
            QString midParam=Util::getMiddleParam(l);

            //emit sendLine("Instruction: <"+l.first()+"> <"+midParam+"> <"+l.last()+">");

            if (l[0]=="MOVE") {

                QString dstPath;
                if      (l.last()=="EUROPATH") dstPath=config->EUROPATH;
                else if (l.last()=="W3PATH") dstPath=config->W3PATH;
                else if (l.last()=="MAPPATH") dstPath=config->MAPPATH;

                QFile from(config->APPDATA+"\\"+midParam);
                if (QFile::exists(dstPath+"\\"+midParam)) QFile::remove(dstPath+"\\"+midParam);

                emit sendLine("Moving to "+dstPath+"\\"+midParam);
                if (!from.rename(dstPath+"\\"+midParam)) {
                    emit sendLine("Could not move file "+from.fileName()+" to "+dstPath+"\\"+midParam+" -- "+from.errorString());
                    return false;
                }
                if (midParam=="newxpam.exe") emit restartNeeded(); //this is new client so we tell gui thread to restart after update
            }
            else if (l[0]=="DELETE") {
                emit sendLine("Deleting "+midParam);

                if     (l.last()=="EUROPATH") QFile::remove(config->EUROPATH+"\\"+midParam);
                else if(l.last()=="W3PATH")   QFile::remove(config->W3PATH+"\\"+midParam);
                else if(l.last()=="MAPPATH")  QFile::remove(config->MAPPATH+"\\"+midParam);
            }
        }
    }
    else {
        emit sendLine("Could not open instructions file");
        return false;
    }
    inst.close();

    //cleanup appdata
    QFile::remove(config->APPDATA+"\\instructions.txt");

    emit sendLine("...");
    emit sendLine("...");
    return true;
}

void Updater::receiveProgress(qint64 bytesReceived, qint64 bytesTotal) {
    if (progressTime.elapsed() > 1000 && bytesTotal != -1) {
        int percents = (int)(((float)bytesReceived/(float)bytesTotal)*100.0);
        emit modifyLastLine("("+QString::number(bytesReceived)+" Bytes / "+QString::number(bytesTotal)+" Bytes) -- "+QString::number(percents)+"%");

        progressTime.restart();
    }
}

void Updater::receiveFinishdl(QByteArray data) {
    dlthread->exit();
    delete downloader;
    delete dlthread;

    emit sendLine("...");

    //check hash
    QString sha1(QCryptographicHash::hash(data, QCryptographicHash::Sha1).toHex());
    bool hashok=false;
    if (sha1==real.value("sha1").toString()) hashok=true;

    //data is empty in case of an error
    if (data.isEmpty() || !hashok) {
        if (mirrorno==3) {
            emit sendLine("All mirrors failed. Aborting the update");
            emit updateFinished(false, false);
            return;
        }

        emit sendLine("There was an error downloading the update files. Trying another mirror");
        mirrorno++;

        QUrl url(mirrors[mirrorno]);
        dlthread=new QThread();
        downloader=new Downloader(url);

        QObject::connect(this, SIGNAL(startDl()), downloader, SLOT(startDl()));
        QObject::connect(downloader, SIGNAL(finisheddl(QByteArray)), this, SLOT(receiveFinishdl(QByteArray)));
        QObject::connect(downloader, SIGNAL(progress(qint64,qint64)), this, SLOT(receiveProgress(qint64,qint64)));
        QObject::connect(downloader, SIGNAL(sendInfo(QString)), this, SIGNAL(sendLine(QString)));

        downloader->moveToThread(dlthread);
        dlthread->start();
        emit startDl();
    }
    else {
        //download was OK
        if (!QDir(config->APPDATA).exists()) QDir().mkpath(config->APPDATA);

        if (QFile::exists(zippath)) QFile::remove(zippath);

        QFile fz(zippath);
        fz.open(QFile::WriteOnly);
        if (fz.isOpen() && fz.isWritable()){
            fz.write(data);
        }
        else{
            emit sendLine("Could not open patch.zip -- "+fz.errorString());
            return;
        }
        fz.close();

        if (!extractZip()){
            emit sendLine("Extraction process failed. Aborting update");
            return;
        }
        if (!instructions()){
            emit sendLine("Instruction process failed. Aborting update");
            return;
        }
        //change registry version
        Registry reg;
        if (!reg.setPatchVersion(latestVersion)){
            emit sendLine("Error changing current version in registry. Aborting update");
            return;
        }
        //change config
        config->PATCH=reg.getPatchVersion();

        QFile f(config->EUROPATH+"\\changelog.txt");
        f.open(QFile::ReadOnly);
        if (f.isOpen()) {
            QString changelog(f.readAll());
            emit sendLine(changelog);
        }

        emit updateFinished(true, false);
    }
}

/*
 * When there are no redirects and no need for progress reporting
 * For getting JSON
 */
QByteArray Updater::simpleDl(QUrl url) {
    QNetworkAccessManager nam;
    QNetworkReply * reply = nam.get(QNetworkRequest(url));

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        return reply->readAll();
    }
    else {
        emit sendLine("Error with simple download: "+reply->errorString());
        QByteArray ba;
        return ba;
    }
}
