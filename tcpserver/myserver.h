#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QMap>
#include <QTcpSocket>
// #include <QObject>
class MyServer //: public QObject
{
    //Q_OBJECT
public:
    MyServer(QHostAddress address, quint16 port);
    ~MyServer();
private:
    QTcpServer _server;
    QMap<QTcpSocket*, QMetaObject::Connection> _clients;
    // QSet<QMetaObject::Connection> _client_conn_objs;
};

#endif // MYSERVER_H
