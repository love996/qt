#include "myserver.h"
#include <QTcpSocket>

MyServer::MyServer(QHostAddress address, quint16 port)
{
    QObject::connect(&_server, &QTcpServer::newConnection, [&]{
        auto socket_ptr = _server.nextPendingConnection();
        auto conn_read = QObject::connect(socket_ptr, &QTcpSocket::readyRead, [socket_ptr]{
            char buf[1024] = {0};
            socket_ptr->read(buf, sizeof(buf));
            qDebug() << buf;
        });
        _clients.insert(socket_ptr, conn_read);
    } );
    qDebug() << "listen in" << address << port;
    _server.listen(address, port);
}

MyServer::~MyServer()
{
    for (auto iter = _clients.begin(); iter != _clients.end(); ++iter) {
        delete iter.key();
        QObject::disconnect(iter.value());
    }
//    for (auto &conn_obj : _client_conn_objs) {
//        QObject::disconnect(conn_obj);
//    }
}


