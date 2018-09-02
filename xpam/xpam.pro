#-------------------------------------------------
#
# Project created by QtCreator 2013-11-23T14:33:58
#
#-------------------------------------------------

QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01
DEFINES += _ATL_XP_TARGETING
DEFINES += PSAPI_VERSION=1 #_DEVELOPMENT

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
    w3.cpp \
    test.cpp \
    mpq.cpp \
    patcher.cpp

HEADERS  += mainwindow.h \
    registry.h \
    util.h \
    gproxy.h \
    config.h \
    winutils.h \
    downloader.h \
    updater.h \
    w3.h \
    test.h \
    mpq.h \
    logger.h \
    patcher.h

FORMS    += mainwindow.ui

RESOURCES += \
    xpam.qrc

OTHER_FILES += \
    update.json \
    update.bat \
    update.json.example

### DEFINES
#CONFIG += static
#DEFINES += QUAZIP_STATIC
DEFINES += NOMINMAX
DEFINES += _UNICODE
DEFINES += UNICODE

### QUAZIP
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/quazip/ -lquazip
win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/quazip/ -lquazip

INCLUDEPATH += $$PWD/quazip
DEPENDPATH += $$PWD/quazip

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/quazip/quazip.lib
win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/quazip/quazip.lib

### ZLIB
INCLUDEPATH +=$$PWD/zlib
DEPENDPATH += $$PWD/zlib

## STORMLIB
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/stormlib/ -lStormLib
win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/stormlib/ -lStormLib

INCLUDEPATH += $$PWD/stormlib
DEPENDPATH += $$PWD/stormlib

## WINDOWS
LIBS += version.lib

# Fix for UI changes not taking effect
UI_DIR = $$PWD

### MANIFEST

#win32 {
#    CONFIG -= embed_manifest_exe
#    WINSDK_DIR = C:/Program Files (x86)/Microsoft SDKs/Windows/v7.0A/Bin
#    WIN_PWD = $$replace(PWD, /, \\)
#    OUT_PWD_WIN = $$replace(OUT_PWD, /, \\)
#    QMAKE_POST_LINK = "$$WINSDK_DIR/mt.exe -manifest $$quote($$WIN_PWD\\$$basename(TARGET).manifest) -outputresource:$$quote($$OUT_PWD_WIN\\$${DESTDIR_TARGET};1)"
#}

win32 {
    CONFIG += embed_manifest_exe
    QMAKE_LFLAGS_WINDOWS += /MANIFESTUAC:level=\'requireAdministrator\'
}

#win32:CONFIG(release, debug|release): QMAKE_POST_LINK += cd \"C:/git/xpam/build-xpam-Qt_5_2_static_msvc2010-Release\" && copy /Y \"xpam.exe\" \"$$PWD/../../installer/installer/data/xpam.exe\" && upx \"$$PWD/../../installer/installer/data/xpam.exe\"


DEFINES += PORTABLE
