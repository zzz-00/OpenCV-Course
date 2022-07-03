#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int main()
{
    VideoCapture cap;

    cap.open(0);
    // cap.open("http://admin:admin@192.168.0.155:8081");

    if (!cap.isOpened())
    {
        std::cout << "不能打开视频文件" << std::endl;
        return -1;
    }

    double fps = cap.get(CAP_PROP_FPS);
    std::cout << "fps: " << fps << std::endl;
    while (1)
    {
        Mat frame;
        bool rSuccess = cap.read(frame);
        if (!rSuccess)
        {
            std::cout << "不能从视频文件中读取帧" << std::endl;
            break;
        }
        else
        {
            imshow("frame", frame);
        }
        waitKey(30);
    }
    return 0;
}