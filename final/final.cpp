#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
using namespace cv;

void FlameDetection(const Mat &srcMat, Mat &dstMat);
void clear(Mat &srcMat);
void FindPoint(const Mat &srcMat, std::vector<Point> &point);
bool polynomial_curve_fit(std::vector<cv::Point> &key_point, int n, cv::Mat &A);

int main()
{
    VideoCapture srcCap;
    srcCap.open("D:\\project\\opencv_vscode\\final\\1.mp4"); // 480 * 268
    Mat frame;
    Mat result;
    Mat gMat, backgroundMat;
    Mat bMat, subMat;
    int cnt = 0;
    while (1)
    {
        srcCap >> frame;
        cvtColor(frame, gMat, CV_BGR2GRAY);
        if (frame.empty())
        {
            break;
        }

        if (cnt == 0)
        {
            gMat.copyTo(backgroundMat);
        }
        FlameDetection(frame, result); // ª—ÊºÏ≤‚

        if (cnt >= 100)
        {
            // ÀÆ÷˘ºÏ≤‚
            std::vector<Point> WaterPoint;
            Mat A;
            absdiff(gMat, backgroundMat, subMat);
            threshold(subMat, bMat, 100, 255, THRESH_BINARY);
            clear(bMat);
            FindPoint(bMat, WaterPoint);
            polynomial_curve_fit(WaterPoint, 3, A);
            std::vector<Point> FitPoint;
            for (int x = 180; x < bMat.cols; x++)
            {
                double y = A.at<double>(0, 0) + A.at<double>(1, 0) * x + A.at<double>(2, 0) * std::pow(x, 2) + A.at<double>(3, 0) * std::pow(x, 3);
                FitPoint.push_back(Point(x, y));
            }
            polylines(result, FitPoint, false, Scalar(0, 0, 255));
        }

        cnt++;
        imshow("frame", frame);
        // imshow("backgroundMat", backgroundMat);
        imshow("result", result);
        waitKey(30);
    }
    return 0;
}

void FlameDetection(const Mat &srcMat, Mat &dstMat)
{
    srcMat.copyTo(dstMat);
    // ª—Ê
    // 0-180
    double i_minH = 3;
    double i_maxH = 54;
    // 0-255
    double i_minS = 50;
    double i_maxS = 255;
    // 0-255
    double i_minV = 240;
    double i_maxV = 255;

    Mat hsvMat;
    Mat binaryMat;
    cvtColor(srcMat, hsvMat, COLOR_BGR2HSV);
    inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), binaryMat);

    Mat closeMat;
    Mat structing;
    structing = getStructuringElement(MORPH_ELLIPSE, Size(20, 20), Point(-1, -1));
    morphologyEx(binaryMat, closeMat, MORPH_CLOSE, structing);

    // ºÏ≤‚¬÷¿™
    std::vector<std::vector<Point>> contours;
    findContours(closeMat, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    for (int i = 0; i < contours.size(); i++)
    {
        RotatedRect rbox = minAreaRect(contours[i]);
        rectangle(dstMat, Rect(rbox.boundingRect()), Scalar(255, 0, 255), 1);
    }

    // imshow("binaryMat", binaryMat);
    // imshow("closeMat", closeMat);
}

void clear(Mat &srcMat)
{
    for (int y = 0; y < 100; y++)
    {
        for (int x = 300; x < srcMat.cols; x++)
        {
            srcMat.at<uchar>(y, x) = 0;
        }
    }
    for (int y = 0; y < srcMat.rows; y++)
    {
        for (int x = 0; x < 180; x++)
        {
            srcMat.at<uchar>(y, x) = 0;
        }
    }
    for (int y = 150; y < srcMat.rows; y++)
    {
        for (int x = 220; x < 260; x++)
        {
            srcMat.at<uchar>(y, x) = 0;
        }
    }
}

void FindPoint(const Mat &srcMat, std::vector<Point> &point)
{
    for (int x = 180; x < 400; x++)
    {
        for (int y = 20; y < 200; y++)
        {
            if (srcMat.at<uchar>(y, x) == 255)
            {
                point.push_back(Point(x, y));
                break;
            }
        }
    }

    Mat image = cv::Mat::zeros(srcMat.rows, srcMat.cols, CV_8UC3);
    for (int i = 0; i < point.size(); i++)
    {
        circle(image, point[i], 1, Scalar(0, 0, 255), -1, 8, 0);
    }
    imshow("point", image);
}

bool polynomial_curve_fit(std::vector<cv::Point> &key_point, int n, cv::Mat &A)
{
    //Number of key points
    int N = key_point.size();

    //ππ‘Ïæÿ’ÛX
    cv::Mat X = cv::Mat::zeros(n + 1, n + 1, CV_64FC1);
    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            for (int k = 0; k < N; k++)
            {
                X.at<double>(i, j) = X.at<double>(i, j) + std::pow(key_point[k].x, i + j);
            }
        }
    }

    //ππ‘Ïæÿ’ÛY
    cv::Mat Y = cv::Mat::zeros(n + 1, 1, CV_64FC1);
    for (int i = 0; i < n + 1; i++)
    {
        for (int k = 0; k < N; k++)
        {
            Y.at<double>(i, 0) = Y.at<double>(i, 0) + std::pow(key_point[k].x, i) * key_point[k].y;
        }
    }

    A = cv::Mat::zeros(n + 1, 1, CV_64FC1);
    //«ÛΩ‚æÿ’ÛA
    cv::solve(X, Y, A, cv::DECOMP_LU);
    return true;
}