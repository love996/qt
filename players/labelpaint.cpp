#include "labelpaint.h"

#include <QPainter>


LabelPaint::LabelPaint()
{

}

void LabelPaint::paintEvent(QPaintEvent *event)
{
    // QPainter painter(this);
    QPainter painter(this);
    painter.drawRect(10, 10, 30, 30);
    return QLabel::paintEvent(event);
}
