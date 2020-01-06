#include <QFileInfo>
#include <iostream>
#include <QVariant>
#include <QDebug>
#include <fstream>

int main(int argc, char *argv[])
{
    QVariant v;
    int x = 100;
    v.setValue(100);
    qDebug() << v.value<QString>() ;
    std::fstream fs("a.txt", std::ios::in | std::ios::out);
    if (!fs) {
        qDebug() << "打开文件失败";
        return 1;
    }

    return 0;
}
