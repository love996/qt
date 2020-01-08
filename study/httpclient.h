#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H


#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSettings>

struct HttpResponse
{
    QList<QNetworkReply::RawHeaderPair> headerList;
    QByteArray body;
};

class HttpClient
{
public:
    HttpClient(const QString &host);
    const HttpResponse &get(const QString &path);
private:
    QNetworkAccessManager _client;
    QString _host;
private:
    QNetworkRequest getRequest(const QString &path);
    const HttpResponse &getResponse(QNetworkReply *reply);
};

#endif // HTTPCLIENT_H
