#include "tcpserver.h"
using namespace std;

#include <QTcpSocket>
#include <QTimer>
#include <QThread>
/*
TcpServer::TcpServer(const QHostAddress &addr, quint16 port)
    :_cb(nullptr)
{
    _server.listen(addr, port);
    _timerSend.setInterval(1000);
    _timerSend.start();
    qDebug() << "is listening:" << _server.isListening();
    // 处理连接
    initSlots();
}

TcpServer::TcpServer(const QString &addr, quint16 port)
    :TcpServer(QHostAddress(addr), port)
{

}

TcpServer::~TcpServer()
{
}

void TcpServer::registerConnectedCallback(ConnectedCallback cb)
{
    _cb = cb;
}

void TcpServer::error(QAbstractSocket::SocketError e)
{
    qDebug() << "erorr:" << e;
}

void TcpServer::newConnection()
{
    qDebug() << "begin new connection";
    auto connPtr(shared_ptr<QTcpSocket>(_server.nextPendingConnection()));
    if (_cb) {
        _cb(connPtr);
    }
    else {
        QObject::connect(&_timerSend, &QTimer::timeout, [connPtr]{
                connPtr->write("hello");
        });
        _delegateConnections.insert(connPtr);
    }
    qDebug() << "new connection";
}

void TcpServer::initSlots()
{
    QObject::connect(&_server, &QTcpServer::newConnection, [this]{
        qDebug() << "new client";
        this->newConnection();
    });
    qDebug() << "init slots";
}
*/

