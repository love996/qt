#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <memory>

#include <QObject>
#include <QTcpSocket>


class TcpConnection// : public QObject
{
    //Q_OBJECT
public:
    using ReadyReadCallback = void (*)(std::shared_ptr<QTcpSocket>);
    using ReadCallback = void (*)(int length);
public:
    // TcpConnection();
    TcpConnection(std::shared_ptr<QTcpSocket> socketPtr/*QObject *parent = nullptr*/);
    TcpConnection(const QHostAddress &addr, quint16 port);
    TcpConnection(const QString &addr, quint16 port);
    void connect(const QHostAddress &addr, quint16 port);
    void setSocket(std::shared_ptr<QTcpSocket> socketPtr);
    void registerReadyReadCallback(ReadyReadCallback cb);
    // void finishedCallback(QByteArray &buffer, ReadCallback cb);
    // signals:

private:
    std::shared_ptr<QTcpSocket> _socketPtr;
    ReadyReadCallback _cb;
    std::vector<QMetaObject::Connection> _slots;
// public slots:

private:
    void initSlots();
    void clear();

    void socketError(QAbstractSocket::SocketError);
};

#endif // TCPCONNECTION_H
