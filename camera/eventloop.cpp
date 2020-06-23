#include "eventloop.h"
#include <QThread>
#include <QApplication>

static QThread g_thread;

void init(int argc = 0, char *argv[] = nullptr)
{
    QApplication app(argc, argv);
    app.moveToThread(&g_thread);
    // app.exec();
    g_thread.start();
}

QThread &event_thread()
{
    return g_thread;
}
