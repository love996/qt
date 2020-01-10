#include <QCoreApplication>
#include "myserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    MyServer server(QHostAddress(QString("0.0.0.0")), 12345);
    return app.exec();
}
