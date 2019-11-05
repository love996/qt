#include "common.h"

// if p2 is in p1
bool isInViewRange(const QPoint &p1, const QPoint &p2, int view_size)
{
    auto [posl, posr] = getViewRangePos(p1, view_size);
    return p2.x() >= posl.x() && p2.x() <= posr.x()
        && p2.y() >= posl.y() && p2.y() <= posr.y();
}

/*




void moveUp(QPoint &p, int step, int limitDown)
{
    p.setY(p.y() - step);
    while (limitDown > 0 && p.y() < 0) {
        p.setY(limitDown + p.y());
    }
}



void moveDown(QPoint &p, int step, int limitDown)
{
    p.setY(p.y() + step);
    while (limitDown > 0 && p.y() > limitDown) {
        p.setY(p.y() - limitDown);
    }
}

void moveLeft(QPoint &p, int step, int limitRight)
{
    p.setX(p.x() - step);
    while (limitRight > 0 && p.x() < 0) {
        p.setX(limitRight + p.x());
    }
}

void moveRight(QPoint &p, int step, int limitRight)
{
    p.setX(p.x() + step);
    while (limitRight > 0 && p.x() > limitRight) {
        p.setX(p.x() - limitRight);
    }
}
*/
