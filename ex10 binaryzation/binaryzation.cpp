#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int main()
{
    Mat srcMat = imread("D:\\project\\opencv_vscode\\ex1 rgb1_3\\1_1.jpg", 0);
    if (!srcMat.data)
    {
        std::cout << "图像载入失败" << std::endl;
        return 0;
    }
    Mat ThreadBinaryMat;
    Mat ThreadOtsuMat;
    Mat AdaptThreadMat;
    threshold(srcMat, ThreadBinaryMat, 100, 255, THRESH_BINARY);
    threshold(srcMat, ThreadOtsuMat, 100, 255, THRESH_OTSU);
    adaptiveThreshold(srcMat, AdaptThreadMat, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 15, 10);
    // adaptiveThreshold(srcMat, AdaptThreadMat, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 15, 10);

    imshow("ThreadBinaryMat", ThreadBinaryMat);
    imshow("ThreadOtsuMat", ThreadOtsuMat);
    imshow("AdaptThreadMat", AdaptThreadMat);
    waitKey(0);

    return 0;
}