#include "playermap.h"
#include <QPainter>
#include <cstdlib>

PlayerMap::PlayerMap(const QPoint &p, const QSize size)
    :point_begin(p),
      point_end(p.x() + size.width(), p.y() + size.height())
{
    players.reserve(1000);
}

void PlayerMap::addPlayerCount(int count)
{
    // int left = 0, up = 0;
    int right = abs(point_end.x() - point_begin.x() + 1);
    int down = abs(point_end.y() - point_begin.y() + 1);
    while (count-- > 0) {
        players.push_back(QPoint(rand()%right, rand() % down));
    }
}

void PlayerMap::showRect(QPaintDevice *device, int view_size)
{
    if (device == nullptr) {
        return;
    }
    QPainter painter(device);
    QVector<QRect> rects;
    rects.reserve(players.size());
    for (auto &player : players) {
        rects.push_back(QRect(player.x() - view_size, player.y() - view_size, player.x() + view_size, player.y() + view_size));
    }
    painter.drawRects(rects);
}

void PlayerMap::showPalyer(QPaintDevice *device)
{
    if (device == nullptr) {
        return;
    }
    QPainter painter(device);
    painter.drawPoints(players);
}
