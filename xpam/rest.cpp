#include "rest.h"
#include "QJsonDocument"
#include "QJsonObject"
#include "QUrl"
#include "QNetworkRequest"
#include "QNetworkAccessManager"
#include "QEventLoop"
#include "QDebug"
#include "QNetworkReply"
#include "QJsonArray"

bool Rest::authenticate(QString username, QString secret) {

    QUrl serviceUrl = QUrl("https://eurobattle.net/api/pvpgn/auth");
    QNetworkRequest request(serviceUrl);
    request.setTransferTimeout(10000);
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);

    QJsonObject json;
    json.insert("username",username);
    json.insert("secret",secret);
    QJsonDocument jsonDoc(json);
    QByteArray jsonData=jsonDoc.toJson();
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

    QNetworkAccessManager nam;
    QNetworkReply * reply = nam.post(request, jsonData);

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

QString Rest::getSeverStatus() {
    QUrl serviceUrl = QUrl("https://eurobattle.net/new/api/pvpgn/status/json");
    QNetworkRequest request(serviceUrl);
    request.setTransferTimeout(2000);
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);

    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

    QNetworkAccessManager nam;
    QNetworkReply * reply = nam.get(request);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray ba(reply->readAll());
        reply->deleteLater();
        QJsonDocument json =  QJsonDocument::fromJson(ba);
        QJsonArray data=json.array();
        if (data.size()>0) {
            return data.at(0).toString();
        }
        else {
            return "";
        }
    }
    else {
        return "";
    }
}
