#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int main()
{
    VideoCapture cap(0);
    // VideoCapture cap("http://admin:admin@192.168.255.42:8081");

    double scale = 0.5;

    // ·ôÉ«
    // 0-180
    double i_minH = 0;
    double i_maxH = 20;
    // 0-255
    double i_minS = 43;
    double i_maxS = 255;
    // 0-255
    double i_minV = 55;
    double i_maxV = 255;

    while (1)
    {
        Mat frame;
        Mat hsvMat;
        Mat detectMat; // mask
        Mat buffMat;
        Mat dstMat;

        cap >> frame;
        cvtColor(frame, hsvMat, COLOR_BGR2HSV);
        inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);

        GaussianBlur(frame, buffMat, Size(5, 5), 10);
        buffMat.copyTo(dstMat, detectMat);
        // imshow("dstMat", dstMat);
        frame.copyTo(dstMat, 255 - detectMat);

        imshow("frame", frame);
        imshow("detectMat", detectMat);
        imshow("dstMat", dstMat);

        waitKey(30);
    }

    return 0;
}