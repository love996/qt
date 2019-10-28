#ifndef COMMON_H
#define COMMON_H
#include <QPoint>

void moveUp(QPoint &p, int step, int limitDown = 0);

void moveDown(QPoint &p, int step, int limitDown = 0);

void moveLeft(QPoint &p, int step, int limitRight = 0);

void moveRight(QPoint &p, int step, int limitRight = 0);

inline void moveUp(QPoint *p, int step, int limitDown = 0)
{
    return moveUp(*p, step, limitDown);
}

inline void moveDown(QPoint *p, int step, int limitDown = 0)
{
    return moveDown(*p, step, limitDown);
}

inline void moveLeft(QPoint *p, int step, int limitDown = 0)
{
    return moveLeft(*p, step, limitDown);
}

inline void moveRight(QPoint *p, int step, int limitDown = 0)
{
    return moveRight(*p, step, limitDown);
}

// if p2 is in p1
bool isInViewRange(const QPoint &p1, const QPoint &p2, int view_range);


#endif // COMMON_H
