#include "tcpconnection.h"

#include <functional>
#include <memory>
using namespace std;

#include <QHostAddress>
#include <QThread>

TcpConnection::TcpConnection(std::shared_ptr<QTcpSocket> socketPtr)
    :_socketPtr(socketPtr)
    ,_cb(nullptr)
{

}

TcpConnection::TcpConnection(const QHostAddress &addr, quint16 port)
    :TcpConnection(make_shared<QTcpSocket>())
{
    connect(addr, port);
    initSlots();
}

TcpConnection::TcpConnection(const QString &addr, quint16 port)
    :TcpConnection(QHostAddress(addr), port)
{

}

void TcpConnection::connect(const QHostAddress &addr, quint16 port)
{
    _socketPtr->connectToHost(addr, port);
    qDebug() << "connect is open:" << _socketPtr->isOpen();
}

void TcpConnection::setSocket(std::shared_ptr<QTcpSocket> socketPtr)
{
    _socketPtr = socketPtr;
    clear();
    initSlots();
}

void TcpConnection::registerReadyReadCallback(TcpConnection::ReadyReadCallback cb)
{
     _cb = cb;
}

void TcpConnection::initSlots()
{
    using SocketErrorFunc = void (QTcpSocket::*)(QAbstractSocket::SocketError);
    _slots.push_back(QObject::connect(_socketPtr.get(), static_cast<SocketErrorFunc>(&QTcpSocket::error), [this](QTcpSocket::SocketError e){
        socketError(e);
    }));

    _slots.push_back(QObject::connect(_socketPtr.get(), &QTcpSocket::connected, [](){
        qDebug() << "connect server!";
    }));

    _slots.push_back(QObject::connect(_socketPtr.get(), &QTcpSocket::readyRead, [this]{
        if (_cb) {
            _cb(_socketPtr);
        }
        else {
            qDebug() << "socket ready read";
                char buf[2] = {};
                _socketPtr->read(buf, 1);
                qDebug() << buf;

        }
    }));
}

void TcpConnection::clear()
{
    for (auto &slot: _slots) {
        QObject::disconnect(slot);
    }
    _slots.clear();
}

void TcpConnection::socketError(QAbstractSocket::SocketError e)
{
    qDebug() << "socket error:" << e;
}
