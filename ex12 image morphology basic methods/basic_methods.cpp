#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

int main()
{
    Mat srcMat = imread("D:\\project\\opencv_vscode\\ex12 image morphology basic methods\\1.png", 0);
    Mat bMat;
    Mat erodeMat;
    Mat dilateMat;
    Mat openMat;
    Mat closeMat;

    Mat structing;
    structing = getStructuringElement(MORPH_ELLIPSE, Size(20, 20), Point(-1, -1));

    threshold(srcMat, bMat, 100, 255, THRESH_OTSU);

    erode(bMat, erodeMat, structing);
    dilate(bMat, dilateMat, structing);
    morphologyEx(bMat, openMat, MORPH_OPEN, structing);
    morphologyEx(bMat, closeMat, MORPH_CLOSE, structing);

    imshow("bMat", bMat);
    imshow("erodeMat", erodeMat);
    imshow("dilateMat", dilateMat);
    imshow("openMat", openMat);
    imshow("closeMat", closeMat);

    waitKey(0);

    return 0;
}