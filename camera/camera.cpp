#include "camera.h"
#include "ui_camera.h"

#include <QCamera>
#include <QCameraInfo>
#include <QCameraImageCapture>
#include <QDebug>
#include <QVideoFrame>

Camera::Camera(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Camera)
{
    ui->setupUi(this);

    cameraList();
}

Camera::~Camera()
{
    delete ui;
}

QStringList Camera::cameraList()
{
    return {};
}







