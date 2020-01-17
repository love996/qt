#include "testzip.h"
#include "JlCompress.h"
#include <QDebug>
void testunzip()
{
    qDebug() << "解压";
    qDebug() << "解压结果:" << JlCompress::extractDir("D:\\ota\\20200117\\ota_linux.zip", "D:\\ota\\20200117\\ota_linux");
}

