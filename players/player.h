#ifndef PLAYER_H
#define PLAYER_H

#include <QPoint>
#include <QPainter>
#include <set>


class Player
{
public:
    Player();
    Player(const QPoint &pos, int number);
    void showViewRange(QPainter *painter, int view_range);
    void show(QPainter *painter, int point_size);
    void move(int dx, int dy, int limitDown, int limitRight);
    const char * sendMsg();
    void receiveMsg(const char *msg);
    void showMsg();
    const QPoint &pos() const
    {
        return _pos;
    }
private:
    QPoint _pos;
    int _number;
    char _msg_buf[32];
    std::set<const char*> _receive_msgs;

};

#endif // PLAYER_H
