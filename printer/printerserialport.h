#ifndef PRINTERSERIALPORT_H
#define PRINTERSERIALPORT_H

#include <QObject>
#include <QString>
#include <QSerialPort>
#include <QTimer>

class PrinterSerialPort : public QObject
{
    Q_OBJECT
public:
    explicit PrinterSerialPort(const QString &name, QObject *parent = nullptr);
    void queryStatus();
signals:

public slots:
    void readyRead();
private:
    QString _name;
    QSerialPort _serial_port;
    QTimer _timer;
private:
    void checkStatus(int status);
};

#endif // PRINTERSERIALPORT_H
