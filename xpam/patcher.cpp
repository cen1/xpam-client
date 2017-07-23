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

bool Patcher::patch(Config * config) {

    QMessageBox patchW3;
    patchW3.setWindowTitle("Patch W3?");
    patchW3.setText("Client can automatically update your W3 to the latest required patch. Accept or do it manually.");
    patchW3.setStandardButtons(QMessageBox::Yes);
    patchW3.addButton(QMessageBox::No);
    patchW3.setDefaultButton(QMessageBox::No);
    if(patchW3.exec() == QMessageBox::Yes){

        //Progress dialog
        QProgressDialog progress("Patching W3", "Cancel", 0, 100);
        progress.setWindowModality(Qt::WindowModal);
        progress.setCancelButton(0);
        progress.show();

        //User agreed, patch W3
        QString xdelta3 = config->EUROPATH+"\\xdelta3.exe";
        QStringList patchNameFilter("*.patch");
        QDir w3dir(config->W3PATH);
        QStringList patchFiles = w3dir.entryList(patchNameFilter);
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
            p.setWorkingDirectory(config->W3PATH);
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
                QFile ftp(config->W3PATH+"/"+patchFiles[i]);
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
            QFile f(config->W3PATH+"/"+newFiles.at(i));
            if (f.exists()) {
                QFile existing(config->W3PATH+"/"+fileToReplace);
                if (existing.exists()) {
                    existing.remove();
                }
                if (!f.rename(config->W3PATH+"/"+fileToReplace)) {
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

        return true;
    }
    else {
      return false;
    }
}

QString Patcher::getCurrentW3Version(Config * config) {
    QString exename = config->W3_EXENAME_LATEST+"."+W3::W3_LATEST;
    QString fullPath = config->W3PATH+"\\"+exename;
    QFile f(fullPath);
    if (!f.exists()) {
        fullPath = config->W3PATH+"\\"+config->W3_EXENAME_LATEST;
    }
    Logger::log(fullPath, config);
    QString w3version = Winutils::getFileVersion(fullPath);
    if (w3version=="1.0.0.1") {
        //Pre 1.28.4
        fullPath = config->W3PATH+"\\war3.exe";
        w3version = Winutils::getFileVersion(fullPath);
    }

    return w3version;
}

void Patcher::cleanMetadata(Config * config) {

    QDir w3dir(config->W3PATH);

    //Remove .patch files
    QStringList patchNameFilter("*.patch");
    QStringList patchFiles = w3dir.entryList(patchNameFilter);

    for (int i=0; i<patchFiles.size(); i++) {
        QFile f(config->W3PATH+"/"+patchFiles.at(i));
        if (f.exists()) {
            f.remove();
        }
    }

    //Remove .new files
    QStringList newNameFilter("*.new");
    QStringList newFiles = w3dir.entryList(newNameFilter);

    for (int i=0; i<newFiles.size(); i++) {
        QFile f(config->W3PATH+"/"+newFiles.at(i));
        if (f.exists()) {
            f.remove();
        }
    }

    //Remove patch.meta
    QFile pm(config->W3PATH+"/patch.meta");
    if (pm.exists()) {
        pm.remove();
    }
}
