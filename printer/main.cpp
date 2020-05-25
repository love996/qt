//#include <QPrinter>
//#include <QPrinterInfo>
#include <QDebug>
//#include <QSerialPort>
#include <QSerialPortInfo>
#include <memory>
#include <iostream>
#include <filesystem>
#include <QCoreApplication>
#include "printer.h"
#include <QApplication>
#include "printerserialport.h"

//#undef UNICODE
//#include <Windows.h>
//extern "C" {
//#include <hidsdi.h>
//#include <SetupAPI.h>
//}


#include "libusb/libusb.h"
#include "libusb/libusbi.h"
//#include "libusb/hotplug.h"
#include <QSerialPort>
#include <QPainter>

void get_last_error()
{
    DWORD errorCode = GetLastError();
    qDebug() << "errorCode:" << errorCode;
    char *text;
    FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                  FORMAT_MESSAGE_IGNORE_INSERTS, NULL, errorCode,
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                  (LPSTR)&text, 0, NULL);
    std::cout << text;

    LocalFree(text);
}

static void print_devs(libusb_device **devs)
{
    libusb_device *dev;
    int i = 0, j = 0;
    uint8_t path[8];

    while ((dev = devs[i++]) != NULL) {
        printf("priv:%s bus_number:%04x port:%04x address:%04x\n",
               dev->os_priv,
               dev->bus_number,
               dev->port_number,
               dev->device_address);
        struct libusb_device_descriptor desc;
        int r = libusb_get_device_descriptor(dev, &desc);
        if (r < 0) {
            fprintf(stderr, "failed to get device descriptor");
            return;
        }

        printf("vid:%04x: pid:%04x (bus %d, device %d)",
            desc.idVendor, desc.idProduct,
            libusb_get_bus_number(dev), libusb_get_device_address(dev));

        r = libusb_get_port_numbers(dev, path, sizeof(path));
        if (r > 0) {
            printf(" path: %d", path[0]);
            for (j = 1; j < r; j++)
                printf(".%d", path[j]);
        }
        printf("\n");

    }
}

class DevPrinter
{
public:
    DevPrinter(const std::string&);
    ~DevPrinter();

public:
    void printer(const QPixmap&);
private:
    std::shared_ptr<QPrinter> m_ptrPrinter;
};

DevPrinter::DevPrinter(const std::string &strName)
{
    m_ptrPrinter = std::make_shared<QPrinter>(QPrinter::ScreenResolution);
    QStringList listPrinter = QPrinterInfo::availablePrinterNames();
    QString strPrinterName;
    for (const auto& printer : listPrinter) {
        if (printer.contains(QString::fromStdString(strName)))  {
            strPrinterName = printer;
        }
    }
    if (!strPrinterName.isEmpty()) {
        m_ptrPrinter->setPrinterName(strPrinterName);
        m_ptrPrinter->setPageMargins(0, 0, 0, 0, QPrinter::DevicePixel);
    }
}

DevPrinter::~DevPrinter()
{
}

void DevPrinter::printer(const QPixmap &pixmap)
{
    if (!m_ptrPrinter->isValid()) {
        return;
    }
    QPrinter printer(QPrinter::HighResolution);
    QPainter painter(&printer);
    QRect rect = painter.viewport();
    QSize size = pixmap.size();
    painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
    painter.setWindow(pixmap.rect());
    painter.drawPixmap(0, 0, pixmap);
}
#include "dialog.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Dialog dlg;
    qDebug() << "我是中文";
    qDebug() << QPrinterInfo::availablePrinterNames();
    DevPrinter printer("POS58 Printer");
    QPixmap pixmap("./img/ticket2.bmp");
    printer.printer(pixmap);
    PrinterSerialPort printerSerialPort("COM3");
    dlg.show();
    return app.exec();
}
