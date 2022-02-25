#include<opencv2/opencv.hpp>
using namespace cv;

class QuickDemo //����һ��QuickDemo����
{
public:
	void colorSpace_Demo(Mat& imge); //����һ���࣬�����������һ��ͼƬ����ͼƬ����
};

void QuickDemo::colorSpace_Demo(Mat& image)
{
	Mat gray, hsv;//����2���������ͼ��gray��hsv��
	cvtColor(image, hsv, COLOR_BGR2HSV);//ͼ��ת�����������԰�imageת��hsv��������������ת�ɵ�����
	cvtColor(image, gray, COLOR_BGR2GRAY);//ͼ��ת�����������԰�imageת��hsv��������������ת�ɵ�����
	imshow("HSV", hsv);
	imshow("�Ҷ�", gray);
	imwrite("E:\\VS2019_OpenCV\\IMG\\hsv.jpg", hsv);//����ͼƬ��ǰ���Ǳ���ͼ�ĵ�ַ�������Ǳ���ͼ������
	imwrite("E:\\VS2019_OpenCV\\IMG\\gray.jpg", gray);
}

