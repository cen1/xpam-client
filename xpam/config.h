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
    QString ACTIVE_MODE_KEY;
    QString W3_KEY_126;
    QString W3_KEY_LATEST;
    QString W3PATH_126;
    QString W3PATH_LATEST;
    QString DOCPATH;
    QString DOCMAPPATH;
    QString DOCMAPPATHDL;
    QString OLDMAPPATH;
    QString OLDMAPPATHDL;
    QString EUROPATH;
    QString SOUNDPATH;
    QString APPDATA;
    QString SYSTEM;
    bool USE_DUAL_VERSION;
    bool ASK_FOR_W3_FAST_UPDATE;
    bool HAS_QUICK_PATCH;

    QVector<QString> W3_OPTIONS;
    QVector<QString> GPROXY_OPTIONS;
    QVector<QString> W3_VERSIONS;
    QVector<QString> DOTA_MAPS;

    QUrl json1;
    QUrl json2;
    QUrl json3;

    QString BETAPIN;

    Config();
    QSettings settings();
    QString getCurrentW3Path();

    QString getCurrentW3Exename();

    QString getCurrentW3Version();

    QString getCurrentW3ExePath();
};


#endif //CONFIG_H
