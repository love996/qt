#include <QFileInfo>
#include <iostream>
#include <QVariant>
#include <QDebug>
#include <fstream>
#include <filesystem>

int main(int argc, char *argv[])
{
    QVariant v;
    int x = 100;
    v.setValue(100);
    qDebug() << v.value<QString>() ;
    std::fstream fs("a_中文测试.txt", std::ios::in | std::ios::out);
    if (!fs) {

        std::cout << "打开文件失败\n";
        // return 1;
    }
    std::cout << "打开文件成功\n";
    // qDebug() << QString::fromLatin1("打开文件成功");
    qDebug() << QString::fromStdString("打开文件成功");
    qDebug() << QString::fromUtf8("打开文件成功");

    return 0;
}
