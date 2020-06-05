#include "mousedialog.h"
#include "ui_mousedialog.h"
#include <QMouseEvent>
#include <QDebug>
#include <windows.h>
#include <QDesktopWidget>
#include <QMessageBox>

#include "util.h"

MouseDialog::MouseDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MouseDialog)
{
    ui->setupUi(this);
    qDebug() << (void*)this->parentWidget();
    this->setMouseTracking(true);
    // this->grabMouse();
    // this->setEnabled(true);
    _screen_ptr = window()->screen();
    WId wid = winId();
    qDebug() << _screen_ptr->geometry();
    QObject::connect(&_timer_mouse, &QTimer::timeout,
                     this, &MouseDialog::moveMouse);

    // _timer_mouse.start(2000);
    // QCursor::setPos(_start_menu);

    moveMouse();
    auto pixmap = captureScreen();
    pixmap.save("screen.png");

}

MouseDialog::~MouseDialog()
{
    delete ui;
}

void MouseDialog::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "received mouse move";
    ui->mouse_x->setText(QString("x:%1").arg(event->globalX()));
    ui->mouse_y->setText(QString("y:%1").arg(event->globalY()));
    return QDialog::mouseMoveEvent(event);
}

void MouseDialog::moveMouse()
{
    auto desktop_ptr = QApplication::desktop();
    qDebug() << "moveMouse";
    QPointF p{100, 100};
    p = _start_menu;
//    QMouseEvent *event = new QMouseEvent(QEvent::MouseMove,
//                                         p,
//                                         Qt::NoButton,
//                                         Qt::NoButton,
//                                         Qt::NoModifier);
//    QApplication::sendEvent(this, event);
    // desktop_ptr-
    QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonPress, p,
                      Qt::LeftButton, Qt::LeftButton,
                      Qt::NoModifier);
    QApplication::sendEvent(desktop_ptr, event);
    event = new QMouseEvent(QEvent::MouseButtonRelease, p,
                      Qt::LeftButton, Qt::LeftButton,
                      Qt::NoModifier);
    QApplication::sendEvent(desktop_ptr, event);
//    ::mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
//    ::mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}


void MouseDialog::on_click_clicked()
{
    QMessageBox msg;
    msg.setText("clicked");
    msg.exec();
}

void MouseDialog::on_pushButton_clicked()
{
    QMessageBox msg;
    msg.setText("clicked");
    msg.exec();
}
