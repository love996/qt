#include "httpclient.h"


HttpClient::HttpClient(const QString & host)
    :_host(host)
{

}

const HttpResponse &HttpClient::get(const QString &path)
{
   auto req = getRequest(path);
    _client.get(req);
}

QNetworkRequest HttpClient::getRequest(const QString &path)
{
    QUrl url(QString("%1/%2").arg(_host, path));
    QNetworkRequest request(url);
    request.setRawHeader("Accept", "*/*");
    request.setRawHeader("Connection", "keep-alive");
}
