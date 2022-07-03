#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
using namespace cv;

void gamma_correction(const Mat &src, Mat &dst, float gamma);

int main()
{
    Mat srcMat = imread("D:\\project\\opencv_vscode\\ex35 gamma\\1.jpg");
    if (srcMat.empty())
    {
        std::cerr << "Í¼Ïñ¼ÓÔØÊ§°Ü" << std::endl;
        return -1;
    }
    Mat dstMat;
    float gamma = 1/3.0;
    gamma_correction(srcMat, dstMat, gamma);

    imshow("srcMat", srcMat);
    imshow("dstMat", dstMat);
    waitKey(0);
    return 0;
}

void gamma_correction(const Mat &src, Mat &dst, float gamma)
{
    uchar LUT[256];
    src.copyTo(dst);
    for (int i = 0; i < 256; i++)
    {
        float f = i / 255.0;
        f = pow(f, gamma);
        LUT[i] = uchar(f * 255);
    }
    if (dst.channels() == 1)
    {
        MatIterator_<uchar> it = dst.begin<uchar>();
        MatIterator_<uchar> it_end = dst.end<uchar>();
        for (; it != it_end; it++)
        {
            *it = LUT[(*it)];
        }
    }
    else
    {
        MatIterator_<Vec3b> it = dst.begin<Vec3b>();
        MatIterator_<Vec3b> it_end = dst.end<Vec3b>();
        for (; it != it_end; it++)
        {
            (*it)[0] = LUT[(*it)[0]];
            (*it)[1] = LUT[(*it)[1]];
            (*it)[2] = LUT[(*it)[2]];
        }
    }
}