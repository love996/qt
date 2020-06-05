#include "util.h"
#include <QGuiApplication>
#include <QScreen>

QPixmap captureScreen()
{
    auto screen = QGuiApplication::primaryScreen();
    return screen->grabWindow(0);
}
