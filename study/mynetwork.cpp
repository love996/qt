#include "mynetwork.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <iostream>
#include <fstream>
#include <QFile>
using namespace std;

typedef void (QNetworkAccessManager::*error_ptr)(QNetworkReply::NetworkError);
MyNetWork::MyNetWork(QObject *parent)
    :QObject(parent)
{

}


void MyNetWork::httpGet()
{
    // QUrl url("http://58.216.158.92:9101/");
    QUrl url("http://www.baidu.com");
    static QNetworkAccessManager *netmanager = new QNetworkAccessManager;
    netmanager->connectToHost("http://www.baidu.com");
    static QNetworkRequest *request = new QNetworkRequest;
    request->setRawHeader("Accept", "*/*");
    request->setRawHeader("Connection", "keep-alive");

    // TLS
//    QSslConfiguration conf = request->sslConfiguration();
//    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
//    conf.setProtocol(QSsl::TlsV1_1OrLater);
//    request->setSslConfiguration(conf);


//    QObject::connect(netmanager, (error_ptr)&QNetworkAccessManager::error,
//                     [](QNetworkReply::NetworkError err){
//        qDebug() << err;
//    });
//    QObject::connect(reply, &QNetworkReply::readyRead,
//                     [&]{
//        qDebug() << "ready read";
//        char data[1 * 1024 * 1024] = {0};
//        int byteRead = reply->read(data, sizeof(data));
//        qDebug() << byteRead;
//        static ofstream out("out.txt");
//        out.write(data, byteRead);
//        out.flush();
//    });
    static QNetworkReply *reply = netmanager->get(*request);
    QObject::connect(netmanager, &QNetworkAccessManager::finished,
                     [](QNetworkReply *reply){
        qDebug() << "finished";
        qDebug() << reply->error();

        auto data = reply->readAll();
        std::cout << data.size();
        QFile file("out.html");
        file.open(QFile::WriteOnly);
        file.write(data);
        file.close();

        qDebug() << reply->rawHeaderPairs();
//        for (auto ch : data) {
//            qDebug() << QString::fromLocal8Bit(QString(ch).toStdString().data());
//        }
//        for (auto iter = data.begin(); iter != data.end(); ++iter){
//            qDebug() << *iter;
//        }
        qDebug() << strlen(data);
    });
    QObject::connect(reply, &QNetworkReply::downloadProgress,
                     [&](qint64 byteSend, qint64 byteTotal){
        qDebug() << byteSend << "/" << byteTotal;
    });

    qDebug() << reply->error();
    auto data = reply->readAll();
    qDebug() << reply->rawHeaderList();
    qDebug() << data.length();

}
