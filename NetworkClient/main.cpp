#include <QCoreApplication>
#include "tcpconnection.h"
#include "threadconnection.h"
#include <QEventLoop>
#include <QEventLoopLocker>

#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // TcpConnection connection("127.0.0.1", 12345);
    std::thread([]{
        QEventLoop eventLoop;
        TcpConnection connection("127.0.0.1", 12345);
        eventLoop.exec();
    }).detach();
    ThreadConnection tconnection;
    qDebug() << tconnection.thread();
    tconnection.start();
    return a.exec();
}
