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
        _players[i].move(dx, dy,_map_size.height(),  _map_size.width());
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
    static QColor green(100, 150, 100);
    static QPen pen(green);
    static QBrush brush(green, Qt::BrushStyle::SolidPattern);

    painter->setPen(pen);
    painter->setBrush(brush);
}

void PlayerMap::setCurrPlayerPainter(QPainter *painter)
{
    static QColor red(255, 0, 0);
    static QPen pen(red);
    static QBrush brush(red, Qt::BrushStyle::SolidPattern);

    painter->setPen(pen);
    painter->setBrush(brush);
}

void PlayerMap::setViewRangePainter(QPainter *painter)
{
    static QColor black(0, 0, 0);
    static QPen pen(black);
    pen.setStyle(Qt::PenStyle::DotLine);
    static QBrush brush(black, Qt::BrushStyle::NoBrush);

    painter->setPen(pen);
    painter->setBrush(brush);
}

void PlayerMap::setInViewRangePainter(QPainter *painter)
{
    static QColor green(0, 200, 0);
    static QPen pen(green);
    // pen.setStyle(Qt::PenStyle::DotLine);
    static QBrush brush(green, Qt::BrushStyle::SolidPattern);

    painter->setPen(pen);
    painter->setBrush(brush);
}

void PlayerMap::calcViewRange()
{
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

void PlayerMap::calcViewRange2()
{
    for (auto &player : _players) {
        _pos_player.emplace(player.pos(), player);
        _pos_l_r.emplace(player.pos());
        _pos_t_d.emplace(player.pos());
    }
    for (auto &player : _players) {
        auto pos = player.pos();
        QPoint poslt(pos.x() - _view_size / 2, pos.y() - _view_size / 2);
        QPoint posrd(pos.x() + _view_size / 2, pos.y() + _view_size / 2);
//        QPoint posrt(pos.x() + _view_size / 2, pos.y() - _view_size / 2);
//        QPoint posld(pos.x() - _view_size / 2, pos.y() + _view_size / 2);
        // auto [pos1, pos2] = getViewRangePos(pos, _view_size);
        auto iter_l_r_begin =_pos_l_r.upper_bound(poslt);
        auto iter_l_r_end = _pos_l_r.lower_bound(posrd);
        auto iter_t_d_begin =_pos_t_d.upper_bound(poslt);
        auto iter_t_d_end = _pos_t_d.lower_bound(posrd);
         // std::cout << player.sendMsg() << std::endl;
         // qDebug(player.sendMsg());
        Set<QPoint, LessTD> set1(iter_t_d_begin, iter_t_d_end);
        for (auto iter = iter_l_r_begin; iter != iter_l_r_end && iter != _pos_l_r.end(); ++iter) {
            // qDebug() << "iter:" << *iter;
            if (set1.find(*iter) != set1.end() && _pos_player.find(*iter) != _pos_player.end()) {
                player.receiveMsg(_pos_player.find(*iter)->second.sendMsg());
            }
        }
    }
    _pos_player.clear();
    _pos_l_r.clear();
    _pos_t_d.clear();
}

void PlayerMap::showViewRange(QPainter *painter)
{
    if (painter == nullptr) {
        return;
    }
    for (auto &player : _players) {
        player.showViewRange(painter, _view_size);
    }
}

void PlayerMap::showPalyer(QPainter *painter)
{
    if (painter == nullptr) {
        return;
    }
    // painter->save();


//    QPainter painter_in_range;
//    painter_in_range.begin(painter->device());
//    setInViewRangePainter(&painter_in_range);

    int painter_i = 0;

    for (size_t i = 0; i < _players.size(); ++i) {
        if (i == _curr_player) {
            // painter->save();

            setCurrPlayerPainter(painter);
            _players[i].show(painter, _point_size + 1);

            // view range
            setViewRangePainter(painter);
            _players[i].showViewRange(painter, _view_size);

            // painter->restore();
        }
        else {
            if (-1 != _curr_player && isInViewRange(_players[_curr_player].pos(), _players[i].pos(), _view_size)) {
                // painter->save();
                if (painter_i != 1) {

                    setInViewRangePainter(painter);
                    painter_i = 1;
                }
                _players[i].show(painter, _point_size);


                // painter->restore();
            }
            else {
                if ( painter_i != 2 ) {
                    setPlayerPainter(painter);
                    painter_i = 2;
                }
                _players[i].show(painter, _point_size);

            }
        }
    }
    // painter->restore();
}
