#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QResizeEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent *event) override;
    ~Widget();

private slots:
    void on_add_player_clicked();

    void on_is_running_stateChanged(int arg1);

    void on_next_player_clicked();

    void on_view_range_valueChanged(int value);

private:
    Ui::Widget *ui;
    QTimer timer_run;
    QTimer timer_update_map;
};
#endif // WIDGET_H
