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

    //Check w3 version
    QString w3version = Winutils::getFileVersion(config->W3PATH+"\\war3.exe");
    if (w3version != config->W3_VERSION_LATEST) {
        QMessageBox msgBox;
        msgBox.setText("You need to manually update your Warcraft 3 version. See forum for instructions. Found version: "+w3version+" but needs version "+config->W3_VERSION_LATEST);

        msgBox.exec();
    }
    else if (w3version==config->W3_VERSION_LATEST) {
        /* Manual folder moving not necessary, it is done by w3
        QDir doc(config->DOCMAPPATH);
        if (!doc.exists()) {
            QMessageBox msgBox;
            msgBox.setText("Version 1.28.1 moves writable folders such as Maps and ScreenShots to user Documents folder. Would you like the client to move them for you? (BACKUP YOUR GAME FIRST!)");
            QPushButton *yes = msgBox.addButton(tr("Yes, move the folders"), QMessageBox::ActionRole);
            QPushButton *no = msgBox.addButton(QMessageBox::Abort);

            msgBox.exec();

            if (msgBox.clickedButton() == yes) {
                QString result = Updater::moveToDocuments(config);
                logUpdate(result);
                QMessageBox msgBoxR;
                msgBoxR.setText(result);
                msgBoxR.exec();
            }
        }*/
    }

    //Add CD keys if needed
    Updater::replaceCDKeys(config);

    //Display w3 info
    ui->labelW3Path->setText("W3 path: "+config->W3PATH);
    if (w3version==config->W3_VERSION_LATEST) {
        ui->labelW3Version->setText("Detected W3 version: "+w3version+" (OK)");
    }
    else {
        ui->labelW3Version->setText("Detected W3 version: "+w3version+" (ERROR, needed: "+config->W3_VERSION_LATEST+")");
    }

    //Rename war3Patch.mpq to war3Mod.mpw as of 1.28.2
    Updater::renamePatchMpq(config);

    //Enable or disable DotA gateway
    if (config->USE_DUAL_VERSION) {
        ui->pushButtonGWD->setEnabled(true);
    }
    else {
        ui->pushButtonGWD->setEnabled(false);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

//GProxy gateway, Start w3 and gproxy
void MainWindow::on_pushButtonGWG_clicked()
{
    //hard WINAPI checks for w3 and gproxy running, all kind of problems if they are...
    if (Util::isRunning("war3.exe")) {
        status("Warcraft III is already running");
        return;
    }
    if (Util::isRunning("gproxy.exe")) {
        status("GProxy is already running");
        return;
    }

    ui->tabWidget->setCurrentIndex(1);

    //preloader
    QMovie *movie = new QMovie(":/preloader.gif");
    ui->preloaderLabel1->setMovie(movie);
    ui->preloaderLabel1->movie()->start();

    //set gproxy gateway as default
    Registry::setGproxyGateways();

    QString gpdir=config->EUROPATH;
    QString gpexe="\""+gpdir+"\\gproxy.exe\"";

    status("Launching GProxy...");
    ui->labelGproxyout->setText("Working directory: "+gpdir);

    gproxy=new GProxy(gpdir, gpexe);
    gpt=new QThread();
    gproxy->moveToThread(gpt);

    QObject::connect(gpt, SIGNAL(started()), gproxy, SLOT(readStdout()));
    QObject::connect(gproxy, SIGNAL(gproxyReady()), this, SLOT(gproxyReady()));
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
    //again, hard WINAPI check
    if (Util::isRunning("war3.exe")) {
        status("Warcraft III is already running");
        return;
    }

    //set normal gateway as default
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
        on_pushButtonGWG_clicked();
    }
}

//Start w3 when gproxy emits READY state
void MainWindow::gproxyReady() {
    ui->labelGproxyout->setText("EMITTED");
    if (Util::isRunning("war3.exe")) {
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

//Update client at startup
void MainWindow::checkUpdates(){

    isStartupUpdate=true;

    //disable beta button or all kind of hell will ensue
    ui->pushButtonBU->setDisabled(true);

    ui->tabWidget->setCurrentIndex(2);
    lockTabs(ui->tabWidget->currentIndex());

    updater=new Updater(config, false);
    upt=new QThread();
    updater->moveToThread(upt);

    QObject::connect(upt, SIGNAL(started()), updater, SLOT(startUpdate()));
    QObject::connect(updater, SIGNAL(updateFinished(bool, bool, bool)), this, SLOT(updateFinished(bool, bool, bool)));
    QObject::connect(updater, SIGNAL(sendLine(QString)), this, SLOT(logUpdate(QString)));
    QObject::connect(updater, SIGNAL(sendLine(QString)), ui->textBrowserUpdate, SLOT(append(QString)), Qt::QueuedConnection);
    QObject::connect(updater, SIGNAL(modifyLastLine(QString)), this, SLOT(modifyLastLineSlot(QString)));
    QObject::connect(updater, SIGNAL(hideSplashScreen()), this, SLOT(hideSplashScreen()));

    QObject::connect(updater, SIGNAL(updateFinished(bool,bool,bool)), upt, SLOT(quit()));
    QObject::connect(updater, SIGNAL(updateFinished(bool,bool,bool)), updater, SLOT(deleteLater()));
    QObject::connect(upt, SIGNAL(finished()), upt, SLOT(deleteLater()));

    upt->start();
}

//Beta update
void MainWindow::on_pushButtonBU_clicked()
{
    isStartupUpdate=false;
    ui->textBrowserUpdate->clear();

    if (config->BETAPIN!=ui->betapinbox->text()) return;
    lockTabs(ui->tabWidget->currentIndex());

    updater=new Updater(config, true);
    upt=new QThread();
    updater->moveToThread(upt);

    QObject::connect(upt, SIGNAL(started()), updater, SLOT(startUpdate()));
    QObject::connect(updater, SIGNAL(updateFinished(bool, bool, bool)), this, SLOT(updateFinished(bool, bool, bool)));
    QObject::connect(updater, SIGNAL(sendLine(QString)), this, SLOT(logUpdate(QString)));
    QObject::connect(updater, SIGNAL(sendLine(QString)), ui->textBrowserUpdate, SLOT(append(QString)), Qt::QueuedConnection);
    QObject::connect(updater, SIGNAL(modifyLastLine(QString)), this, SLOT(modifyLastLineSlot(QString)));

    QObject::connect(updater, SIGNAL(updateFinished(bool,bool,bool)), upt, SLOT(quit()));
    QObject::connect(updater, SIGNAL(updateFinished(bool,bool,bool)), updater, SLOT(deleteLater()));
    QObject::connect(upt, SIGNAL(finished()), upt, SLOT(deleteLater()));

    upt->start();
}

//Ok tells us if there was a critical error
//Utd tells us if client is up to date
void MainWindow::updateFinished(bool restartNeeded, bool ok, bool utd) {
    ui->textBrowserUpdate->append("Updater finished");
    if (isStartupUpdate) hideSplashScreen();

    if (utd) {
        ui->tabWidget->setCurrentIndex(0);
        status("Client is up to date");
        //if (isStartupUpdate) emit updateCheckFinished();
        unlockTabs();
        ui->pushButtonBU->setEnabled(true);
    }
    else {
        if (ok) {
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
                unlockTabs();
            }
        }
        else {
            unlockTabs();
            ui->textBrowserUpdate->append("Update failed. Check the log or update tab to find out the reason.");
            status("Update failed due to critical error");
            ui->pushButtonBU->setEnabled(true);
        }
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
    const QString path = QFileDialog::getExistingDirectory(this);
    QString p = path;
    p=p.replace(QChar('/'), QChar('\\'));

    Registry reg;
    if (reg.setInstallPath(p) && reg.setW3dir(p)) {
        status("W3 path set to "+p);
    }
    else {
        status("Failed to set W3 path");
    }
}
