#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include "ui_dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_pressed();

    void on_pushButton_released();

private:
    Ui::Widget *ui;
    Ui_Dialog *dialog;
    QDialog _uiDialog;
    QTimer _timerPressed;
};
#endif // WIDGET_H
