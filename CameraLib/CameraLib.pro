CONFIG -= qt

TEMPLATE = lib
DEFINES += CAMERALIB_LIBRARY

CONFIG += c++11

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
    camera.cpp \
    cameralib.cpp \
    error_info.cpp \
    icamera.cpp

HEADERS += \
    CameraLib_global.h \
    camera.h \
    cameralib.h \
    error_info.h \
    icamera.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}

INCLUDEPATH += D:\\third_party\\opencv4_3_0\\install\\include
LIBS += -LD:\\third_party\\opencv4_3_0\\install\x64\\mingw\\bin \
        -lopencv_core430 -lopencv_videoio430 -lopencv_imgcodecs430 \
        -lopencv_highgui430
!isEmpty(target.path): INSTALLS += target
