#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
int main()
{
    Mat srcMat = imread("D:\\project\\opencv_vscode\\ex23 warpAffine\\1.png");
    if (srcMat.empty())
    {
        std::cerr << "Í¼Ïñ¼ÓÔØÊ§°Ü" << std::endl;
        return -1;
    }
    std::vector<Mat> channels;
    split(srcMat, channels);
    Mat B = channels.at(0);
    Mat G = channels.at(1);
    Mat R = channels.at(2);
    Mat dstMat_B;
    Mat dstMat_G;
    Mat dstMat_R;
    Mat dstMat;
    equalizeHist(B, dstMat_B);
    equalizeHist(G, dstMat_G);
    equalizeHist(R, dstMat_R);
    srcMat.copyTo(dstMat);
    int height = dstMat.rows;
    int width = dstMat.cols;
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            dstMat.at<cv::Vec3b>(j, i)[0] = dstMat_B.at<uchar>(j, i);
            dstMat.at<cv::Vec3b>(j, i)[1] = dstMat_G.at<uchar>(j, i);
            dstMat.at<cv::Vec3b>(j, i)[2] = dstMat_R.at<uchar>(j, i);
        }
    }
    imshow("srcMat", srcMat);
    imshow("dstMat", dstMat);
    waitKey(0);
    return 0;
}