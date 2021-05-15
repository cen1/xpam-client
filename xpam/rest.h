#ifndef REST_H
#define REST_H

#include "QObject"

class Rest: public QObject
{
    Q_OBJECT
public:
    static bool authenticate(QString username, QString secret);
    static QString getSeverStatus();
};

#endif // REST_H
