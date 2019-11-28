#include "labelpaint.h"

#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <chrono>


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
    using namespace std;
    auto t1 = chrono::steady_clock::now();

    player_map.playersRun(step);
    auto t2 = chrono::steady_clock::now();

    auto d = chrono::duration_cast<chrono::microseconds>(t2 - t1);

    qDebug() << "time elpease =" << d.count() << "us";
}

void LabelPaint::addPlayerCount(int count)
{
    player_map.addPlayerCount(count);
}

void LabelPaint::nextPlayer()
{
    player_map.nextPlayer();
}
