#include <opencv2/opencv.hpp>
#include <iostream>
int main()
{
    using namespace cv;
    Mat srcMat = imread("D:\\project\\opencv_vscode\\ex7 split\\1.png");
    std::vector<Mat> channels;
    split(srcMat, channels);
    Mat B = channels.at(0);
    Mat G = channels.at(1);
    Mat R = channels.at(2);

    imshow("srcMat", srcMat);
    imshow("red", R);
    imshow("green", G);
    imshow("blue", B);

    waitKey(0);
    return 0;
}