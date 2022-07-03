#include <iostream>
#include <opencv2/opencv.hpp>
int main()
{
    using namespace cv;
    float histgram[256] = {0};
    Mat srcMat = imread("D:\\project\\opencv_vscode\\ex23 warpAffine\\1.png", 0);
    int height = srcMat.rows;
    int width = srcMat.cols;
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            histgram[srcMat.at<uchar>(j, i)]++;
        }
    }

    int max = 0;

    for (int i = 0; i < 255; i++)
    {
        if (histgram[i] > max)
            max = histgram[i];
    }
    // 画直方图
    Mat displayMat = Mat::zeros(256, 256, CV_8UC3);
    for (int i = 0; i < 255; i++)
    {
        rectangle(displayMat, Rect(i, 256 - 256 * histgram[i] / max, 1, 256 * histgram[i] / max), CV_RGB(255, 255, 255), 1, 8, 0);
    }
    imshow("srcMat", srcMat);
    imshow("displayMat", displayMat);
    waitKey(0);
    return 0;
}