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

        cap >> frame;
        blur(frame, dstMat, Size(3, 3));

        imshow("frame", frame);
        imshow("dstMat", dstMat);

        waitKey(30);
    }

    return 0;
}