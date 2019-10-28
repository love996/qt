#include "player.h"
#include <QPainter>
#include <QDebug>



void Player::showViewRange(QPaintDevice *device, QPoint *p, int view_range)
{

    QPainter painter(device);
    QPen pen;
    pen.setColor(QColor(255));
    pen.setWidth(1);
    pen.setStyle(Qt::PenStyle::DashLine);
    painter.setPen(pen);
    QRect rect(p->x() - view_range, p->y() - view_range,
               2*view_range, 2*view_range);
    painter.drawRect(rect);
}

//ViewRange::ViewRange()
//{

//}

//ViewRange::ViewRange(int x1, int y1, int x2, int y2)
//{

//}

//void ViewRange::reset(int x1, int y1, int x2, int y2)
//{
//    p1.rx() = x1;
//    p1.ry() = y1;
//    p2.rx() = x2;
//    p2.ry() = y2;
//}
