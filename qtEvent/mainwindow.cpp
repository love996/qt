#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMouseEvent>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->testEvent->installEventFilter(this);
    this->installEventFilter(this);
    QMouseEvent *mouseEvent = new QMouseEvent(QEvent::MouseButtonPress, {}, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication::sendEvent(ui->testEvent, mouseEvent);


}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *ptrEvent)
{
    if (this == obj && ptrEvent->type() == QEvent::Show) {
        qDebug() << "show window";
        on_testEvent_clicked();
    }
    qDebug() << "this pos:" << this->pos();
    QPoint pos = QWidget::mapToGlobal(this->pos());
    //qDebug() << "this global pos:" << pos;
    if (obj == ui->testEvent && ptrEvent->type() == QEvent::MouseButtonPress) {
        qDebug() << "received mouse pressed";
    }
    return QMainWindow::eventFilter(obj, ptrEvent);
}


void MainWindow::on_testEvent_clicked()
{
    m_ptrBack.reset(new QLabel);
    auto size = this->size();
    qDebug() << size;
    m_ptrBack->setMaximumSize(size);
    m_ptrBack->setMinimumSize(size);
    m_ptrBack->setStyleSheet(QString("background: #C0C0C0"));
    m_ptrBack->setWindowOpacity(0.8);
    m_ptrBack->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    auto pos = QWidget::mapToGlobal(QPoint{0, 0});
    m_ptrBack->move(pos);
    m_ptrBack->show();
}
