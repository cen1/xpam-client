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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "registry.h"
#include "util.h"
#include "logger.h"
#include "QProcess"
#include "QThread"
#include "QTextStream"
#include "QDesktopWidget"
#include "QClipboard"
#include "QDesktopServices"
#include "gproxy.h"
#include "w3.h"
#include "patcher.h"
#include "updater.h"
#include "config.h"
#include "QMovie"
#include "QObjectList"
#include "QFileDialog"

#ifndef WINUTILS_H
    #include "winutils.h"
#endif

W3 * w3=nullptr;         //w3 process
GProxy * gproxy=nullptr;        //gproxy object
Updater * updater=nullptr;      //updater object

QThread * w3t=nullptr;
QThread * gpt=nullptr;          //gproxy thread
QThread * upt=nullptr;          //updater thread

Config * config=new Config();   //global config

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);

    isStartupUpdate=true;
    ismax=false;

    //gproxy options
    connect(ui->checkBox_console, SIGNAL(clicked(bool)), this, SLOT(handleCheckbox(bool)));
    connect(ui->checkBox_option_sounds, SIGNAL(clicked(bool)), this, SLOT(handleCheckbox(bool)));
    connect(ui->checkBox_sound_1, SIGNAL(clicked(bool)), this, SLOT(handleCheckbox(bool)));
    connect(ui->checkBox_sound_2, SIGNAL(clicked(bool)), this, SLOT(handleCheckbox(bool)));
    connect(ui->checkBox_sound_3, SIGNAL(clicked(bool)), this, SLOT(handleCheckbox(bool)));
    connect(ui->checkBox_sound_4, SIGNAL(clicked(bool)), this, SLOT(handleCheckbox(bool)));
    connect(ui->checkBox_sound_5, SIGNAL(clicked(bool)), this, SLOT(handleCheckbox(bool)));
    connect(ui->checkBox_sound_6, SIGNAL(clicked(bool)), this, SLOT(handleCheckbox(bool)));
    connect(ui->checkBox_sound_7, SIGNAL(clicked(bool)), this, SLOT(handleCheckbox(bool)));
    connect(ui->checkBox_sound_8, SIGNAL(clicked(bool)), this, SLOT(handleCheckbox(bool)));
    connect(ui->checkBox_sound_9, SIGNAL(clicked(bool)), this, SLOT(handleCheckbox(bool)));
    connect(ui->checkBox_sound_10, SIGNAL(clicked(bool)), this, SLOT(handleCheckbox(bool)));
    connect(ui->checkBox_chatbuffer, SIGNAL(clicked(bool)), this, SLOT(handleCheckbox(bool)));
    connect(ui->checkBox_debug, SIGNAL(clicked(bool)), this, SLOT(handleCheckbox(bool)));
    connect(ui->checkBox_telemetry, SIGNAL(clicked(bool)), this, SLOT(handleCheckbox(bool)));

    //w3 options
    connect(ui->checkBox_windowed, SIGNAL(clicked(bool)), this, SLOT(handleCheckboxClient(bool)));
    connect(ui->checkBox_opengl, SIGNAL(clicked(bool)), this, SLOT(handleCheckboxClient(bool)));
    connect(ui->checkBox_fullscreen, SIGNAL(clicked(bool)), this, SLOT(handleCheckboxClient(bool)));
    connect(ui->checkBox_updates, SIGNAL(clicked(bool)), this, SLOT(handleCheckboxClient(bool)));

    //load w3 options
    this->initClientOptions();

    //initiate gproxy options
    this->initGproxyOptions();

    updatesEnabled = ui->checkBox_updates->isChecked();

    //Clean the update log on every startup
    QFile log(config->EUROPATH+"\\xpam.log");
    log.open(QFile::WriteOnly | QFile::Truncate);
    log.close();

    //Add CD keys if needed
    Updater::replaceCDKeys(config);

    //Rename war3Patch.mpq to war3Mod.mpw as of 1.28.2
    Updater::renamePatchMpq(config);

    //Enable or disable DotA gateway
    if (config->USE_DUAL_VERSION) {
        ui->pushButtonGWD->setEnabled(true);
    }
    else {
        ui->pushButtonGWD->setEnabled(false);
    }

    //Set current w3 version on slider
    QString currentV = W3::getActiveVersion(config);
    if (currentV==W3::W3_126) {
        ui->horizontalSliderW3Version->setValue(0);
    }
    else if (currentV==W3::W3_LATEST) {
        ui->horizontalSliderW3Version->setValue(1);
    }
    else {
        status("ERROR: unable to determine current W3 version, corrupt state");
        ui->horizontalSliderW3Version->setEnabled(false);
    }

    //Sanity checks
    W3::sanityCheck(config);

    //Set TFT as default client
    Registry r;
    r.setDefaultTFT();

    //Hide slider for now
    ui->horizontalSliderW3Version->hide();
    ui->labelChangeVersion->hide();
    ui->label126->hide();
    ui->labelLatest->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//GProxy gateway, Start w3 and gproxy
void MainWindow::on_pushButtonGWG_clicked()
{
    if (config->USE_DUAL_VERSION) {
        W3::setVersion(W3::W3_LATEST, config);
    }
    startW3AndGproxy(config->W3_EXENAME_LATEST);
}

void MainWindow::startW3AndGproxy(QString w3Exename, QString restrictedVersion) {

    //Hard WINAPI checks for w3 and gproxy running, all kind of problems if they are...
    if (Util::isRunning(w3Exename)) {
        status("Warcraft III is already running");
        return;
    }
    if (Util::isRunning("gproxy.exe")) {
        status("GProxy is already running");
        return;
    }

    ui->tabWidget->setCurrentIndex(1);

    //Preloader
    QMovie *movie = new QMovie(":/preloader.gif");
    ui->preloaderLabel1->setMovie(movie);
    ui->preloaderLabel1->movie()->start();

    //Set gproxy gateway as default
    Registry::setGproxyGateways();

    QString gpdir=config->EUROPATH;
    QString gpexe="\""+gpdir+"\\gproxy.exe\"";

    status("Launching GProxy...");
    ui->labelGproxyout->setText("Working directory: "+gpdir);

    gproxy=new GProxy(gpdir, gpexe, w3Exename, restrictedVersion, config->W3PATH);
    gpt=new QThread();
    gproxy->moveToThread(gpt);

    QObject::connect(gpt, SIGNAL(started()), gproxy, SLOT(readStdout()));
    QObject::connect(gproxy, SIGNAL(gproxyReady(QString)), this, SLOT(gproxyReady(QString)));
    QObject::connect(gproxy, SIGNAL(gproxyExiting()), this, SLOT(gproxyExiting()));
    QObject::connect(gproxy, SIGNAL(sendLine(QString)), this, SLOT(receiveLine(QString)), Qt::QueuedConnection);

    QObject::connect(gproxy, SIGNAL(gproxyExiting()), gpt, SLOT(quit()));
    QObject::connect(gproxy, SIGNAL(gproxyExiting()), gproxy, SLOT(deleteLater()));
    QObject::connect(gpt, SIGNAL(finished()), gpt, SLOT(deleteLater()));

    gpt->start();
}

//Start w3 only, NORMAL gateway
void MainWindow::on_pushButtonGWN_clicked()
{    
    if (config->USE_DUAL_VERSION) {
        W3::setVersion(W3::W3_LATEST, config);
    }

    //Again, hard WINAPI check
    if (Util::isRunning(config->W3_EXENAME_LATEST)) {
        status("Warcraft III is already running");
        return;
    }

    //Set normal gateway as default
    Registry::setGateways();

    QString w3dir=config->W3PATH;
    QString w3exe=w3dir+"\\w3l.exe";

    status("Launching Warcraft III...");

    QStringList list;
    if (ui->checkBox_windowed->isChecked()) list << "-windowed";
    if (ui->checkBox_fullscreen->isChecked()) list << "-nativefullscr";
    if (ui->checkBox_opengl->isChecked()) list << "-opengl";

    w3=new W3(w3dir, w3exe, list, config);
    w3t=new QThread();
    w3->moveToThread(w3t);

    QObject::connect(w3t, SIGNAL(started()), w3, SLOT(startW3()));
    QObject::connect(w3, SIGNAL(w3Exited()), this, SLOT(w3Exited()));

    QObject::connect(w3, SIGNAL(w3Exited()), w3t, SLOT(quit()));
    QObject::connect(w3, SIGNAL(w3Exited()), w3, SLOT(deleteLater()));
    QObject::connect(w3t, SIGNAL(finished()), w3t, SLOT(deleteLater()));

    w3t->start();
}

//Dota gateway, Start w3 and gproxy, switch version as needed
void MainWindow::on_pushButtonGWD_clicked()
{
    if (config->USE_DUAL_VERSION) {
        //Switch version
        W3::setVersion(W3::W3_126, config);

        //Start gproxy gateway
        startW3AndGproxy(config->W3_EXENAME_126, config->W3_VERSION_126);
    }
}

//Start w3 when gproxy emits READY state
void MainWindow::gproxyReady(QString w3Exename) {
    ui->labelGproxyout->setText("EMITTED");
    if (Util::isRunning(w3Exename)) {
        status("Warcraft III is already running");
        return;
    }

    QString w3dir=config->W3PATH;
    QString w3exe=w3dir+"\\w3l.exe";

    status("Launching Warcraft III...");

    QStringList list;
    if (ui->checkBox_windowed->isChecked()) list << "-windowed";
    if (ui->checkBox_fullscreen->isChecked()) list << "-nativefullscr";
    if (ui->checkBox_opengl->isChecked()) list << "-opengl";

    w3=new W3(w3dir, w3exe, list, config);
    w3t=new QThread();
    w3->moveToThread(w3t);

    QObject::connect(w3t, SIGNAL(started()), w3, SLOT(startW3()));
    QObject::connect(w3, SIGNAL(w3Exited()), this, SLOT(w3Exited()));

    QObject::connect(w3, SIGNAL(w3Exited()), w3t, SLOT(quit()));
    QObject::connect(w3, SIGNAL(w3Exited()), w3, SLOT(deleteLater()));
    QObject::connect(w3t, SIGNAL(finished()), w3t, SLOT(deleteLater()));

    w3t->start();

    ui->preloaderLabel1->movie()->stop();
}

void MainWindow::gproxyExiting() {
    status("GProxy has closed");
}

void MainWindow::receiveLine(QString line)
{
    ui->labelGproxyout->setText(line);
    if (line=="[GPROXY] Detected W3 as running")
    {
        if (ui->preloaderLabel1->movie()!=0)
        {
            ui->preloaderLabel1->movie()->stop();
            ui->preloaderLabel1->movie()->deleteLater();
        }
        ui->preloaderLabel1->setText(QString("✓"));
        ui->preloaderLabel1->setStyleSheet("color: green");
    }
    else if (line=="GProxy process exited")
    {
        if (ui->preloaderLabel1->movie()!=0)
        {
            ui->preloaderLabel1->movie()->stop();
            ui->preloaderLabel1->movie()->deleteLater();
        }
        ui->preloaderLabel1->setText(QString("x"));
        ui->preloaderLabel1->setStyleSheet("color: red");
    }
    else if (line=="Received the EXIT signal")
    {
        if (ui->preloaderLabel1->movie()!=0)
        {
            ui->preloaderLabel1->movie()->stop();
            ui->preloaderLabel1->movie()->deleteLater();
        }
        ui->preloaderLabel1->setText(QString("x"));
        ui->preloaderLabel1->setStyleSheet("color: red");
    }
    else if (line.startsWith("[AMH]"))
    {
        ui->labelGproxywarnings->setText("Antihack detected a possible hack program.");
        if (ui->preloaderLabel1->movie()!=0)
        {
            ui->preloaderLabel1->movie()->stop();
            ui->preloaderLabel1->movie()->deleteLater();
        }
        ui->preloaderLabel1->setText(QString("x"));
        ui->preloaderLabel1->setStyleSheet("color: red");
    }
    else if (line.startsWith("[SYSERROR]"))
    {
        this->ui->labelGproxywarnings->setText("A critical error encountered.. if you can't fix it yourself, send log to <a style=\"color: #007dc1;\" href=\"http://eurobattle.net/forums/18-Technical-Support\">Tech Support</a>");
        if (this->ui->preloaderLabel1->movie()!=0)
        {
            this->ui->preloaderLabel1->movie()->stop();
            this->ui->preloaderLabel1->movie()->deleteLater();
        }
        this->ui->preloaderLabel1->setText("x");
        this->ui->preloaderLabel1->setStyleSheet("color: red");
    }
}

void MainWindow::w3Exited() {
    status("W3 closed");
}

//Update W3 on startup
bool MainWindow::checkW3Updates(){

    //Either autopatch fails or there is no autopatch and W3 version is incorrect
    QString w3version = Patcher::getCurrentW3Version(config);
    if (w3version!=config->W3_VERSION_LATEST) {
        Logger::log("Warcraft needs to be updated, detected version "+w3version+", needed version "+config->W3_VERSION_LATEST, config);

        //Figure out which incremental version we need to dl
        QRegExp rx("(\\.)");
        QStringList query = w3version.split(rx);
        if (query.size()<2) {
            status("Could not parse w3 version");
            Logger::log("Could not parse w3 version", config);
            return false;
        }
        QString baseVersion = query.at(0)+"."+query.at(1)+"."+query.at(2);

        bool goAhead=false;

        if (config->ASK_FOR_W3_FAST_UPDATE) {
            QMessageBox patchW3;
            patchW3.setWindowTitle("Patch W3?");
            patchW3.setText("Client can automatically update your W3 to the latest required patch. Accept or update manually. Please wait until all partial updates finish.");
            patchW3.setStandardButtons(QMessageBox::Yes);
            patchW3.addButton(QMessageBox::No);
            patchW3.setDefaultButton(QMessageBox::No);
            if (patchW3.exec() == QMessageBox::Yes) {
                goAhead=true;
            }
        }
        else {
            goAhead=true;
        }

        if (goAhead) {
            this->diffW3Update(baseVersion);
            return true;
        }
    }
    return false;
}

//Update client at startup
void MainWindow::checkUpdates(){

    isStartupUpdate=true;

    //disable beta button or all kind of hell will ensue
    ui->pushButtonBU->setDisabled(true);
    ui->pushButton_updateW3->setDisabled(true);

    ui->tabWidget->setCurrentIndex(3);
    lockTabs(ui->tabWidget->currentIndex());

    updater=new Updater(config, 0);
    upt=new QThread();
    updater->moveToThread(upt);

    QObject::connect(upt, SIGNAL(started()), updater, SLOT(startUpdate()));
    QObject::connect(updater, SIGNAL(updateFinished(bool, bool, bool, bool, int)), this, SLOT(updateFinished(bool, bool, bool, bool, int)));
    QObject::connect(updater, SIGNAL(sendLine(QString)), this, SLOT(logUpdate(QString)));
    QObject::connect(updater, SIGNAL(sendLine(QString)), ui->textBrowserUpdate, SLOT(append(QString)), Qt::QueuedConnection);
    QObject::connect(updater, SIGNAL(modifyLastLine(QString)), this, SLOT(modifyLastLineSlot(QString)));
    QObject::connect(updater, SIGNAL(hideSplashScreen()), this, SLOT(hideSplashScreen()));

    QObject::connect(updater, SIGNAL(updateFinished(bool, bool, bool, bool, int)), upt, SLOT(quit()));
    QObject::connect(updater, SIGNAL(updateFinished(bool ,bool ,bool, bool, int)), updater, SLOT(deleteLater()));
    QObject::connect(upt, SIGNAL(finished()), upt, SLOT(deleteLater()));

    updateInProgress=true;

    upt->start();
}

//Beta update
void MainWindow::on_pushButtonBU_clicked()
{
    isStartupUpdate=false;
    ui->textBrowserUpdate->clear();

    if (config->BETAPIN!=ui->betapinbox->text()) return;
    lockTabs(ui->tabWidget->currentIndex());

    updater=new Updater(config, 3);
    upt=new QThread();
    updater->moveToThread(upt);

    QObject::connect(upt, SIGNAL(started()), updater, SLOT(startUpdate()));
    QObject::connect(updater, SIGNAL(updateFinished(bool, bool, bool, bool, int)), this, SLOT(updateFinished(bool, bool, bool, bool, int)));
    QObject::connect(updater, SIGNAL(sendLine(QString)), this, SLOT(logUpdate(QString)));
    QObject::connect(updater, SIGNAL(sendLine(QString)), ui->textBrowserUpdate, SLOT(append(QString)), Qt::QueuedConnection);
    QObject::connect(updater, SIGNAL(modifyLastLine(QString)), this, SLOT(modifyLastLineSlot(QString)));

    QObject::connect(updater, SIGNAL(updateFinished(bool, bool, bool, bool, int)), upt, SLOT(quit()));
    QObject::connect(updater, SIGNAL(updateFinished(bool, bool, bool, bool, int)), updater, SLOT(deleteLater()));
    QObject::connect(upt, SIGNAL(finished()), upt, SLOT(deleteLater()));

    updateInProgress=true;
    ui->pushButton_updateW3->setEnabled(false);
    ui->pushButtonBU->setEnabled(false);

    upt->start();
}

void MainWindow::updateFinished(bool restartNeeded, bool ok, bool isUpToDate, bool canceled, int type) {

    Logger::log("Update finished", config);
    updateInProgress=false;
    bool enableButtons=true;

    ui->textBrowserUpdate->append("Updater finished");
    if (isStartupUpdate) hideSplashScreen();

    //Do a diff W3 update
    if (type==1 && ok) {
        Logger::log("Diff update successful", config);
        bool patchResult = Patcher::patch(config);

        if (!patchResult) {
            Patcher::cleanMetadata(config);
            QMessageBox msgBox;
            msgBox.setText("Unable to do fast incremental update to W3 "+config->W3_VERSION_LATEST+". Would you like to do a full game update instead? This could take a while.");
            msgBox.setStandardButtons(QMessageBox::Yes);
            msgBox.addButton(QMessageBox::No);
            msgBox.setDefaultButton(QMessageBox::No);
            if(msgBox.exec() == QMessageBox::Yes){
                //Execute manual update
                on_pushButton_updateW3_released();
            }
        }
        else {
            ui->tabWidget->setCurrentIndex(0);
            if (checkW3Updates()) {
                enableButtons=false;
            }
        }
    }
    else if (type==1 && !ok) {
        status("Could not find an incremental W3 patch, full upgrade needed.");
        Logger::log("Could not find an incremental W3 patch, full upgrade needed.", config);
        QMessageBox msgBox;
        msgBox.setText("Unable to do fast incremental update to W3 "+config->W3_VERSION_LATEST+". Would you like to do a full game update instead? This could take a while.");
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        if(msgBox.exec() == QMessageBox::Yes){
            //Execute manual update
            on_pushButton_updateW3_released();
        }
    }
    else if (type==2 && !ok) {
        status("Full W3 update failed, you will have to update manually.");
        Logger::log("Full W3 update failed, you will have to update manually.", config);
        ui->pushButton_updateW3->setText("Perform full W3 update (1GB download)");
    }
    else if (type==2 && canceled) {
        status("Full W3 update was canceled.");
        Logger::log("Full W3 update was canceled.", config);
    }
    else {
        Logger::log("Client update finished", config);

        //Client updates
        if (isUpToDate) {
            status("Client is up to date");
            Logger::log("Client is up to date", config);

            //No new patch, now check if W3 needs updating
            if (checkW3Updates()) {
                Logger::log("W3 needs to be updated", config);
                enableButtons=false;
            }
            else {
                //No W3 updates needed
                Logger::log("W3 is up to date", config);
                ui->tabWidget->setCurrentIndex(0);
            }
        }
        else {
            //Client needed updating
            if (ok) {
                Logger::log("Client was updated", config);
                ui->textBrowserUpdate->append("Client was updated");

                ui->pushButtonBU->setEnabled(true);
                if (restartNeeded){
                    QStringList args;
                    args << "/c";
                    args << "update.bat";
                    QProcess::startDetached(config->SYSTEM+"\\cmd.exe", args);
                    QApplication::quit();
                }
                else {
                }
            }
            else {
                Logger::log("Client update failed", config);
                ui->textBrowserUpdate->append("Update failed. Check the log or update tab to find out the reason.");
                status("Update failed due to critical error");
                ui->pushButtonBU->setEnabled(true);
            }
        }
    }

    if (enableButtons) {
        ui->pushButton_updateW3->setEnabled(true);
        ui->pushButtonBU->setEnabled(true);
        unlockTabs();
    }
}

//Handle gproxy options
void MainWindow::handleCheckbox(bool checked)
{
    QString option = QObject::sender()->objectName().remove("checkBox_");
    QString value = "0";
    if (checked) value="1";

    bool r=config->SetOption(config->EUROPATH+"\\gproxy.cfg", option, value);
    if (!r) ui->statusBar->showMessage("Could not change gproxy config", 10000);
}

//Handle client options
void MainWindow::handleCheckboxClient(bool checked)
{
    QString option = QObject::sender()->objectName().remove("checkBox_");
    QString value = "0";
    if (checked) value="1";

    if (QObject::sender()==ui->checkBox_fullscreen) {
        if (ui->checkBox_windowed->isChecked()) {
            ui->checkBox_windowed->setChecked(false);
            config->SetOption(config->EUROPATH+"\\xpam.cfg", "windowed", "0");
        }
    }
    if (QObject::sender()==ui->checkBox_windowed) {
        if (ui->checkBox_fullscreen->isChecked()) {
            ui->checkBox_fullscreen->setChecked(false);
            config->SetOption(config->EUROPATH+"\\xpam.cfg", "fullscreen", "0");
        }
    }

    bool r=config->SetOption(config->EUROPATH+"\\xpam.cfg", option, value);
    if (!r) ui->statusBar->showMessage("Could not change client config", 10000);
}

//Init checkboxes according to cfg file
void MainWindow::initGproxyOptions() {
    QFile conf(config->EUROPATH+"\\gproxy.cfg");
    if (conf.open(QFile::ReadOnly))
        ui->statusBar->showMessage("Unable to load gproxy options", 10000);

    QStringList lines;
    while(!conf.atEnd())
        lines.append(conf.readLine());

    conf.close();
    for (auto i = lines.begin(); i!=lines.end(); i++) {
        if ((*i).startsWith("#")) continue;
        QStringList l = (*i).split("=");
        QCheckBox * find = this->findChild<QCheckBox *>("checkBox_"+l[0].simplified());
        if (find!=0) {
            if (l[1].simplified()=="1") find->setChecked(true);
            else if (l[1].simplified()=="0") find->setChecked(false);
        }
    }
}

//Init checkboxes according to cfg
void MainWindow::initClientOptions() {
    QFile conf(config->EUROPATH+"\\xpam.cfg");
    if (conf.open(QFile::ReadOnly))
        ui->statusBar->showMessage("Unable to load client options", 10000);

    QStringList lines;
    while(!conf.atEnd())
        lines.append(conf.readLine());

    conf.close();
    for (auto i = lines.begin(); i!=lines.end(); i++) {
        if ((*i).startsWith("#")) continue;
        QStringList l = (*i).split("=");
        QCheckBox * find = this->findChild<QCheckBox *>("checkBox_"+l[0].simplified());
        if (find!=0) {
            if (l[1].simplified()=="1") find->setChecked(true);
            else if (l[1].simplified()=="0") find->setChecked(false);
        }
    }

    if (ui->checkBox_fullscreen->isChecked() && ui->checkBox_windowed->isChecked()) {
        ui->checkBox_fullscreen->setChecked(true);
        ui->checkBox_windowed->setChecked(false);
       config->SetOption(config->EUROPATH+"\\xpam.cfg", "windowed", "0");
    }
}

//This slot is only connected for startup update check
//signal emitted when there is an update avalible
//so we hide splash screen to see progress
void MainWindow::hideSplashScreen() {
    qDebug() << "Closing splash screen";
    emit updateCheckFinished();
}

//Update log in case program crashes and you can't see the text browser for errors
void MainWindow::logUpdate(QString line) {
    Logger::log(line, config);
}

void MainWindow::lockTabs(int except){
    for (int i=0; i<ui->tabWidget->count(); i++) {
        if (i!=except) ui->tabWidget->setTabEnabled(i, false);
    }
}

void MainWindow::unlockTabs() {
    for (int i=0; i<ui->tabWidget->count(); i++) {
        ui->tabWidget->setTabEnabled(i, true);
    }
}

//Deletes last in text browser and appends a new one
void MainWindow::modifyLastLineSlot(QString line) {
    removeLastLine();
    ui->textBrowserUpdate->append(line);
}

//Deletes last line in text browser
void MainWindow::removeLastLine() {
    ui->textBrowserUpdate->setFocus();
    QTextCursor storeCursorPos = ui->textBrowserUpdate->textCursor();
    ui->textBrowserUpdate->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
    ui->textBrowserUpdate->moveCursor(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    ui->textBrowserUpdate->moveCursor(QTextCursor::End, QTextCursor::KeepAnchor);
    ui->textBrowserUpdate->textCursor().removeSelectedText();
    ui->textBrowserUpdate->textCursor().deletePreviousChar();
    ui->textBrowserUpdate->setTextCursor(storeCursorPos);
}

//Write to status bar
void MainWindow::status(QString status) {
    ui->statusBar->showMessage(status, 10000);
}

//Copy gproxy log to clipboard
void MainWindow::on_pushButtonGPCL_clicked()
{
    QFile logfile(config->EUROPATH+"/gproxy.log");
    if (logfile.open(QFile::ReadOnly))
    {
        QString s(logfile.readAll());
        QApplication::clipboard()->setText(s);
    }
}

//Open gproxy log in notepad
void MainWindow::on_pushButtonGPNOTEPAD_clicked()
{
    QDesktopServices::openUrl(QUrl("file:///"+config->EUROPATH+"/gproxy.log"));
}

//Open client log in notepad
void MainWindow::on_pushButtonClientLog_clicked()
{
    QDesktopServices::openUrl(QUrl("file:///"+config->EUROPATH+"/xpam.log"));
}

//Set new w3 path
void MainWindow::on_pushButton_w3path_clicked()
{
    QFileDialog qfd;
    qfd.setDirectory(config->W3PATH);
    const QString path = qfd.getExistingDirectory(this);
    QString p = path;
    p=p.replace(QChar('/'), QChar('\\'));

    if (p!="") { //On Cancel it returns empty
        QFile f(p+"\\"+config->W3_EXENAME_LATEST);
        if (!f.exists()) {
            status("Failed to set W3 path, "+config->W3_EXENAME_LATEST+" not present in that directory.");
        }
        else {
            Registry reg;
            if (reg.setInstallPath(p) && reg.setW3dir(p)) {
                status("W3 path set to "+p);
                config->W3PATH=p;
                displayW3Version();
            }
            else {
                status("Failed to set W3 path");
            }
        }
    }
}

void MainWindow::on_horizontalSliderW3Version_sliderReleased()
{
    ui->horizontalSliderW3Version->setEnabled(false);
    QString newVersion = config->W3_VERSION_126;

    bool r = false;
    if (ui->horizontalSliderW3Version->value()==0) {
        //126
        r = W3::setVersion(W3::W3_126, config);
    }
    else {
        //LATEST
        r = W3::setVersion(W3::W3_LATEST, config);
        newVersion = config->W3_VERSION_LATEST;
    }
    if (r) {
        status("W3 version was changed to "+newVersion);
    }

    ui->horizontalSliderW3Version->setEnabled(true);
}

//Full W3 update
void MainWindow::on_pushButton_updateW3_released()
{

    if (updateInProgress) {
        Logger::log("Update is in progress, cancelling", config);
        //User wants to cancel
        emit cancelUpdate();
        ui->pushButton_updateW3->setText("Perform full W3 update (1GB download)");
        return;
    }
    Logger::log("Starting W3 update", config);

    QMessageBox patchW3;
    patchW3.setWindowTitle("Patch W3 to "+config->W3_VERSION_LATEST);
    QString text = "This will download 1GB of files and replace your W3 with version"+config->W3_VERSION_LATEST+". You should only do this if quick update failed or you think your files might be corrupted. Proceed anyway?";

    patchW3.setText(text);
    patchW3.setStandardButtons(QMessageBox::Yes);
    patchW3.addButton(QMessageBox::No);
    patchW3.setDefaultButton(QMessageBox::No);
    if(patchW3.exec() == QMessageBox::Yes) {

        isStartupUpdate=false;
        ui->textBrowserUpdate->clear();

        ui->pushButtonBU->setEnabled(false);

        ui->tabWidget->setCurrentIndex(3);
        lockTabs(ui->tabWidget->currentIndex());

        updater=new Updater(config, 2, config->W3_VERSION_LATEST+".FULL");
        upt=new QThread();
        updater->moveToThread(upt);

        QObject::connect(upt, SIGNAL(started()), updater, SLOT(startUpdate()));
        QObject::connect(updater, SIGNAL(updateFinished(bool, bool, bool, bool, int)), this, SLOT(updateFinished(bool, bool, bool, bool, int)));
        QObject::connect(updater, SIGNAL(sendLine(QString)), this, SLOT(logUpdate(QString)));
        QObject::connect(updater, SIGNAL(sendLine(QString)), ui->textBrowserUpdate, SLOT(append(QString)), Qt::QueuedConnection);
        QObject::connect(updater, SIGNAL(modifyLastLine(QString)), this, SLOT(modifyLastLineSlot(QString)));

        QObject::connect(this, SIGNAL(cancelUpdate()), updater, SLOT(cancelUpdate()));

        QObject::connect(updater, SIGNAL(updateFinished(bool, bool, bool, bool, int)), upt, SLOT(quit()));
        QObject::connect(updater, SIGNAL(updateFinished(bool, bool, bool ,bool, int)), updater, SLOT(deleteLater()));
        QObject::connect(upt, SIGNAL(finished()), upt, SLOT(deleteLater()));

        updateInProgress=true;
        ui->pushButton_updateW3->setText("Cancel");

        upt->start();
    }
}

//Diff W3 update
void MainWindow::diffW3Update(QString version) {
    Logger::log("Starting quick W3 update", config);

    isStartupUpdate=false;
    ui->textBrowserUpdate->clear();

    ui->pushButtonBU->setEnabled(false);
    ui->pushButton_updateW3->setEnabled(false);

    ui->tabWidget->setCurrentIndex(3);
    lockTabs(ui->tabWidget->currentIndex());

    updater=new Updater(config, 1, version);
    upt=new QThread();
    updater->moveToThread(upt);

    QObject::connect(upt, SIGNAL(started()), updater, SLOT(startUpdate()));
    QObject::connect(updater, SIGNAL(updateFinished(bool, bool, bool, bool, int)), this, SLOT(updateFinished(bool, bool, bool, bool, int)));
    QObject::connect(updater, SIGNAL(sendLine(QString)), this, SLOT(logUpdate(QString)));
    QObject::connect(updater, SIGNAL(sendLine(QString)), ui->textBrowserUpdate, SLOT(append(QString)), Qt::QueuedConnection);
    QObject::connect(updater, SIGNAL(modifyLastLine(QString)), this, SLOT(modifyLastLineSlot(QString)));

    QObject::connect(this, SIGNAL(cancelUpdate()), updater, SLOT(cancelUpdate()));

    QObject::connect(updater, SIGNAL(updateFinished(bool, bool, bool, bool, int)), upt, SLOT(quit()));
    QObject::connect(updater, SIGNAL(updateFinished(bool, bool, bool, bool, int)), updater, SLOT(deleteLater()));
    QObject::connect(upt, SIGNAL(finished()), upt, SLOT(deleteLater()));

    updateInProgress=true;

    upt->start();
}

void MainWindow::displayW3Version() {
    ui->labelW3Path->setText("W3 path: "+config->W3PATH);
    QString w3versionDetected = Patcher::getCurrentW3Version(config);
    if (w3versionDetected==config->W3_VERSION_LATEST) {
        ui->labelW3Version->setText("Detected latest W3 version: "+w3versionDetected+" (OK)");
    }
    else {
        ui->labelW3Version->setText("Detected latest W3 version: "+w3versionDetected+" (ERROR, needed: "+config->W3_VERSION_LATEST+")");
    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (index==2) {
        //Refresh detected w3 version
        displayW3Version();
    }
}
