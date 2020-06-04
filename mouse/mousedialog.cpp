#include "mousedialog.h"
#include "ui_mousedialog.h"
#include <QMouseEvent>
#include <QDebug>

MouseDialog::MouseDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MouseDialog)
{
    ui->setupUi(this);
    this->setMouseTracking(true);
    this->grabMouse();
    _screen_ptr = window()->screen();
    WId wid = winId();
    qDebug() << _screen_ptr->geometry();
    QObject::connect(&_timer_mouse, &QTimer::timeout,
                     this, &MouseDialog::moveMouse);
    _timer_mouse.start(2000);
}

MouseDialog::~MouseDialog()
{
    delete ui;
}

void MouseDialog::mouseMoveEvent(QMouseEvent *event)
{
    ui->mouse_x->setText(QString("x:%1").arg(event->globalX()));
    ui->mouse_y->setText(QString("y:%1").arg(event->globalY()));
}

void MouseDialog::moveMouse()
{
    qDebug() << "moveMouse";
    QMouseEvent *event = new QMouseEvent(QEvent::MouseMove, _start_menu,
                      Qt::NoButton, Qt::NoButton,
                      Qt::NoModifier);
    QApplication::sendEvent(this, event);
}

