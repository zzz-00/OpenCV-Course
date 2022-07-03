#include <opencv2/opencv.hpp>
#include <iostream>

void OTSU_function(const cv::Mat &srcMat)
{
    // 统计图像各灰度级的像素个数
    cv::Mat ThreadBinaryMat;
    int height = srcMat.rows;
    int width = srcMat.cols;
    int size = height * width;
    float histgram[256] = {0};
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            histgram[srcMat.at<uchar>(j, i)]++;
        }
    }

    // 计算类间方差并保存最大值
    int i_max; // 最大方差对应的灰度级
    float w1 = 0, w2 = 0, u = 0, u1 = 0, u2 = 0, variance = 0, maxvariance = 0;
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
    threshold(srcMat, ThreadBinaryMat, i_max, 255, cv::THRESH_BINARY);
    cv::imshow("ThreadBinaryMat", ThreadBinaryMat);
}