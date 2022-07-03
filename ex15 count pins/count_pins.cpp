#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

int main()
{
    Mat srcMat = imread("D:\\project\\opencv_vscode\\ex15 count pins\\1.png", 0);

    Mat grayMat = 255 - srcMat;
    Mat bMat;
    threshold(grayMat, bMat, 100, 255, THRESH_OTSU);

    Mat structing = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
    Mat openMat;
    morphologyEx(bMat, openMat, MORPH_OPEN, structing, Point(-1, -1));

    Mat labels;
    Mat states;
    Mat centroids;
    int count = connectedComponentsWithStats(openMat, labels, states, centroids); // 连通域计数
    int error = 0;
    int x, y, width, height;
    for (int i = 1; i < count; i++)
    {
        x = states.at<int>(i, 0);
        y = states.at<int>(i, 1);
        width = states.at<int>(i, 2);
        height = states.at<int>(i, 3);
        int ratio = height / width;
        if (ratio > 10)
        {
            error++;
        }
        else
        {
            rectangle(openMat, Rect(x, y, width, height), CV_RGB(255, 255, 255), 1, 8);
        }
    }

    std::cout << count - 1 - error;
    imshow("srcMat", srcMat);
    imshow("openMat", openMat);

    waitKey(0);
    return 0;
}