#include "printerserialport.h"
#include <QMessageBox>

PrinterSerialPort::PrinterSerialPort(const QString &name, QObject *parent)
    : QObject(parent)
     ,_serial_port(name)
{
    QObject::connect(&_serial_port, &QSerialPort::readyRead,
                     this, &PrinterSerialPort::readyRead);
    _serial_port.setBaudRate(QSerialPort::Baud19200);
    _serial_port.setDataBits(QSerialPort::Data8);
    _serial_port.open(QSerialPort::ReadWrite);
    _timer.setInterval(500);
    QObject::connect(&_timer, &QTimer::timeout,
                     this, &PrinterSerialPort::queryStatus);
    _timer.start();
}

void PrinterSerialPort::queryStatus()
{
    char buffer[] = {0x10, 0x04, 0x02};
    _serial_port.write(buffer, sizeof(buffer));
}

void PrinterSerialPort::readyRead()
{
    auto bytes = _serial_port.readAll();
    for (auto b : bytes) {
        printf("%0X ", b);
    }
    printf("\n");
    checkStatus(bytes[0]);
}

void PrinterSerialPort::checkStatus(int status)
{
    bool noPaper = status & 0x20;
    if (noPaper) {
        _timer.stop();
        if (QMessageBox::Retry ==
                QMessageBox::warning(nullptr, "status", "no paper", QMessageBox::Retry | QMessageBox::Ignore)) {
            _timer.start();
        }
        else {
        }
    }
}
