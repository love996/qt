#ifndef THREADCONNECTION_H
#define THREADCONNECTION_H

#include <QThread>

class ThreadConnection : public QThread
{
public:
    ThreadConnection();
    virtual void run() override;
};

#endif // THREADCONNECTION_H
