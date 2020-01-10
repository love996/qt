#include "myclient.h"

MyClient::MyClient(QHostAddress address, quint16 port)
{
    QObject::connect(&_socket, &QTcpSocket::disconnected, []{
        qDebug() << "connect failed";
    });
//    QObject::connect(&_socket, &QTcpSocket::error(QAbstractSocket::SocketError), [](QAbstractSocket::SocketError e){
//        qDebug() << "connect error";
//    });
    qDebug() << _socket.error();
    qDebug() << _socket.state();
    _socket.connectToHost(address, port);
    _socket.waitForConnected();
    qDebug() << _socket.isOpen();
    qDebug() << _socket.isValid();
    qDebug() << _socket.isReadable();
    qDebug() << _socket.isWritable();
    qDebug() << _socket.error();
    qDebug() << _socket.state();
}

void MyClient::send()
{
    _socket.write("hello");
}
