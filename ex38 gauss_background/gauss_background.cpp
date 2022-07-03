#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

void GaussianBackground(std::vector<Mat> srcMats, Mat &meanMat, Mat &varianceMat);
void GaussianThreshold(const Mat &srcMat, const Mat &meanMat, const Mat &varianceMat, int n, Mat &dstMat);

int main()
{
    VideoCapture cap(0);
    Mat frame;
    Mat dstMat;
    int count = 0;
    int nBackground = 300;
    std::vector<Mat> srcMats;
    Mat meanMat;
    Mat varianceMat;
    while (1)
    {
        cap >> frame;
        if (frame.empty())
        {
            break;
        }
        cvtColor(frame, frame, CV_BGR2GRAY);
        if (count < nBackground)
        {
            srcMats.push_back(frame);
        }
        else if (count == nBackground)
        {
            meanMat.create(frame.size(), CV_8UC1);
            varianceMat.create(frame.size(), CV_32FC1);
            GaussianBackground(srcMats, meanMat, varianceMat);
        }
        else
        {
            dstMat.create(frame.size(), CV_8UC1);
            GaussianThreshold(frame, meanMat, varianceMat, 3, dstMat);
            imshow("frame", frame);
            imshow("dstMat", dstMat);
        }

        count++;
        waitKey(30);
    }
    return 0;
}

void GaussianBackground(std::vector<Mat> srcMats, Mat &meanMat, Mat &varianceMat)
{
    for (int y = 0; y < srcMats[0].rows; y++)
    {
        for (int x = 0; x < srcMats[0].cols; x++)
        {
            int sum = 0;
            float variance = 0;

            //求均值
            for (int i = 0; i < srcMats.size(); i++)
            {
                sum += srcMats[i].at<uchar>(y, x);
            }
            meanMat.at<uchar>(y, x) = (uchar)(sum / srcMats.size());

            //求方差
            for (int i = 0; i < srcMats.size(); i++)
            {
                variance += (float)pow((srcMats[i].at<uchar>(y, x) - meanMat.at<uchar>(y, x)), 2);
            }
            varianceMat.at<float>(y, x) = variance / srcMats.size();
        }
    }
}

void GaussianThreshold(const Mat &srcMat, const Mat &meanMat, const Mat &varianceMat, int n, Mat &dstMat)
{
    for (int y = 0; y < srcMat.rows; y++)
    {
        for (int x = 0; x < srcMat.cols; x++)
        {
            int diff = abs(srcMat.at<uchar>(y, x) - meanMat.at<uchar>(y, x));
            int th = (int)n * varianceMat.at<float>(y, x);

            if (diff > th)
            {
                dstMat.at<uchar>(y, x) = 255;
            }
            else
            {
                dstMat.at<uchar>(y, x) = 0;
            }
        }
    }
}