#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>
using namespace cv;

const float PI = 3.14159;
const int BlockSize = 16;
const int AngleQuantification = 8;

void HOG(Mat srcMat, float *hist, Mat &histgram, int angle_quantification, int block_size);
void comparison(float *hist1, float *hist2, int size, float &distance);

int main()
{
    Mat refMat = imread("D:\\project\\opencv_vscode\\ex32 HOG\\1.jpg");
    Mat cmpMat1 = imread("D:\\project\\opencv_vscode\\ex32 HOG\\2.jpg");
    Mat cmpMat2 = imread("D:\\project\\opencv_vscode\\ex32 HOG\\3.jpg");
    if (refMat.empty() || cmpMat1.empty() || cmpMat2.empty())
    {
        std::cerr << "图像加载失败" << std::endl;
        return -1;
    }

    Mat refhistgram;
    Mat cmphistgram1;
    Mat cmphistgram2;
    float distance;

    int nX = refMat.cols / BlockSize;
    int nY = refMat.rows / BlockSize;
    int bins = nX * nY * AngleQuantification;

    float *ref_hist = new float[bins];
    float *cmp_hist1 = new float[bins];
    float *cmp_hist2 = new float[bins];
    memset(ref_hist, 0, sizeof(float) * bins);
    memset(cmp_hist1, 0, sizeof(float) * bins);
    memset(cmp_hist2, 0, sizeof(float) * bins);

    HOG(refMat, ref_hist, refhistgram, AngleQuantification, BlockSize);
    HOG(cmpMat1, cmp_hist1, cmphistgram1, AngleQuantification, BlockSize);
    HOG(cmpMat2, cmp_hist2, cmphistgram2, AngleQuantification, BlockSize);

    float dist1, dist2;
    comparison(ref_hist, cmp_hist1, bins, dist1);
    comparison(ref_hist, cmp_hist2, bins, dist2);
    std::cout << dist1 << std::endl
              << dist2 << std::endl;
    if (dist1 <= dist2)
    {
        std::cout << "image1 is similar." << std::endl;
    }
    else
    {
        std::cout << "image2 is similar." << std::endl;
    }

    imshow("refMat", refMat);
    imshow("cmpMat1", cmpMat1);
    imshow("cmpMat2", cmpMat2);
    imshow("refhistgram", refhistgram);
    imshow("cmphistgram1", cmphistgram1);
    imshow("cmphistgram2", cmphistgram2);
    waitKey(0);
    delete[] ref_hist;
    delete[] cmp_hist1;
    delete[] cmp_hist2;
    return 0;
}

void HOG(Mat srcMat, float *hist, Mat &histgram, int angle_quantification, int block_size)
{
    int nX = srcMat.cols / block_size;
    int nY = srcMat.rows / block_size;
    int bins = nX * nY * angle_quantification;

    Mat gx, gy, mag, angle;
    Sobel(srcMat, gx, CV_32F, 1, 0, 1);
    Sobel(srcMat, gy, CV_32F, 0, 1, 1);
    cartToPolar(gx, gy, mag, angle, true);

    // hist赋值
    for (int y = 0; y < nY * block_size; y++)
    {
        for (int x = 0; x < nX * block_size; x++)
        {
            hist[(y / block_size * nX + x / block_size) * angle_quantification + int((angle.at<float>(y, x) - 1) * angle_quantification / 360)] += mag.at<float>(y, x);
        }
    }

    // 画直方图
    histgram = Mat::zeros(500, bins, CV_32F);
    for (int i = 0; i < bins; i++)
    {
        rectangle(histgram, Rect(i, 500 - hist[i] / 20, 1, hist[i] / 20), CV_RGB(255, 255, 255), 1, 8, 0);
    }
}

// 比较相似度
void comparison(float *hist1, float *hist2, int size, float &distance)
{
    float sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += pow((hist1[i] - hist2[i]), 2);
    }
    distance = sqrt(sum);
}
