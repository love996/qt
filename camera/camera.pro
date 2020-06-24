QT       += core gui
QT += mutimedia
QT += mutimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dcamera.cpp \
    eventloop.cpp \
    main.cpp \
    camera.cpp

HEADERS += \
    camera.h \
    dcamera.h \
    eventloop.h \
    image.h \
    util.h

FORMS += \
    camera.ui

INCLUDEPATH += D:\\third_party\\opencv4_3_0\\install\\include
LIBS += -LD:\\third_party\\opencv4_3_0\\install\x64\\mingw\\bin \
        -lopencv_core430 -lopencv_videoio430 -lopencv_imgcodecs430 \
        -lopencv_highgui430

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target