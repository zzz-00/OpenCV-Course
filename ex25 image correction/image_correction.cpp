#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

int main()
{
    Mat srcMat = imread("D:\\project\\opencv_vscode\\ex25 image correction\\1.jpg");
    Mat dstMat_perspective;
    if (srcMat.empty())
    {
        std::cerr << "图像加载失败" << std::endl;
        return -1;
    }

    Mat grayMat;
    Mat binaryMat;
    cvtColor(srcMat, grayMat, COLOR_BGR2GRAY);
    threshold(grayMat, binaryMat, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

    Mat openMat;
    Mat structing;
    structing = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
    morphologyEx(binaryMat, openMat, MORPH_OPEN, structing);

    std::vector<std::vector<Point>> contours;
    findContours(openMat, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE); // 寻找轮廓
    int index = -1;
    int max = 0;
    // 找到面积最大的轮廓
    for (int i = 0; i < contours.size(); i++)
    {
        double area = contourArea(contours[i]);
        if (area > max)
        {
            max = area;
            index = i;
        }
    }

    RotatedRect rect = minAreaRect(contours[index]); // 最小面积矩形
    Point2f src_pt[4];
    Point2f dst_pt[4];
    rect.points(src_pt);
    dst_pt[0] = Point2f(srcMat.cols, srcMat.rows);
    dst_pt[1] = Point2f(0, srcMat.rows);
    dst_pt[2] = Point2f(0, 0);
    dst_pt[3] = Point2f(srcMat.cols, 0);

    const Mat perspective_matrix = getPerspectiveTransform(src_pt, dst_pt);
    warpPerspective(srcMat, dstMat_perspective, perspective_matrix, srcMat.size());

    imshow("srcMat", srcMat);
    imshow("openMat", openMat);
    imshow("dstMat", dstMat_perspective);
    waitKey(0);
    return 0;
}