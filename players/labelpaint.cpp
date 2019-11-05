#include "labelpaint.h"

#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QTime>


LabelPaint::LabelPaint(QWidget *parent, Qt::WindowFlags f)
    :QLabel(parent, f)
{
}

void LabelPaint::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    player_map.showPalyer(&painter);
    // player_map
    return QLabel::paintEvent(event);
}

void LabelPaint::resizeEvent(QResizeEvent *e)
{
    player_map.reset(e->size());
}

void LabelPaint::playerRun(int step)
{
    QTime startTime = QTime::currentTime();



    player_map.playersRun(step);
    QTime stopTime = QTime::currentTime();
    int elapsed = startTime.msecsTo(stopTime);
    qDebug()<<"QTime.currentTime ="<<elapsed<<"ms";
}

void LabelPaint::addPlayerCount(int count)
{
    player_map.addPlayerCount(count);
}

void LabelPaint::nextPlayer()
{
    player_map.nextPlayer();
}
