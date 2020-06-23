#ifndef EVENT_H
#define EVENT_H

#include <QObject>

class Event : public QObject
{
    Q_OBJECT
public:
    Event();
public:
signals:
    void signal_msg_queue();
    void signal_msg_sync();
public slots:
    void on_signal_msg();
};



#endif // EVENT_H
