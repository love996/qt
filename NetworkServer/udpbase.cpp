#include "udpbase.h"
#include <string.h>
void defaultRead(QUdpSocket &socket)
{
    char buffer[40960] = {0};
    socket.readDatagram(buffer, sizeof(buffer));
    qDebug() << buffer;
}

UdpBase::UdpBase(const QHostAddress &addr, quint16 port)
    :_host(addr),
     _port(port)
{
    _cbRead = defaultRead;
}

UdpBase::UdpBase(const QString &addr, quint16 port)
    :UdpBase(QHostAddress(addr), port)
{

}

void UdpBase::readCallback(UdpBase::ReadCallback &&cb)
{
    _cbRead = std::forward<UdpBase::ReadCallback>(cb);
}
