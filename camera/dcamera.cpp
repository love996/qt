#include "dcamera.h"
#include <QCamera>
#include <QCameraInfo>
#include <QCameraImageCapture>
#include <QTimer>
#include <QPixmap>
#include <QCameraViewfinderSettings>
#include "util.h"

#include "eventloop.h"

CameraImpl::CameraImpl()
    :_timer_take_picture_ptr(std::make_shared<QTimer>())
{

}

std::shared_ptr<CameraInfo> CameraImpl::default_camera() const
{
    auto camera = QCameraInfo::defaultCamera();
    std::shared_ptr<CameraInfo> camera_info_ptr;
    if (!camera.isNull()) {
        camera_info_ptr = std::make_shared<CameraInfo>();
        camera_info_ptr->name = camera.deviceName().toStdString();
        camera_info_ptr->description = camera.description().toStdString();
    }
    return camera_info_ptr;
}

std::vector<CameraInfo> CameraImpl::cameras() const
{
    std::vector<CameraInfo> cameras;
    for (auto &info : QCameraInfo::availableCameras()) {
        CameraInfo camera;
        camera.name = info.deviceName().toStdString();
        camera.description = info.description().toStdString();
        cameras.emplace_back(std::move(camera));
    }
    return cameras;
}

void CameraImpl::open(const std::string &name)
{
    init(name);
}

void CameraImpl::expose(int e)
{
    _capture_ptr
}

void CameraImpl::fps(int f)
{
    auto e = _camera_ptr->exposure();
    // _camera_ptr-

}

int CameraImpl::fps() const
{
//    QCameraViewfinderSettings set;
//    set.setResolution(1920, 1080);
//    set.set
}

void CameraImpl::init(const std::string &name)
{
    clear_obj(_camera_ptr, _capture_ptr, _timer_take_picture_ptr);
    _camera_ptr = std::make_shared<QCamera>(QByteArray::fromStdString(name));
    _capture_ptr = std::make_shared<QCameraImageCapture>(_camera_ptr.get());
    _capture_ptr->setCaptureDestination(QCameraImageCapture::CaptureToBuffer);
    // camera
    QObject::connect(_camera_ptr.get(), &QCamera::statusChanged,
                     this, &CameraImpl::status_chaned);
    QObject::connect(_camera_ptr.get(), static_cast<void (QCamera::*)(QCamera::Error)>(&QCamera::error),
                     this, &CameraImpl::error);


    QObject::connect(_capture_ptr.get(), &QCameraImageCapture::imageCaptured,
                     this, &CameraImpl::image_captured);
    QObject::connect(_timer_take_picture_ptr.get(), &QTimer::timeout,
                     this, &CameraImpl::tack_picture);
    _camera_ptr->start();
    _camera_ptr->moveToThread(&event_thread());
    _capture_ptr->moveToThread(&event_thread());
    _timer_take_picture_ptr->moveToThread(&event_thread());
}

void CameraImpl::tack_picture()
{
    if(_camera_ptr->state() == _camera_ptr->UnloadedState){
        qDebug()<< _camera_ptr->error() << _camera_ptr->errorString();

        //_camera_ptr->start();
        //_camera_ptr->stateChanged(_camera_ptr->LoadedState);
        //m_ptrViewFinder->show();
        //_camera_ptr->stateChanged(_camera_ptr->ActiveState);

        qDebug()<<"changed state";
    }
    //_camera_ptr->statusChanged(QCamera::Status::ActiveStatus);
    _capture_ptr->capture();
    //_camera_ptr->unlock();
    qDebug() << "拍完照片获取参数";
    // statusChaned(QCamera::Status::ActiveStatus);
}

void CameraImpl::error(int no)
{
    _error = no;
}

void CameraImpl::status_chaned(int status)
{
    _status = status;
}

void CameraImpl::image_captured(int id, const QImage &preview)
{
//    qDebug() << "get image";
//    auto pixmap = QPixmap::fromImage(preview);
//    ui->picture->setPixmap(pixmap);
}
