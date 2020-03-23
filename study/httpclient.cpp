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
    QUrl url(QString("%1/%2").arg(_host, path));
    auto req = getRequest(url);
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

QNetworkRequest HttpClient::getRequest(const QUrl &url)
{
    QNetworkRequest request;
    request.setRawHeader("Accept", "*/*");
    request.setRawHeader("Connection", "keep-alive");
    if (url.url().indexOf("https") != -1) {
        QSslConfiguration conf = request.sslConfiguration();
        conf.setPeerVerifyMode(QSslSocket::VerifyNone);
        conf.setProtocol(QSsl::TlsV1SslV3);
        request.setSslConfiguration(conf);
    }
    request.setUrl(url);
    return request;
}

void HttpClient::finished(QNetworkReply *reply)
{
    _replyInfoMap[reply]->httpResponse->headerList = reply->rawHeaderPairs();
    _replyInfoMap[reply]->httpResponse->body.append(reply->readAll());
    _replyInfoMap[reply]->httpResponse->downloadFile = _replyInfoMap[reply]->downloadFile.fileName();

    // qDebug() << reply->rawHeaderPairs() << _replyInfoMap[reply]->downloadFile.fileName() << _replyInfoMap[reply]->httpResponse->body << reply->url();

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

QString getFilenameFromHeader(const QString &text)
{
    QString findStr = "filename=";
    int index = text.indexOf(findStr);
    return text.mid(index + findStr.size());
}

QString getFilenameFromUrl(const QString &url)
{
    auto index = url.lastIndexOf("/");
    return url.mid(index+1);
}

void HttpClient::readyRead(QNetworkReply *reply)
{
    if (_replyInfoMap[reply]->httpResponse->headerList.size() == 0) {
        _replyInfoMap[reply]->httpResponse->headerList = reply->rawHeaderPairs();
        if (reply->rawHeader("Content-Type") == QString("application/octet-stream")) {
            auto filename = getFilenameFromHeader(reply->rawHeader("Content-Disposition"));
            initDownloadFile(reply, filename);
        }
        else if (QString("image/jpeg") == reply->rawHeader("Content-Type")) {
            auto filename = getFilenameFromUrl(reply->url().url());
            initDownloadFile(reply, filename);
        }
        qDebug() << reply->rawHeaderPairs();
    }
    qDebug() << reply->size();
    if (_replyInfoMap[reply]->downloadFile.isOpen()) {
        _replyInfoMap[reply]->downloadFile.write(reply->readAll());
    }
    else {
        _replyInfoMap[reply]->httpResponse->body.append(reply->readAll());
    }
}

void HttpClient::initDownloadFile(QNetworkReply *reply, QString filename)
{
    _replyInfoMap[reply]->downloadFile.setFileName(filename);
//    _replyInfoMap[reply]->downloadFile.setPermissions(QFile::Permission::ExeUser |
//                                                     QFile::Permission::ExeOwner |
//                                                     QFile::Permission::ExeGroup);
    _replyInfoMap[reply]->downloadFile.open(QFile::WriteOnly | QFile::Truncate);
}
