#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
const std::string window_name = "binaryMat";
void threshold_Mat(int th, void *data)
{
    Mat src = *(Mat *)(data);
    Mat dst;
    // 二值化
    threshold(src, dst, th, 255, 0);
    imshow(window_name, dst);
}

int main()
{
    Mat srcMat;
    srcMat = imread("D:\\project\\opencv_vscode\\course\\ex1 rgb1_3\\1_1.jpg", 0);
    int lowTh = 30;
    int maxTh = 255;

    if (!srcMat.data)
    {
        std::cout << "图像载入失败" << std::endl;
        return 0;
    }
    imshow(window_name, srcMat);
    createTrackbar("threshold", window_name, &lowTh, maxTh, threshold_Mat, &srcMat);
    waitKey(0);
    return 0;
}