#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    //QMainWindow::paintEvent(e);
    QPainter painter(this);
    QPen pen(QColor(255,0,0));
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawRect(10, 10, 100, 100);
    pen.setColor(QColor(0, 255, 0));
    painter.setPen(pen);
    painter.drawRect(100, 100, 100, 100);

    QBrush brush(QColor(0, 255, 0), Qt::BrushStyle::SolidPattern);

    painter.setBrush(brush);
    painter.drawEllipse(200, 200, 100, 100);
    brush.setColor(QColor(0, 0, 255));

    painter.setBrush(brush);
    painter.drawEllipse(300, 300, 100, 100);
    return QMainWindow::paintEvent(e);
}

MainWindow::~MainWindow()
{
    delete ui;
}

