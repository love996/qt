#include "testslot.h"
#include <QDebug>
#include <QThread>
using namespace std;
TestSlot::TestSlot()
{
    // QObject::connect(this, &TestSlot::sendData, this, &TestSlot::receiveData);
}

//void TestSlot::receiveData(std::unique_ptr<char> &&ptr)
//{
//    qDebug() << ptr.get();
//}

TestSlot slot;

void testSlotFunc()
{
    QThread t;
//    slot.moveToThread(&t);
//    auto ptr = unique_ptr<char>(new char[20]);
//    strcpy(ptr.get(), "hello");
//    emit slot.sendData(std::move(ptr));
}
