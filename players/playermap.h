#ifndef PLAYERMAP_H
#define PLAYERMAP_H

#include <QPoint>
#include <QSize>
#include <QWidget>
#include <QVector>

#include "player.h"

class PlayerMap
{
public:
    PlayerMap();
    PlayerMap(const QPoint &p, const QSize size);
    void reset(const QPoint &p, const QSize size);
    void showViewRange(QPaintDevice *device, int view_size);
    void showPalyer(QPaintDevice *device);
    void addPlayerCount(int count);
    void playersRun(int step);
    void nextPlayer();
    void setViewRange(int view_range)
    {
        _view_range = view_range;
    }

private:
    QPoint point_begin;
    QPoint point_end;
    QVector<Player> players;
    std::vector<int> players_number;
    QVector<QPoint> players_pos;
    int _curr_player;
    int _view_range;
private:
    void initPlayersDirect();
    void genPlayersDirect();
};

#endif // PLAYERMAP_H
