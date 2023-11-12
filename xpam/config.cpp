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


#include "config.h"
#include "registry.h"
#include "winutils.h"
#include <QStandardPaths>
#include <QDir>

Config::Config()
{
    VERSION_CLIENT = "1.1.0.0";

    W3_VERSION_LATEST = "1.28.5.7680";
    W3_VERSION_126 = "1.26.0.6401";

    W3_KEY_126 = "WAR3_126";
    W3_KEY_LATEST = "WAR3_LATEST";

    W3_EXENAME_126="war3.exe";
    W3_EXENAME_LATEST="Warcraft III.exe";

    BETAPIN = "1377";

//#ifdef PORTABLE
    //EUROPATH    = QDir::currentPath();
    //W3PATH      = QDir::currentPath()+"/../Warcraft III";
    //IS_PORTABLE = true;
//#else
    IS_PORTABLE = false;

    EUROPATH    = Registry::getEuroPath().replace(QChar('\\'), QChar('/'));
    XPAM_CONFIG_PATH = EUROPATH+"/xpam.ini";
    GPROXY_CONFIG_PATH = EUROPATH+"/gproxy.ini";
    //GPROXY_CONFIG_PATH_CFG = EUROPATH+"/gproxy.cfg";
    SOUNDPATH   = EUROPATH+"/sounds";

    QSettings settings(XPAM_CONFIG_PATH, QSettings::IniFormat);
    ACTIVE_MODE_KEY = settings.value("active_mode", W3_KEY_LATEST).toString();
    if (ACTIVE_MODE_KEY != W3_KEY_LATEST && ACTIVE_MODE_KEY != W3_KEY_126) {
        // active_mode always should be valid, because we are using W3_KEY_* as a ini group
        ACTIVE_MODE_KEY = W3_KEY_LATEST;
        settings.setValue("active_mode", ACTIVE_MODE_KEY);
    }
    W3PATH_126 = settings.value(W3_KEY_126 + "/path", "").toString().replace(QChar('\\'), QChar('/'));
    W3PATH_LATEST = settings.value(W3_KEY_LATEST + "/path", Registry::getW3dir()).toString().replace(QChar('\\'), QChar('/'));
    GPROXY_SERVER = settings.value("server", "server.eurobattle.net").toString();
    PLINK = EUROPATH+"/plink.exe";
    SOCKS = EUROPATH+"/proxychains_win32_x86.exe";
    SOCKS_CFG = EUROPATH+"/proxychains.conf";

    DOCPATH     = QStandardPaths::locate(QStandardPaths::DocumentsLocation, QString(), QStandardPaths::LocateDirectory)+"Warcraft III";
    DOCMAPPATH  = QStandardPaths::locate(QStandardPaths::DocumentsLocation, QString(), QStandardPaths::LocateDirectory)+"Warcraft III/Maps";
    DOCMAPPATHDL= QStandardPaths::locate(QStandardPaths::DocumentsLocation, QString(), QStandardPaths::LocateDirectory)+"Warcraft III/Maps/Download";

    MAPPATH_126  = W3PATH_126+"/Maps";
    MAPPATH_126DL= W3PATH_126+"/Maps/Download";

    PATCH       = Registry::getPatchVersion();
    APPDATA     = Winutils::getAppData()+"/Eurobattle.net";
    APPDATA_BNET_CACHE = Winutils::getAppDataLocal()+"/Blizzard/Warcraft III/BattleNet/Cache";
    APPDATA_BNET_DOWNLOADS = Winutils::getAppDataLocal()+"/Blizzard/Warcraft III/BattleNet/Downloads";
    SYSTEM      = Winutils::getSystem32();

    ASK_FOR_W3_FAST_UPDATE = true;
    HAS_QUICK_PATCH=true;

    DOTA_CONFIG_PATH = W3PATH_126+"/config.dota.ini";

    W3l_CONFIG_PATH_126 = W3PATH_126+"/w3l.ini";
    W3l_CONFIG_PATH_LATEST = W3PATH_LATEST+"/w3l.ini";

#ifdef _DEVELOPMENT
    json1 = "http://localhost:8080/update.json";
    json2 = "http://localhost:8080/update.json";
    json3 = "http://localhost:8080/update.json";
#else
    json1 = "https://xpam.pl/update2/update.json";
    json2 = "https://tools.eurobattle.net/update2/update.json";
    json3 = "https://gist.githubusercontent.com/cen1/ed211e8ed3a3039f715bc649f9cad59e/raw/update2.json";
#endif    
    // List of checkboxes which are standing for Warcraft 3 arguments
    W3_OPTIONS.append("windowed");
    W3_OPTIONS.append("fullscreen");
    W3_OPTIONS.append("opengl");
    W3_OPTIONS.append("gproxy");
    W3_OPTIONS.append("pfEnable");

    // List of XPAM options
    XPAM_OPTIONS.append("updates");

    // List of GProxy options
    GPROXY_OPTIONS.append("debug");
    GPROXY_OPTIONS.append("chatbuffer");
    GPROXY_OPTIONS.append("console");
    GPROXY_OPTIONS.append("autojoin");
    GPROXY_OPTIONS.append("telemetry");

    GPROXY_OPTIONS.append("option_sounds");
    GPROXY_OPTIONS.append("sound_1");
    GPROXY_OPTIONS.append("sound_2");
    GPROXY_OPTIONS.append("sound_3");
    GPROXY_OPTIONS.append("sound_4");
    GPROXY_OPTIONS.append("sound_5");
    GPROXY_OPTIONS.append("sound_6");
    GPROXY_OPTIONS.append("sound_7");
    GPROXY_OPTIONS.append("sound_8");
    GPROXY_OPTIONS.append("sound_9");
    GPROXY_OPTIONS.append("sound_10");
    GPROXY_OPTIONS.append("sound_11");
    GPROXY_OPTIONS.append("sound_12");

    //Quickpatch w3 versions
    W3_VERSIONS.append("1.28.0");
    W3_VERSIONS.append("1.28.1");
    W3_VERSIONS.append("1.28.2");
    W3_VERSIONS.append("1.28.4");
    W3_VERSIONS.append("1.28.5");

    W3_MAGNET_126 = "magnet:?xt=urn:btih:c2b42798b4502f1b05172a5f7eaf89bec5bd6466&dn=Warcraft_III_1.26_repack.zip&tr=udp%3a%2f%2ftracker.opentrackr.org%3a1337%2fannounce&tr=https%3a%2f%2ftracker2.ctix.cn%3a443%2fannounce&tr=https%3a%2f%2ftracker1.520.jp%3a443%2fannounce&tr=udp%3a%2f%2fopen.tracker.cl%3a1337%2fannounce&tr=udp%3a%2f%2fopentracker.i2p.rocks%3a6969%2fannounce&tr=udp%3a%2f%2fopen.demonii.com%3a1337%2fannounce&tr=udp%3a%2f%2ftracker.openbittorrent.com%3a6969%2fannounce&tr=http%3a%2f%2ftracker.openbittorrent.com%3a80%2fannounce&tr=udp%3a%2f%2fopen.stealth.si%3a80%2fannounce&tr=udp%3a%2f%2fexodus.desync.com%3a6969%2fannounce&tr=udp%3a%2f%2ftracker.torrent.eu.org%3a451%2fannounce&tr=udp%3a%2f%2fexplodie.org%3a6969%2fannounce&tr=udp%3a%2f%2ftracker1.bt.moack.co.kr%3a80%2fannounce&tr=udp%3a%2f%2ftracker.theoks.net%3a6969%2fannounce&tr=udp%3a%2f%2ftracker-udp.gbitt.info%3a80%2fannounce&tr=udp%3a%2f%2fp4p.arenabg.com%3a1337%2fannounce&tr=https%3a%2f%2ftracker.tamersunion.org%3a443%2fannounce&tr=https%3a%2f%2ftracker.gbitt.info%3a443%2fannounce&tr=http%3a%2f%2ftracker.gbitt.info%3a80%2fannounce&tr=udp%3a%2f%2fuploads.gamecoast.net%3a6969%2fannounce";
    W3_MAGNET_128 = "magnet:?xt=urn:btih:cc982e0ac9a6353dcd5432832a71446f6848baf6&dn=Warcraft_III_1.28.5_repack.zip&tr=udp%3a%2f%2ftracker.opentrackr.org%3a1337%2fannounce&tr=https%3a%2f%2ftracker2.ctix.cn%3a443%2fannounce&tr=https%3a%2f%2ftracker1.520.jp%3a443%2fannounce&tr=udp%3a%2f%2fopen.tracker.cl%3a1337%2fannounce&tr=udp%3a%2f%2fopentracker.i2p.rocks%3a6969%2fannounce&tr=udp%3a%2f%2fopen.demonii.com%3a1337%2fannounce&tr=udp%3a%2f%2ftracker.openbittorrent.com%3a6969%2fannounce&tr=http%3a%2f%2ftracker.openbittorrent.com%3a80%2fannounce&tr=udp%3a%2f%2fopen.stealth.si%3a80%2fannounce&tr=udp%3a%2f%2fexodus.desync.com%3a6969%2fannounce&tr=udp%3a%2f%2ftracker.torrent.eu.org%3a451%2fannounce&tr=udp%3a%2f%2fexplodie.org%3a6969%2fannounce&tr=udp%3a%2f%2ftracker1.bt.moack.co.kr%3a80%2fannounce&tr=udp%3a%2f%2ftracker.theoks.net%3a6969%2fannounce&tr=udp%3a%2f%2ftracker-udp.gbitt.info%3a80%2fannounce&tr=udp%3a%2f%2fp4p.arenabg.com%3a1337%2fannounce&tr=https%3a%2f%2ftracker.tamersunion.org%3a443%2fannounce&tr=https%3a%2f%2ftracker.gbitt.info%3a443%2fannounce&tr=http%3a%2f%2ftracker.gbitt.info%3a80%2fannounce&tr=udp%3a%2f%2fuploads.gamecoast.net%3a6969%2fannounce";
}

QString Config::getCorrectW3Key(QString modeKey) {
    return modeKey == W3_KEY_126 ? W3_KEY_126 : W3_KEY_LATEST;
}

QString Config::getW3Path(QString modeKey) {
    return getCorrectW3Key(modeKey) == W3_KEY_126 ? W3PATH_126 : W3PATH_LATEST;
}

QString Config::getCurrentW3Path() {
    return getW3Path(ACTIVE_MODE_KEY);
}

QString Config::getW3Exename(QString modeKey) {
    return getCorrectW3Key(modeKey) == W3_KEY_126 ? W3_EXENAME_126 : W3_EXENAME_LATEST;
}

QString Config::getCurrentW3Exename() {
    return getW3Exename(ACTIVE_MODE_KEY);
}

QString Config::getW3ExePath(QString modeKey) {
    modeKey = getCorrectW3Key(modeKey);
    return getW3Path(modeKey) + "/" + getW3Exename(modeKey);
}

QString Config::getCurrentW3ExePath() {
    return getW3ExePath(ACTIVE_MODE_KEY);
}

QString Config::getW3Version(QString modeKey) {
    return getCorrectW3Key(modeKey) == W3_KEY_126 ? W3_VERSION_126 : W3_VERSION_LATEST;
}

QString Config::getCurrentW3Version() {
    return getW3Exename(ACTIVE_MODE_KEY);
}

