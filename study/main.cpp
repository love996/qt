#include "widget.h"
#include "testjson.h"
#include "func.h"
#include "mynetwork.h"
#include "mynetmanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
//    QNetworkAccessManager *netManager =new QNetworkAccessManager();
//    MyNetManager manager(netManager);
//    manager.get(QUrl("http://blog.csdn.net/u010002704"));
    MyNetWork network;
    network.httpGet();
    w.show();
    return a.exec();
}
