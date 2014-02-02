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
#include "QDesktopWidget"
#include "gproxy.h"
#include "w3.h"
#include "updater.h"
#include "config.h"
//#include "QSslSocket"

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

//start w3 and gproxy
void MainWindow::on_pushButtonSWGP_clicked()
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

    //set gproxy gateway as default
    Registry::setGproxyGateways();

    QString gpdir=config->EUROPATH;
    QString gpexe="\""+gpdir+"\\gproxy.exe\"";

    status("Launching GProxy...");
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
void MainWindow::on_pushButtonSWOGP_clicked()
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
    if (ui->checkBoxWindowed->isChecked()) list << "-windowed";

    w3=new W3(w3dir, w3exe, list);
    QObject::connect(this, SIGNAL(startW3()), w3, SLOT(startW3()));
    QObject::connect(w3, SIGNAL(w3Exited()), this, SLOT(w3Exited()));

    w3t=new QThread();

    w3->moveToThread(w3t);
    w3t->start();
    emit startW3();
}

//start w3 when gproxy emits
void MainWindow::gproxyReady() {
    ui->textBrowser->append("EMITTED");
    if (Util::isRunning("war3.exe")) {
        status("Warcraft III is already running");
        return;
    }

    QString w3dir=config->W3PATH;
    QString w3exe=w3dir+"\\w3l.exe";

    status("Launching Warcraft III...");

    QStringList list;
    if (ui->checkBoxWindowed->isChecked()) list << "-windowed";

    w3=new W3(w3dir, w3exe, list);
    QObject::connect(this, SIGNAL(startW3()), w3, SLOT(startW3()));
    QObject::connect(w3, SIGNAL(w3Exited()), this, SLOT(w3Exited()));

    w3t=new QThread();

    w3->moveToThread(w3t);
    w3t->start();
    emit startW3();
}

void MainWindow::gproxyExiting() {
    status("GProxy has closed");
    gpt->exit();
    gproxy->deleteLater();
    gpt->deleteLater();

    ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::w3Exited() {
    status("W3 closed");
    w3t->exit();
    w3->deleteLater();
    w3t->deleteLater();
}

//update at startup
void MainWindow::checkUpdates(){

    //disable beta button or all kind of hell will ensue
    ui->pushButtonBU->setDisabled(true);

    //clean the update log on every startup
    QFile log(config->EUROPATH+"\\xpam.log");
    log.open(QFile::WriteOnly | QFile::Truncate);
    log.close();

    ui->tabWidget->setCurrentIndex(2);
    lockTabs(ui->tabWidget->currentIndex());

    updater=new Updater(config, false);

    QObject::connect(this, SIGNAL(startUpdate()), updater, SLOT(startUpdate()));
    QObject::connect(updater, SIGNAL(updateFinished(bool, bool, bool)), this, SLOT(updateFinished(bool, bool, bool)));
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
void MainWindow::on_pushButtonBU_clicked()
{
    isStartupUpdate=false;
    ui->textBrowserUpdate->clear();
    /*if (QSslSocket::supportsSsl()) status("SSL supported");
    else status("SSL not supported");*/

    if (config->BETAPIN!=ui->betapinbox->text()) return;
    lockTabs(ui->tabWidget->currentIndex());

    updater=new Updater(config, true);

    QObject::connect(this, SIGNAL(startUpdate()), updater, SLOT(startUpdate()));
    QObject::connect(updater, SIGNAL(updateFinished(bool, bool, bool)), this, SLOT(updateFinished(bool, bool, bool)));
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
void MainWindow::updateFinished(bool restartNeeded, bool ok, bool utd) {
    ui->textBrowserUpdate->append("Updater finished");
    hideSplashScreen();

    upt->exit();
    updater->deleteLater();
    upt->deleteLater();

    if (utd) {
        ui->tabWidget->setCurrentIndex(0);
        status("Client is up to date");
        if (isStartupUpdate) emit updateCheckFinished();
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

//this slot is only connected for startup update check
//signal emitted when there is an update avalible
//so we hide splash screen to see progress
void MainWindow::hideSplashScreen() {
    emit updateCheckFinished();
}

//update log in case program crashes and you can't see the text browser for errors
void MainWindow::logUpdate(QString line) {
    QFile log(config->EUROPATH+"\\xpam.log");
    log.open(QFile::WriteOnly | QFile::Append | QFile::Text);
    if (log.isOpen()) {
        QTextStream out(&log);
        out << line << "\n";
        log.close();
    }
    else {
        status("Can't write to log file");
    }
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

//deletes last in in text browser and appends a new one
void MainWindow::modifyLastLineSlot(QString line) {
    removeLastLine();
    ui->textBrowserUpdate->append(line);
}

//deletes last line in text browser
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

//write to status bar
void MainWindow::status(QString status) {
    ui->statusBar->showMessage(status, 10000);
}


//close, max, min
void MainWindow::on_closeButton_clicked()
{
    QApplication::quit();
}

void MainWindow::on_maxButton_clicked()
{
    if (!isMaximized()) {
        showMaximized();
    }
    else {
        this->showNormal();
    }
}

void MainWindow::on_minButton_clicked()
{
    this->showMinimized();
}

//window moving handlers
void MainWindow::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    down = true;
    lastPos = event->globalPos();
  }

  QWidget::mousePressEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
  down = false;
  QWidget::mouseReleaseEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  if (down) {
    QPoint curPos = event->globalPos();
    if (curPos != lastPos) {
      QPoint diff = (lastPos - curPos);
      move(pos() - diff);
      lastPos = curPos;
    }
  }

  QWidget::mouseMoveEvent(event);
}
