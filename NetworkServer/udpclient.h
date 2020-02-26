#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include "udpbase.h"


class UdpClient : public UdpBase
{
public:
    UdpClient(const QHostAddress &host, quint16 port);
    UdpClient(const QString &host, quint16 port);

    qint64 write(const char *data, qint64 size);
private:
    void init();
};

#endif // UDPCLIENT_H
