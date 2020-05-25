#ifndef PRINTER_H
#define PRINTER_H
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QPrinter>
#include <QPrinterInfo>
#include <QBitmap>
#include <QPixmap>
#include <QImage>
#include <QRgb>
#include <fstream>

inline std::pair<unsigned char, unsigned char> toLH(ushort n)
{
    return {n & 0xff, (n % 0xff00) >> 8 };
}

inline std::string hex2str(char *ptr, int size)
{
    char buffer[3];
    std::string str;
    for (int i = 0; i < size; ++i) {
        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "%02X", ptr[i]);
        str.append(buffer);
        // qDebug() << size << str.c_str();
    }
    return str;
}

class Printer : public QObject
{
    Q_OBJECT
public:
    Printer(QString name)
        :serialport(name)
         // _bitmap("img/ticket.bmp")
    {
        for (auto & port : QSerialPortInfo::availablePorts()) {
            qDebug() << port.portName();
        }
        qDebug() << _bitmap.load("img/ticket.bmp");
        qDebug() << "databit:" << serialport.setDataBits(QSerialPort::Data8);
        qDebug() << "setBaudRate:" << serialport.setBaudRate(QSerialPort::Baud9600);
        qDebug() << "open:" << serialport.open(QSerialPort::ReadWrite);
        QObject::connect(&serialport, &QSerialPort::readyRead, [this]{
            char rbuffer[256] = {};
            auto rbyte = serialport.read(rbuffer, sizeof(rbuffer));
            qDebug() << "received" << rbyte;
            for (int i = 0; i < rbyte; ++i) {
                qDebug() << (int)rbuffer[i];
                qDebug() << "no papper:" << (bool)(rbuffer[i] & 0x20) << endl;
            }
        });

        const char *_format = R"(1B 40
%s
1B 33 00
0A
)";

        // bitmap = "1D 6B 61 08 02 08 00 30 31 32 33 34 35 36 37";
        auto [wl, wh] = toLH(_bitmap.width());
        auto [hl, hh] = toLH(_bitmap.height());
        // auto data = toHex(img);
        QString data;
        qDebug() << "start" << _bitmap.width() << _bitmap.height();
        for (int h = 0; h < _bitmap.height(); ++h) {
            QString line;
            for ( int w = 0; w < _bitmap.width(); ++w) {
                // qDebug() << "(" << w << "," << h << ")";
                QRgb pixel = _bitmap.pixel(w, h);
                int gray = qGray(pixel);
                line += QString::number(static_cast<unsigned char>(gray), 16);
            }
            line = QString::asprintf("1b 2a 00 %02X %02X %s", wl, wh, line.toStdString().c_str());
            _cmd += QString::asprintf(_format, line.toStdString().c_str());
            // break;
        }
        // grayImg.save("gray.bmp");
        // _cmd = _cmd.sprintf(_cmd.toStdString().c_str(), data.toStdString().c_str());
        qDebug() << _cmd;
        std::ofstream ofs("cmd.txt");
        ofs.write(_cmd.toStdString().c_str(), _cmd.toStdString().size());
        ofs.close();
        _cmd = _cmd.simplified();
        _cmd.remove(' ');
        qDebug() << _cmd;
        getchar();
        std::vector<unsigned char> datas;
        for (int i = 0; i < _cmd.size(); i += 2) {
            datas.push_back(_cmd.mid(i, 2).toInt(nullptr, 16));
        }
        qDebug() << "send bytes:" << serialport.write((const char*)datas.data(), datas.size());
        for (auto &name : QPrinterInfo::availablePrinterNames()) {
            qDebug() << name;
        }
    }
private:
    QSerialPort serialport;
    QPrinter printer;
    QImage _bitmap;
    QString _cmd;
};

#endif // PRINTER_H
