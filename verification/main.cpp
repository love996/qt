#include "verificationdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VerificationDialog w;
    w.show();
    return a.exec();
}
