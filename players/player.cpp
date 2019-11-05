#include "player.h"
#include <QPainter>
#include <QDebug>
#include <QRectF>
#include "common.h"

#include <iostream>
using std::cout;
using std::endl;


void Player::showViewRange(QPainter *painter, int view_range)
{
    QRect rect(_pos.x() - view_range/2, _pos.y() - view_range/2,
               view_range, view_range);
    painter->drawRect(rect);
}

void Player::show(QPainter *painter, int point_size)
{
    double lx = _pos.x() - point_size / 2.0;
    double ly = _pos.y() - point_size / 2.0;
    painter->drawEllipse(QRectF(lx, ly, point_size, point_size));
}

void Player::move(int dx, int dy, int limitDown, int limitRight)
{
    ::move(_pos, dx, dy, limitDown, limitRight);
}

const char* Player::sendMsg()
{
    return _msg_buf;
}

void Player::receiveMsg(const char *msg)
{
    // qDebug() << "收到消息:" << msg;
    _receive_msgs.insert(msg);
}

void Player::showMsg()
{
    return;
    if (_receive_msgs.size() == 0) return;
    qDebug("玩家[%d](%d,%d)收到消息:", _number, _pos.x(), _pos.y());
    {
        QDebug debug(qDebug());
        for (const char *msg : _receive_msgs) {
            debug << msg;
        }
    }
    _receive_msgs.clear();
}

Player::Player()
{

}

Player::Player(const QPoint &pos, int number)
    :_pos(pos),
     _number(number),
     _msg_buf{0}
{
    sprintf(_msg_buf, "我是玩家[%d](%d,%d)号", _number, _pos.x(), _pos.y());
}
