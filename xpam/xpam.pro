#-------------------------------------------------
#
# Project created by QtCreator 2013-11-23T14:33:58
#
#-------------------------------------------------

QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = xpam
TEMPLATE = app

RC_FILE = xpam.rc

SOURCES += main.cpp\
        mainwindow.cpp \
    registry.cpp \
    gproxy.cpp \
    config.cpp \
    downloader.cpp \
    updater.cpp \
    w3.cpp

HEADERS  += mainwindow.h \
    registry.h \
    util.h \
    gproxy.h \
    config.h \
    winutils.h \
    downloader.h \
    updater.h \
    w3.h

FORMS    += mainwindow.ui

RESOURCES += \
    xpam.qrc

OTHER_FILES += \
    update.json \
    update.bat

CONFIG += static

#quazip
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/quazip/ -lquazip
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/quazip/ -lquazipd

INCLUDEPATH += $$PWD/quazip
DEPENDPATH += $$PWD/quazip

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/quazip/quazip.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/quazip/quazipd.lib

DEFINES += NOMINMAX
DEFINES += QUAZIP_STATIC
INCLUDEPATH += C:\git\qt5win32-msvc2010\qt5\qtbase\src\3rdparty\zlib

#end quazip

#CONFIG -= embed_manifest_exe

#win32:CONFIG(release, debug|release): QMAKE_POST_LINK += cd $$PWD/release && copy /Y \"xpam.exe\" \"$$PWD/../../installer/installer/data/xpam.exe\" && upx \"$$PWD/../../installer/installer/data/xpam.exe\"
