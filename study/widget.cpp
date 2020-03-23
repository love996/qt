#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    dialog = new Ui_Dialog;
    dialog->setupUi(&_uiDialog);
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete dialog;
    delete ui;
}


void Widget::on_pushButton_pressed()
{
    qDebug() << __FUNCTION__;
    // _timerPressed.setInterval(3000);
    _timerPressed.setSingleShot(true);
    QObject::connect(&_timerPressed, &QTimer::timeout, [this]{
        _uiDialog.setModal(true);
        _uiDialog.show();
    });
    _timerPressed.start(3000);
}

void Widget::on_pushButton_released()
{
    _timerPressed.stop();
}
