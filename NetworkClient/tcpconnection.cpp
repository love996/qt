#include "tcpconnection.h"

#include <functional>
#include <memory>
using namespace std;

#include <QHostAddress>
#include <QThread>

TcpConnectionBase::TcpConnectionBase(std::shared_ptr<QTcpSocket> socketPtr)
    :_socketPtr(socketPtr)
    ,_cb(nullptr)
{

}

TcpConnectionBase::TcpConnectionBase(const QHostAddress &addr, quint16 port)
    :TcpConnectionBase(make_shared<QTcpSocket>())
{
    connect(addr, port);
    initSlots();
}

TcpConnectionBase::TcpConnectionBase(const QString &addr, quint16 port)
    :TcpConnectionBase(QHostAddress(addr), port)
{

}

void TcpConnectionBase::connect(const QHostAddress &addr, quint16 port)
{
    _socketPtr->connectToHost(addr, port);
    qDebug() << "connect is open:" << _socketPtr->isOpen();
}

void TcpConnectionBase::setSocket(std::shared_ptr<QTcpSocket> socketPtr)
{
    _socketPtr = socketPtr;
    clear();
    initSlots();
}

void TcpConnectionBase::registerReadyReadCallback(TcpConnectionBase::ReadyReadCallback cb)
{
     _cb = cb;
}

void TcpConnectionBase::initSlots()
{
    using SocketErrorFunc = void (QTcpSocket::*)(QAbstractSocket::SocketError);
    _slots.push_back(QObject::connect(_socketPtr.get(), static_cast<SocketErrorFunc>(&QTcpSocket::error), [this](QTcpSocket::SocketError e){
        socketError(e);
    }));

    _slots.push_back(QObject::connect(_socketPtr.get(), &QTcpSocket::connected, [](){
        qDebug() << "connect server!";
    }));

    _slots.push_back(QObject::connect(_socketPtr.get(), &QTcpSocket::readyRead, [this]{
        this->readyRead(_socketPtr);
    }));
}

void TcpConnectionBase::clear()
{
    for (auto &slot: _slots) {
        QObject::disconnect(slot);
    }
    _slots.clear();
}

void TcpConnectionBase::socketError(QAbstractSocket::SocketError e)
{
    qDebug() << "socket error:" << e;
}

void TcpConnection::readyRead(std::shared_ptr<QTcpSocket> socketPtr)
{

    qDebug() << socketPtr->readAll();

}
