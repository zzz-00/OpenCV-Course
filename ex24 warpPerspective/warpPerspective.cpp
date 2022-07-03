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
    const Point2f src_pt[] = {Point2f(150, 150), Point2f(150, 300), Point2f(350, 300), Point2f(350, 150)};
    const Point2f dst_pt[] = {Point2f(200, 150), Point2f(200, 300), Point2f(340, 270), Point2f(340, 180)};

    const Mat perspective_matrix = getPerspectiveTransform(src_pt, dst_pt);
    warpPerspective(srcMat, dstMat, perspective_matrix, srcMat.size());

    imshow("srcMat", srcMat);
    imshow("dstMat", dstMat);
    waitKey(0);
    return 0;
}