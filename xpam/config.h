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
    QString W3_VERSION_LATEST;
    QString W3_VERSION_126;
    QString W3_EXENAME_LATEST;
    QString W3_EXENAME_126;
    int PATCH;
    QString XPAM_CONFIG_PATH;
    QString GPROXY_CONFIG_PATH;
    QString DOTA_CONFIG_PATH;
    QString W3l_CONFIG_PATH_LATEST;
    QString W3l_CONFIG_PATH_126;
    //QString GPROXY_CONFIG_PATH_CFG;
    QString ACTIVE_MODE_KEY;
    QString W3_KEY_126;
    QString W3_KEY_LATEST;
    QString W3PATH_126;
    QString W3PATH_LATEST;
    QString DOCPATH;
    QString DOCMAPPATH;
    QString DOCMAPPATHDL;
    QString MAPPATH_126;
    QString MAPPATH_126DL;
    QString EUROPATH;
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
    QVector<QString> W3_VERSIONS;

    QUrl json1;
    QUrl json2;
    QUrl json3;

    QString BETAPIN;

    Config();
    QSettings settings();

    QString getCorrectW3Key(QString modeKey);

    QString getW3Path(QString modeKey);
    QString getCurrentW3Path();

    QString getW3Exename(QString modeKey);
    QString getCurrentW3Exename();

    QString getW3Version(QString modeKey);
    QString getCurrentW3Version();

    QString getW3ExePath(QString modeKey);
    QString getCurrentW3ExePath();
};

#endif //CONFIG_H
