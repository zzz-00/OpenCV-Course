#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
using namespace cv;

const int BlockSize = 16;
const int AngleQuantification = 8;

void HOG(Mat srcMat, float *hist, int angle_quantification, int block_size);
void comparison(float *hist1, float *hist2, int size, float &distance);

int main()
{
    Mat image = imread("D:\\project\\opencv_vscode\\ex39 temp1\\img.png");
    Mat tempMat = imread("D:\\project\\opencv_vscode\\ex39 temp1\\template.png", 0);

    if (image.empty() || tempMat.empty())
    {
        std::cerr << "image load failed..." << std::endl;
        return -1;
    }
    Mat grayMat;
    cvtColor(image, grayMat, CV_BGR2GRAY);

    int maxX = 0;
    int maxY = 0;
    float minDist = FLT_MAX, dist = 0;
    int nX = tempMat.cols / BlockSize;
    int nY = tempMat.rows / BlockSize;
    int bins = nX * nY * AngleQuantification;
    float *tempHist = new float[bins];
    HOG(tempMat, tempHist, AngleQuantification, BlockSize);
    for (int y = 0; y < grayMat.rows - tempMat.rows + 1; y++)
    {
        for (int x = 0; x < grayMat.cols - tempMat.cols + 1; x++)
        {
            float *roiHist = new float[bins];
            Mat roi = grayMat(Rect(x, y, tempMat.cols, tempMat.rows));
            HOG(roi, roiHist, AngleQuantification, BlockSize);
            comparison(tempHist, roiHist, bins, dist);
            if (dist < minDist)
            {
                minDist = dist;
                maxX = x;
                maxY = y;
            }
            delete[] roiHist;
        }
    }

    rectangle(image, Rect(maxX, maxY, tempMat.cols, tempMat.rows), Scalar(0, 0, 255), 1);
    imshow("image", image);

    waitKey(0);
    delete[] tempHist;
    return 0;
}

void HOG(Mat srcMat, float *hist, int angle_quantification, int block_size)
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