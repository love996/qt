#ifndef MOUSEDIALOG_H
#define MOUSEDIALOG_H

#include <QDialog>
#include <QScreen>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MouseDialog; }
QT_END_NAMESPACE

class MouseDialog : public QDialog
{
    Q_OBJECT

public:
    MouseDialog(QWidget *parent = nullptr);
    ~MouseDialog();
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    Ui::MouseDialog *ui;
    QPoint _start_menu{20, 20};
    QScreen *_screen_ptr;
    QTimer _timer_mouse;
private:
    void moveMouse();
};
#endif // MOUSEDIALOG_H
