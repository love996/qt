#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QObject>
#include <QTcpSocket>

class TcpConnection // : public QObject
{
    // Q_OBJECT
public:
    using ReadyReadCallback = void (*)(QTcpSocket &socket);
    using ReadCallback = void (*)(int length);
public:
    explicit TcpConnection(/*QObject *parent = nullptr*/);
    void connect(const QHostAddress &addr, quint16 port);
    void setSocket(QTcpSocket &&socket);
    void readyReadCallback(ReadyReadCallback cb);
    // void finishedCallback(QByteArray &buffer, ReadCallback cb);
// signals:
private:
    QTcpSocket _socket;
    ReadyReadCallback _cb;
// public slots:

private:
    void initSlots();

    void socketError(QAbstractSocket::SocketError);
};

#endif // TCPCONNECTION_H
