#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <memory>
#include <functional>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QHeaderView>
#include <QSettings>
#include <QFile>

struct HttpResponse
{
    QList<QNetworkReply::RawHeaderPair> headerList;
    QByteArray body;
    QString downloadFile;
};

using HttpCallBack = std::function<void (std::shared_ptr<HttpResponse>)>;

class HttpClient : public QObject
{
    Q_OBJECT
public:
    HttpClient(const QString &host = "", QObject *parent = nullptr);
    void get(const QString &path, HttpCallBack cb);
    void post(const QString &path, const QByteArray &data, HttpCallBack cb);
    void download(const QUrl &url, HttpCallBack cb);
private:
    QNetworkAccessManager _client;
    QString _host;
    struct ReplyInfo
    {
        std::vector<QMetaObject::Connection> connObjs;
        HttpCallBack cb;
        std::shared_ptr<HttpResponse> httpResponse;
        QFile downloadFile;
    };
    QMap<QNetworkReply*, std::shared_ptr<ReplyInfo>> _replyInfoMap;
private:
    QNetworkRequest getRequest(const QString &path);
    QNetworkRequest getRequest(const QUrl &url);
private:
    void finished(QNetworkReply *reply);
    void clearReply(QNetworkReply *reply);
    void registerCallback(QNetworkReply *reply, HttpCallBack cb);
    void readyRead(QNetworkReply *reply);
    void readyWriteFile(QNetworkReply *reply);
    void initDownloadFile(QNetworkReply *reply);
};

#endif // HTTPCLIENT_H
