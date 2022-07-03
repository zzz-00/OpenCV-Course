#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

int main()
{
    VideoCapture cap(0);
    while (1)
    {
        Mat frame;
        Mat dstMat;

        cap >> frame;                 // ֡
        medianBlur(frame, dstMat, 3); // ��ֵ�˲�

        imshow("dstMat", dstMat);
        imshow("frame", frame);

        waitKey(30);
    }

    return 0;
}