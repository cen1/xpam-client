#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QMap>
#include <QUrl>
#include <QVector>
#include <QSettings>

class Config : public QObject
{
    Q_OBJECT
public:
    QString VERSION_CLIENT;

    // Supported Warcraft III versions. Each version is a fully independent
    // "slot" that can be installed and used simultaneously with the others,
    // with its own install path, executable, torrent and loader config.
    //  - 1.26 and 1.28 use the legacy registry "Battle.net Gateways" mechanism.
    //  - 1.29+ uses realms.ini + Misc\bnetGateway index (see registry.cpp).
    QString W3_VERSION_126;
    QString W3_VERSION_128;
    QString W3_VERSION_129;

    QString W3_EXENAME_126;
    QString W3_EXENAME_128;
    QString W3_EXENAME_129;

    QString W3_KEY_126;
    QString W3_KEY_128;
    QString W3_KEY_129;

    QString W3PATH_126;
    QString W3PATH_128;
    QString W3PATH_129;

    QString W3_MAGNET_126;
    QString W3_MAGNET_128;
    QString W3_MAGNET_129;

    QString W3l_CONFIG_PATH_126;
    QString W3l_CONFIG_PATH_128;
    QString W3l_CONFIG_PATH_129;

    int PATCH;
    QString XPAM_CONFIG_PATH;
    QString GPROXY_CONFIG_PATH;
    QString DOTA_CONFIG_PATH;
    //QString GPROXY_CONFIG_PATH_CFG;
    QString ACTIVE_MODE_KEY;
    QString DOCPATH;
    QString DOCMAPPATH;
    QString DOCMAPPATHDL;
    QString MAPPATH_126;
    QString MAPPATH_126DL;
    QString EUROPATH;
    QString GPROXYPATH;
    QString SOUNDPATH;
    QString APPDATA;
    QString APPDATA_BNET_CACHE;
    QString APPDATA_BNET_DOWNLOADS;
    QString SYSTEM;
    QString GPROXY_SERVER;
    QString PLINK;
    QString SOCKS;
    QString SOCKS_CFG;
    bool ASK_FOR_W3_FAST_UPDATE;
    bool HAS_QUICK_PATCH;
    bool IS_PORTABLE;

    QVector<QString> XPAM_OPTIONS;
    QVector<QString> W3_OPTIONS;
    QVector<QString> GPROXY_OPTIONS;

    QUrl json1;
    QUrl json2;
    QUrl json3;

    QString BETAPIN;

    Config();
    QSettings settings();

    // Normalizes an arbitrary/legacy mode key to one of the three supported
    // keys, defaulting to 1.29 only when the input is unrecognised.
    QString getCorrectW3Key(QString modeKey);

    // true for the classic 1.26 slot
    bool isW3126(QString modeKey);
    // true for versions using the 1.29+ realms.ini/bnetGateway gateway scheme
    bool usesRealmsIni(QString modeKey);

    QString getW3Path(QString modeKey);
    QString getCurrentW3Path();

    QString getW3Exename(QString modeKey);
    QString getCurrentW3Exename();

    QString getW3Version(QString modeKey);
    QString getCurrentW3Version();
    // Human readable version without the build number, e.g. "1.26", "1.28.5", "1.29.2"
    QString getW3ShortVersion(QString modeKey);

    QString getW3ExePath(QString modeKey);
    QString getCurrentW3ExePath();

    QString getW3Magnet(QString modeKey);

    QString getW3lConfigPath(QString modeKey);
    QString getCurrentW3lConfigPath();

    // update.json key for the per-version quick loader patch, e.g. "129_quick"
    QString getQuickJsonKey(QString modeKey);
    QString getCurrentQuickJsonKey();

    QString getPathFromKey(QString key);
};

#endif //CONFIG_H
