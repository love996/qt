#include "playermap.h"
#include <QPainter>
#include <cstdlib>
#include <QDebug>
#include "common.h"

PlayerMap::PlayerMap()
    :_curr_player(-1)
{

}

void PlayerMap::reset(const QSize &map_size)
{
    _map_size = map_size;
}

void PlayerMap::addPlayerCount(int count)
{
    while (count-- > 0) {
        _players.push_back(Player(QPoint(rand()%_map_size.width(), rand() % _map_size.height()), _players.size()));
    }
}

void PlayerMap::playersRun(int step)
{
    if (0 >= step) return;
    int dx, dy, direct;
    for (size_t i = 0; i < _players.size(); ++i) {
        direct = rand() % 2 ? -1 : 1;
        dx = rand() % step * direct;
        dy = rand() % step * direct;
        _players[i].move(dx, dy, _map_size.width(), _map_size.height());
    }
    calcViewRange();
}

void PlayerMap::nextPlayer()
{
    ++_curr_player;
    if (_curr_player >= int(_players.size())) {
        _curr_player = -1;
    }
}

void PlayerMap::setPlayerPainter(QPainter *painter)
{
    QColor green(100, 150, 100);
    QPen pen(green);
    QBrush brush(green, Qt::BrushStyle::SolidPattern);

    painter->setPen(pen);
    painter->setBrush(brush);
}

void PlayerMap::setCurrPlayerPainter(QPainter *painter)
{
    QColor red(255, 0, 0);
    QPen pen(red);
    QBrush brush(red, Qt::BrushStyle::SolidPattern);

    painter->setPen(pen);
    painter->setBrush(brush);
}

void PlayerMap::setViewRangePainter(QPainter *painter)
{
    QColor black(0, 0, 0);
    QPen pen(black);
    pen.setStyle(Qt::PenStyle::DotLine);
    QBrush brush(black, Qt::BrushStyle::NoBrush);

    painter->setPen(pen);
    painter->setBrush(brush);
}

void PlayerMap::calcViewRange()
{

//    for (auto &player : _players) {
//        _pos_player.emplace(player.pos(), player);
//    }
    for (auto &player : _players) {
        //auto pos = player.pos();
//        QPoint pos1(pos.x() - _view_size / 2, pos.y() - _view_size / 2);
//        QPoint pos2(pos.x() + _view_size / 2, pos.y() + _view_size / 2);
        //auto [pos1, pos2] = getViewRangePos(pos, _view_size);
//        auto iter_begin =_pos_player.upper_bound(pos1);
//        auto iter_end = _pos_player.lower_bound(pos2);
        // std::cout << player.sendMsg() << std::endl;
        // qDebug(player.sendMsg());
//        for (auto iter = iter_begin; iter != iter_end && iter != _pos_player.end(); ++iter) {
//            if (&iter->second != &player) {
//                iter->second.receiveMsg(player.sendMsg());
//            }
//        }
        for (auto &player2 : _players) {
            if (&player != &player2) {
                if (isInViewRange(player.pos(), player2.pos(), _view_size))
                    player2.receiveMsg(player.sendMsg());
            }
        }
    }
    for (auto &player : _players) {
        player.showMsg();
    }
}

void PlayerMap::showViewRange(QPainter *painter)
{
    if (painter == nullptr) {
        return;
    }
    for (auto &player : _players) {
        player.show(painter, _view_size);
    }
}

void PlayerMap::showPalyer(QPainter *painter)
{
    if (painter == nullptr) {
        return;
    }
    painter->save();
    setPlayerPainter(painter);

    for (size_t i = 0; i < _players.size(); ++i) {
        if (i == _curr_player) {
            painter->save();

            setCurrPlayerPainter(painter);
            _players[i].show(painter, _point_size + 1);

            // view range
            setViewRangePainter(painter);
            _players[i].showViewRange(painter, _view_size);

            painter->restore();
        }
        else {
            _players[i].show(painter, _point_size);
        }
    }
    painter->restore();
}
