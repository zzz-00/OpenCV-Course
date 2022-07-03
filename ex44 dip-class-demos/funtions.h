#pragma once
//#include "parameters.h"
#include <opencv.hpp>
#include <dnn.hpp>

using namespace cv;
using namespace std;
using namespace dnn;


//ͨ���Ǽ���ֵ����ȥ�����ŶȽϵ͵�bouding box
void postprocess(cv::Mat& frame, std::vector<cv::Mat>& outs);

// ����������
std::vector<cv::String> getOutputsNames(const cv::dnn::Net& net);


//���Ƽ����
void drawPred(int classId, float conf, int left, int top, int right, int bottom, cv::Mat& frame);

int yoloV3();

int openpose();


