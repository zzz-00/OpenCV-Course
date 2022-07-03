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

    std::vector<cv::Vec4i> lines;
    HoughLinesP(canny, lines, 1, CV_PI / 180, 10, 50, 20);

    // 绘制直线
    std::vector<cv::Vec4i>::iterator it = lines.begin();
    for (; it != lines.end(); ++it)
    {
        Point pt1, pt2;
        pt1.x = (*it)[0];
        pt1.y = (*it)[1];
        pt2.x = (*it)[2];
        pt2.y = (*it)[3];
        line(srcMat, pt1, pt2, Scalar(0, 0, 255), 1, CV_AA);
    }
    imshow("srcMat", srcMat);
    imshow("binary", binary);
    imshow("canny", canny);
    waitKey(0);
    return 0;
}