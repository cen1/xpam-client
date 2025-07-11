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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QString"
#include "QMouseEvent"
#include "QSettings"
#include "QPushButton"
//#include "QWebView"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void readStdout();              //starts the gproxy
    void startW3();                 //starts w3
    void startUpdate();             //starts the update
    void updateCheckFinished();     //terminates the splash screen event loop
    void cancelUpdate();
    void terminateCurrentGproxyInstance();
    void cancelTorrentDownload();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void checkUpdates();
    bool checkW3Updates();
    bool updatesEnabled;
    bool checkW3PathUnicode();
    void setNewW3PathSetting(QString modeKey, QSettings *settings, QString newPath);
    
private slots:
    void on_pushButtonGWG_clicked();
    void on_pushButtonGWD_clicked();
    void on_pushButtonBU_clicked();
    void handleCheckBoxGProxy(bool checked);
    void handleSpinBoxGProxy(int value);
    void handleCheckboxXpam(bool checked);
    void handleCheckboxClient(bool checked);
    void handleCheckboxDota(bool checked);
    void handleCheckboxW3l(bool checked);

    void initGproxyOptions();
    void initXpamOptions();
    void initClientOptions();

    void on_pushButtonGPCL_clicked();
    void on_pushButtonGPNOTEPAD_clicked();
    void on_pushButtonClientLog_clicked();

    bool checkModeAvailability(QString modeKey, bool shouldWarnUser=false);
    bool changeActiveMode(QString modeKey, bool shouldWarnUser=false);

    void quit();

    bool showW3PathDialog(QString modeKey);

    void on_pushButton_warLatestPath_clicked();

    void on_pushButton_war126Path_clicked();

    void on_checkBoxUseGproxy126Toggled(bool checked);

    //void on_pushButton_updateW3_released();

    //void on_pushButton_updateW3_clicked();

    void on_pushButton_warLatestClear_clicked();
    void on_pushButton_war126Clear_clicked();

    void on_pushButton_DotaConfig_clicked();

    void on_pushButton_login_clicked();

    void on_pushButton_diff_account_clicked();

    void on_lineEdit_username_returnPressed();

    void on_lineEdit_password_returnPressed();

    void on_pushButtonGPNOTEPAD_CFG_clicked();

    void on_pushButtonClientConfig_clicked();

    void on_tabWidget_currentChanged(int index);

    void showServerStatus();

    void on_pushButton_download_128_clicked();

    void on_pushButton_download_126_clicked();

public slots:
    void gproxyReady(QString w3Exename, bool ft);
    void gproxyExiting(bool killedForcefully);
    void receiveLine(QString line);
    void receiveLineW3(QString line);
    void w3Exited();

    void updateFinished(bool restartNeeded, bool ok, bool isUpToDate, bool retry, int type);
    void hideSplashScreen();
    void logUpdate(QString line);
    void modifyLastLineSlot(QString line);
    void handleTorrentWorking(bool finished);
    void handleTorrentProgress(int percent);
    void handleTorrentFinished(int code);

private:
    Ui::MainWindow *ui;

    void postUpdate();
    void lockTabs(int except);
    void unlockTabs();
    void removeLastLine();
    void status(QString status);
    void initLogin();

    bool isStartupUpdate;
    QTimer *serverStatusTimer;

    //window moving
    bool down;
    QPoint lastPos;

    //min and max
    bool ismax;
    QPoint normalpos;
    QSize normalsize;
    int lastCheckedMap=0;

    void startW3AndGproxy(bool ft=false);
    void runW3(bool ft=false);

    void diffW3Update(QString version);
    int checkMapUpdates();
    int checkW3LoaderFiles();
    //void rewriteGproxyCfg(QString username, QString secret);
    void tmpPlumbing();
    void doLogin();
    void setupWebLinkProtoHandlers();
    void initTorrentDownload();

    bool updateInProgress;
    QVector<QJsonObject> UPDATE_MAPS;
    int w3LoaderCheckCounter = 1;
    int currentTorrentVersionDl=0;
    QPushButton * currentTorrentDlButton=nullptr;

    //QWebView *m_Mview;

protected:
    //void mousePressEvent(QMouseEvent *event);
    //void mouseReleaseEvent(QMouseEvent *event);
    //void mouseMoveEvent(QMouseEvent *event);
};

#endif // MAINWINDOW_H
