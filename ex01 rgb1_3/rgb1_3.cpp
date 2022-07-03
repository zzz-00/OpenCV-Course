#include <opencv2/opencv.hpp>
#include <iostream>
int main()
{
	cv::Mat srcMat = cv::imread("D:\\project\\opencv_vscode\\ex1 rgb1_3\\1_1.jpg");
	int height = srcMat.rows; // 行数
	int width = srcMat.cols;  // 每行元素的总元素数量
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			uchar average = (srcMat.at<cv::Vec3b>(j, i)[0] + srcMat.at<cv::Vec3b>(j, i)[1] + srcMat.at<cv::Vec3b>(j, i)[2]) / 3;
			srcMat.at<cv::Vec3b>(j, i)[0] = average;
			srcMat.at<cv::Vec3b>(j, i)[1] = average;
			srcMat.at<cv::Vec3b>(j, i)[2] = average;
		}
	}
	cv::imshow("src", srcMat);
	cv::waitKey();
	return 0;
}