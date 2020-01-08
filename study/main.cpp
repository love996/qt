#include "widget.h"
#include "testjson.h"
#include "func.h"
#include "mynetwork.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Widget w;
    testJson();
    MyNetWork myNetWork;
    myNetWork.httpGet();
    // w.show();
    return a.exec();
}
