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
#include "mpq.h"
#include "logger.h"

/* Types
 * 0 = client
 * 1 = diff w3 patch
 * 2 = full w3 upate
 * 3 = beta
 * 4 = dota
 */
Updater::Updater(Config * c, int t, QString w) {
    config=c;
    type=t;
    w3=w;
    mirrorno=0;
    restartNeeded=false;
    downloader=nullptr;
    zippath = config->APPDATA+"\\patch.zip";
}

Updater::~Updater() {

}

void Updater::startUpdate() {
    /*
     * XPAM CLIENT UPDATE PROCEDURE - DOCUMENTATION
     * 1. Access 3 different update.json mirrors. 2 out of 3 must be the same for the procedure to continue
     * 2. First object is latest stable patch, second object is beta patch. Each patch has current patch version,
     *    4 mirrors to the update zip archive and sha1 hash of the archive. Patches are full, not incremental.
     *    See Other Files->update.json
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
     * 11. If instructions.txt included a file called newxpam.exe then start update.bat and exit app.
     *     Update.bat removes xpam.exe and renames newxpam.exe (if it exists). Then starts xpam.exe
     *
     *
     * UPLOAD INSTRUCTIONS
     * -Google Drive: make sure you mark as public
     * -SkyDrive: ID from public link
     * -Ubuntu ONE: More->Publish
     */
    QTime now = QTime::currentTime();
    qsrand(now.msec());

    if (downloader!=nullptr) {
        emit sendLine("FORBIDDEN RESTART");
        emit updateFinished(restartNeeded, false, false, false, type);
        return;
    }

    QByteArray j1=simpleDl(config->json1);
    QByteArray j2=simpleDl(config->json2);
    QByteArray j3=simpleDl(config->json3);

    if ((j1.isEmpty() && j2.isEmpty()) || (j1.isEmpty() && j3.isEmpty()) || (j2.isEmpty() && j3.isEmpty())) {
        emit sendLine("Update info is empty. Update servers are down or there might be a problem with your internet connection");
        emit updateFinished(restartNeeded, false, false, false, type);
        return;
    }

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
        emit sendLine("Update info mismatch.");
        emit updateFinished(restartNeeded, false, false, false, type);
        return;
    }

    int setResult = setCurrentPlusOneJson();
    if (setResult==0){
        //Up to date client
        Logger::log("Client is up to date", config);
        emit updateFinished(restartNeeded, true, true, false, type);
        return;
    }
    else if (setResult==2){
        //No W3 patch found
        Logger::log("No W3 patch found to dl", config);
        emit updateFinished(restartNeeded, false, false, false, type);
        return;
    }

    latestVersion = qRound(real.value("version").toDouble());
    if (type==0 || type==3) {
        emit sendLine("Local version: "+QString::number(config->PATCH)+" Incremental version: "+QString::number(latestVersion));
    }

    //Tell splash screen to hide, only taken into account if it is a startup update
    //This means that we have an update so it'd be nice to see the progress
    if (type==3) emit hideSplashScreen();

    mirrors << real.value("mirror1").toString();
    mirrors << real.value("mirror2").toString();
    mirrors << real.value("mirror3").toString();
    mirrors << real.value("mirror4").toString();

    QString mirrorUrl = mirrors[mirrorno];
    if (type==2) {
        int mn = getRandomMirror();
        mirrorUrl = mirrors.at(mn);
        emit sendLine("Downloading from random: mirror "+(QString::number(mn))+" ("+mirrorUrl+")");
    }
    else {
        emit sendLine("Downloading from: mirror "+(QString::number(mirrorno))+" ("+mirrorUrl+")");
    }

    QUrl url(mirrorUrl);

    downloader=new Downloader(url, config);
    dlthread = new QThread();
    downloader->moveToThread(dlthread);

    QObject::connect(dlthread, SIGNAL(started()), downloader, SLOT(startDl()));
    QObject::connect(downloader, SIGNAL(progress(qint64,qint64)), this, SLOT(receiveProgress(qint64,qint64)));
    QObject::connect(downloader, SIGNAL(sendInfo(QString)), this, SIGNAL(sendLine(QString)));
    QObject::connect(downloader, SIGNAL(finisheddl()), this, SLOT(receiveFinishdl()));

    QObject::connect(downloader, SIGNAL(finisheddl()), dlthread, SLOT(quit()));
    QObject::connect(downloader, SIGNAL(finisheddl()), downloader, SLOT(deleteLater()));
    QObject::connect(dlthread, SIGNAL(finished()), dlthread, SLOT(deleteLater()));

    progressTime = QTime().currentTime();
    progressTime.start();

    dlthread->start();
}

/*
 * Extracts patch.zip
 */
bool Updater::extractZip() {

    Logger::log("1", config);
    emit sendLine("...");
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
                emit sendLine("Could not extract file "+filePath+" "+dstFile.errorString());
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
    return true;
}

bool Updater::instructions() {
    //read instructions.txt and execute
    /*
     * MOVE, DELETE or ICONS
     * Filename
     * EUROPATH, SOUNDPATH, W3PATH, W3PATH_126 or MAPPATH
    */
    QFile inst(config->APPDATA+"\\instructions.txt");
    if (inst.open(QIODevice::ReadOnly)) {
        QTextStream in(&inst);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList l = line.split(" ");
            QString midParam=Util::getMiddleParam(l);

            //emit sendLine("Instruction: <"+l.first()+"> <"+midParam+"> <"+l.last()+">");

            QString dstPath;
            if      (l.last()=="EUROPATH") dstPath=config->EUROPATH;
            else if (l.last()=="W3PATH") dstPath=config->W3PATH_LATEST;
            else if (l.last()=="W3PATH_126") dstPath=config->W3PATH_126;
            else if (l.last()=="MAPPATH") dstPath=config->DOCMAPPATHDL;
            else if (l.last()=="SOUNDPATH") dstPath=config->SOUNDPATH;

            if (l[0]=="MOVE") {

                //Skip cdkey files if they exist in destination
                if (midParam=="roc.w3k" || midParam=="tft.w3k") {
                    QFile cdkey(dstPath+"/"+midParam);
                    if (cdkey.exists()) {
                        continue;
                    }
                }

                QFile from(config->APPDATA+"\\"+midParam);
                if (QFile::exists(dstPath+"\\"+midParam)) QFile::remove(dstPath+"\\"+midParam);

                //check if download folder exists
                if(l.last()=="MAPPATH")
                {
                    if (!QDir().exists(dstPath))
                        QDir().mkdir(dstPath);
                }

                emit sendLine("Moving to "+dstPath+"\\"+midParam);
                if (!from.rename(dstPath+"\\"+midParam)) {
                    emit sendLine("Could not move file "+from.fileName()+" to "+dstPath+"\\"+midParam+" -- "+from.errorString());
                    return false;
                }
                if (midParam=="newxpam.exe") restartNeeded=true;
            }
            else if (l[0]=="DELETE") {
                emit sendLine("Deleting "+midParam);

                QFile::remove(dstPath+"\\"+midParam);
            }
            else if (l[0]=="ICONS") {
                if (!updateMPQ(dstPath)) {
                    emit sendLine("Failed to update icons. Please contact Technical Support");
                    return false;
                }
                QFile::remove(config->APPDATA+"\\icons.txt");
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
    return true;
}

bool Updater::updateMPQ(QString w3path)
{
    emit sendLine("Updating MPQ with custom icons");
    //O = open
    //d = delete file
    //f = flush
    //a = add from to
    //C = close
    //exit
    Mpq mpq;
    QFile inputFile(config->APPDATA+"\\icons.txt");
    if (inputFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&inputFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList l = line.split(" ");

            if (l[0]=="O") {
                if (mpq.open(w3path+"\\"+l[1])==false) {
                    emit sendLine(Util::getLastErrorMsg()+config->W3PATH_LATEST+"\\"+l[1]);
                    return false;
                }
            }
            else if(l[0]=="d") {
                mpq.removeFile(l[1]);
            }
            else if(l[0]=="f") {

            }
            else if(l[0]=="a") {
                QFile f(config->APPDATA+"\\"+l[1]);
                f.open(QIODevice::ReadOnly);
                QByteArray ba;
                ba = f.readAll();
                DWORD size=ba.size();
                emit sendLine(l[2]+" ("+QString::number(size)+")");

                if (size==0) return false;
                if (mpq.createFile(l[2], size)==false) {
                    emit sendLine(Util::getLastErrorMsg());
                    return false;
                }
                if (mpq.writeFile(ba)==false) {
                    emit sendLine(Util::getLastErrorMsg());
                    return false;
                }
                if (mpq.finishWriteFile()==false) {
                    emit sendLine(Util::getLastErrorMsg());
                    return false;
                }
                f.close();
                QFile::remove(config->APPDATA+"\\"+l[1]);
            }
            else if(l[0]=="c") {
                emit sendLine("Closing mpq");
                mpq.close();
            }
            else if(l[0]=="exit") {
                emit sendLine("End of icons.txt instruction file");
                inputFile.close();
                return true;
            }
        }
    }
    else {
        emit sendLine("Could not open file icons.txt");
        return false;
    }
    emit sendLine("Something went terribly wrong...");
    return false;
}

// Receives download progress from downloader
// We use a timer so we don't waste cycles
void Updater::receiveProgress(qint64 bytesReceived, qint64 bytesTotal) {
    //emit sendLine("Slot activated "+QString::number(bytesReceived));
    if (progressTime.elapsed() > 200 && bytesTotal != -1) {
        int percents = qRound((((float)bytesReceived/(float)bytesTotal)*100.0));
        emit modifyLastLine("("+QString::number(bytesReceived)+" Bytes / "+QString::number(bytesTotal)+" Bytes) -- "+QString::number(percents)+"%");

        progressTime.restart();
    }
}

void Updater::receiveFinishdl() {

    //Check hash
    Logger::log("Checking file hash...", config);
    emit sendLine("Checking file hash...");

    bool hashok=false;
    QString sha1="unknown";

    QFile fz(zippath);
    if (fz.exists() && fz.size()!=0) {

        QCryptographicHash crypto(QCryptographicHash::Sha1);
        fz.open(QFile::ReadOnly);
        while(!fz.atEnd()){
          crypto.addData(fz.read(8192));
        }
        QByteArray hash = crypto.result();
        sha1 = QString(hash.toHex());
        if (sha1==real.value("sha1").toString()) {
            hashok=true;
        }
        fz.close();
    }
    else {
        emit sendLine("Error with download, could not open result file.");
        Logger::log("Error with download, could not open result file.", config);
    }

    //Data is empty or hash mismatch
    if (!hashok) {
        if (mirrorno==3) {
            emit sendLine("All mirrors failed. Aborting the update");
            emit updateFinished(restartNeeded, false, false, false, type);
            return;
        }
        emit sendLine("Remote checksum: "+real.value("sha1").toString()+"; Local checksum: "+sha1);
        emit sendLine("There was an error downloading the update files. Trying another mirror");
        mirrorno++;

        QString mirrorUrl = mirrors[mirrorno];
        if (type==2) {
            int mn = getRandomMirror();
            mirrorUrl = mirrors.at(mn);
            emit sendLine("Downloading from random: mirror "+(QString::number(mn))+" ("+mirrorUrl+")");
        }
        else {
            emit sendLine("Downloading from: mirror "+(QString::number(mirrorno))+" ("+mirrorUrl+")");
        }

        QUrl url(mirrorUrl);

        downloader=new Downloader(url, config);
        dlthread = new QThread();
        downloader->moveToThread(dlthread);

        QObject::connect(dlthread, SIGNAL(started()), downloader, SLOT(startDl()));
        QObject::connect(downloader, SIGNAL(progress(qint64,qint64)), this, SLOT(receiveProgress(qint64,qint64)));
        QObject::connect(downloader, SIGNAL(sendInfo(QString)), this, SIGNAL(sendLine(QString)));
        QObject::connect(downloader, SIGNAL(finisheddl()), this, SLOT(receiveFinishdl()));

        QObject::connect(downloader, SIGNAL(finisheddl(QByteArray)), dlthread, SLOT(quit()));
        QObject::connect(downloader, SIGNAL(finisheddl(QByteArray)), downloader, SLOT(deleteLater()));
        QObject::connect(dlthread, SIGNAL(finished()), dlthread, SLOT(deleteLater()));

        dlthread->start();
    }
    else {
        //Download was OK
        Logger::log("Extracting zip", config);
        emit sendLine("File hash OK. Extracting update ZIP...");

        if (!extractZip()){
            emit sendLine("Extraction process failed. Aborting update");
            return;
        }
        if (!instructions()){
            emit sendLine("Instruction process failed. Aborting update");
            return;
        }
        //Change registry version
        if (type==0 || type==3) {
            if (!Registry::setPatchVersion(latestVersion)){
                emit sendLine("Error changing current version in registry. Aborting update");
                return;
            }
            //Change config
            config->PATCH=Registry::getPatchVersion();

            QFile f(config->EUROPATH+"\\changelog.txt");
            f.open(QFile::ReadOnly);
            if (f.isOpen()) {
                QString changelog(f.readAll());
                emit sendLine(changelog);
                f.close();
            }

            emit sendLine("...");

            //Check if an even newer (incremental) update exists
            emit sendLine("Checking if there is an even newer patch...");
            if (setCurrentPlusOneJson()==1) { //if next patch exists
                restartNeeded=true; //client will restart and then do the next incremental update
            }
        }

        //Successful update
        emit updateFinished(restartNeeded, true, false, false, type);
    }
}

int Updater::setCurrentPlusOneJson() {
    QJsonDocument json = QJsonDocument::fromJson(jsonba);
    QJsonObject obj=json.object();
    QJsonValue value;

    if (type==3) {
        emit sendLine("Requested patch: beta");
        QString key = "beta";
        QStringList keys = obj.keys();

        if (!keys.contains(key)) {
            emit sendLine("No beta patch exists. Xpam is up to date");
            return 0;
        }
        value=obj.value("beta");
        real=value.toObject();
        if (qRound(real.value("version").toDouble()) <= config->PATCH) {
            emit sendLine("Beta patch is current. Xpam is up to date");
            return 0;
        }
    }
    else if (type==1 || type==2) {
        //Full or partial W3 update
        emit sendLine("Requested patch: full or quick W3 update");
        QString key = w3;
        QStringList keys = obj.keys();

        if (!keys.contains(key)) {
            emit sendLine("No W3 patch exists.");
            return 2;
        }
        value=obj.value(w3);
        real=value.toObject();
    }
    else if (type==4) {
        //DotA map download
        emit sendLine("Requested patch: DotA map download");
        QString key = w3;
        QStringList keys = obj.keys();

        if (!keys.contains(key)) {
            emit sendLine("No DotA map exists on download server.");
            return 2;
        }
        value=obj.value(w3);
        real=value.toObject();
    }
    else {
        emit sendLine("Requested patch: stable");
        int incremental=config->PATCH+1;
        QString key = QString::number(incremental);
        QStringList keys = obj.keys();

        if (!keys.contains(key)) {
            emit sendLine("No newer patch exists. Xpam is up to date");
            return 0;
        }
        value=obj.value(key);
        real=value.toObject();
    }
    return 1;
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
        QByteArray ba(reply->readAll());
        reply->deleteLater();
        return ba;
    }
    else {
        emit sendLine("Error with simple download: "+reply->errorString());
        QByteArray ba;
        reply->deleteLater();
        return ba;
    }
}

QString Updater::moveToDocuments(Config *config) {

    QStringList folders;
    folders << "Ai Scripts";
    folders << "Campaigns";
    folders << "Errors";
    folders << "Maps";
    folders << "Replay";
    folders << "ScreenShots";
    folders << "Scripts";
    folders << "Strings";
    folders << "Logs";

    QString log="";

    QDir w3doc(config->DOCPATH);
    if (!w3doc.exists()) {
        w3doc.mkpath(".");
    }

    QDir dir;

    for (int i = 0; i < folders.size(); ++i) {
        boolean moved = dir.rename(config->W3PATH_LATEST+"\\"+folders.at(i), config->DOCPATH+"/"+folders.at(i));

        log+="<br />"+config->W3PATH_LATEST+"\\"+folders.at(i)+" -> "+config->DOCPATH+"/"+folders.at(i);
        if (moved) {
            log+=" (MOVED)";
        }
        else {
            log+=" (FAILED)";
            QDir newdir(config->DOCPATH+"//"+folders.at(i));
            if (!newdir.exists()) {
                newdir.mkpath(".");
                log+=" (created new empty folder)";
            }
        }
    }
    return log;
}

void Updater::replaceCDKeys(Config *config) {
       QFile roc(config->W3PATH_LATEST+"\\roc.w3k");
       if (!roc.exists()) {
           QFile rocNew(config->W3PATH_LATEST+"\\roc.w3k.new");
           if (rocNew.exists()) {
               rocNew.rename(config->W3PATH_LATEST+"\\roc.w3k");
           }
       }

       QFile tft(config->W3PATH_LATEST+"\\tft.w3k");
       if (!tft.exists()) {
           QFile tftnew(config->W3PATH_LATEST+"\\tft.w3k.new");
           if (tftnew.exists()) {
               tftnew.rename(config->W3PATH_LATEST+"\\tft.w3k");
           }
       }
}

void Updater::renamePatchMpqForLatestW3(Config *config) {
    QFile modMpq(config->W3PATH_LATEST+"\\War3Mod.mpq");
    if (!modMpq.exists()) {
        QFile patchMpq(config->W3PATH_LATEST+"\\War3Patch.mpq");
        if (patchMpq.exists()) {
            patchMpq.copy(config->W3PATH_LATEST+"\\War3Mod.mpq");
        }
    }
}

void Updater::cancelUpdate() {
    this->downloader->reply->abort();
    this->downloader->deleteLater();
    emit sendLine("Update ABORTED BY USER");
    emit updateFinished(false, true, true, true, type);
}

int Updater::getRandomMirror() {

    QString mirrorsTried="";
    for (int i=0; i<this->usedMirrors.size(); i++) {
        mirrorsTried+=QString::number(this->usedMirrors.at(i))+"..";
    }
    if (mirrorsTried=="") {
        emit sendLine("Mirrors tried so far: none");
    }
    else {
        emit sendLine("Mirrors tried so far: "+mirrorsTried);
    }

    int high=3;
    int low=0;
    int mirrorNo = qrand() % ((high + 1) - low) + low;
    while (this->usedMirrors.contains(mirrorNo)) {
        mirrorNo = qrand() % ((high + 1) - low) + low;
    }
    //Does not contain
    this->usedMirrors.append(mirrorNo);

    emit sendLine("Picked random mirror: "+QString::number(mirrorNo));
    return mirrorNo;
}
