#ifndef CAMERA_H
#define CAMERA_H
#include "icamera.h"

class Camera
{
public:
    Camera();
    virtual bool is_open() const;
    virtual void open();
    virtual void open(CameraError &e) noexcept;
    virtual void close() noexcept;
    virtual void close(CameraError &e) noexcept;
    // 曝光
    virtual void expose(int e);
    virtual int expose() const;
    // 帧率
    virtual void fps(int f);
    virtual int fps() const;
    virtual double current_fps() const;
    // 拍摄一张图片，同步等待返回，如果打开了异步模式，则获取当前最新的图片，立即返回
    virtual Image take_picture();
    virtual void enable_async_take_picture(bool e);
    // 注册异步回调，每获得一张图片则会调用此函数
    // 回调函数签名 void (std::shared_ptr<Image>, CameraError)
    void async_picture_handler(PictureHandler handler);
    virtual void start_video(const std::string &filename);
    virtual void end_video();
private:
    std::shared_ptr<ICamera> _camera_ptr;
};

#endif // CAMERA_H
