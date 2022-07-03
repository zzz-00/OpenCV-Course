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

    const Point2f src_pt[] = {Point2f(0, 0), Point2f(0, 415), Point2f(415, 0)};
    const Point2f dst_pt[] = {Point2f(0, 415), Point2f(415, 415), Point2f(0, 0)};

    const Mat affine_matrix = getAffineTransform(src_pt, dst_pt);
    warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());

    imshow("srcMat", srcMat);
    imshow("dstMat", dstMat);
    waitKey(0);
    return 0;
}