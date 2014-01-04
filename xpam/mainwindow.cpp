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
#include "QProcess"
#include "QThread"
#include "QTextStream"
#include "gproxy.h"
#include "updater.h"
#include "config.h"

QProcess * w3p=NULL;

QThread * gpt=NULL;
QThread * upt=NULL;

GProxy * gproxy=NULL;
Updater * updater=NULL;

Config * config=new Config();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    isStartupUpdate=true;
    isrestartNeeded=false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

//start w3 and gproxy
void MainWindow::on_pushButton_2_clicked()
{
    if (Util::isRunning("war3.exe")) {
        ui->statusLabel->setText("Warcraft III is already running");
        return;
    }
    if (Util::isRunning("gproxy.exe")) {
        ui->statusLabel->setText("GProxy is already running");
        return;
    }

    ui->tabWidget->setCurrentIndex(1);

    //start gproxy
    Registry reg;

    //set gproxy gateway as default
    reg.setGproxyGateways();
    //ui->debugLabel->setText(QString::number(ret));

    QString gpdir=reg.getEuroPath();
    QString gpexe="\""+gpdir+"\\gproxy.exe\"";

    ui->statusLabel->setText("Launching GProxy...");
    ui->textBrowser->append("Working directory: "+gpdir);

    gproxy=new GProxy(gpdir, gpexe);
    QObject::connect(this, SIGNAL(readStdout()), gproxy, SLOT(readStdout()));
    QObject::connect(gproxy, SIGNAL(gproxyReady()), this, SLOT(gproxyReady()));
    QObject::connect(gproxy, SIGNAL(gproxyExiting()), this, SLOT(gproxyExiting()));
    QObject::connect(gproxy, SIGNAL(sendLine(QString)), ui->textBrowser, SLOT(append(QString)), Qt::QueuedConnection);

    gpt=new QThread();

    gproxy->moveToThread(gpt);
    gpt->start();
    emit readStdout();
}

//start w3 only
void MainWindow::on_pushButton_clicked()
{    
    if (Util::isRunning("war3.exe")) {
        ui->statusLabel->setText("Warcraft III is already running");
        return;
    }

    Registry reg;

    //set normal gateway as default
    reg.setGateways();

    QString w3dir=reg.getW3dir();
    QString w3exe=w3dir+"\\w3l.exe";

    ui->statusLabel->setText("Launching Warcraft III...");

    QStringList list;
    if (ui->checkBox->isChecked()) list << "-windowed";

    w3p = new QProcess(0);
    w3p->setWorkingDirectory(w3dir);
    w3p->start(w3exe, list);
    if (!w3p->waitForStarted(5000)) {
        ui->statusLabel->setText("Could not start Warcraft: "+w3p->errorString());
        return;
    }
    ui->statusLabel->setText("Warcraft III started");
}

//start w3 when gproxy emits
void MainWindow::gproxyReady() {
    ui->textBrowser->append("EMITTED");
    if (Util::isRunning("war3.exe")) {
        ui->statusLabel->setText("Warcraft III is already running");
        return;
    }

    Registry reg;

    QString w3dir=reg.getW3dir();
    QString w3exe=w3dir+"\\w3l.exe";

    ui->statusLabel->setText("Launching Warcraft III...");

    QStringList list;
    if (ui->checkBox->isChecked()) list << "-windowed";

    w3p = new QProcess(0);
    w3p->setWorkingDirectory(w3dir);
    w3p->start(w3exe, list);
    if (!w3p->waitForStarted(5000)) {
        ui->statusLabel->setText("Could not start Warcraft: "+w3p->errorString());
        return;
    }
    ui->statusLabel->setText("Warcraft III started");
}

void MainWindow::gproxyExiting() {
    ui->statusLabel->setText("GProxy has closed");
    gproxy->deleteLater();
    gpt->deleteLater();
    ui->tabWidget->setCurrentIndex(0);
}

//update at startup
void MainWindow::checkUpdates(){

    //disable beta button or all kind of hell will ensue
    ui->pushButton_3->setDisabled(true);

    //clean the update log on every startup
    QFile log(config->EUROPATH+"\\xpam.log");
    log.open(QFile::WriteOnly | QFile::Truncate);
    log.close();

    ui->tabWidget->setCurrentIndex(2);
    lockTabs(ui->tabWidget->currentIndex());

    updater=new Updater(config, false);

    QObject::connect(this, SIGNAL(startUpdate()), updater, SLOT(startUpdate()));
    QObject::connect(updater, SIGNAL(updateFinished(bool, bool)), this, SLOT(updateFinished(bool, bool)));
    QObject::connect(updater, SIGNAL(sendLine(QString)), this, SLOT(logUpdate(QString)));
    QObject::connect(updater, SIGNAL(sendLine(QString)), ui->textBrowserUpdate, SLOT(append(QString)), Qt::QueuedConnection);
    QObject::connect(updater, SIGNAL(modifyLastLine(QString)), this, SLOT(modifyLastLineSlot(QString)));
    QObject::connect(updater, SIGNAL(hideSplashScreen()), this, SLOT(hideSplashScreen()));

    upt=new QThread();
    updater->moveToThread(upt);
    upt->start();
    emit startUpdate();
}

//beta update
void MainWindow::on_pushButton_3_clicked()
{
    isStartupUpdate=false;
    ui->textBrowserUpdate->clear();

    if (config->BETAPIN!=ui->betapinbox->text()) return;
    lockTabs(ui->tabWidget->currentIndex());

    updater=new Updater(config, true);

    QObject::connect(this, SIGNAL(startUpdate()), updater, SLOT(startUpdate()));
    QObject::connect(updater, SIGNAL(updateFinished(bool, bool)), this, SLOT(updateFinished(bool, bool)));
    QObject::connect(updater, SIGNAL(sendLine(QString)), this, SLOT(logUpdate(QString)));
    QObject::connect(updater, SIGNAL(sendLine(QString)), ui->textBrowserUpdate, SLOT(append(QString)), Qt::QueuedConnection);
    QObject::connect(updater, SIGNAL(modifyLastLine(QString)), this, SLOT(modifyLastLineSlot(QString)));

    upt=new QThread();
    updater->moveToThread(upt);
    upt->start();
    emit startUpdate();
}

//ok tells us if there was a critical error
//utd tells us if client is up to date
void MainWindow::updateFinished(bool ok, bool utd) {

    upt->exit();
    updater->deleteLater();
    upt->deleteLater();

    if (utd) {
        ui->tabWidget->setCurrentIndex(0);
        ui->statusLabel->setText("Client is up to date");
        if (isStartupUpdate) emit updateCheckFinished();
        unlockTabs();
    }
    else {
        if (ok) {
            ui->textBrowserUpdate->append("Client was updated");

            QFile changelog(config->EUROPATH+"\\changelog.txt");
            changelog.open(QFile::ReadOnly);
            if (changelog.isOpen()){
                QString text(changelog.readAll());
                QMessageBox msgBox;
                msgBox.setText(text);
                msgBox.exec();
            }
            if (isrestartNeeded){
                QStringList args;
                args << "/c";
                args << "update.bat";
                QProcess::startDetached("C:\\Windows\\system32\\cmd.exe", args);
            }
            else {
                unlockTabs();
            }
        }
        else {
            unlockTabs();
            ui->textBrowserUpdate->append("Update failed. Check the log or update tab to find out the reason.");
            ui->statusLabel->setText("Update failed due to critical error");
        }
    }
}

//this slot is only connected for startup update check
//signal emitted when there is an update avalible
//so we hide splash screen to see progress
void MainWindow::hideSplashScreen() {
    emit updateCheckFinished();
}

void MainWindow::logUpdate(QString line) {
    QFile log(config->EUROPATH+"\\xpam.log");
    log.open(QFile::WriteOnly | QFile::Append | QFile::Text);
    if (log.isOpen()) {
        QTextStream out(&log);
        out << line << "\n";
        log.close();
    }
    else {
        ui->statusLabel->setText("Can't write to log file");
    }
}

void MainWindow::restartNeeded(){
    isrestartNeeded=true;
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

void MainWindow::modifyLastLineSlot(QString line) {
    removeLastLine();
    ui->textBrowserUpdate->append(line);
}

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
