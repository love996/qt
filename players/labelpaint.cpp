#include "labelpaint.h"

#include <QPainter>
#include <QDebug>
#include <QTimer>


LabelPaint::LabelPaint(QWidget *parent, Qt::WindowFlags f)
    :QLabel(parent)
{
//    timer.connect(&timer, SIGNAL(timeout()),
//                  this, SLOT(update()));
//    timer.setInterval(1000);
//    timer.start();
}

void LabelPaint::paintEvent(QPaintEvent *event)
{
    // QPainter painter(this);
//    static int i = 0;
//    qDebug() << "label paint " << ++i;
    QPainter painter(this);
    player_map.showPalyer(this);
    return QLabel::paintEvent(event);
}
