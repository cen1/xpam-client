#ifndef CONFIG_H
#define CONFIG_H



#include <QObject>
#include <QMap>
#include <QUrl>

class Config : public QObject
{
    Q_OBJECT
public:
    QString VERSION;
    int PATCH;
    QString W3PATH;
    QString MAPPATH;
    QString EUROPATH;
    QString SOUNDPATH;
    QString APPDATA;
    QString SYSTEM;

    QUrl json1;
    QUrl json2;
    QUrl json3;

    QString BETAPIN;

    bool SetOption(QString file, QString option, QString value);
    Config();
};


#endif //CONFIG_H
