#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
const uchar threshold = 100;
int main()
{
	Mat srcMat = imread("D:\\project\\opencv_vscode\\ex1 rgb1_3\\1_1.jpg");
	Mat shallowMat = srcMat;
	Mat deepMat;
	srcMat.copyTo(deepMat);
	int height = srcMat.rows;
	int width = srcMat.cols;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			uchar average = (srcMat.at<cv::Vec3b>(j, i)[0] + srcMat.at<cv::Vec3b>(j, i)[1] + srcMat.at<cv::Vec3b>(j, i)[2]) / 3;
			if (average > ::threshold)
				average = 255;
			else
				average = 0;
			srcMat.at<cv::Vec3b>(j, i)[0] = average;
			srcMat.at<cv::Vec3b>(j, i)[1] = average;
			srcMat.at<cv::Vec3b>(j, i)[2] = average;
		}
	}
	imshow("srcMat", srcMat);
	imshow("shallowMat", shallowMat);
	imshow("deepMat", deepMat);
	waitKey();
	return 0;
}