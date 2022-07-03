#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int main()
{
    Mat srcMat = imread("D:\\project\\opencv_vscode\\ex31 lid\\1.jpg");
    if (srcMat.empty())
    {
        std::cerr << "Í¼Ïñ¼ÓÔØÊ§°Ü" << std::endl;
        return -1;
    }

    // ±­¸Ç
    // 0-180
    double i_minH = 140;
    double i_maxH = 180;
    // 0-255
    double i_minS = 110;
    double i_maxS = 255;
    // 0-255
    double i_minV = 100;
    double i_maxV = 255;

    Mat hsvMat;
    Mat binaryMat;
    cvtColor(srcMat, hsvMat, COLOR_BGR2HSV);
    inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), binaryMat);

    std::vector<std::vector<Point>> contours;
    findContours(binaryMat, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    for (int i = 0; i < contours.size(); i++)
    {
        RotatedRect rbox = minAreaRect(contours[i]);
        if (rbox.boundingRect().height / rbox.boundingRect().width < 1.4 && rbox.boundingRect().area() > 200)
        {
            rectangle(srcMat, Rect(rbox.boundingRect()), Scalar(255, 0, 255), 1);
        }
    }

    imshow("srcMat", srcMat);
    imshow("binaryMat", binaryMat);
    waitKey(0);
    return 0;
}