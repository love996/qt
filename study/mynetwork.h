#ifndef MYNETWORK_H
#define MYNETWORK_H
#include <QObject>

class MyNetWork : public QObject
{
    Q_OBJECT
public:
    MyNetWork(QObject *parent = nullptr);
    ~MyNetWork(){}
    void httpGet();
public:
signals:
private slots:
};

#endif // MYNETWORK_H
