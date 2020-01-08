#include "mytest.h"

#include <QTest>
#include <QDebug>

QTEST_MAIN(MyTest)

MyTest::MyTest(QObject *parent)
    :QObject(parent)
{

}

void MyTest::json()
{
    qDebug() << "json";
}
