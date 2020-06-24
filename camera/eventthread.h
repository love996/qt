#ifndef EVENTTHREAD_H
#define EVENTTHREAD_H
#include <QThread>


class EventThread : public QThread
{
    Q_OBJECT
public:
    EventThread();
};

#endif // EVENTTHREAD_H
