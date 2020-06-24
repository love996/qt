#include "eventloop.h"
#include <QThread>
#include <QApplication>
#include <QDebug>
#include "alwaysrun.h"

static QThread g_thread;



void init()
{
    static AlwaysRun run(&event_thread());
//    run.moveToThread(&event_thread());
//    event_thread().start();
}

QThread &event_thread()
{
    qDebug() << "thread status is running:" << g_thread.isRunning();
    return g_thread;
}
