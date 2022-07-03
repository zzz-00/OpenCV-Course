#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
using namespace cv;
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

    Mat resultMat;
    int match_method = 0;
    matchTemplate(grayMat, tempMat, resultMat, match_method);
    double min, max;
    Point minP, maxP;
    normalize(resultMat, resultMat, 0, 1, NORM_MINMAX, -1, Mat());
    Point matchLoc;
    minMaxLoc(resultMat, &min, &max, &minP, &maxP, Mat());
    if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
    {
        matchLoc = minP;
    }
    else
    {
        matchLoc = maxP;
    }
    rectangle(image, matchLoc, Point(matchLoc.x + tempMat.cols, matchLoc.y + tempMat.rows), Scalar(0, 0, 255), 1);

    imshow("image", image);
    imshow("resultMat", resultMat);
    waitKey(0);
    return 0;
}