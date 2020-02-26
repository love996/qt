#ifndef UDPBASE_H
#define UDPBASE_H

#include <QObject>
#include <QUdpSocket>
#include <functional>

#define BUFFER_SIZE 40960

class UdpBase : public QObject
{
    using ReadCallback = std::function<void (QUdpSocket&)>;
public:
    UdpBase(const QHostAddress &addr, quint16 port);
    UdpBase(const QString &addr, quint16 port);
    void readCallback(ReadCallback &&cb);
    void error(QAbstractSocket::SocketError e);

protected:
    QHostAddress _host;
    quint16 _port;
    QUdpSocket _socket;
    ReadCallback _cbRead;
private:
    void init();
};

#endif // UDPBASE_H
