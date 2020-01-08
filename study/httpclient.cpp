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
   auto sig_obj = QObject::connect(&_client, &QNetworkAccessManager::finished,
                                   std::bind(&HttpClient::finished, this, placeholders::_1));
   _replySigMap.insert(reply, std::move(sig_obj));
   _replyCB.insert(reply, cb);

}

QNetworkRequest HttpClient::getRequest(const QString &path)
{
    QUrl url(QString("%1/%2").arg(_host, path));
    QNetworkRequest request(url);
    request.setRawHeader("Accept", "*/*");
    request.setRawHeader("Connection", "keep-alive");
    return request;
}

const HttpResponse &HttpClient::getResponse(QNetworkReply *reply)
{

}

void HttpClient::finished(QNetworkReply *reply)
{
    qDebug() << "finished";
    auto resp = make_shared<HttpResponse>();
    resp->headerList = reply->rawHeaderPairs();
    resp->body = reply->readAll();
    _replyCB[reply](resp);

}
