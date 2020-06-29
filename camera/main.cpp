#include "camera_impl.h"

#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include "eventloop.h"
#include <QThread>
// #include <opencv2/opencv.hpp>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    qDebug() << "main thread:" << QThread::currentThreadId();
    init();
    // CameraImpl camera;
    for (auto camera_info : CameraImpl::cameras()) {
        qDebug() << camera_info.name.c_str()
                 << camera_info.description.c_str();
    }
//    QMessageBox msg;
//    msg.setText("hello text");
//    msg.open();
//    cv::VideoCapture cap(1);
//    cap.get(1);
//    while (1) {
//        cv::Mat mat;
//        cap >> mat;

//        cv::imshow("camera", mat);
//        if ('q' == cv::waitKey(1)) {
//            break;
//        }
//    }
    // w.show();
    return a.exec();
}
