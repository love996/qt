#ifndef EVENTLOOP_H
#define EVENTLOOP_H

class QThread;

void init();

QThread &event_thread();

#endif // EVENTLOOP_H
