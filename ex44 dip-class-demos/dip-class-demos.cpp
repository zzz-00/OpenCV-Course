// dip-class-demos.cpp : �������̨Ӧ�ó������ڵ㡣

//#include "stdafx.h"
#include <opencv.hpp>
#include "funtions.h"
//#include "parameters.h"

using namespace cv;
using namespace std;

int main()
{
	//��ʼ��ʱ
	double start = static_cast<double>(cvGetTickCount());

	int method = 0;

	if (method == 0) {
		yoloV3();
	}
	else if (method == 1) {
		openpose();
	}

	//������ʱ
	double time = ((double)cvGetTickCount() - start) / cvGetTickFrequency();
	//��ʾʱ��
	cout << "processing time:" << time / 1000 << "ms" << endl;

	//�ȴ�������Ӧ�����������������
	system("pause");
    return 0;
}

