#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

int main()
{
    Mat srcMat = imread("D:\\project\\opencv_vscode\\ex23 warpAffine\\1.png");
    Mat dstMat;
    if (srcMat.empty())
    {
        std::cout << "Í¼Ïñ¼ÓÔØÊ§°Ü" << std::endl;
        return -1;
    }
    float angle = -10.0;
    float scale = 1;
    Point2f center(srcMat.cols * 0.5, srcMat.rows * 0.5);
    const Mat affine_matrix = getRotationMatrix2D(center, angle, scale);
    warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());

    imshow("srcMat", srcMat);
    imshow("dstMat", dstMat);
    waitKey(0);
    return 0;
}