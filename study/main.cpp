#include "widget.h"
#include "testjson.h"
#include "func.h"
#include "httpclient.h"
#include <QFile>
#include <thread>

#include <QApplication>
#include <QThread>

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
    client.download(QUrl("http://file02.16sucai.com/d/file/2014/0704/e53c868ee9e8e7b28c424b56afe2066d.jpg"), [](std::shared_ptr<HttpResponse> resp){
        qDebug() << resp->headerList;
        QFile file("image.jpg");
        file.open(QFile::WriteOnly);
        file.write(resp->body);
        file.close();
    });
    {
        QThread t;
        client.moveToThread(&t);
        t.wait();
    }
    //https://dl.pstmn.io/download/latest/win64
//    client.download(QUrl("http://117.143.109.160/cache/mirrors.ustc.edu.cn/qtproject/archive/qt/5.12/5.12.6/qt-opensource-windows-x86-5.12.6.exe?ich_args2=135-03183104063132_660e9ea433e9829c33acd45f1991c1bd_10001002_9c896324d7c7f6d59f3f518939a83798_bbd4a790ebdfab15c815c8755ed0a68f"), [](std::shared_ptr<HttpResponse> resp){
//        qDebug() << resp->headerList;
//        qDebug() << "download:" << resp->downloadFile << "finished";
//    });
    w.show();
    return a.exec();
}
