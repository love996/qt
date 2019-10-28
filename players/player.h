#ifndef PLAYER_H
#define PLAYER_H

#include <QPoint>
#include <QPaintDevice>

//class ViewRange
//{
//public:
//    ViewRange();
//    ViewRange(int x1, int y1, int x2, int y2);
//    void reset(int x1, int y1, int x2, int y2);

//private:
//    QPoint p1;
//    QPoint p2;
//};


class Player
{
public:
    void showViewRange(QPaintDevice *device, QPoint *p, int view_range);

private:
    // QPoint *_pos;
    // ViewRange view_range;
};

#endif // PLAYER_H
