#ifndef LABELPAINT_H
#define LABELPAINT_H
#include <QLabel>
#include <QTimer>
#include "playermap.h"

class LabelPaint : public QLabel
{
    Q_OBJECT
public:
    // using QLabel::QLabel;
    LabelPaint(QWidget *parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());
    //LabelPaint();
    virtual void paintEvent(QPaintEvent *) override;
    PlayerMap &getMap()
    {
        return player_map;
    }

signals:

public slots:
private:
    PlayerMap player_map;
    bool is_view_open{false};
    bool is_running{false};
    QTimer timer;
};

#endif // LABELPAINT_H
