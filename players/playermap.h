#ifndef PLAYERMAP_H
#define PLAYERMAP_H

#include <QPoint>
#include <QSize>
#include <QWidget>
#include <QVector>
#include <functional>

#include "player.h"
#include "common.h"

struct LessLR
{
    bool operator()(const QPoint &p1, const QPoint &p2)
    {
        return p1.x() < p2.x() || (p1.x() == p2.x() && p1.y() < p2.y());
    }
};

struct LessTD
{
    bool operator()(const QPoint &p1, const QPoint &p2)
    {
        return p1.y() < p2.y() || (p1.y() == p2.y() && p1.x() < p2.x());
    }
};

class PlayerMap
{
public:
    PlayerMap();
    // PlayerMap(const QPoint &p, const QSize size);
    void reset(const QSize &map_size);
    void showViewRange(QPainter *painter);
    void showPalyer(QPainter *painter);
    void addPlayerCount(int count);
    void playersRun(int step);
    void nextPlayer();
    void setViewRange(int view_size)
    {
        _view_size = (view_size+1)/2*2;
    }

private:
    QSize _map_size;
    std::vector<Player> _players;
    // std::vector<int> players_number;
    // QVector<QPoint> players_pos;
    int _curr_player;
    int _view_size;
    int _point_size{5};
    Map<QPoint, Player&, LessLR> _pos_player;
    Set<QPoint, LessLR> _pos_l_r;
    Set<QPoint, LessTD> _pos_t_d;
private:
    void setPlayerPainter(QPainter *painter);
    void setCurrPlayerPainter(QPainter *painter);
    void setViewRangePainter(QPainter *painter);
    void setInViewRangePainter(QPainter *painter);

private:
    void calcViewRange();
    void calcViewRange2();
};

#endif // PLAYERMAP_H
