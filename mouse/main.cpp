#include "mousedialog.h"

#include <QApplication>
#include <QMouseEvent>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MouseDialog w;
    w.show();
    return a.exec();
}
