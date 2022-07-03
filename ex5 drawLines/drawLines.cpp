#include <opencv2/opencv.hpp>
#include <iostream>
int main()
{
    using namespace cv;
    Mat displayMat = Mat::zeros(500, 500, CV_8UC3);

    circle(displayMat, Point(100, 100), 100, CV_RGB(255, 0, 0), 1, 8, 0);
    line(displayMat, Point(200, 200), Point(300, 200), CV_RGB(0, 255, 0), 1, 8, 0);
    rectangle(displayMat, Rect(300, 300, 50, 50), CV_RGB(0, 0, 255), 1, 8, 0);

    imshow("Lines", displayMat);
    waitKey(0);
    return 0;
}