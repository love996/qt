#include "tcpconnection.h"

#include <functional>

TcpConnection::TcpConnection(/*QObject *parent*/) // : QObject(parent)
{

}

void TcpConnection::connect(const QHostAddress &addr, quint16 port)
{
    _socket.connectToHost(addr, port);
}

void TcpConnection::initSlots()
{
    using SocketErrorFunc = void (QTcpSocket::*)(QAbstractSocket::SocketError);
    QObject::connect(&_socket, static_cast<SocketErrorFunc>(&QTcpSocket::error), this, &TcpConnection::socketError);
    QObject::connect(&_socket, &QTcpSocket::readyRead, [this]{
        this->_cb(_socket);
    });
}

void TcpConnection::socketError(QAbstractSocket::SocketError e)
{
    qDebug() << "socket error:" << e;
}
