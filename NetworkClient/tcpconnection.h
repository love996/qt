#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <memory>

#include <QObject>
#include <QTcpSocket>


class TcpConnectionBase//  : public QObject
{
    //Q_OBJECT
public:
    using ReadyReadCallback = void (*)(std::shared_ptr<QTcpSocket>);
    using ReadCallback = void (*)(int length);
public:
    // TcpConnection();
    TcpConnectionBase(std::shared_ptr<QTcpSocket> socketPtr/*QObject *parent = nullptr*/);
    TcpConnectionBase(const QHostAddress &addr, quint16 port);
    TcpConnectionBase(const QString &addr, quint16 port);
    virtual ~TcpConnectionBase(){}
    void connect(const QHostAddress &addr, quint16 port);
    void setSocket(std::shared_ptr<QTcpSocket> socketPtr);
    void registerReadyReadCallback(ReadyReadCallback cb);
    // void finishedCallback(QByteArray &buffer, ReadCallback cb);
    // signals:
protected:
    virtual void readyRead(std::shared_ptr<QTcpSocket> socketPtr) = 0;

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

class TcpConnection : public TcpConnectionBase
{
    using TcpConnectionBase::TcpConnectionBase;
public:
    virtual void readyRead(std::shared_ptr<QTcpSocket> socketPtr) override;
};

#endif // TCPCONNECTION_H
