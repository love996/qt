#include "common.h"

// if p2 is in p1
bool isInViewRange(const QPoint &p1, const QPoint &p2, int view_range)
{
    int left = p1.x() - view_range;
    int right = p1.x() + view_range;
    int up = p1.y() - view_range;
    int down = p1.y() + view_range;
    return p2.x() >= left && p2.x() <= right
        && p2.y() >= up && p2.y() <= down;
}



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
