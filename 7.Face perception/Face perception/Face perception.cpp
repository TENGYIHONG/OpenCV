#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cstdio>
using namespace std;
using namespace cv;
int main()
{
	// 【1】加载分类器
	CascadeClassifier cascade;
	cascade.load("D:\\Program Files (x86)\\OpenCV\\opencv\\sources\\data\\haarcascadeshaarcascade_frontalface_default.xml");
	cascade.load("D:\\Program Files (x86)\\OpenCV\\opencv\\sources\\data\\haarcascade_frontalface_default.xml");


	Mat srcImage, grayImage, dstImage;
	// 【2】读取图片
	srcImage = imread("E:\\VS2019_OpenCV\\IMG\\2.png");
	dstImage = srcImage.clone();
	imshow("【原图】", srcImage);

	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY); // 生成灰度图，提高检测效率

	// 定义7种颜色，用于标记人脸
	Scalar colors[] =
	{
		// 红橙黄绿青蓝紫
		CV_RGB(255, 0, 0),
		CV_RGB(255, 97, 0),
		CV_RGB(255, 255, 0),
		CV_RGB(0, 255, 0),
		CV_RGB(0, 255, 255),
		CV_RGB(0, 0, 255),
		CV_RGB(160, 32, 240)
	};

	// 【3】检测
	vector<Rect> rect;
	cascade.detectMultiScale(grayImage, rect, 1.1, 3, 0);  // 分类器对象调用
	printf("检测到人脸个数：%d\n", rect.size()); // 将识别的人脸的数量显示在控制台中
	// 【4】标记--在脸部画圆
	for (int i = 0; i < rect.size(); i++)
	{
		Point  center;
		int radius;
		center.x = cvRound((rect[i].x + rect[i].width * 0.5));
		center.y = cvRound((rect[i].y + rect[i].height * 0.5));
		radius = cvRound((rect[i].width + rect[i].height) * 0.25);
		circle(dstImage, center, radius, colors[i % 7], 2);

		// 【5】显示
		imshow("【人脸识别detectMultiScale】", dstImage);

		waitKey(0);
		return 0;
	}
