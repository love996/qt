#include "widget.h"
#include "testjson.h"
#include "pubfunc.h"
#include "httpclient.h"
#include <QFile>
#include <thread>

#include <QApplication>
#include <QThread>
#include "testslot.h"
#include <QDir>
#include <testprocess.h>
#include "testzip.h"

int main(int argc, char *argv[])
{
//    qDebug() << "md5" << fileMD5(argv[0]);
//    qDebug() << QSslSocket::sslLibraryBuildVersionString() ;
//    qDebug() << QSslSocket::supportsSsl();
//    QDir dir("/testdir/testfile.zip");
//    QFile file("/testdir/testfile.zip");
//    QFileInfo fileInfo("/testdir/testfile.zip");

//    qDebug() << dir.dirName();
//    qDebug() << file.fileName() << file.fileName().mid(0, file.fileName().indexOf(".zip"));
//    qDebug() << fileInfo.fileName() << fileInfo.baseName() << fileInfo.absolutePath() << fileInfo.absoluteDir() << fileInfo.absoluteFilePath();
//    return 0;
    TestProcess();
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
    client.download(QUrl("https://middle-oss.oss-cn-shenzhen.aliyuncs.com/ota/20200318/6zVmxh_OTA_ReleaseV0.8.3R.zip"), [](std::shared_ptr<HttpResponse> resp){
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
}


