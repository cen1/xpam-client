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
#include "torrentdownloader.h"
#include "registry.h"
#include "util.h"
#include "logger.h"
#include "QProcess"
#include "QThread"
#include "QTextStream"
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
#include "QJsonDocument"
#include "QJsonArray"
#include "bnethash.h"
#include "rest.h"
#include "QUrl"

#ifndef WINUTILS_H
    #include "winutils.h"
#endif

W3 * w3=nullptr;         //w3 process
GProxy * gproxy=nullptr;        //gproxy object
Updater * updater=nullptr;      //updater object
TorrentDownloader * tdl=nullptr;

QThread * w3t=nullptr;
QThread * gpt=nullptr;          //gproxy thread
QThread * upt=nullptr;          //updater thread
QThread * tdlt=nullptr;

Config * config=new Config();   //global config

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);

    isStartupUpdate=true;
    ismax=false;    

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
    connect(ui->checkBox_pfEnable_latest, SIGNAL(clicked(bool)), this, SLOT(handleCheckBoxGProxy(bool)));

    connect(ui->spinBox_autojoin_delay, SIGNAL(valueChanged(int)), this, SLOT(handleSpinBoxGProxy(int)));
    connect(ui->spinBox_autojoin_gndelay, SIGNAL(valueChanged(int)), this, SLOT(handleSpinBoxGProxy(int)));

    // W3 options
    connect(ui->checkBox_windowed_latest, SIGNAL(clicked(bool)), this, SLOT(handleCheckboxClient(bool)));
    connect(ui->checkBox_opengl_latest, SIGNAL(clicked(bool)), this, SLOT(handleCheckboxClient(bool)));
    connect(ui->checkBox_fullscreen_latest, SIGNAL(clicked(bool)), this, SLOT(handleCheckboxClient(bool)));
    connect(ui->checkBox_gproxy_latest, SIGNAL(clicked(bool)), this, SLOT(handleCheckboxClient(bool)));
    connect(ui->checkBox_pfEnable_latest, SIGNAL(clicked(bool)), this, SLOT(handleCheckboxClient(bool)));

    connect(ui->checkBox_windowed_126, SIGNAL(clicked(bool)), this, SLOT(handleCheckboxClient(bool)));
    connect(ui->checkBox_opengl_126, SIGNAL(clicked(bool)), this, SLOT(handleCheckboxClient(bool)));
    connect(ui->checkBox_gproxy_126, SIGNAL(clicked(bool)), this, SLOT(handleCheckboxClient(bool)));
    connect(ui->checkBox_w3l_126_lobby, SIGNAL(clicked(bool)), this, SLOT(handleCheckboxW3l(bool)));

    //DotA Options
    connect(ui->checkBox_dota_GAMEOPTIONS_WideScreen, SIGNAL(clicked(bool)), this, SLOT(handleCheckboxDota(bool)));

    // XPAM options
    connect(ui->checkBox_updates, SIGNAL(clicked(bool)), this, SLOT(handleCheckboxXpam(bool)));

    // Load XPAM options
    this->initXpamOptions();

    // Load W3 options
    this->initClientOptions();

    // Initiate GProxy options
    this->initGproxyOptions();

    // Authenticate
    this->initLogin();

    // Clear the update log on every startup
    QFile log(config->EUROPATH+"/xpam.log");
    log.open(QFile::WriteOnly | QFile::Truncate);
    log.close();

    // Set W3 path labels
    if (config->W3PATH_126!="") {
        ui->label_War126Path->setText(config->W3PATH_126);
        ui->label_War126Path->setToolTip(config->W3PATH_126);
    }
    else {
        ui->label_War126Path->setText("NOT SET!");
    }
    if (config->W3PATH_LATEST!="") {
        ui->label_WarLatestPath->setText(config->W3PATH_LATEST);
        ui->label_WarLatestPath->setToolTip(config->W3PATH_LATEST);
    }
    else {
        ui->label_WarLatestPath->setText("NOT SET!");
    }

    changeActiveMode(config->ACTIVE_MODE_KEY);

    updatesEnabled = ui->checkBox_updates->isChecked();

    //Add CD keys if needed
    Logger::log("CD keys", config);
    Updater::replaceCDKeys(config);

    //Rename war3Patch.mpq to war3Mod.mpw as of 1.28.2
    Logger::log("war3Patch.mpq", config);;
    Updater::renamePatchMpqForLatestW3(config);

    //Sanity checks
    Logger::log("sanity checks", config);;
    W3::sanityCheck(config);

    //Prefill map update info
    Logger::log("map updates", config);
    if (updatesEnabled) {
        Logger::log("Prefilling map update info", config);
        DlResponse jsonResponse = Updater::getUpdateJson(config);
        if (jsonResponse.getSuccess()) {
            QByteArray jsonba = jsonResponse.getData();
            QJsonDocument json = QJsonDocument::fromJson(jsonba);
            QJsonObject obj=json.object();
            QStringList keys = obj.keys();

            if (keys.contains("maps")) {
                Logger::log("Mandatory maps found on remote", config);
                QJsonValue value = obj.value("maps");
                QJsonArray maps = value.toArray();

                foreach (const QJsonValue & value, maps) {
                    QJsonObject obj = value.toObject();
                    UPDATE_MAPS.append(obj);
                    Logger::log("Added remote map entry "+obj.value("name").toString(), config);
                }
            }
        }
        else {
            Logger::log("Failed to fetch map metadata", config);
            Logger::log(jsonResponse.getErrorMessage(), config);
        }
    }

    //Set TFT as default client
    Logger::log("default client", config);
    Registry r;
    r.createEuroKey();
    r.createBlizzKey();
    r.setDefaultTFT();

    //Temporary hacks
    Logger::log("workarounds", config);
    tmpPlumbing();

    //News web
    Logger::log("web", config);
    QSettings settings(config->XPAM_CONFIG_PATH, QSettings::IniFormat);
    QString newsUrl = settings.value("news_url", "https://eurobattle.net/client/news").toString();
    qDebug() << "News URL: " << newsUrl;
    this->ui->mmWebEngineView->load(QUrl(newsUrl));
    this->ui->mmWebEngineView->show();

    //Web link init
    Logger::log("weblink", config);
    setupWebLinkProtoHandlers();

    //Server status
    Logger::log("server status", config);
    showServerStatus();
    this->serverStatusTimer = new QTimer(this);
    connect(this->serverStatusTimer, SIGNAL(timeout()), this, SLOT(showServerStatus()));
    this->serverStatusTimer->start(1000*60*15);

    this->repaint();
}

//Method that is called after client is up to date and ready to be used
void MainWindow::postUpdate() {

    //Launch game
    if (QCoreApplication::arguments().size()>=2) {
        QString arg = QCoreApplication::arguments().at(1);
        Logger::log(arg, config);
        if ("xpam:126"==arg) {
            on_pushButtonGWD_clicked();
        }
        else if ("xpam:128"==arg){
            on_pushButtonGWG_clicked();
        }
    }
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
        if (ui->checkBox_pfEnable_latest->isChecked()) {
            Registry::setGateways();
            startW3AndGproxy(true);
        }
        else if (ui->checkBox_gproxy_latest->isChecked()) {
            Registry::setGproxyGateways();
            startW3AndGproxy();
        }
        else {
            Registry::setGateways();
            runW3();
        }
    }
}

void MainWindow::startW3AndGproxy(bool ft) {

    if (ft) qDebug() << "ft enabled";

    //Ft and no login
    if (ft && ui->label_online->isHidden()) {
        QMessageBox mb(QMessageBox::Critical, "Login first",
           "In order to use auto port forwarding functionality you must login first.",
           QMessageBox::Ok);
         mb.exec();
         return;
    }

    //Ft and no config
    QSettings settings(config->GPROXY_CONFIG_PATH, QSettings::IniFormat);
    if (ft && (settings.value("pf_username", "")=="" || settings.value("pf_secret", "")=="")) {
        QMessageBox mb(QMessageBox::Critical, "Relog",
           "Please login again on the dashboard.",
           QMessageBox::Ok);
         mb.exec();
         return;
    }

    qDebug("Starting W3 and GProxy ");

    //Hard WINAPI checks for w3 and gproxy running, all kind of problems if they are...
    if (Util::isRunning(config->W3_EXENAME_LATEST) || Util::isRunning(config->W3_EXENAME_LATEST)) {
        qDebug() << "w3r";
        status("Warcraft III is already running");
        return;
    }
    if (Util::isRunning("gproxy.exe")) {
        qDebug() << "gpr";
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
    if (!ft) {
        Registry::setGproxyGateways();
    }

    QString gpdir=config->EUROPATH;
    QString gpexe="\""+gpdir+"\\gproxy.exe\"";
    QString gpmode=(config->ACTIVE_MODE_KEY == config->W3_KEY_126) ? "restricted" : "normal";
    status("Launching GProxy...");
    ui->labelGproxyout->setText("Working directory: "+gpdir);

    gproxy=new GProxy(gpdir, gpexe, gpmode, config->GPROXY_SERVER, w3Exename, w3Path, config->PLINK, ft);
    gpt=new QThread();

    QObject::connect(gpt, SIGNAL(started()), gproxy, SLOT(readStdout()));
    QObject::connect(gproxy, SIGNAL(gproxyReady(QString, bool)), this, SLOT(gproxyReady(QString, bool)));
    QObject::connect(gproxy, SIGNAL(gproxyExiting(bool)), this, SLOT(gproxyExiting(bool)));
    QObject::connect(gproxy, SIGNAL(sendLine(QString)), this, SLOT(receiveLine(QString)), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(terminateCurrentGproxyInstance()), gproxy, SLOT(kill()));

    QObject::connect(gproxy, SIGNAL(gproxyExiting(bool)), gpt, SLOT(quit()));
    QObject::connect(gproxy, SIGNAL(gproxyExiting(bool)), gproxy, SLOT(deleteLater()));
    QObject::connect(gpt, SIGNAL(finished()), gpt, SLOT(deleteLater()));

    gproxy->moveToThread(gpt);
    gpt->start();
}

void MainWindow::runW3(bool ft) {

    if (ft) qDebug() << "ft enabled";

    //Again, hard WINAPI check
    if (Util::isRunning(config->W3_EXENAME_LATEST) || Util::isRunning(config->W3_EXENAME_LATEST)) {
        status("Warcraft III is already running");
        return;
    }
    QString w3dir=config->getCurrentW3Path();
    QString w3exe=w3dir+"/w3l.exe";

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

    w3=new W3(w3dir, w3exe, list, config, ft);
    w3t=new QThread();
    w3->moveToThread(w3t);

    QObject::connect(w3t, SIGNAL(started()), w3, SLOT(startW3()));
    QObject::connect(w3, SIGNAL(w3Exited()), this, SLOT(w3Exited()));
    if (ft) {
        QObject::connect(w3, SIGNAL(log(QString)), this, SLOT(receiveLineW3(QString)));
    }

    QObject::connect(w3, SIGNAL(w3Exited()), w3t, SLOT(quit()));
    QObject::connect(w3, SIGNAL(w3Exited()), w3, SLOT(deleteLater()));
    QObject::connect(w3t, SIGNAL(finished()), w3t, SLOT(deleteLater()));

    w3t->start();
}

//Start w3 when gproxy emits READY state
void MainWindow::gproxyReady(QString w3Exename, bool ft) {
    ui->labelGproxyout->setText("EMITTED");
    Logger::log("GProxy is ready", config);

    runW3(ft);

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

void MainWindow::receiveLineW3(QString line)
{
    Logger::log(line, config);
}

void MainWindow::w3Exited() {
    status("W3 closed");
}

//Update W3 on startup
bool MainWindow::checkW3Updates(){

    if (config->IS_PORTABLE) {
        return true;
    }

    if (config->W3PATH_LATEST == "") return false; //no latest w3 installed

    //Either autopatch fails or there is no autopatch and W3 version is incorrect
    QString w3version = Patcher::getCurrentW3Version(config);
    if (w3version!=config->W3_VERSION_LATEST) {
        Logger::log("Warcraft needs to be updated, detected version "+w3version+", needed version "+config->W3_VERSION_LATEST, config);

        //Figure out which incremental version we need to dl
        QRegularExpression rx("(\\.)");
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

    ui->tabWidget->setCurrentIndex(5);
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

//Iterates over map vector and downloads missing maps. Returns false when no updates exist.
int MainWindow::checkMapUpdates() {

    if (this->UPDATE_MAPS.size() > 0 && this->lastCheckedMap < this->UPDATE_MAPS.size()) {

        QJsonObject mapEntry = this->UPDATE_MAPS.at(this->lastCheckedMap);

        QString mapName = mapEntry.value("name").toString();
        QString targetPathKey = mapEntry.value("targetPath").toString();
        QString w3Path = (targetPathKey == "W3PATH_126") ? config->W3PATH_126 : config->W3PATH_LATEST;

        // If dl path does not exist, skip
        if (w3Path==config->W3PATH_LATEST && (config->W3PATH_LATEST=="" || !QDir(config->DOCMAPPATHDL).exists())) {
            Logger::log("Map path does not exist, ignoring map download.", config);
            return 0;
        }
        if (w3Path==config->W3PATH_126 && (config->W3PATH_126=="" || !QDir(config->MAPPATH_126DL).exists())) {
            Logger::log("Map path does not exist, ignoring map download.", config);
            return 0;
        }

        Logger::log("Checking if map exist: "+mapName, config);

        QString dlPath = config->DOCMAPPATHDL;
        if (w3Path==config->W3PATH_126) {
            dlPath=config->MAPPATH_126DL;
        }

        // Check main map file
        bool needsDownload = false;
        QFile map(dlPath+"/"+mapName);
        if (!map.exists()) {
            needsDownload = true;
            Logger::log("Main map missing: " + mapName, config);
        }

        // Check additional files
        if (!needsDownload && mapEntry.contains("additional_files") && mapEntry.value("additional_files").isArray()) {
            QJsonArray additionalFiles = mapEntry.value("additional_files").toArray();
            for (const QJsonValue& fileEntry : additionalFiles) {
                if (!fileEntry.isObject()) continue; //malformed..

                QJsonObject fileObj = fileEntry.toObject();
                QString extraFileName = fileObj.value("name").toString();
                QString extraPathKey = fileObj.value("path").toString();
                QString extraPath = config->getPathFromKey(extraPathKey);

                QFile extraFile(extraPath + "/" + extraFileName);
                if (!extraFile.exists()) {
                    Logger::log("Additional file missing: " + extraFileName, config);
                    needsDownload = true;
                    break;
                }
            }
        }

        if (!needsDownload) {
            Logger::log(mapName + " and all additional files exist.", config);
            this->lastCheckedMap++;
            return checkMapUpdates(); // recursive call to continue
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
        this->lastCheckedMap++;

        Logger::log(mapName+" does not exist or is missing extra files, downloading.", config);

        upt->start();

        return 1;
    }
    return 0;
}

// Checks if core files are missing from W3 installs
// First counter pass is for latest, second is for 126
// Returns 1 if update is needed
int MainWindow::checkW3LoaderFiles() {

    if (this->w3LoaderCheckCounter<0) return 0;

    QString path = config->W3PATH_LATEST;
    if (this->w3LoaderCheckCounter==0)
        path = config->W3PATH_126;

    this->w3LoaderCheckCounter--;

    if (path == "") {
        checkW3LoaderFiles(); // go to next w3
        return 0;
    }

    if (!QFile::exists(path+"\\w3l.exe") ||
        !QFile::exists(path+"\\w3lh.dll") ||
        !QFile::exists(path+"\\wl27.dll") ||
        !QFile::exists(path+"\\libssl-3.dll") ||
        !QFile::exists(path+"\\libcrypto-3.dll") ||
        !QFile::exists(path+"\\zlib1.dll")) {

        Logger::log("Missing loader file detected", config);

        isStartupUpdate=false;

        lockTabs(ui->tabWidget->currentIndex());

        QString jsonKey = "126_quick";
        if (path == config->W3PATH_LATEST) jsonKey = "128_quick";

        updater=new Updater(config, 5, jsonKey);
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

        Logger::log(path+" has missing loader files, downloading.", config);

        upt->start();

        return 1;
    }
    else {
        Logger::log("Loader files for "+path+" are present", config);
        checkW3LoaderFiles(); // go to next w3
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
                int mapret = checkMapUpdates();
                if (mapret==0) {
                    ui->tabWidget->setCurrentIndex(0);
                    postUpdate();
                }
                else if (mapret==1) {
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
        Logger::log("Map download successful", config);
        if (checkMapUpdates()==0) {
            ui->tabWidget->setCurrentIndex(0);
            postUpdate();
        }
    }
    else if (type==5 && ok) {
        Logger::log("Loader files fixed successfully", config);
        if (checkW3LoaderFiles()==0) {
            //Map dl is always last step, bad design but it is what it is..
            int mapret = checkMapUpdates();
            if (mapret==0) {
                ui->tabWidget->setCurrentIndex(0);
            }
            else if (mapret==1) {
                enableButtons=false;
            }
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

                if (checkW3LoaderFiles()) {
                    Logger::log("W3 loader files need to be updated", config);
                    enableButtons=false;
                }
                else {
                    //Return 0 means no updates are needed (anymore), go to initial tab
                    int mapret = checkMapUpdates();
                    if (mapret==0) {
                        ui->tabWidget->setCurrentIndex(0);
                    }
                    else if (mapret==1) {
                        enableButtons=false;
                    }
                }
            }

            postUpdate();
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
                else {
                    postUpdate();
                }
            }
            else {
                Logger::log("Client update failed", config);
                ui->textBrowserUpdate->append("Update failed. Check the log or update tab to find out the reason.");
                status("Update failed due to critical error");
                ui->pushButtonBU->setEnabled(true);

                postUpdate();
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
    QString option = Util::fromCamelCase(QObject::sender()->objectName().remove("checkBox_").remove("_latest"));
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
        //Pf and gproxy exclusivity
        if (QObject::sender()==ui->checkBox_pfEnable_latest && ui->checkBox_gproxy_latest->isChecked()) {
            ui->checkBox_gproxy_latest->setChecked(false);
            settings.setValue(config->W3_KEY_LATEST + "/gproxy", "0");
        }
        if (QObject::sender()==ui->checkBox_gproxy_latest && ui->checkBox_pfEnable_latest->isChecked()) {
            ui->checkBox_pfEnable_latest->setChecked(false);
            settings.setValue(config->W3_KEY_LATEST + "/pfEnable", "0");
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

//Handle DotA options
void MainWindow::handleCheckboxDota(bool checked)
{
    QSettings settings(config->DOTA_CONFIG_PATH, QSettings::IniFormat);
    QStringList tokens = QObject::sender()->objectName().split("_");

    if (tokens.size() != 4 || tokens[1]!="dota") {
        return;
    }
    // checkBox_dota_[group]_[option] e.g. checkBox_dota_GAMEOPTIONS_WideScreen
    QString group = tokens[2];
    QString option = tokens[3];

    settings.setValue(group + "/" + option, QVariant(checked).toString());
}

//Handle w3l options
void MainWindow::handleCheckboxW3l(bool checked)
{
    // checkBox_w3l_[126/latest]_option

    QStringList tokens = QObject::sender()->objectName().split("_");

    if (tokens.size() != 4) {
        return;
    }

    QString configPath = tokens[2] == "126" ? config->W3l_CONFIG_PATH_126 : config->W3l_CONFIG_PATH_LATEST;

    QSettings settings(configPath, QSettings::IniFormat);
    QString option = tokens[3];

    if (option=="lobby") {
         settings.setValue("DOTA/lobby_overlay_enabled", QVariant(checked).toString());
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
            qDebug() << "checkBox_"+option_name + "_" + postfix;
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

   //Pf and gproxy exclusivity
   if (ui->checkBox_gproxy_latest->isChecked()) {
       ui->checkBox_pfEnable_latest->setChecked(false);
   }
   if (ui->checkBox_pfEnable_latest->isChecked()) {
       ui->checkBox_gproxy_latest->setChecked(false);
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

//Clear path for W3 latest
void MainWindow::on_pushButton_warLatestClear_clicked()
{
    QSettings settings(config->XPAM_CONFIG_PATH, QSettings::IniFormat);
    setNewW3PathSetting(config->W3_KEY_LATEST, &settings, "");
}

//Set new W3 path for 1.26
void MainWindow::on_pushButton_war126Path_clicked()
{
    showW3PathDialog(config->W3_KEY_126);
}

//Clear path for W3 1.26
void MainWindow::on_pushButton_war126Clear_clicked()
{
    QSettings settings(config->XPAM_CONFIG_PATH, QSettings::IniFormat);
    setNewW3PathSetting(config->W3_KEY_126, &settings, "");
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

    ui->tabWidget->setCurrentIndex(5);
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

    if (w3path != "") {
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
    }

    return true;
}

void MainWindow::quit() {
    Logger::log("Quitting due to restart", config);
    QApplication::quit();
}

void MainWindow::on_checkBoxUseGproxy126Toggled(bool checked) {
    UNREFERENCED_PARAMETER(checked);
    ui->checkBox_gproxy_126->setChecked(true);
}

void MainWindow::on_pushButton_DotaConfig_clicked() {
    QString cfg = config->DOTA_CONFIG_PATH;
    QFile f(cfg);
    if (f.exists()) {
        QDesktopServices::openUrl(QUrl("file:///"+cfg));
    }
    else {
        QMessageBox mb(QMessageBox::Critical, "No dota.config.ini",
           "There is no dota.config.ini in your W3 folder.",
           QMessageBox::Ok);
         mb.exec();
    }
}

void MainWindow::on_pushButton_login_clicked()
{
    doLogin();
}

void MainWindow::initLogin() {
    QSettings settings(config->XPAM_CONFIG_PATH, QSettings::IniFormat);
    QString username = settings.value("username", "").toString();
    QString secret = settings.value("secret", "").toString();
    if (username=="" || secret=="") {
        ui->label_online->hide();
        ui->pushButton_diff_account->hide();
    }
    else {
        bool auth = Rest::authenticate(username, secret);
        if (auth) {
            ui->label_offline->hide();
            ui->lineEdit_username->hide();
            ui->lineEdit_password->hide();
            ui->pushButton_login->hide();

            ui->pushButton_diff_account->show();
            ui->label_online->show();
            ui->label_online->setText("<html><head/><body><p>You are currently <span style=\" color:#55aa00;\">online</span> as <span style=\"color: rgb(0, 170, 255);\">"+username+"</span></p></body></html>");
        }
        else {
            ui->label_online->hide();
            ui->pushButton_diff_account->hide();
            status("Failed to login on startup");
        }
    }
}

void MainWindow::on_pushButton_diff_account_clicked()
{
    ui->lineEdit_username->show();
    ui->lineEdit_password->show();
    ui->pushButton_login->show();
    ui->pushButton_diff_account->hide();
}

/*void MainWindow::rewriteGproxyCfg(QString key, QString value) {

    QFile gpCfg(config->GPROXY_CONFIG_PATH_CFG);

    if (gpCfg.open(QIODevice::ReadOnly)) {
       QTextStream in(&gpCfg);
       QStringList lines;

       bool updated=false;

       while (!in.atEnd()) {
          QString line = in.readLine();
          if (line.startsWith(key)) {
              lines << key+" = "+value;
              updated=true;
          }
          else {
              lines << line;
          }
       }
       if (!updated) {
           lines << key+" = "+value;
       }

       gpCfg.close();

       if (gpCfg.open(QFile::WriteOnly | QFile::Truncate)) {
           QTextStream out(&gpCfg);
           for (int i = 0; i < lines.size(); ++i) {
               out << lines.at(i) << "\r\n";
           }
           gpCfg.close();
       }
    }
}*/

void MainWindow::on_lineEdit_username_returnPressed()
{
    doLogin();
}

void MainWindow::on_lineEdit_password_returnPressed()
{
    doLogin();
}

void MainWindow::doLogin() {
    QString username = ui->lineEdit_username->text();
    QString pass = ui->lineEdit_password->text().toLower();

    if (username=="" || pass=="") {
        QMessageBox mb(QMessageBox::Critical, "Failed to login", "Empty username or password.", QMessageBox::Ok);
        mb.exec();
    }

    Bnethash bh;
    QString hashStr = bh.getHashString(pass);

    QString hash256 = QString(QCryptographicHash::hash(hashStr.toLocal8Bit(), QCryptographicHash::Sha256).toHex());

    bool auth = Rest::authenticate(username, hash256);
    if (auth) {
        ui->label_offline->hide();
        ui->lineEdit_username->hide();
        ui->lineEdit_password->hide();
        ui->pushButton_login->hide();

        ui->pushButton_diff_account->show();
        ui->label_online->show();
        ui->label_online->setText("<html><head/><body><p>You are currently <span style=\" color:#55aa00;\">online</span> as <span style=\"color: rgb(0, 170, 255);\">"+username+"</span></p></body></html>");

        QSettings settings(config->XPAM_CONFIG_PATH, QSettings::IniFormat);
        settings.setValue("username", ui->lineEdit_username->text());
        settings.setValue("secret", hash256);

        QSettings settingsGp(config->GPROXY_CONFIG_PATH, QSettings::IniFormat);
        settingsGp.setValue("pf_username", ui->lineEdit_username->text());
        settingsGp.setValue("pf_secret", hash256);
    }
    else {
        ui->label_online->hide();
        ui->pushButton_diff_account->hide();
        QMessageBox mb(QMessageBox::Critical, "Failed to login", "Failed to login due to bad username or password.", QMessageBox::Ok);
        mb.exec();
    }
}

//Temporary things which need to be run due to insufficient updater capabilities
void MainWindow::tmpPlumbing() {
    QFile f1(config->EUROPATH+"/euro3icons.bni");
    if (f1.exists()) {
        QFile f11(config->APPDATA_BNET_DOWNLOADS+"/euro3icons.bni");
        if (f11.exists()) {
            f11.remove();

        }
        bool f1b = f1.rename(config->APPDATA_BNET_DOWNLOADS+"/euro3icons.bni");
        if (f1b) qDebug() << "f1 renamed";
        else qDebug() << "f1 renamed failed";
    }
    else {
        Logger::log("Ignoring f1, foes not exist", config);
    }

    QFile f2(config->EUROPATH+"/bncache.dat");
    if (f2.exists()) {
        QFile f22(config->APPDATA_BNET_CACHE+"/bncache.dat");
        if (f22.exists()) {
            f22.remove();
        }
        bool f2b = f2.rename(config->APPDATA_BNET_CACHE+"/bncache.dat");
        if (f2b) qDebug() << "f2 renamed";
        else qDebug() << "f2 renamed failed";
    }
    else {
        Logger::log("Ignoring f2, foes not exist", config);
    }
}

void MainWindow::on_pushButtonGPNOTEPAD_CFG_clicked()
{
    QDesktopServices::openUrl(QUrl("file:///"+config->EUROPATH+"/gproxy.ini"));
}

void MainWindow::on_pushButtonClientConfig_clicked()
{
    QDesktopServices::openUrl(QUrl("file:///"+config->EUROPATH+"/xpam.ini"));
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (index==2) {
        //W3l config
        qDebug() << config->W3l_CONFIG_PATH_126;
        QSettings settingsW3l126(config->W3l_CONFIG_PATH_126, QSettings::IniFormat);
        bool lobby = settingsW3l126.value("DOTA/lobby_overlay_enabled", "false").toBool();
        ui->checkBox_w3l_126_lobby->setChecked(lobby);
    }
    else if (index==3) {
        //DotA config
        QSettings settingsDota(config->DOTA_CONFIG_PATH, QSettings::IniFormat);
        bool goWideScreen = settingsDota.value("GAMEOPTIONS/WideScreen", "false").toBool();
        ui->checkBox_dota_GAMEOPTIONS_WideScreen->setChecked(goWideScreen);
    }
}

void MainWindow::setupWebLinkProtoHandlers() {
     Registry r;
     bool s = r.createWebProtoKeys(config->EUROPATH+"/xpam.exe");
     if (s) Logger::log("Web link proto initialized", config);
     else Logger::log("Web link proto not initialized", config);
}

void MainWindow::showServerStatus() {
    qDebug() << "server status update";
    QString status = Rest::getSeverStatus();
    if (""!=status) {
        ui->label_serverStatus->setText(status);
        ui->label_serverStatus->setStyleSheet("QLabel {color:#55aa00}");
    }
    else {
        ui->label_serverStatus->setText("Could not fetch server status.");
        ui->label_serverStatus->setStyleSheet("QLabel {color:red}");
    }
}

void MainWindow::on_pushButton_download_128_clicked()
{
    if (this->currentTorrentVersionDl==0) {
        this->currentTorrentVersionDl = 128;
        this->currentTorrentDlButton = ui->pushButton_download_128;
        ui->pushButton_download_126->setDisabled(true);
        this->initTorrentDownload();
    }
    else {
        //cancel
        qDebug() << "cancel";
        emit cancelTorrentDownload();
    }
}

void MainWindow::on_pushButton_download_126_clicked()
{
    if (this->currentTorrentVersionDl==0) {
        this->currentTorrentVersionDl = 126;
        this->currentTorrentDlButton = ui->pushButton_download_126;
        ui->pushButton_download_128->setDisabled(true);
        this->initTorrentDownload();
    }
    else {
        //cancel
        emit cancelTorrentDownload();
    }
}

void MainWindow::initTorrentDownload()
{
    QString magnetLink = config->W3_MAGNET_128;
    if (this->currentTorrentVersionDl == 126) {
        magnetLink=config->W3_MAGNET_126;
    }

    tdl=new TorrentDownloader(magnetLink, config->APPDATA);
    tdlt=new QThread();
    tdl->moveToThread(tdlt);

    connect(tdl, SIGNAL(progress(int)), this, SLOT(handleTorrentProgress(int)));
    connect(tdl, SIGNAL(working(bool)), this, SLOT(handleTorrentWorking(bool)));
    connect(tdl, SIGNAL(finished(int)), this, SLOT(handleTorrentFinished(int)));
    connect(tdl, SIGNAL(sendLine(QString)), this, SLOT(logUpdate(QString)));
    connect(tdlt, SIGNAL(started()), tdl, SLOT(download()));
    connect(this, SIGNAL(cancelTorrentDownload()), tdl, SLOT(cancelDownload()));

    this->currentTorrentDlButton->setStyleSheet("color: green");

    tdlt->start();
}

void MainWindow::handleTorrentWorking(bool finished)
{
    if (finished) return;

    QString currentText = this->currentTorrentDlButton->text();
    if (currentText.endsWith("...")) {
        currentText.remove(currentText.length()-3, 3);
        this->currentTorrentDlButton->setText(currentText+".  ");
    }
    else if (currentText.endsWith("Download")) {
        this->currentTorrentDlButton->setText(currentText+".  ");
    }
    else if (currentText.endsWith(".. ")) {
        currentText.remove(currentText.length()-3, 3);
        this->currentTorrentDlButton->setText(currentText+"...");
    }
    else if (currentText.endsWith(".  ")) {
        currentText.remove(currentText.length()-3, 3);
        this->currentTorrentDlButton->setText(currentText+".. ");
    }
}

void MainWindow::handleTorrentProgress(int percent)
{
    QString currentText = this->currentTorrentDlButton->text();
    if (!currentText.startsWith("(")) {
        currentText = "(0%) "+currentText;
    }
    QRegularExpression pattern("\\((\\d+%)\\)");
    QString resultString = currentText.replace(pattern, "("+QString::number(percent)+"%)");
    this->currentTorrentDlButton->setText(resultString);
}

void MainWindow::handleTorrentFinished(int code)
{
    if (code==2) {
        status("Download cancelled");
    }
    else if (code>0) {
        status("Download failed with error code "+QString::number(code));
    }
    this->currentTorrentVersionDl = 0;

    this->currentTorrentDlButton->setStyleSheet("color: white");
    this->currentTorrentDlButton->setText("Download");
    ui->pushButton_download_126->setDisabled(false);
    ui->pushButton_download_128->setDisabled(false);
    tdlt->quit();
    tdl->deleteLater();
    tdlt->deleteLater();

    if (code==0) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Download completed to %appdata% folder");
        msgBox.setInformativeText("Unpack the downloaded zip to a location of your choice (for example: D:/mygames/Warcraft III 1.2X), then set the game path location to that folder");
        msgBox.addButton("Open download location", QMessageBox::AcceptRole);
        msgBox.addButton("Close", QMessageBox::ActionRole);

        int choice = msgBox.exec();

        if (choice == 0) {
            QUrl url(config->APPDATA);
            QDesktopServices::openUrl(url);
        }
    }
}


