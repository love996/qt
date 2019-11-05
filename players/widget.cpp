#include "widget.h"
#include "ui_widget.h"

#include <QPixmap>
#include <QPainter>

#include <cstdlib>
#include <time.h>
//#include <QDebug>
//#include <iostream>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    srand(time(nullptr));

    QObject::connect(&timer_run, &QTimer::timeout,
                     [this](){
        ui->player_map->playerRun( ui->running_speed->value());
    });
    QObject::connect(&timer_update_map, &QTimer::timeout,
                     [this](){
        ui->player_map->update();
    });
    ui->player_map->setViewRange(ui->view_range->value());
    timer_run.setInterval(1000);
    timer_update_map.setInterval(1000);
    // std::cout << "开始" << std::endl;
    qDebug("开始");
}

void Widget::paintEvent(QPaintEvent *event)
{
    return QWidget::paintEvent(event);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_add_player_clicked()
{
    ui->player_map->addPlayerCount(ui->add_player_count->text().toInt());
    ui->player_map->update();
}

void Widget::on_is_running_stateChanged(int state)
{
    if (state == Qt::CheckState::Checked) {
        timer_run.start();
        timer_update_map.start();
    }
    else {
        timer_run.stop();
        timer_update_map.stop();
        ui->player_map->update();
    }
}

void Widget::on_next_player_clicked()
{
    ui->player_map->nextPlayer();
}

void Widget::on_view_range_valueChanged(int value)
{
    ui->player_map->setViewRange(value);
}
