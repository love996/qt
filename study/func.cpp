#include "func.h"
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QByteArray>

void testDataStream()
{

    QFile file("file.txt");
    file.open(QFile::ReadWrite);
    QByteArray str;
    QTextStream stream(&str);
    stream << "abc" << 1 << "200" << 1.23;
    qDebug() << str;
    file.write(str);
}
