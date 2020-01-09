#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <memory>
#include <functional>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSettings>

struct HttpResponse
{
    QList<QNetworkReply::RawHeaderPair> headerList;
    QByteArray body;
};

using HttpCallBack = std::function<void (std::shared_ptr<HttpResponse>)>;

class HttpClient
{
public:
    HttpClient(const QString &host);
    void get(const QString &path, HttpCallBack cb);
    void post(const QString &path, const QByteArray &data, HttpCallBack cb);
private:
    QNetworkAccessManager _client;
    QString _host;
    QMap<QNetworkReply*, QMetaObject::Connection> _replySigMap;
    QMap<QNetworkReply*, HttpCallBack> _replyCB;
private:
    QNetworkRequest getRequest(const QString &path);
private:
    void finished(QNetworkReply *reply);
    void clearReply(QNetworkReply *reply);
    void registerCallback(QNetworkReply *reply, HttpCallBack cb);
};

#endif // HTTPCLIENT_H
