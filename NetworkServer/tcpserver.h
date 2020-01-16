#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>

#include "tcpconnection.h"

class TcpServer// : public QObject
{
    //Q_OBJECT
public:
public:
    explicit TcpServer(const QHostAddress &addr, quint16 port, QObject *parent = nullptr);
    ~TcpServer();

    void connected();

//signals:

//public slots:

private:
    QTcpServer _server;

    void initSlogs();
};

#endif // TCPSERVER_H
