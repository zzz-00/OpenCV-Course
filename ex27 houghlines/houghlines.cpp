#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
int main()
{
    Mat srcMat = imread("D:\\project\\opencv_vscode\\ex27 houghlines\\1.jpg");
    if (srcMat.empty())
    {
        std::cerr << "图像加载失败" << std::endl;
        return -1;
    }

    Mat gray;
    cvtColor(srcMat, gray, CV_RGBA2GRAY);
    Mat binary;
    threshold(gray, binary, 100, 255, THRESH_OTSU);
    Mat canny;
    Canny(binary, canny, 50, 100);

    std::vector<cv::Vec2f> lines;
    HoughLines(canny, lines, 1, CV_PI / 180, 125);
    // Mat lineMat;
    // HoughLines(binary, lineMat, 1, CV_PI / 180, 290);

    // 绘制直线
    std::vector<cv::Vec2f>::iterator it = lines.begin();
    for (; it != lines.end(); ++it)
    {
        float rho = (*it)[0], theta = (*it)[1];
        Point pt1, pt2;
        double a = cos(theta);
        double b = sin(theta);
        double x0 = a * rho;
        double y0 = b * rho;
        pt1.x = saturate_cast<int>(x0 + 1000 * (-b));
        pt1.y = saturate_cast<int>(y0 + 1000 * (a));
        pt2.x = saturate_cast<int>(x0 - 1000 * (-b));
        pt2.y = saturate_cast<int>(y0 - 1000 * (a));
        line(srcMat, pt1, pt2, Scalar(0, 0, 255), 1, CV_AA);
    }

    imshow("srcMat", srcMat);
    imshow("binary", binary);
    imshow("canny", canny);
    waitKey(0);
    return 0;
}