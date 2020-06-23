#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

#include "event.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Event event;
    emit event.signal_msg_sync();
    emit event.signal_msg_queue();
    qDebug() << "emit signal msg";

    w.show();




    return a.exec();
}
