#include "widget.h"
#include "ui_widget.h"

#include <QPixmap>
#include <QPainter>

#include <cstdlib>
#include <time.h>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    srand(time(nullptr));
    ui->player_map->getMap().reset(QPoint(0, 0), ui->player_map->size());
    QObject::connect(&timer_run, &QTimer::timeout,
                     [this](){
        ui->player_map->getMap().playersRun( ui->running_speed->value());
    });
    QObject::connect(&timer_update_map, &QTimer::timeout,
                     [this](){
        ui->player_map->update();
    });
                  // std::bind(&PlayerMap::playersRun, &(ui->player_map->getMap()), ui->running_speed->value()));
    timer_run.setInterval(10);
    timer_update_map.setInterval(50);
    ui->player_map->getMap().setViewRange(ui->view_range->value());
}

void Widget::paintEvent(QPaintEvent *event)
{
//    static int i = 0;
//    qDebug() << "widget paintevent" << ++i;
    return QWidget::paintEvent(event);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_add_player_clicked()
{
    ui->player_map->getMap().addPlayerCount(ui->add_player_count->text().toInt());
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
    ui->player_map->getMap().nextPlayer();
}

void Widget::on_view_range_valueChanged(int value)
{
    ui->player_map->getMap().setViewRange(value);
}
