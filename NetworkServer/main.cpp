#include <QCoreApplication>
#include "tcpserver.h"
#include "udpserver.h"
#include "udpclient.h"
#include <QTimer>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // TcpServer server(QHostAddress::Any, 12345);
    UdpServer server("127.0.0.1", 12345);
    UdpClient client("127.0.0.1", 12345);

    char buffer[] = "hello world";

    QTimer timer;
    timer.setInterval(1000);
    QObject::connect(&timer, &QTimer::timeout,
                     &client, std::bind(&UdpClient::write, &client, buffer, sizeof(buffer)-1));
    timer.start();

    return a.exec();
}
