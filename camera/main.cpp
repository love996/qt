#include "camera.h"

#include <QApplication>
#include <QMessageBox>
#include <opencv2/opencv.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Camera w;
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
    w.show();
    return a.exec();
}
