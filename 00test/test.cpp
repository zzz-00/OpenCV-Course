#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int main()
{
    Mat srcMat = imread("D:\\project\\opencv_vscode\\course\\ex1 rgb1_3\\1_1.jpg");
    if (srcMat.empty())
    {
        std::cerr << "load failed" << std::endl; // 1
        return -1;
    } 
    imshow("srcMat", srcMat); 
    waitKey(0);
    return 0;
}