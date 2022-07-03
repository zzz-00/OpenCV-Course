#include <opencv2/opencv.hpp>
#include <iostream>
int main()
{
	cv::Mat srcMat = cv::imread("D:\\project\\opencv_vscode\\ex1 rgb1_3\\1_1.jpg", 0);
	cv::imshow("src", srcMat);
	cv::waitKey();
	return 0;
}