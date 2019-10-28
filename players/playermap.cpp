#include "playermap.h"
#include <QPainter>
#include <cstdlib>
#include <QDebug>
#include "common.h"

PlayerMap::PlayerMap()
    :_curr_player(-1)
{

}

PlayerMap::PlayerMap(const QPoint &p, const QSize size)
    :PlayerMap()
{
    reset(p, size);
}

void PlayerMap::reset(const QPoint &p, const QSize size)
{
    point_begin = QPoint(p);
    point_end = QPoint(p.x() + size.width(), p.y() + size.height());
    // players.reserve(1000);
}

void PlayerMap::addPlayerCount(int count)
{
    // int left = 0, up = 0;
    int right = abs(point_end.x() - point_begin.x() + 1);
    int down = abs(point_end.y() - point_begin.y() + 1);
    while (count-- > 0) {
        players_pos.push_back(QPoint(rand()%right, rand() % down));
        players.push_back(Player());
    }
    initPlayersDirect();

}

void PlayerMap::playersRun(int step)
{
    // 是否显示视野范围

    // int directs = 4;
    genPlayersDirect();
    int i = 0;
    int limitRight = point_end.x();
    int limitDown = point_end.y();
    for (; i < players.size() / 4; ++i) {
        moveLeft(players_pos[players_number[i]], step, limitRight);
    }
    for (; i < players.size() / 2; ++i) {
        moveRight(players_pos[players_number[i]], step, limitRight);
    }
    for (; i < players.size() / 4 * 3; ++i) {
        moveUp(players_pos[players_number[i]], step, limitDown);
    }
    for (; i < players.size(); ++i) {
        moveDown(players_pos[players_number[i]], step, limitDown);
    }
    qDebug() << "point_end:" << point_end;

}

void PlayerMap::nextPlayer()
{
    ++_curr_player;
    if (_curr_player >= players.size()) {
        _curr_player = -1;
    }
}

void PlayerMap::initPlayersDirect()
{
    players_number.resize(players.size());
    for (int i = 0; i < players.size(); ++i) {
        players_number[i] = i;
    }
}

void PlayerMap::genPlayersDirect()
{
    for (int i = 0; i < players.size() * 3; ++i) {
        int m = rand() % players.size();
        int n = rand() % players.size();
        assert(m < players.size() && n < players.size());
        std::swap(players_number[m], players_number[n]);
    }
}

void PlayerMap::showViewRange(QPaintDevice *device, int view_size)
{
//    if (device == nullptr) {
//        return;
//    }
//    QPainter painter(device);
//    QVector<QRect> rects;
//    rects.reserve(players.size());
//    for (auto &player : players) {
//        rects.push_back(QRect(player.pos()->x() - view_size, player.pos()->y() - view_size,
//                              player.pos()->x() + view_size, player.pos()->y() + view_size));
//    }
//    painter.drawRects(rects);
}

void PlayerMap::showPalyer(QPaintDevice *device)
{
    if (device == nullptr) {
        return;
    }

    QPainter painter(device);
    // qDebug() << players;
    QPen pen(QColor(255, 0, 0));
    pen.setWidth(5);
    painter.setPen(pen);
    //for (auto &player : players) {
    painter.drawPoints(players_pos);

    if (-1 != _curr_player) {
        QVector<QPoint> points_in_view_range;
        players[_curr_player].showViewRange(device, &players_pos[_curr_player], _view_range);
        for (int i = 0; i < players.size(); ++i) {
            if (isInViewRange(players_pos[_curr_player], players_pos[i], _view_range)) {
                points_in_view_range.push_back(players_pos[i]);
            }
        }
        QPainter painter(device);
        QPen pen(QColor(0, 255, 0));
        pen.setWidth(5);
        painter.setPen(pen);
        //for (auto &player : players) {


        painter.drawPoints(points_in_view_range);

        QPen pen_blue(QColor(0, 0, 255));
        pen_blue.setWidth(5);
        QPainter painter_curr(device);
        painter_curr.setPen(pen_blue);
        painter_curr.drawPoint(players_pos[_curr_player]);
    }


    //}

}
