#ifndef LABELPAINT_H
#define LABELPAINT_H
#include <QLabel>
#include "playermap.h"

class LabelPaint : public QLabel
{
    Q_OBJECT
public:
    // using QLabel::QLabel;
    LabelPaint();
    //LabelPaint();
    virtual void paintEvent(QPaintEvent *) override;

signals:

public slots:
private:
    PlayerMap player_map;
    bool is_view_open{false};
    bool is_running{false};
};

#endif // LABELPAINT_H
