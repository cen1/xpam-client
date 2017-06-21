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

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void checkUpdates();
    bool updatesEnabled;
    
private slots:
    void on_pushButtonSWGP_clicked();
    void on_pushButtonSWOGP_clicked();
    void on_pushButtonBU_clicked();
    //void on_closeButton_clicked();
    //void on_maxButton_clicked();
    //void on_minButton_clicked();
    void handleCheckbox(bool checked);
    void handleCheckboxClient(bool checked);
    void initGproxyOptions();
    void initClientOptions();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void on_pushButton_w3path_clicked();

public slots:
    void gproxyReady();
    void gproxyExiting();
    void receiveLine(QString line);
    void w3Exited();

    void updateFinished(bool restartNeeded, bool ok, bool utd); //utd: Up To Date
    void hideSplashScreen();
    void logUpdate(QString line);
    void modifyLastLineSlot(QString line);

private:
    Ui::MainWindow *ui;

    void lockTabs(int except);
    void unlockTabs();
    void removeLastLine();
    void status(QString status);

    bool isStartupUpdate;

    //window moving
    bool down;
    QPoint lastPos;

    //min and max
    bool ismax;
    QPoint normalpos;
    QSize normalsize;

protected:
    //void mousePressEvent(QMouseEvent *event);
    //void mouseReleaseEvent(QMouseEvent *event);
    //void mouseMoveEvent(QMouseEvent *event);
};

#endif // MAINWINDOW_H
