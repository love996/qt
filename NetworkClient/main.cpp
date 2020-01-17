#include <QCoreApplication>
#include "tcpconnection.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TcpConnection connection("127.0.0.1", 12345);
    return a.exec();
}
