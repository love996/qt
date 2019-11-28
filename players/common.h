#ifndef COMMON_H
#define COMMON_H
#include <QPoint>
#include <map>
#include <iostream>
#include <vector>
#include <set>

template <typename K, typename V, typename Comp = std::less<K>>
using Map = std::map<K, V, Comp>;



template <typename K, typename Comp = std::less<K>>
using Set = std::set<K, Comp>;

inline bool operator<(const QPoint &p1, const QPoint &p2)
{
    return p1.x() < p2.x() && p1.y() < p2.y();
}

inline void move(QPoint &p, int dx, int dy, int limitDown, int limitRight)
{
    p.rx() += dx;
    p.ry() += dy;
    while (limitRight < p.rx()) {
        p.rx() -= limitRight;
    }
    while (limitDown < p.ry()) {
        p.ry() -= limitDown;
    }
    while ( p.rx() < 0) {
        p.rx() += limitRight;
    }
    while( p.ry() < 0) {
        p.ry() += limitDown;
    }
}

//template <typename T>
//std::ostream & operator<<(std::ostream &os, std::vector<T> list)
//{
//    for (auto &o : list) {
//        os << o << ' ';
//    }
//    return os;
//}

/*
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

*/

bool isInViewRange(const QPoint &p1, const QPoint &p2, int view_range);

inline std::pair<QPoint, QPoint> getViewRangePos(const QPoint &p, int viewSize)
{
    QPoint pos1(p.x() - viewSize / 2, p.y() - viewSize / 2);
    QPoint pos2(p.x() + viewSize / 2, p.y() + viewSize / 2);
    return {pos1, pos2};
}

#endif // COMMON_H
