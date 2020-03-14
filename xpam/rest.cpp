#include "rest.h"
#include "QJsonDocument"
#include "QJsonObject"
#include "QUrl"
#include "QNetworkRequest"
#include "QNetworkAccessManager"
#include "QEventLoop"
#include "replytimeout.h"

bool Rest::authenticate(QString username, QString secret) {

    QUrl serviceUrl = QUrl("http://warden.eurobattle.net/api/pvpgn/auth");
    QNetworkRequest request(serviceUrl);
    QJsonObject json;
    json.insert("username",username);
    json.insert("secret",secret);
    QJsonDocument jsonDoc(json);
    QByteArray jsonData=jsonDoc.toJson();
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

    QNetworkAccessManager nam;
    QNetworkReply * reply = nam.post(request, jsonData);
    ReplyTimeout::set(reply, 5000);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray ba(reply->readAll());
        reply->deleteLater();
        QJsonDocument json =  QJsonDocument::fromJson(ba);
        QJsonObject obj=json.object();
        bool success = obj.value("success").toBool();
        qDebug() << ba;
        qDebug() << success;
        return success;
    }
    else {
        return false;
    }
}
