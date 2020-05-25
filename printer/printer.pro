QT = gui
QT += serialport printsupport

CONFIG += c++1z console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD\\libusb
LIBS += -L$$PWD
LIBS += -llibusb-1.0 #-lhid -lsetupapi

SOURCES += \
        dialog.cpp \
        main.cpp \
        printerserialport.cpp



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    dialog.h \
    libusb/config.h \
    libusb/darwin_usb.h \
    libusb/haiku_usb.h \
    libusb/haiku_usb_raw.h \
    libusb/hotplug.h \
    libusb/libusb.h \
    libusb/libusbi.h \
    libusb/linux_usbfs.h \
    libusb/poll_posix.h \
    libusb/poll_windows.h \
    libusb/sunos_usb.h \
    lusb0_usb.h \
    printer.h \
    printerserialport.h

DISTFILES += \
    img/ticket.bmp \
    libusb/libusb-1.0.lib

FORMS += \
    dialog.ui
