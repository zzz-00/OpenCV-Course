#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

const int circle_r = 20;

int main()
{
    Mat srcMat = imread("D:\\project\\opencv_vscode\\ex14 count circle\\1.jpg", 0);
    Mat bMat = 255 - srcMat; // 反相

    Mat structing; // 结构算子
    structing = getStructuringElement(MORPH_ELLIPSE, Size(circle_r, circle_r), Point(-1, -1));

    Mat openMat; // 开运算
    morphologyEx(bMat, openMat, MORPH_OPEN, structing);

    Mat labels;
    Mat states;
    Mat centroids;
    int count = connectedComponentsWithStats(openMat, labels, states, centroids); // 连通域计数
    std::cout << count - 1;

    imshow("srcMat", srcMat);
    imshow("bMat", bMat);
    imshow("openMat", openMat);

    waitKey(0);
    return 0;
}