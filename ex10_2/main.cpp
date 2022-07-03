#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int OTSU_function(const cv::Mat &srcMat);
int main()
{
    Mat srcMat = imread("D:\\project\\opencv_vscode\\ex7 split\\1.png", 0);
    Mat ThreadBinaryMat;
    Mat ThreadOtsuMat;
    int threshold1;
    threshold1 = OTSU_function(srcMat);
    threshold(srcMat, ThreadBinaryMat, threshold1, 255, THRESH_BINARY);
    threshold(srcMat, ThreadOtsuMat, 100, 255, THRESH_OTSU);
    imshow("ThreadBinaryMat", ThreadBinaryMat);
    imshow("ThreadOtsuMat", ThreadOtsuMat);
    waitKey(0);
    return 0;
}

int OTSU_function(const cv::Mat &srcMat)
{
    // 统计图像各灰度级的像素个数
    int height = srcMat.rows;
    int width = srcMat.cols;
    int size = height * width;
    double histgram[256] = {0};
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            histgram[srcMat.at<uchar>(j, i)]++;
        }
    }

    // 计算类间方差并保存最大值
    int i_max; // 最大方差对应的灰度级
    double w1 = 0, w2 = 0, u = 0, u1 = 0, u2 = 0, variance = 0, maxvariance = 0;
    // 前景像素比例w1
    // 背景像素比例w2
    // 总平均灰度值u
    // 前景平均灰度值u1
    // 背景平均灰度值u2
    // 类间方差variance
    // 最大类间方差maxvariance
    for (int i = 0; i < 256; i++) // 计算总平均灰度
    {
        histgram[i] = histgram[i] / size;
        u += i * histgram[i];
    }

    for (int i = 0; i < 256; i++) // i为阈值，从0-255遍历
    {
        for (int j = 0; j < 256; j++)
        {
            if (j <= i) // 前景比例
            {
                w1 += histgram[j];
                u1 += j * histgram[j];
            }
            else // 背景比例
            {
                w2 += histgram[j];
                u2 += j * histgram[j];
            }
        }
        u1 = u1 / w1;
        u2 = u2 / w2;

        variance = (w1 * pow((u1 - u), 2) + w2 * pow((u2 - u), 2)) / (w1 + w2);
        if (variance > maxvariance)
        {
            maxvariance = variance;
            i_max = i;
        }
    }
    return i_max;
}