#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    using namespace cv;
    Mat srcMat = imread("D:\\project\\opencv_vscode\\ex15 count pins\\1.png");
    if (srcMat.empty())
    {
        std::cout << "Í¼Ïñ¼ÓÔØÊ§°Ü" << std::endl;
        return -1;
    }
    Mat dstMat_1;
    Mat dstMat_2;
    Mat dstMatdx;
    Mat dstMatdy;

    Sobel(srcMat, dstMatdx, CV_16SC1, 1, 0);
    Sobel(srcMat, dstMatdy, CV_16SC1, 0, 1);

    Canny(dstMatdx, dstMatdy, dstMat_1, 50, 100);
    Canny(srcMat, dstMat_2, 100, 200);
    imshow("srcMat", srcMat);
    imshow("dstMat_1", dstMat_1);
    imshow("dstMat_2", dstMat_2);
    waitKey(0);
    return 0;
}