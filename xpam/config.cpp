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
    VERSION_CLIENT = "1.2.0.0";

    W3_VERSION_126 = "1.26.0.6401";
    W3_VERSION_128 = "1.28.5.7680";
    W3_VERSION_129 = "1.29.2.9231";

    W3_KEY_126 = "WAR3_126";
    W3_KEY_128 = "WAR3_128";
    W3_KEY_129 = "WAR3_129";

    W3_EXENAME_126="war3.exe";
    W3_EXENAME_128="Warcraft III.exe";
    W3_EXENAME_129="Warcraft III.exe";

    BETAPIN = "1377";

//#ifdef PORTABLE
    //EUROPATH    = QDir::currentPath();
    //W3PATH      = QDir::currentPath()+"/../Warcraft III";
    //IS_PORTABLE = true;
//#else
    IS_PORTABLE = false;

    EUROPATH    = Registry::getEuroPath().replace(QChar('\\'), QChar('/'));
    GPROXYPATH  = EUROPATH+"/gproxy";
    XPAM_CONFIG_PATH = EUROPATH+"/xpam.ini";
    GPROXY_CONFIG_PATH = GPROXYPATH+"/gproxy.ini";
    //GPROXY_CONFIG_PATH_CFG = GPROXYPATH+"/gproxy.cfg";
    SOUNDPATH   = EUROPATH+"/sounds";

    QSettings settings(XPAM_CONFIG_PATH, QSettings::IniFormat);
    ACTIVE_MODE_KEY = settings.value("active_mode", W3_KEY_129).toString();
    // Legacy: the single modern slot used to be stored as "WAR3_LATEST" (= 1.29)
    if (ACTIVE_MODE_KEY == "WAR3_LATEST") {
        ACTIVE_MODE_KEY = W3_KEY_129;
    }
    if (ACTIVE_MODE_KEY != W3_KEY_126 && ACTIVE_MODE_KEY != W3_KEY_128 && ACTIVE_MODE_KEY != W3_KEY_129) {
        // active_mode always should be valid, because we are using W3_KEY_* as a ini group
        ACTIVE_MODE_KEY = W3_KEY_129;
    }
    settings.setValue("active_mode", ACTIVE_MODE_KEY);

    W3PATH_126 = settings.value(W3_KEY_126 + "/path", "").toString().replace(QChar('\\'), QChar('/'));
    W3PATH_128 = settings.value(W3_KEY_128 + "/path", "").toString().replace(QChar('\\'), QChar('/'));
    // Preserve the path of pre-existing installs: the 1.29 slot used to be
    // stored under the legacy "WAR3_LATEST" group, falling back to auto-detection.
    W3PATH_129 = settings.value(W3_KEY_129 + "/path",
                     settings.value("WAR3_LATEST/path", Registry::getW3dir()).toString())
                     .toString().replace(QChar('\\'), QChar('/'));
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
    W3l_CONFIG_PATH_128 = W3PATH_128+"/w3l.ini";
    W3l_CONFIG_PATH_129 = W3PATH_129+"/w3l.ini";

#ifdef _DEVELOPMENT
    json1 = "http://localhost:8080/update.json";
    json2 = "http://localhost:8080/update.json";
    json3 = "http://localhost:8080/update.json";
#else
    json1 = "https://xpam.pl/update3/update3.json";
    json2 = "https://tools.eurobattle.net/update3/update3.json";
    json3 = "https://gist.githubusercontent.com/cen1/d5f4c004228905937d470e11fda698a1/raw/update3.json";
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

    W3_MAGNET_126 = "magnet:?xt=urn:btih:c2b42798b4502f1b05172a5f7eaf89bec5bd6466&dn=Warcraft_III_1.26_repack.zip&tr=udp%3a%2f%2ftracker.opentrackr.org%3a1337%2fannounce&tr=https%3a%2f%2ftracker2.ctix.cn%3a443%2fannounce&tr=https%3a%2f%2ftracker1.520.jp%3a443%2fannounce&tr=udp%3a%2f%2fopen.tracker.cl%3a1337%2fannounce&tr=udp%3a%2f%2fopentracker.i2p.rocks%3a6969%2fannounce&tr=udp%3a%2f%2fopen.demonii.com%3a1337%2fannounce&tr=udp%3a%2f%2ftracker.openbittorrent.com%3a6969%2fannounce&tr=http%3a%2f%2ftracker.openbittorrent.com%3a80%2fannounce&tr=udp%3a%2f%2fopen.stealth.si%3a80%2fannounce&tr=udp%3a%2f%2fexodus.desync.com%3a6969%2fannounce&tr=udp%3a%2f%2ftracker.torrent.eu.org%3a451%2fannounce&tr=udp%3a%2f%2fexplodie.org%3a6969%2fannounce&tr=udp%3a%2f%2ftracker1.bt.moack.co.kr%3a80%2fannounce&tr=udp%3a%2f%2ftracker.theoks.net%3a6969%2fannounce&tr=udp%3a%2f%2ftracker-udp.gbitt.info%3a80%2fannounce&tr=udp%3a%2f%2fp4p.arenabg.com%3a1337%2fannounce&tr=https%3a%2f%2ftracker.tamersunion.org%3a443%2fannounce&tr=https%3a%2f%2ftracker.gbitt.info%3a443%2fannounce&tr=http%3a%2f%2ftracker.gbitt.info%3a80%2fannounce&tr=udp%3a%2f%2fuploads.gamecoast.net%3a6969%2fannounce";
    W3_MAGNET_128 = "magnet:?xt=urn:btih:cc982e0ac9a6353dcd5432832a71446f6848baf6&dn=Warcraft_III_1.28.5_repack.zip&tr=udp%3a%2f%2ftracker.opentrackr.org%3a1337%2fannounce&tr=https%3a%2f%2ftracker2.ctix.cn%3a443%2fannounce&tr=https%3a%2f%2ftracker1.520.jp%3a443%2fannounce&tr=udp%3a%2f%2fopen.tracker.cl%3a1337%2fannounce&tr=udp%3a%2f%2fopentracker.i2p.rocks%3a6969%2fannounce&tr=udp%3a%2f%2fopen.demonii.com%3a1337%2fannounce&tr=udp%3a%2f%2ftracker.openbittorrent.com%3a6969%2fannounce&tr=http%3a%2f%2ftracker.openbittorrent.com%3a80%2fannounce&tr=udp%3a%2f%2fopen.stealth.si%3a80%2fannounce&tr=udp%3a%2f%2fexodus.desync.com%3a6969%2fannounce&tr=udp%3a%2f%2ftracker.torrent.eu.org%3a451%2fannounce&tr=udp%3a%2f%2fexplodie.org%3a6969%2fannounce&tr=udp%3a%2f%2ftracker1.bt.moack.co.kr%3a80%2fannounce&tr=udp%3a%2f%2ftracker.theoks.net%3a6969%2fannounce&tr=udp%3a%2f%2ftracker-udp.gbitt.info%3a80%2fannounce&tr=udp%3a%2f%2fp4p.arenabg.com%3a1337%2fannounce&tr=https%3a%2f%2ftracker.tamersunion.org%3a443%2fannounce&tr=https%3a%2f%2ftracker.gbitt.info%3a443%2fannounce&tr=http%3a%2f%2ftracker.gbitt.info%3a80%2fannounce&tr=udp%3a%2f%2fuploads.gamecoast.net%3a6969%2fannounce";
    W3_MAGNET_129 = "magnet:?xt=urn:btih:85d54173944616f7641b14bf4cecf461eaa120ba&dn=Warcraft%5FIII%5F1.29.2.zip&tr=udp%3A%2F%2Ftracker.opentrackr.org%3A1337%2Fannounce&tr=https%3A%2F%2Ftracker2.ctix.cn%3A443%2Fannounce&tr=https%3A%2F%2Ftracker1.520.jp%3A443%2Fannounce&tr=udp%3A%2F%2Fopen.tracker.cl%3A1337%2Fannounce&tr=udp%3A%2F%2Fopentracker.i2p.rocks%3A6969%2Fannounce&tr=udp%3A%2F%2Ftracker.openbittorrent.com%3A6969%2Fannounce&tr=http%3A%2F%2Ftracker.openbittorrent.com%3A80%2Fannounce&tr=udp%3A%2F%2Fopen.stealth.si%3A80%2Fannounce&tr=udp%3A%2F%2Fexodus.desync.com%3A6969%2Fannounce&tr=udp%3A%2F%2Ftracker.torrent.eu.org%3A451%2Fannounce&tr=udp%3A%2F%2Fexplodie.org%3A6969%2Fannounce&tr=udp%3A%2F%2Ftracker1.bt.moack.co.kr%3A80%2Fannounce&tr=udp%3A%2F%2Ftracker.theoks.net%3A6969%2Fannounce&tr=udp%3A%2F%2Ftracker-udp.gbitt.info%3A80%2Fannounce&tr=udp%3A%2F%2Fp4p.arenabg.com%3A1337%2Fannounce&tr=https%3A%2F%2Ftracker.tamersunion.org%3A443%2Fannounce&tr=https%3A%2F%2Ftracker.gbitt.info%3A443%2Fannounce&tr=http%3A%2F%2Ftracker.gbitt.info%3A80%2Fannounce&tr=udp%3A%2F%2Fuploads.gamecoast.net%3A6969%2Fannounce";
}

QString Config::getCorrectW3Key(QString modeKey) {
    if (modeKey == W3_KEY_126) return W3_KEY_126;
    if (modeKey == W3_KEY_128) return W3_KEY_128;
    if (modeKey == W3_KEY_129) return W3_KEY_129;
    // Unrecognised/legacy key: default to the newest supported version.
    return W3_KEY_129;
}

bool Config::isW3126(QString modeKey) {
    return getCorrectW3Key(modeKey) == W3_KEY_126;
}

bool Config::usesRealmsIni(QString modeKey) {
    // 1.29+ dropped the registry "Battle.net Gateways" list in favour of
    // realms.ini + Misc\bnetGateway. 1.26 and 1.28 still use the registry.
    return getCorrectW3Key(modeKey) == W3_KEY_129;
}

QString Config::getW3Path(QString modeKey) {
    modeKey = getCorrectW3Key(modeKey);
    if (modeKey == W3_KEY_126) return W3PATH_126;
    if (modeKey == W3_KEY_128) return W3PATH_128;
    return W3PATH_129;
}

QString Config::getCurrentW3Path() {
    return getW3Path(ACTIVE_MODE_KEY);
}

QString Config::getW3Exename(QString modeKey) {
    modeKey = getCorrectW3Key(modeKey);
    if (modeKey == W3_KEY_126) return W3_EXENAME_126;
    if (modeKey == W3_KEY_128) return W3_EXENAME_128;
    return W3_EXENAME_129;
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
    modeKey = getCorrectW3Key(modeKey);
    if (modeKey == W3_KEY_126) return W3_VERSION_126;
    if (modeKey == W3_KEY_128) return W3_VERSION_128;
    return W3_VERSION_129;
}

QString Config::getCurrentW3Version() {
    return getW3Version(ACTIVE_MODE_KEY);
}

QString Config::getW3ShortVersion(QString modeKey) {
    QStringList parts = getW3Version(modeKey).split('.').mid(0, 3);
    if (parts.size() == 3 && parts.last() == "0") parts.removeLast();
    return parts.join('.');
}

QString Config::getW3Magnet(QString modeKey) {
    modeKey = getCorrectW3Key(modeKey);
    if (modeKey == W3_KEY_126) return W3_MAGNET_126;
    if (modeKey == W3_KEY_128) return W3_MAGNET_128;
    return W3_MAGNET_129;
}

QString Config::getW3lConfigPath(QString modeKey) {
    modeKey = getCorrectW3Key(modeKey);
    if (modeKey == W3_KEY_126) return W3l_CONFIG_PATH_126;
    if (modeKey == W3_KEY_128) return W3l_CONFIG_PATH_128;
    return W3l_CONFIG_PATH_129;
}

QString Config::getCurrentW3lConfigPath() {
    return getW3lConfigPath(ACTIVE_MODE_KEY);
}

QString Config::getQuickJsonKey(QString modeKey) {
    modeKey = getCorrectW3Key(modeKey);
    if (modeKey == W3_KEY_126) return "126_quick";
    if (modeKey == W3_KEY_128) return "128_quick";
    return "129_quick";
}

QString Config::getCurrentQuickJsonKey() {
    return getQuickJsonKey(ACTIVE_MODE_KEY);
}

QString Config::getPathFromKey(QString key) {
    if (key=="W3PATH_126") {
        return this->W3PATH_126;
    }
    else if (key=="W3PATH_128") {
        return this->W3PATH_128;
    }
    else if (key=="W3PATH_129") {
        return this->W3PATH_129;
    }
    // "W3PATH" without a version suffix refers to the currently active install
    else if (key=="W3PATH" || key=="W3PATH_LATEST") {
        return this->getCurrentW3Path();
    }
    else if (key=="MAPPATH_126") {
        return this->MAPPATH_126;
    }
    else if (key=="MAPPATH_126DL") {
        return this->MAPPATH_126DL;
    }
    else if (key=="DOCPATH") {
        return this->DOCPATH;
    }
    else if (key=="DOCMAPPATH") {
        return this->DOCMAPPATH;
    }
    else if (key=="DOCMAPPATHDL") {
        return this->DOCMAPPATHDL;
    }
    else if (key=="EUROPATH") {
        return this->EUROPATH;
    }
    else if (key=="GPROXYPATH") {
        return this->GPROXYPATH;
    }
    else {
        return this->EUROPATH;
    }
}

