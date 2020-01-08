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
private:
    QNetworkAccessManager _client;
    QString _host;
    QMap<QNetworkReply*, QMetaObject::Connection> _replySigMap;
    // QMap<QNetworkReply*, std::shared_ptr<HttpResponse>> _replyMap;
    QMap<QNetworkReply*, HttpCallBack> _replyCB;
private:
    QNetworkRequest getRequest(const QString &path);
    const HttpResponse &getResponse(QNetworkReply *reply);
private:
    void finished(QNetworkReply *reply);
};

#endif // HTTPCLIENT_H
