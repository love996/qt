#include <QCoreApplication>
#include "myclient.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MyClient client(QHostAddress(QString("0.0.0.0")), 12345);
    client.send();
    return a.exec();
}
