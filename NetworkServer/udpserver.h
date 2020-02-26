#ifndef UDPSERVER_H
#define UDPSERVER_H


#include <set>
#include <memory>

#include <QObject>
#include <QUdpSocket>
#include <QTimer>

#include "udpbase.h"

class UdpServer : public UdpBase
{
    Q_OBJECT
public:
    UdpServer(const QHostAddress &host, quint16 port);
    UdpServer(const QString &host, quint16 port);
private:
    void init();
protected:
};

#endif // UDPSERVER_H
