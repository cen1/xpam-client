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

    QFile newPatch(config->W3PATH+"/patch.meta");
    if (newPatch.exists()) {
        newPatch.open(QIODevice::ReadOnly | QIODevice::Text);
        QJsonDocument doc = QJsonDocument::fromJson(newPatch.readAll());
        newPatch.close();
        QJsonObject obj;
        if(!doc.isNull()) {
            if(doc.isObject()) {
                obj = doc.object();
            }
            else {
                Logger::log("Document is not an object", config);
                return false;
            }
        }
        else {
            Logger::log("Invalid JSON.", config);
            return false;
        }

        QString fullPath = config->W3PATH+"\\"+obj.value("oldexe").toString();
        Logger::log(fullPath, config);
        QString w3version = Winutils::getFileVersion(fullPath);
        Logger::log(w3version, config);

        if (w3version == config->W3_VERSION_LATEST) {
            return true; //new patch exists but w3 is already latest version, do nothing
        }
        if (obj.value("oldv").toString()!=w3version) {
            Logger::log("Client could not autopatch W3 because it is not the correct base version, needed is "+w3version, config);
            return false;
        }
        //Check if newexe is already present and correct version
        QString newFullPath = config->W3PATH+"\\"+obj.value("newexe").toString();
        QString newW3version = Winutils::getFileVersion(newFullPath);
        if (newW3version == obj.value("newv").toString()) {
            Logger::log("Executable appears to already be of desired version. Do nothing. ", config);
            return true;
        }


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

            //Validate game version
            QString fullPathNew = config->W3PATH+"\\"+obj.value("newexe").toString();
            QFile newExe(fullPathNew);
            if (newExe.exists()) {
                QString newVersion = Winutils::getFileVersion(fullPathNew);
                if (newVersion != obj.value("newv").toString()) {
                    Logger::log("Patched W3 version is incorrect, something went wrong :/", config);
                    return false;
                }
            }
            else {
                Logger::log("Unable to find new W3 .exe", config);
                return false;
            }

            //Mark patch as done
            newPatch.remove();

            progress.setValue(100);
            progress.close();

            return true;
        }
        else {
          return false;
        }
   }
   else {
        //No new automatic patch exists, check if we need to update W3 manually
        QString exename = config->W3_EXENAME_LATEST+"."+W3::W3_LATEST;
        QString fullPath = config->W3PATH+"\\"+exename;
        QFile f(fullPath);
        if (!f.exists()) {
            fullPath = config->W3PATH+"\\"+config->W3_EXENAME_LATEST;
        }
        Logger::log(fullPath, config);
        QString w3version = Winutils::getFileVersion(fullPath);
        if (w3version != config->W3_VERSION_LATEST) {
            return false;
        }
        else {
            return true;
        }
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

    return w3version;
}
