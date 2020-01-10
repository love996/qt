#ifndef TESTSLOT_H
#define TESTSLOT_H

#include <QObject>
#include <memory>

class TestSlot : public QObject
{
    Q_OBJECT
public:
    TestSlot();
//public: signals:
//    void sendData(std::unique_ptr<char> &&ptr);
//public slots:
//    void receiveData(std::unique_ptr<char> &&ptr);
};

void testSlotFunc();

#endif // TESTSLOT_H
