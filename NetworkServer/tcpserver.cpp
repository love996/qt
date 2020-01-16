#include "tcpserver.h"

TcpServer::TcpServer(const QHostAddress &addr, quint16 port, QObject *parent)
    : QObject(parent)
{
    _server.listen(addr, port);
    // 处理连接

}

TcpServer::~TcpServer()
{
}

void TcpServer::registerCallBack(TcpServer::SocketCallback cb)
{

}
