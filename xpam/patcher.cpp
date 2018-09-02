#include "patcher.h"
#include "QFile"
#include "QJsonDocument"
#include "QJsonObject"
#include "QDir"
#include "QProcess"
#include "QStringList"
#include "winutils.h"
#include "logger.h"
#include "w3.h"
#include "QProgressDialog"
#include "QThread"
#include "QCryptographicHash"

bool Patcher::patch(Config * config) {

    //Progress dialog
    QProgressDialog progress("Patching W3", "Cancel", 0, 100);
    progress.setWindowModality(Qt::WindowModal);
    progress.setCancelButton(0);
    progress.show();

    //User agreed, patch W3
    QString xdelta3 = config->EUROPATH+"\\xdelta3.exe";
    QStringList patchNameFilter("*.patch");
    QDir w3dir(config->W3PATH_LATEST);
    QStringList patchFiles = w3dir.entryList(patchNameFilter);

    QFile hashes(config->APPDATA+"/hashes");
    if (!hashes.exists()) {
        Logger::log("Missing hash file, unable to continue the patching.", config);
        return false;
    }
    hashes.open(QIODevice::ReadOnly);

    QJsonDocument json = QJsonDocument::fromJson(hashes.readAll());
    QJsonObject obj=json.object();

    hashes.close();

    //Check hashes
    for (int i=0; i<patchFiles.size(); i++) {
        QFileInfo qf(patchFiles.at(i));
        QString fileToPatch = qf.completeBaseName();

        QCryptographicHash crypto(QCryptographicHash::Sha1);
        QFile fz(config->W3PATH_LATEST+"/"+fileToPatch);
        fz.open(QFile::ReadOnly);
        while(!fz.atEnd()){
          crypto.addData(fz.read(8192));
        }
        QByteArray hash = crypto.result();
        QString sha1 = QString(hash.toHex());

        QJsonValue val = obj.value(fileToPatch);
        if (val!=QJsonValue::Undefined) {
            if (val!=sha1) {
                Logger::log("Hash mismatch for "+fileToPatch, config);
                return false;
            }
            else {
                Logger::log("Hash matches for "+fileToPatch, config);
                continue;
            }
        }
        else {
            Logger::log("Could not hash check file "+fileToPatch, config);
            return false;
        }
    }

    for (int i=0; i<patchFiles.size(); i++) {
        // xdelta3 -d -s SOURCE OUT TARGET
        QFileInfo qf(patchFiles.at(i));
        QString fileToPatch = qf.completeBaseName();
        QStringList args;
        args << "-d";
        args << "-f";
        args << "-s";
        args << fileToPatch;
        args << patchFiles[i];
        args << fileToPatch+".new";

        QProcess p;
        p.setWorkingDirectory(config->W3PATH_LATEST);
        p.start(xdelta3, args);

        //Log full arguments
        QString arguments="";
        for (int i=0; i<p.arguments().size(); i++) {
            arguments += p.arguments().at(i)+" ";
        }
        Logger::log(p.program(), config);
        Logger::log(arguments, config);

        p.waitForFinished();
        int exitCode = p.exitCode();
        QString exitCodeStr = QString::number(exitCode);

        QString out(p.readAllStandardOutput());
        QString err(p.readAllStandardError());
        Logger::log(out, config);
        Logger::log(err, config);
        Logger::log("Exit status: "+exitCodeStr, config);

        if (exitCode==0) {
            Logger::log("Successfully patched "+fileToPatch, config);
            //Delete .patch file
            QFile ftp(config->W3PATH_LATEST+"/"+patchFiles[i]);
            if (ftp.exists()) {
                ftp.remove();
            }
        }
        else {
            Logger::log("Failed to patch "+fileToPatch, config);
            return false;
        }

        progress.setValue(progress.value()+1);
    }

    //Replace .new files
    QStringList newNameFilter("*.new");
    QStringList newFiles = w3dir.entryList(newNameFilter);

    for (int i=0; i<newFiles.size(); i++) {
        QFileInfo qf(newFiles.at(i));
        QString fileToReplace = qf.completeBaseName();
        QFile f(config->W3PATH_LATEST+"/"+newFiles.at(i));
        if (f.exists()) {
            QFile existing(config->W3PATH_LATEST+"/"+fileToReplace);
            if (existing.exists()) {
                existing.remove();
            }
            if (!f.rename(config->W3PATH_LATEST+"/"+fileToReplace)) {
                Logger::log("Failed to add new W3 file "+newFiles.at(i)+" to "+fileToReplace, config);
                Logger::log(Winutils::getLastErrorMsg(), config);
                return false;
            }
            else {
                Logger::log("Successfully replaced "+fileToReplace, config);
            }
        }

        progress.setValue(progress.value()+1);
    }

    progress.setValue(100);
    progress.close();

    config->ASK_FOR_W3_FAST_UPDATE=false;

    return true;
}

QString Patcher::getCurrentW3Version(Config * config) {
    QString exename = config->W3_EXENAME_LATEST+"."+W3::W3_LATEST;
    QString fullPath = config->W3PATH_LATEST+"\\"+exename;
    QFile f(fullPath);
    if (!f.exists()) {
        fullPath = config->W3PATH_LATEST+"\\"+config->W3_EXENAME_LATEST;
    }
    Logger::log(fullPath, config);
    QString w3version = Winutils::getFileVersion(fullPath);
    if (w3version=="1.0.0.1") {
        //Pre 1.28.4
        fullPath = config->W3PATH_LATEST+"\\war3.exe";
        w3version = Winutils::getFileVersion(fullPath);
    }

    return w3version;
}

void Patcher::cleanMetadata(Config * config) {

    QDir w3dir(config->W3PATH_LATEST);

    //Remove .patch files
    QStringList patchNameFilter("*.patch");
    QStringList patchFiles = w3dir.entryList(patchNameFilter);

    for (int i=0; i<patchFiles.size(); i++) {
        QFile f(config->W3PATH_LATEST+"/"+patchFiles.at(i));
        if (f.exists()) {
            f.remove();
        }
    }

    //Remove .new files
    QStringList newNameFilter("*.new");
    QStringList newFiles = w3dir.entryList(newNameFilter);

    for (int i=0; i<newFiles.size(); i++) {
        QFile f(config->W3PATH_LATEST+"/"+newFiles.at(i));
        if (f.exists()) {
            f.remove();
        }
    }

    //Remove patch.meta
    QFile pm(config->W3PATH_LATEST+"/patch.meta");
    if (pm.exists()) {
        pm.remove();
    }
}
