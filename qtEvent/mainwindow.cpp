#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->testEvent->installEventFilter(this);
    QMouseEvent *mouseEvent = new QMouseEvent(QEvent::MouseButtonPress, {}, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication::sendEvent(ui->testEvent, mouseEvent);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *ptrEvent)
{
    if (obj == ui->testEvent && ptrEvent->type() == QEvent::MouseButtonPress) {
        qDebug() << "received mouse pressed";
    }
}

