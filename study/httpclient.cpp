#include "httpclient.h"
#include <thread>
#include <functional>
using namespace std;

HttpClient::HttpClient(const QString & host, QObject *parent)
    :QObject(parent),
    _host(host)
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

void HttpClient::download(const QUrl &url, HttpCallBack cb)
{
    auto req = getRequest(url);
    auto reply = _client.get(req);
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

QNetworkRequest HttpClient::getRequest(const QUrl &url)
{
    QNetworkRequest request(url);
    request.setRawHeader("Accept", "*/*");
    request.setRawHeader("Connection", "keep-alive");
    return request;
}

void HttpClient::finished(QNetworkReply *reply)
{
    // auto resp = make_shared<HttpResponse>();
    _replyInfoMap[reply]->httpResponse->headerList = reply->rawHeaderPairs();
    _replyInfoMap[reply]->httpResponse->body.append(reply->readAll());
    _replyInfoMap[reply]->httpResponse->downloadFile = _replyInfoMap[reply]->downloadFile.fileName();
    qDebug() << "finished read size:" << _replyInfoMap[reply]->httpResponse->body.size();

    auto resp = _replyInfoMap[reply]->httpResponse;
    auto cb = _replyInfoMap[reply]->cb;
    clearReply(reply);
    cb(resp);
}

void HttpClient::clearReply(QNetworkReply *reply)
{
    for (auto &connObj : _replyInfoMap[reply]->connObjs) {
        QObject::disconnect(connObj);
    }
    _replyInfoMap.remove(reply);
    reply->deleteLater();
}

void HttpClient::registerCallback(QNetworkReply *reply, HttpCallBack cb)
{
    // qDebug() << "headers:" << reply->rawHeaderPairs();
    auto sig_obj = QObject::connect(reply, &QNetworkReply::finished,
                                    std::bind(&HttpClient::finished, this, reply));
    _replyInfoMap[reply] = make_shared<ReplyInfo>();
    _replyInfoMap[reply]->connObjs.push_back(std::move(sig_obj));
    sig_obj = QObject::connect(reply, &QNetworkReply::readyRead,
                               std::bind(&HttpClient::readyRead, this, reply));
    _replyInfoMap[reply]->connObjs.push_back(std::move(sig_obj));
    _replyInfoMap[reply]->cb = cb;
    _replyInfoMap[reply]->httpResponse = make_shared<HttpResponse>();
}

QString getFilename(QString text)
{
    QString findStr = "filename=";
    int index = text.indexOf(findStr);
    return text.mid(index + findStr.size());
}

void HttpClient::readyRead(QNetworkReply *reply)
{
    if (_replyInfoMap[reply]->httpResponse->headerList.size() == 0) {
        _replyInfoMap[reply]->httpResponse->headerList = reply->rawHeaderPairs();
        qDebug() << reply->rawHeader("Content-Type");
        if (reply->rawHeader("Content-Type") == QString("application/octet-stream")) {
            initDownloadFile(reply);
        }
        qDebug() << reply->rawHeaderPairs();
    }
    if (_replyInfoMap[reply]->downloadFile.isOpen()) {
        _replyInfoMap[reply]->downloadFile.write(reply->readAll());
    }
    else {
        _replyInfoMap[reply]->httpResponse->body.append(reply->readAll());
    }
}

void HttpClient::readyWriteFile(QNetworkReply *reply)
{

}

void HttpClient::initDownloadFile(QNetworkReply *reply)
{
    auto filename = getFilename(reply->rawHeader("Content-Disposition"));
    _replyInfoMap[reply]->downloadFile.setFileName(filename);
    _replyInfoMap[reply]->downloadFile.setPermissions(QFile::Permission::ExeUser |
                                                     QFile::Permission::ExeOwner |
                                                     QFile::Permission::ExeGroup);
    _replyInfoMap[reply]->downloadFile.open(QFile::WriteOnly | QFile::Truncate);
}
