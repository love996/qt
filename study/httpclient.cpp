#include "httpclient.h"
#include <thread>
#include <functional>
using namespace std;

HttpClient::HttpClient(const QString & host)
    :_host(host)
{

}

void HttpClient::get(const QString &path, HttpCallBack cb)
{
   auto req = getRequest(path);
   auto reply = _client.get(req);
   registerCallback(reply, cb);
}

void HttpClient::post(const QString &path, const QByteArray &data, HttpCallBack cb)
{
    auto req = getRequest(path);
    auto reply = _client.post(req, data);
    registerCallback(reply, cb);
}

QNetworkRequest HttpClient::getRequest(const QString &path)
{
    QUrl url(QString("%1/%2").arg(_host, path));
    QNetworkRequest request(url);
    request.setRawHeader("Accept", "*/*");
    request.setRawHeader("Connection", "keep-alive");
    return request;
}

void HttpClient::finished(QNetworkReply *reply)
{
    auto resp = make_shared<HttpResponse>();
    resp->headerList = reply->rawHeaderPairs();
    resp->body = reply->readAll();
    _replyCB[reply](resp);
    clearReply(reply);
}

void HttpClient::clearReply(QNetworkReply *reply)
{
    QObject::disconnect(_replySigMap[reply]);
    _replySigMap.remove(reply);
    reply->deleteLater();
    _replyCB.remove(reply);
}

void HttpClient::registerCallback(QNetworkReply *reply, HttpCallBack cb)
{
    auto sig_obj = QObject::connect(reply, &QNetworkReply::finished,
                                    std::bind(&HttpClient::finished, this, reply));
    _replySigMap.insert(reply, std::move(sig_obj));
    _replyCB.insert(reply, cb);
}
