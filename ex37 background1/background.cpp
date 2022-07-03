#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int main()
{
    VideoCapture cap("D:\\project\\opencv_vscode\\final\\1.mp4");
    Mat frame;
    Mat bMat;
    Mat bgMat, subMat;
    Mat resultMat;
    int count = 0;
    while (1)
    {
        cap >> frame;
        if (frame.empty())
        {
            break;
        }
        cvtColor(frame, bMat, CV_BGR2GRAY);
        if (count == 0)
        {
            bMat.copyTo(bgMat);
        }
        else
        {
            absdiff(bMat, bgMat, subMat);
            threshold(subMat, resultMat, 100, 255, THRESH_BINARY);
            imshow("bMat", bMat);
            imshow("Result", resultMat);
        }

        count++;
        if (waitKey(30) == 27)
        {
            destroyAllWindows();
            break;
        }
    }
    return 0;
}