#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
int main()
{
    Mat srcMat = imread("D:\\project\\opencv_vscode\\ex23 warpAffine\\1.png");
    if (srcMat.empty())
    {
        std::cerr << "ͼ�����ʧ��" << std::endl;
        return -1;
    }

    Mat dstMat;
    float angle = -10.0;
    float scale = 1;
    Point2f center(srcMat.cols * 0.5, srcMat.rows * 0.5);
    Mat rot = getRotationMatrix2D(center, angle, scale);
    // ��ȡ����ı���
    Rect bbox = RotatedRect(center, srcMat.size(), angle).boundingRect();
    // ��������������
    rot.at<double>(0, 2) += bbox.width / 2 - center.x;
    rot.at<double>(1, 2) += bbox.height / 2 - center.y;

    warpAffine(srcMat, dstMat, rot, bbox.size());

    imshow("srcMat", srcMat);
    imshow("dstMat", dstMat);
    waitKey(0);
    return 0;
}