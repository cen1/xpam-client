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
#include "QTimer"
#include "QSizePolicy"

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

    //Hide layout dummies
    QSizePolicy sp_retain = ui->checkBox_dummy->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    ui->checkBox_dummy->setSizePolicy(sp_retain);
    ui->checkBox_dummy->hide();

    // GProxy options
    connect(ui->checkBox_console, SIGNAL(clicked(bool)), this, SLOT(handleCheckBoxGProxy(bool)));
    connect(ui->checkBox_chatbuffer, SIGNAL(clicked(bool)), this, SLOT(handleCheckBoxGProxy(bool)));
    connect(ui->checkBox_debug, SIGNAL(clicked(bool)), this, SLOT(handleCheckBoxGProxy(bool)));
    connect(ui->checkBox_telemetry, SIGNAL(clicked(bool)), this, SLOT(handleCheckBoxGProxy(bool)));
    connect(ui->checkBox_autojoin, SIGNAL(clicked(bool)), this, SLOT(handleCheckBoxGProxy(bool)));

    connect(ui->checkBox_option_sounds, SIGNAL(clicked(bool)), this, SLOT(handleCheckBoxGProxy(bool)));
    connect(ui->checkBox_sound_1, SIGNAL(clicked(bool)), this, SLOT(handleCheckBoxGProxy(bool)));
    connect(ui->checkBox_sound_2, SIGNAL(clicked(bool)), this, SLOT(handleCheckBoxGProxy(bool)));
    connect(ui->checkBox_sound_3, SIGNAL(clicked(bool)), this, SLOT(handleCheckBoxGProxy(bool)));
    connect(ui->checkBox_sound_4, SIGNAL(clicked(bool)), this, SLOT(handleCheckBoxGProxy(bool)));
    connect(ui->checkBox_sound_5, SIGNAL(clicked(bool)), this, SLOT(handleCheckBoxGProxy(bool)));
    connect(ui->checkBox_sound_6, SIGNAL(clicked(bool)), this, SLOT(handleCheckBoxGProxy(bool)));
    connect(ui->checkBox_sound_7, SIGNAL(clicked(bool)), this, SLOT(handleCheckBoxGProxy(bool)));
    connect(ui->checkBox_sound_8, SIGNAL(clicked(bool)), this, SLOT(handleCheckBoxGProxy(bool)));
    connect(ui->checkBox_sound_9, SIGNAL(clicked(bool)), this, SLOT(handleCheckBoxGProxy(bool)));
    connect(ui->checkBox_sound_10, SIGNAL(clicked(bool)), this, SLOT(handleCheckBoxGProxy(bool)));
    connect(ui->checkBox_sound_11, SIGNAL(clicked(bool)), this, SLOT(handleCheckBoxGProxy(bool)));
    connect(ui->checkBox_sound_12, SIGNAL(clicked(bool)), this, SLOT(handleCheckBoxGProxy(bool)));

    connect(ui->spinBox_autojoin_delay, SIGNAL(valueChanged(int)), this, SLOT(handleSpinBoxGProxy(int)));
    connect(ui->spinBox_autojoin_gndelay, SIGNAL(valueChanged(int)), this, SLOT(handleSpinBoxGProxy(int)));

    // W3 options
    connect(ui->checkBox_windowed_latest, SIGNAL(clicked(bool)), this, SLOT(handleCheckboxClient(bool)));
    connect(ui->checkBox_opengl_latest, SIGNAL(clicked(bool)), this, SLOT(handleCheckboxClient(bool)));
    connect(ui->checkBox_fullscreen_latest, SIGNAL(clicked(bool)), this, SLOT(handleCheckboxClient(bool)));
     connect(ui->checkBox_gproxy_latest, SIGNAL(clicked(bool)), this, SLOT(handleCheckboxClient(bool)));

    connect(ui->checkBox_windowed_126, SIGNAL(clicked(bool)), this, SLOT(handleCheckboxClient(bool)));
    connect(ui->checkBox_opengl_126, SIGNAL(clicked(bool)), this, SLOT(handleCheckboxClient(bool)));
    connect(ui->checkBox_gproxy_126, SIGNAL(clicked(bool)), this, SLOT(handleCheckboxClient(bool)));

    // XPAM options
    connect(ui->checkBox_updates, SIGNAL(clicked(bool)), this, SLOT(handleCheckboxXpam(bool)));

    // Load XPAM options
    this->initXpamOptions();

    // Load W3 options
    this->initClientOptions();

    // Initiate GProxy options
    this->initGproxyOptions();

    // Clear the update log on every startup
    QFile log(config->EUROPATH+"/xpam.log");
    log.open(QFile::WriteOnly | QFile::Truncate);
    log.close();

    // Set W3 path labels
    if (config->W3PATH_126!="") {
        ui->label_War126Path->setText(config->W3PATH_126);
    }
    else {
        ui->label_War126Path->setText("NOT SET!");
    }
    if (config->W3PATH_LATEST!="") {
        ui->label_WarLatestPath->setText(config->W3PATH_LATEST);
    }
    else {
        ui->label_WarLatestPath->setText("NOT SET!");
    }

    changeActiveMode(config->ACTIVE_MODE_KEY);

    updatesEnabled = ui->checkBox_updates->isChecked();

    //Add CD keys if needed
    Updater::replaceCDKeys(config);

    //Rename war3Patch.mpq to war3Mod.mpw as of 1.28.2
    Updater::renamePatchMpqForLatestW3(config);

    //Sanity checks
    W3::sanityCheck(config);

    //Set TFT as default client
    Registry r;
    r.createEuroKey();
    r.createBlizzKey();
    r.setDefaultTFT();
}

/**
 * @brief MainWindow::checkModeAvailability
 *
 * @param mode_key The mode key to check
 * @param should_warn_user Will redirect user to Warcraft page and show the alert
 * @return
 */
bool MainWindow::checkModeAvailability(QString modeKey, bool shouldWarnUser) {
    if ((modeKey == config->W3_KEY_126 && config->W3PATH_126 != "") ||
        (modeKey == config->W3_KEY_LATEST && config->W3PATH_LATEST != "")) {
        return true;
    }
    if (shouldWarnUser) {
        QString version = config->getW3Version(modeKey);
        status("Please, select the Warcraft " + version + " directory path in order to use this gateway");
        QMessageBox mb(QMessageBox::Critical, "W3 path not set!",
           "Please, select the Warcraft " + version + " directory path in order to use this gateway", QMessageBox::Ok);
        mb.exec();

        // Go to W3 tab
        ui->tabWidget->setCurrentIndex(2);
        if (modeKey == config->W3_KEY_126) {
            ui->pushButton_war126Path->setFocus();
        } else {
            ui->pushButton_warLatestPath->setFocus();
        }
    }
    return false;
}

bool MainWindow::changeActiveMode(QString modeKey, bool shouldWarnUser) {
    if (!checkModeAvailability(modeKey, shouldWarnUser)) {
        return false;
    }
    config->ACTIVE_MODE_KEY = modeKey;
    QSettings settings(config->XPAM_CONFIG_PATH, QSettings::IniFormat);
    settings.setValue("active_mode", config->ACTIVE_MODE_KEY);
    return true;
}

MainWindow::~MainWindow()
{
    delete ui;
}


//Start w3 only, NORMAL gateway
// CURRENTLY NOT USED !!!
void MainWindow::on_pushButtonGWN_clicked()
{
    if (changeActiveMode(config->W3_KEY_LATEST, true)) {
        //Set normal gateway as default
        Registry::setGateways();
        runW3();
    }
}

//Dota gateway, Start w3 and gproxy, switch version as needed
void MainWindow::on_pushButtonGWD_clicked()
{
    if (changeActiveMode(config->W3_KEY_126, true)) {
        //Start gproxy gateway
        startW3AndGproxy();
    }
}

//GProxy gateway (WAR3_LATEST), Start w3 and optionally gproxy
void MainWindow::on_pushButtonGWG_clicked()
{
    if (changeActiveMode(config->W3_KEY_LATEST, true)) {
        if (ui->checkBox_gproxy_latest->isChecked()) {
            Registry::setGproxyGateways();
            startW3AndGproxy();
        }
        else {
            Registry::setGateways();
            runW3();
        }
    }
}

void MainWindow::startW3AndGproxy() {

    qDebug("Starting W3 and GProxy ");

    //Hard WINAPI checks for w3 and gproxy running, all kind of problems if they are...
    if (Util::isRunning(config->W3_EXENAME_LATEST) || Util::isRunning(config->W3_EXENAME_LATEST)) {
        status("Warcraft III is already running");
        return;
    }
    if (Util::isRunning("gproxy.exe")) {
        status("GProxy is already running.");
        return;
    }

    QString w3Path;
    QString w3Exename;

    w3Path = config->getCurrentW3Path();
    w3Exename = config->getCurrentW3Exename();

    //Check if gproxy.exe exists and was not deleted by AV
    QFile gproxyFile(config->EUROPATH+"/gproxy.exe");
    if (!gproxyFile.exists()) {
        QMessageBox mb(QMessageBox::Critical, "GProxy missing",
           "GProxy.exe is missing from Eurobattle.net folder. Maybe your AV deleted it?", QMessageBox::Ok);
         mb.exec();
         return;
    }
    //Check if w3l.exe exists and was not deleted by AV
    QString w3exe = w3Path+"\\w3l.exe";
    QFile w3lFile(w3exe);
    if (!w3lFile.exists()) {
        QMessageBox mb(QMessageBox::Critical, "W3l missing",
           "w3l.exe is missing from Warcraft III folder. Maybe your AV deleted it?", QMessageBox::Ok);
         mb.exec();
         return;
    }

    //Preloader
    QMovie *movie = new QMovie(":/preloader.gif");
    ui->preloaderLabel1->setMovie(movie);
    ui->preloaderLabel1->movie()->start();

    //Set gproxy gateway as default
    Registry::setGproxyGateways();

    QString gpdir=config->EUROPATH;
    QString gpexe="\""+gpdir+"\\gproxy.exe\"";
    QString gpmode=(config->ACTIVE_MODE_KEY == config->W3_KEY_126) ? "restricted" : "normal";
    status("Launching GProxy...");
    ui->labelGproxyout->setText("Working directory: "+gpdir);

    gproxy=new GProxy(gpdir, gpexe, gpmode, config->GPROXY_SERVER, w3Exename, w3Path);
    gpt=new QThread();

    QObject::connect(gpt, SIGNAL(started()), gproxy, SLOT(readStdout()));
    QObject::connect(gproxy, SIGNAL(gproxyReady(QString)), this, SLOT(gproxyReady(QString)));
    QObject::connect(gproxy, SIGNAL(gproxyExiting(bool)), this, SLOT(gproxyExiting(bool)));
    QObject::connect(gproxy, SIGNAL(sendLine(QString)), this, SLOT(receiveLine(QString)), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(terminateCurrentGproxyInstance()), gproxy, SLOT(kill()));

    QObject::connect(gproxy, SIGNAL(gproxyExiting(bool)), gpt, SLOT(quit()));
    QObject::connect(gproxy, SIGNAL(gproxyExiting(bool)), gproxy, SLOT(deleteLater()));
    QObject::connect(gpt, SIGNAL(finished()), gpt, SLOT(deleteLater()));

    gproxy->moveToThread(gpt);
    gpt->start();
}

void MainWindow::runW3() {

    //Again, hard WINAPI check
    if (Util::isRunning(config->W3_EXENAME_LATEST) || Util::isRunning(config->W3_EXENAME_LATEST)) {
        status("Warcraft III is already running");
        return;
    }
    QString w3dir=config->getCurrentW3Path();
    QString w3exe=w3dir+"\\w3l.exe";

    //Check if w3l.exe exists and was not deleted by AV
    QFile w3lFile(w3exe);
    if (!w3lFile.exists()) {
        QMessageBox mb(QMessageBox::Critical, "W3l missing",
           "w3l.exe is missing from Warcraft III folder. Maybe your AV deleted it?", QMessageBox::Ok);
         mb.exec();
         return;
    }

    status("Launching Warcraft III...");

    QStringList list;
    if (config->ACTIVE_MODE_KEY == config->W3_KEY_126) {
        if (ui->checkBox_windowed_126->isChecked()) list << "-windowed";
        if (ui->checkBox_opengl_126->isChecked()) list << "-opengl";
    } else {
        if (ui->checkBox_windowed_latest->isChecked()) list << "-windowed";
        if (ui->checkBox_fullscreen_latest->isChecked()) list << "-nativefullscr";
        if (ui->checkBox_opengl_latest->isChecked()) list << "-opengl";
    }

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

//Start w3 when gproxy emits READY state
void MainWindow::gproxyReady(QString w3Exename) {
    ui->labelGproxyout->setText("EMITTED");
    Logger::log("GProxy is ready", config);

    runW3();

    ui->preloaderLabel1->movie()->stop();
}

void MainWindow::gproxyExiting(bool killedForcefully) {
    qDebug("GProxy exited nicely");
    if (killedForcefully) {
        qDebug("GProxy closed forcefully");
    }
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

    if (config->IS_PORTABLE) {
        return true;
    }

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
    ui->pushButtonBU->setEnabled(false);

    upt->start();
}

//Iterates over dota map vector and downloads missing maps. Returns false when no updates exist.
int MainWindow::checkDotaUpdates() {

    if (config->DOTA_MAPS.size()>0 && this->lastCheckedDota<config->DOTA_MAPS.size()) {

        QString mapName = config->DOTA_MAPS.at(this->lastCheckedDota).first;
        QString w3Path = config->DOTA_MAPS.at(this->lastCheckedDota).second;

        // If dl path does not exist, skip
        if (config->W3PATH_LATEST=="" || (w3Path==config->W3PATH_LATEST && !QDir(config->DOCMAPPATHDL).exists())) {
            Logger::log("Map path does not exist, ignoring DotA map download.", config);
            return 0;
        }
        if (config->W3PATH_126=="" || (w3Path==config->W3PATH_126 && !QDir(config->MAPPATH_126DL).exists())) {
            Logger::log("Map path does not exist, ignoring DotA map download.", config);
            return 0;
        }

        Logger::log("Checking if DotA map exist: "+mapName, config);

        QString dlPath = config->DOCMAPPATHDL;
        if (w3Path==config->W3PATH_126) {
            dlPath=config->MAPPATH_126DL;
        }

        QFile map(dlPath+"/"+mapName);
        if (map.exists()) {
            Logger::log(mapName+" exists.", config);
            this->lastCheckedDota++;
            return checkDotaUpdates();
        }

        isStartupUpdate=false;
        ui->textBrowserUpdate->clear();

        lockTabs(ui->tabWidget->currentIndex());

        updater=new Updater(config, 4, mapName);
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
        ui->pushButtonBU->setEnabled(false);

        //Increment
        this->lastCheckedDota++;

        Logger::log(mapName+" does not exist, downloading.", config);

        upt->start();

        return 1;
    }
    return 0;
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
            msgBox.setText("Unable to do fast incremental update to W3 "+config->W3_VERSION_LATEST+".");
            msgBox.setStandardButtons(QMessageBox::Yes);
            if(msgBox.exec() == QMessageBox::Yes){
                //Execute manual update
                //on_pushButton_updateW3_released();
            }
        }
        else {
            ui->tabWidget->setCurrentIndex(0);
            if (checkW3Updates()) {
                enableButtons=false;
            }
            else {
                //Return 0 means no updates are needed (anymore), go to initial tab
                int dotaret = checkDotaUpdates();
                if (dotaret==0) {
                    ui->tabWidget->setCurrentIndex(0);
                }
                else if (dotaret==1) {
                    enableButtons=false;
                }
            }
        }
    }
    else if (type==1 && !ok) {
        status("Could not find an incremental W3 patch, full upgrade needed.");
        Logger::log("Could not find an incremental W3 patch, full upgrade needed.", config);
        QMessageBox msgBox;
        msgBox.setText("Unable to do fast incremental update to W3 "+config->W3_VERSION_LATEST+".");
        msgBox.setStandardButtons(QMessageBox::Yes);
        if(msgBox.exec() == QMessageBox::Yes){
            //Execute manual update
            //on_pushButton_updateW3_released();
        }
    }
    /*else if (type==2 && !ok) {
        status("Full W3 update failed, you will have to update manually.");
        Logger::log("Full W3 update failed, you will have to update manually.", config);
        ui->pushButton_updateW3->setText("Perform full W3 update (1GB download)");
    }*/
    else if (type==2 && canceled) {
        status("Full W3 update was canceled.");
        Logger::log("Full W3 update was canceled.", config);
    }
    else if (type==4 && ok) {
        Logger::log("Dota map download successful", config);
        if (checkDotaUpdates()==0) {
            ui->tabWidget->setCurrentIndex(0);
        }
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

                //Return 0 means no updates are needed (anymore), go to initial tab
                int dotaret = checkDotaUpdates();
                if (dotaret==0) {
                    ui->tabWidget->setCurrentIndex(0);
                }
                else if (dotaret==1) {
                    enableButtons=false;
                }
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

                    //We might not be in event loop yet
                    QTimer::singleShot(1000, this, SLOT(quit()));
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
        ui->pushButtonBU->setEnabled(true);
        unlockTabs();
    }
}

//Handle XPAM options
void MainWindow::handleCheckboxXpam(bool checked)
{
    QString option = QObject::sender()->objectName().remove("checkBox_");
    QString value = "0";
    if (checked) value="1";
    QSettings settings(config->XPAM_CONFIG_PATH, QSettings::IniFormat);
    settings.setValue(option, value);
}

//Handle GProxy checkbox options
void MainWindow::handleCheckBoxGProxy(bool checked)
{
    QString option = QObject::sender()->objectName().remove("checkBox_");
    QString value = "0";
    if (checked) value="1";
    QSettings settings(config->GPROXY_CONFIG_PATH, QSettings::IniFormat);
    settings.setValue(option, value);
}

//Handle GProxy spinBox options
void MainWindow::handleSpinBoxGProxy(int value)
{
    QString option = QObject::sender()->objectName().remove("spinBox_");
    QSettings settings(config->GPROXY_CONFIG_PATH, QSettings::IniFormat);
    settings.setValue(option, QString::number(value));
}

//Handle client options
void MainWindow::handleCheckboxClient(bool checked)
{
    QSettings settings(config->XPAM_CONFIG_PATH, QSettings::IniFormat);
    QStringList tokens = QObject::sender()->objectName().split("_");
    if (tokens.size() != 3) {
        return;
    }
    // checkBox_[option_name]_[126/latest]
    QString option = tokens[1];
    QString mode_key = tokens[2] == "126" ? config->W3_KEY_126 : config->W3_KEY_LATEST;
    if (mode_key == config->W3_KEY_LATEST) {
        // fullscreen/windowed handling for LATEST version
        if (QObject::sender()==ui->checkBox_fullscreen_latest && ui->checkBox_windowed_latest->isChecked()) {
            ui->checkBox_windowed_latest->setChecked(false);
            settings.setValue(config->W3_KEY_LATEST + "/windowed", "0");
        }
        if (QObject::sender()==ui->checkBox_windowed_latest && ui->checkBox_fullscreen_latest->isChecked()) {
            ui->checkBox_fullscreen_latest->setChecked(false);
            settings.setValue(config->W3_KEY_LATEST + "/fullscreen", "0");
        }
    }
    if (mode_key!=config->W3_KEY_126 || option!="gproxy") {
        settings.setValue(mode_key + "/" + option, checked ? "1" : "0");
    }

    //126 gateway always uses gproxy
    if (!ui->checkBox_gproxy_126->isChecked()) {
        ui->checkBox_gproxy_126->setChecked(true);
    }
}

//Init XPAM checkboxes according to ini file
void MainWindow::initXpamOptions() {
    QSettings settings(config->XPAM_CONFIG_PATH, QSettings::IniFormat);
    foreach (const QString &option_name, config->XPAM_OPTIONS) {
        QCheckBox * find = this->findChild<QCheckBox *>("checkBox_"+option_name);
        if (find != 0) {
            find->setChecked(settings.value(option_name, "0") == "1" ? true : false);
        }
    }
}

//Init gproxy checkboxes according to ini file
void MainWindow::initGproxyOptions() {
    QSettings settings(config->GPROXY_CONFIG_PATH, QSettings::IniFormat);
    foreach (const QString &option_name, config->GPROXY_OPTIONS) {
        QCheckBox * find = this->findChild<QCheckBox *>("checkBox_"+option_name);
        if (find != 0) {
            find->setChecked(settings.value(option_name, "0") == "1" ? true : false);
        }
    }

    ui->spinBox_autojoin_delay->setValue(settings.value("autojoin_delay", "2").toInt());
    ui->spinBox_autojoin_gndelay->setValue(settings.value("autojoin_gndelay", "2").toInt());
}

//Init client checkboxes according to ini file
void MainWindow::initClientOptions() {
    QSettings settings(config->XPAM_CONFIG_PATH, QSettings::IniFormat);
    QVector<QString> checkbox_postfixes = {"126", "latest"};

    foreach (const QString &postfix, checkbox_postfixes) {
        foreach (const QString &option_name, config->W3_OPTIONS) {
            QCheckBox * find = this->findChild<QCheckBox *>("checkBox_"+option_name + "_" + postfix);
            if (find != 0) {
                QString mode_key = postfix == "126" ? config->W3_KEY_126 : config->W3_KEY_LATEST;
                find->setChecked(settings.value(mode_key + "/" + option_name, "0") == "1" ? true : false);
            }
        }
    }

   //Can't have windowed and fullscreen at the same time
   if (ui->checkBox_fullscreen_latest->isChecked() && ui->checkBox_windowed_latest->isChecked()) {
       ui->checkBox_fullscreen_latest->setChecked(true);
       ui->checkBox_windowed_latest->setChecked(false);
       settings.setValue(config->W3_KEY_LATEST + "/windowed", "0");
   }

   //126 gateway always uses gproxy
   if (!ui->checkBox_gproxy_126->isChecked()) {
       ui->checkBox_gproxy_126->setChecked(true);
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

bool MainWindow::showW3PathDialog(QString modeKey) {
    modeKey = config->getCorrectW3Key(modeKey);
    QString exename = config->getW3Exename(modeKey);
    QSettings settings(config->XPAM_CONFIG_PATH, QSettings::IniFormat);

    QFileDialog qfd;
    qfd.setDirectory(settings.value(modeKey + "/path", "").toString());
    const QString path = qfd.getExistingDirectory(this);
    QString p = path;
    p = p.replace(QChar('\\'), QChar('/'));

    if (p=="") {  //On Cancel it returns empty
        return false;
    }
    QString w3_path = p+"/"+exename;
    QFile f(w3_path);
    if (!f.exists()) {
        status("Failed to set W3 path, " + exename + " not present in that directory.");
        return false;
    }
    QString w3version = Winutils::getFileVersion(w3_path);
    QString expectedW3Version = config->getW3Version(modeKey);
    if (w3version != expectedW3Version) {
        status("Failed to set W3 path, " + exename + " has the wrong version. Expected: " + expectedW3Version + ", got: " + w3version);
        return false;
    }
    setNewW3PathSetting(modeKey, &settings, p);

    return true;
}

void MainWindow::setNewW3PathSetting(QString modeKey, QSettings *settings, QString newPath) {

    newPath = newPath.replace(QChar('\\'), QChar('/'));

    settings->setValue(modeKey + "/path", newPath);
    if (modeKey == config->W3_KEY_126) {
        ui->label_War126Path->setText(newPath);
        config->W3PATH_126 = newPath;
    } else {
        ui->label_WarLatestPath->setText(newPath);
        config->W3PATH_LATEST = newPath;
    }
}

//Set new W3 path for latest
void MainWindow::on_pushButton_warLatestPath_clicked()
{
    showW3PathDialog(config->W3_KEY_LATEST);
}

//Set new W3 path for 1.26
void MainWindow::on_pushButton_war126Path_clicked()
{
    showW3PathDialog(config->W3_KEY_126);
}

//Full W3 update
/*void MainWindow::on_pushButton_updateW3_released()
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
}*/

//Diff W3 update
void MainWindow::diffW3Update(QString version) {
    Logger::log("Starting quick W3 update", config);

    isStartupUpdate=false;
    ui->textBrowserUpdate->clear();

    ui->pushButtonBU->setEnabled(false);

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

bool MainWindow::checkW3PathUnicode() {
    bool isUnicode = false;
    QString w3path = config->W3PATH_LATEST;

    for(int i = 0; i < w3path.size(); i++) {
        if(w3path.at(i).unicode() > 127) {
            isUnicode = true;
            break;
        }
    }

    //Check if w3 path contains .exe
    QFile f(config->W3PATH_LATEST+"\\"+config->W3_EXENAME_LATEST);
    if (!f.exists()) {

        // Try to set from w3dir registry
        Registry r;
        QString wp = r.getW3dir();
        if (wp!="") {
            QSettings settings(config->XPAM_CONFIG_PATH, QSettings::IniFormat);
            this->setNewW3PathSetting(config->W3_KEY_LATEST, &settings, wp);
        }

        QFile f2(config->W3PATH_LATEST+"\\"+config->W3_EXENAME_LATEST);
        if (!f2.exists()) {
            QMessageBox mb(QMessageBox::Critical, "W3 path alert",
               "Your W3 path is missing 'Warcraft III.exe' which probably means the path is incorrect.",
               QMessageBox::Ok);
             mb.exec();
             return false;
        }
    }

    Logger::log("W3 path sanity check: "+w3path, config);
    if (isUnicode) {
        Logger::log("W3 path is unicode", config);
        QMessageBox mb(QMessageBox::Critical, "Unicode alert",
           "It appears your W3 is installed in  path that contains non-ASCII characters. Please move it to path that conains only ASCII characters or you will have a lot of problems.",
           QMessageBox::Ok);
         mb.exec();
         return false;
    }

    return true;
}

void MainWindow::quit() {
    Logger::log("Quitting due to restart", config);
    QApplication::quit();
}

void MainWindow::on_checkBox_useGproxy_126_toggled(bool checked)
{
    ui->checkBox_gproxy_126->setChecked(true);
}
