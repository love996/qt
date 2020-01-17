#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <set>
#include <memory>

#include <QObject>
#include <QTcpServer>

class TcpServer //: public QObject
{
    //Q_OBJECT
public:
    using ConnectedCallback = void (*)(std::shared_ptr<QTcpSocket>);
public:
    TcpServer(const QHostAddress &addr, quint16 port);
    TcpServer(const QString &addr, quint16 port);
    ~TcpServer();
    void registerConnectedCallback(ConnectedCallback cb);
    void error(QAbstractSocket::SocketError e);

//signals:

//public slots:

private:
    QTcpServer _server;
    ConnectedCallback _cb;
    std::set<std::shared_ptr<QTcpSocket>> _delegateConnections;
private:
    void initSlots();
    void newConnection();

protected:
};

#endif // TCPSERVER_H
