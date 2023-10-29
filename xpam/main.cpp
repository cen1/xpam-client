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
#include <Qt>
#include <QApplication>
#include "QSplashScreen"
#include "QWebEngineProfile"
#include "QWebEngineSettings"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QIcon(":/favicon.ico"));

    //Mm
    QWebEngineSettings *web_settings = QWebEngineProfile::defaultProfile()->settings();
    web_settings->setAttribute(QWebEngineSettings::ShowScrollBars, true);
    web_settings->setAttribute(QWebEngineSettings::PdfViewerEnabled, false);
    web_settings->setAttribute(QWebEngineSettings::WebGLEnabled, false);
    web_settings->setAttribute(QWebEngineSettings::LocalContentCanAccessFileUrls, false);
    web_settings->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, false);
    web_settings->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows, false);

    //splash screen to hide the few seconds of update check
    QPixmap pixmap(":/splash.png");
    QSplashScreen splash(pixmap);
    splash.show();
    splash.showMessage("Checking for updates...", Qt::AlignLeft, Qt::white);

    if (w.checkW3PathUnicode()) {
        if (w.updatesEnabled) {
            w.checkUpdates();

            //wait for update check to finish
            QEventLoop loop;
            QObject::connect(&w, SIGNAL(updateCheckFinished()), &loop, SLOT(quit()));
            loop.exec();
        }
    }

    //Uncomment for frameless window
    //w.setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    w.show();
    splash.finish(&w);
    
    return a.exec();
}
