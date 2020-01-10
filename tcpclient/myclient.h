#ifndef MYCLIENT_H
#define MYCLIENT_H
#include <QTcpSocket>
#include <QHostAddress>
class MyClient
{
public:
    MyClient(QHostAddress address, quint16 port);
    void send();
private:
    QTcpSocket _socket;
};

#endif // MYCLIENT_H
