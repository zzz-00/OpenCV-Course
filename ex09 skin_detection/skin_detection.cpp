#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
    // VideoCapture cap("http://admin:admin@192.168.209.80:8081");
    VideoCapture cap(0);

    double scale = 0.5;

    // 肤色
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
        Mat detectMat;

        cap >> frame;
        Size ResImgSiz = Size(frame.cols * scale, frame.rows * scale);
        Mat rFrame = Mat(ResImgSiz, frame.type());
        resize(frame, rFrame, ResImgSiz, INTER_LINEAR);

        cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);

        cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);

        imshow("detectMat", detectMat);
        imshow("frame", frame);

        waitKey(30);
    }

    return 0;
}