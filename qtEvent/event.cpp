#include "event.h"
#include <QMessageBox>

Event::Event()
    :QObject(nullptr)
{
    QObject::connect(this, &Event::signal_msg_queue,
                     this, &Event::on_signal_msg,
                     Qt::QueuedConnection);
    QObject::connect(this, &Event::signal_msg_sync,
                     this, &Event::on_signal_msg,
                     Qt::DirectConnection);
}

void Event::on_signal_msg()
{
    QMessageBox msg;
    msg.setText("signal msg");
    msg.exec();
}
