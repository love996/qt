#ifndef DCAMERA_H
#define DCAMERA_H
#include "image.h"
#include <vector>
#include <atomic>
#include <QObject>
//#include <QCamera>

class QCamera;
class QTimer;
class QImage;
class QCameraImageCapture;


class CameraImpl : public QObject
{

public:
    CameraImpl();

    std::shared_ptr<CameraInfo> default_camera() const;
    std::vector<CameraInfo> cameras() const;
    void open(const std::string &name);
    void open(const CameraInfo &info);
    void open(int index);
    void expose(int e);
    int expose() const;
    void fps(int f);
    int fps() const;
private:
    std::shared_ptr<QCamera> _camera_ptr;
    std::vector<CameraInfo> _cameras;
    std::shared_ptr<QTimer> _timer_take_picture_ptr;
    std::shared_ptr<QCameraImageCapture> _capture_ptr;
    Image _current_image;
    std::atomic<int> _status;
    std::atomic<int> _error;
private:
    void init(const std::string &name);
    void image_captured(int id, const QImage &preview);
    void status_chaned(int status);
    void tack_picture();
    void error(int no);
};

#endif // DCAMERA_H
