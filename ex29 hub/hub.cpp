#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int main()
{
    Mat srcMat = imread("D:\\project\\opencv_vscode\\ex29 hub\\1.png");
    if (srcMat.empty())
    {
        std::cerr << "Í¼Ïñ¼ÓÔØÊ§°Ü" << std::endl;
        return -1;
    }

    Mat gray;
    cvtColor(srcMat, gray, COLOR_BGR2GRAY);

    Mat binary;
    threshold(gray, binary, 100, 255, THRESH_OTSU);
    binary = 255 - binary;

    Mat structing;
    structing = getStructuringElement(MORPH_ELLIPSE, Size(3, 3), Point(-1, -1));
    Mat openMat;
    morphologyEx(binary, openMat, MORPH_OPEN, structing);

    std::vector<std::vector<Point>> contours;
    findContours(openMat, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    for (int i = 0; i < contours.size(); i++)
    {
        RotatedRect rbox = minAreaRect(contours[i]);
        if (rbox.boundingRect().height / rbox.boundingRect().width < 1.4 && rbox.size.area() < 4000 && rbox.size.area() > 900)
        {
            drawContours(srcMat, contours, i, Scalar(0, 255, 255), FILLED, 8);
        }
    }

    imshow("srcMat", srcMat);
    imshow("binary", binary);
    imshow("openMat", openMat);
    waitKey(0);
    return 0;
}