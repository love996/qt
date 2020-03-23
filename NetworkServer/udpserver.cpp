#include "udpserver.h"

void serverRead(QUdpSocket &socket)
{
    char buffer[BUFFER_SIZE] = {0};
    QHostAddress host;
    quint16 port;
    socket.readDatagram(buffer, sizeof(buffer), &host, &port);
    qDebug() << buffer;
    char sb[] = "server echo hello world!";
    qDebug() << host << ":" << port;
    socket.writeDatagram(sb, sizeof(sb)-1, host, port);
}

UdpServer::UdpServer(const QHostAddress &host, quint16 port)
    :UdpBase(host, port)
{
    init();
}

UdpServer::UdpServer(const QString &host, quint16 port)
    :UdpServer(QHostAddress(host), port)
{

}

void UdpServer::init()
{
    _socket.bind(_port);
    _cbRead = serverRead;
    QObject::connect(&_socket, &QUdpSocket::readyRead, this, std::bind(_cbRead, std::ref(_socket)));
}
