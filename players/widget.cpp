#include "widget.h"
#include "ui_widget.h"

#include <QPixmap>
#include <QPainter>

#include <cstdlib>
#include <time.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    srand(time(nullptr));
}

void Widget::paintEvent(QPaintEvent *event)
{

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_add_player_clicked()
{
    ui->player_map->update();
    // ui->player_map->
}
