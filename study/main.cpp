#include "widget.h"
#include "testjson.h"
#include "func.h"
#include "mynetwork.h"
#include "mynetmanager.h"
#include "httpclient.h"
#include <QFile>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
//    QNetworkAccessManager *netManager =new QNetworkAccessManager();
//    MyNetManager manager(netManager);
//    manager.get(QUrl("http://blog.csdn.net/u010002704"));
    HttpClient client("http://www.baidu.com");
    client.get("/", [](std::shared_ptr<HttpResponse> resp){
        qDebug() << resp->headerList;
        qDebug() << resp->body.size();
        QFile file("out.html");
        file.open(QFile::WriteOnly);
        file.write(resp->body);
        file.close();
        qDebug() << resp->body;
    });
    w.show();
    return a.exec();
}
