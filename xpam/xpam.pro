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
    updater.cpp

HEADERS  += mainwindow.h \
    registry.h \
    util.h \
    gproxy.h \
    config.h \
    winutils.h \
    downloader.h \
    updater.h

FORMS    += mainwindow.ui

RESOURCES += \
    xpam.qrc

OTHER_FILES += \
    update.json

CONFIG += static

CONFIG(debug, debug|release){
    DESTDIR = $$PWD/../Debug
    OBJECTS_DIR = $$PWD/../Debug
    MOC_DIR = $$PWD/../Debug
}

CONFIG(release, debug|release){
    DESTDIR = $$PWD/../Release
    OBJECTS_DIR = $$PWD/../Release
    MOC_DIR = $$PWD/../Release
}

#quazip
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/quazip/ -lquazip
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/quazip/ -lquazipd

INCLUDEPATH += $$PWD/quazip
DEPENDPATH += $$PWD/quazip

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/quazip/quazip.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/quazip/quazipd.lib

DEFINES += NOMINMAX
DEFINES += QUAZIP_STATIC
INCLUDEPATH += C:\git\qt5\qt5\qtbase\src\3rdparty\zlib
#end quazip

#CONFIG -= embed_manifest_exe

#QMAKE_POST_LINK += upx.exe ../Release-static/release/xpam.exe
