#include "mynetwork.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <iostream>
#include <fstream>
using namespace std;

typedef void (QNetworkReply::*error_ptr)(QNetworkReply::NetworkError);
MyNetWork::MyNetWork(QObject *parent)
    :QObject(parent)
{

}


void MyNetWork::httpGet()
{
    QUrl url("http://www.baidu.com");
    static QNetworkAccessManager *netmanager = new QNetworkAccessManager;
    static QNetworkRequest *request = new QNetworkRequest(url);
    // request->setRawHeader("Content-Type", "application/json");
    request->setRawHeader("Accept", "*/*");
    request->setRawHeader("Accept-Encoding", "gzip, deflate");
    request->setRawHeader("Connection", "keep-alive");
    static QNetworkReply *reply = netmanager->get(*request);
    QObject::connect(reply, (error_ptr)&QNetworkReply::error,
                     [](QNetworkReply::NetworkError err){
        qDebug() << err;
    });
    QObject::connect(reply, &QNetworkReply::readyRead,
                     [&]{
        qDebug() << "ready read";
        char data[1 * 1024 * 1024] = {0};
        int byteRead = reply->read(data, sizeof(data));
        qDebug() << byteRead;
        ofstream out("out.txt", ios::app);
        out.write(data, byteRead);
        out.close();
    });
    QObject::connect(reply, &QNetworkReply::finished,
                     [&]{
        qDebug() << "finished";
        qDebug() << reply->error();
        static char data[4 * 1024 * 1024] = {0};
        qDebug() << sizeof(data);

        qDebug() << reply->readBufferSize();
        reply->read(data, sizeof(data));
        std::cout << data;
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
