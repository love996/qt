#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool eventFilter(QObject *obj, QEvent *ptrEvent);

private slots:
    void on_testEvent_clicked();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<QLabel> m_ptrBack;
};
#endif // MAINWINDOW_H
