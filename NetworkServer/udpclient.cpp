#include "udpclient.h"


UdpClient::UdpClient(const QHostAddress &host, quint16 port)
    :UdpBase(host, port)
{
    init();
}

UdpClient::UdpClient(const QString &host, quint16 port)
    :UdpClient(QHostAddress(host), port)
{

}

qint64 UdpClient::write(const char *data, qint64 size)
{
    return _socket.write(data, size);
}

void UdpClient::init()
{
    _socket.connectToHost(_host, _port);
    QObject::connect(&_socket, &QUdpSocket::readyRead, this, std::bind(_cbRead, std::ref(_socket)));
}
