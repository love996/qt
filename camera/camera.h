#ifndef CAMERA_H
#define CAMERA_H

#include <QMainWindow>
#include <QCamera>
#include <QCameraImageCapture>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Camera; }
QT_END_NAMESPACE

class Camera : public QMainWindow
{
    Q_OBJECT

public:
    Camera(QWidget *parent = nullptr);
    ~Camera();
    QStringList cameraList();

private:
    Ui::Camera *ui;
    QTimer _timer;
    std::shared_ptr<QCamera> _camera_ptr;
    std::shared_ptr<QCameraImageCapture> _capture_ptr;
};
#endif // CAMERA_H
