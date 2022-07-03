#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main()
{
    VideoCapture cap(0);
    while (1)
    {
        Mat frame;
        Mat dstMatdx;
        Mat dstMatdy;

        cap >> frame;
        Sobel(frame, dstMatdx, CV_8UC1, 1, 0);
        Sobel(frame, dstMatdy, CV_8UC1, 0, 1);

        imshow("frame", frame);
        imshow("dstMatdx", dstMatdx);
        imshow("dstMatdy", dstMatdy);

        waitKey(30);
    }

    return 0;
}