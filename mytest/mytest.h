#ifndef MYTEST_H
#define MYTEST_H


#include <QObject>

class MyTest  : public QObject
{
    // Q_OBJECT
public:
    explicit MyTest(QObject *parent = nullptr);
signals:

public slots:
private slots:
    void json();

};

#endif // MYTEST_H
