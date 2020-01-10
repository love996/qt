#include "widget.h"
#include "testjson.h"
#include "func.h"
#include "httpclient.h"
#include <QFile>

#include <QApplication>
#include "testslot.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    testJson();
    HttpClient client("http://www.baidu.com");
    client.get("/", [](std::shared_ptr<HttpResponse> resp){
        QFile file("out.html");
        file.open(QFile::WriteOnly);
        file.write(resp->body);
        file.close();
    });
    client.download(QUrl("https://middle-oss.oss-cn-shenzhen.aliyuncs.com/ota/20200109/0lihuE_32503d8a137e49c6b3605630de9fb0fb.jpg"), [](std::shared_ptr<HttpResponse> resp){
        qDebug() << resp->headerList;
        QFile file("image.jpg");
        file.open(QFile::WriteOnly);
        file.write(resp->body);
        file.close();
    });
    //https://dl.pstmn.io/download/latest/win64
    client.download(QUrl("http://117.143.109.160/cache/mirrors.ustc.edu.cn/qtproject/archive/qt/5.12/5.12.6/qt-opensource-windows-x86-5.12.6.exe?ich_args2=135-03183104063132_660e9ea433e9829c33acd45f1991c1bd_10001002_9c896324d7c7f6d59f3f518939a83798_bbd4a790ebdfab15c815c8755ed0a68f"), [](std::shared_ptr<HttpResponse> resp){
        qDebug() << resp->headerList;

    });
//    client.get("/", [](std::shared_ptr<HttpResponse> resp){
//        qDebug() << resp->headerList;
//        qDebug() << resp->body.size();
//        qDebug() << "22222";
//        QFile file("out.html");
//        file.open(QFile::WriteOnly);
//        file.write(resp->body);
//        file.close();
//        qDebug() << resp->body;
//    });
    testSlotFunc();
    w.show();
    return a.exec();
}
