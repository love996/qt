#ifndef ALWAYSRUN_H
#define ALWAYSRUN_H

#include <QObject>
#include <QThread>

class AlwaysRun : public QObject
{
    Q_OBJECT
public:
    explicit AlwaysRun(QThread *t, QObject *parent = nullptr)
        :QObject(parent)
    {
        QObject::connect(this, &AlwaysRun::sig_nothing,
                         this, &AlwaysRun::slot_nothing);
        this->moveToThread(t);
        t->start();
    }

signals:
    void sig_nothing();
public slots:
    void slot_nothing(){}

};

#endif // ALWAYSRUN_H
