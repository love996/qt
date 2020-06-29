#include "icamera.h"
#include <opencv2/opencv.hpp>

bool ICamera::is_open() const
{
    return _is_open;
}

//void ICamera::open()
//{
//    CameraError e;
//    open(e);
//    if (e.code) {
//        throw CameraException(e.msg);
//    }
//}

void ICamera::open(CameraError &e) noexcept
{
    if (!_video_ptr) {
        _video_ptr = std::make_shared<cv::VideoCapture>();
    }
    if (!_video_ptr) {
        e = CameraError(MallocFail);
        return;
    }
    if (!_video_ptr->isOpened()) {
        _video_ptr->open(_camera_name);
        e = CameraError(OpenCameraFail);
        return;
    }
}

//void ICamera::close() noexcept
//{
//    _video_ptr->release();
//    _video_ptr.reset();
//}

void ICamera::close(CameraError &e) noexcept
{
    _video_ptr->release();
}

double ICamera::expose(double exposure, CameraError &ec) noexcept
{
    double old = _video_ptr->get(cv::CAP_PROP_EXPOSURE);
    if (0 == old) {
        ec.set(GetExposureFail);
        return -1;
    }
    bool r = _video_ptr->set(cv::CAP_PROP_EXPOSURE, exposure);
    if (!r) {
        ec.set(SetExposureFail);
        return old;
    }
    return old;
}

Image ICamera::take_picture()
{
    if (_enable_async) {

    }
    else {

    }
}

//ICamera::ICamera(std::shared_ptr<cv::VideoCapture> ptr)
//    :_video_ptr(ptr)
//    ,_camera_name(ptr->getBackendName())
//    ,_is_open(ptr != nullptr && ptr->isOpened())
//    ,_enable_async(false)
//{
//}

ICamera::ICamera(const std::string &camera_name)
    :_camera_name(camera_name)
    ,_is_open(false)
    ,_enable_async(false)
{
}
