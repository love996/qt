#ifndef LABELPAINT_H
#define LABELPAINT_H
#include <QLabel>
#include <QTimer>
#include <QResizeEvent>
#include "playermap.h"

class LabelPaint : public QLabel
{
    Q_OBJECT
public:
    LabelPaint(QWidget *parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());
    //LabelPaint();
    virtual void paintEvent(QPaintEvent *) override;
    virtual void resizeEvent(QResizeEvent *) override;
    void playerRun(int step);
    void addPlayerCount(int count);
    void nextPlayer();
    inline void setViewRange(int view_size)
    {
        player_map.setViewRange(view_size);
    }

private:
    PlayerMap player_map;
    bool _is_view_open{false};
    // bool is_running{false};
    // QTimer timer;
    // int _view_range;

};

#endif // LABELPAINT_H
