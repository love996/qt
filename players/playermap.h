#ifndef PLAYERMAP_H
#define PLAYERMAP_H

#include <QPoint>
#include <QSize>
#include <QWidget>
#include <QVector>

class PlayerMap
{
public:
    PlayerMap(const QPoint &p, const QSize size);
    void showRect(QPaintDevice *device, int view_size);
    void showPalyer(QPaintDevice *device);
    void addPlayerCount(int count);
private:
    const QPoint point_begin;
    const QPoint point_end;
    QVector<QPoint> players;
};

#endif // PLAYERMAP_H
