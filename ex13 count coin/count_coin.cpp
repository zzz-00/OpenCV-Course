#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

int main()
{
    using std::cout;
    Mat srcMat = imread("D:\\project\\opencv_vscode\\ex13 count coin\\1.png", 0);
    if (!srcMat.data)
    {
        cout << "图像加载失败" << std::endl;
        return 0;
    }
    Mat bMat;
    Mat labels;
    Mat states;
    Mat centroids;

    threshold(srcMat, bMat, 100, 255, THRESH_OTSU);

    int count = connectedComponentsWithStats(bMat, labels, states, centroids);

    cout << count;
    int x, y, width, height;
    for (int i = 1; i < count; i++)
    {
        x = states.at<int>(i, 0);
        y = states.at<int>(i, 1);
        width = states.at<int>(i, 2);
        height = states.at<int>(i, 3);
        rectangle(bMat, Rect(x, y, width, height), CV_RGB(255, 255, 255), 1, 8);
    }

    imshow("srcMat", srcMat);
    imshow("bMat", bMat);

    waitKey(0);
    return 0;
}