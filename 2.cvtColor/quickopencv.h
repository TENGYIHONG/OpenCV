#include<opencv2/opencv.hpp>
using namespace cv;

class QuickDemo //创建一个QuickDemo对象
{
public:
	void colorSpace_Demo(Mat& imge); //定义一个类，里面包含输入一个图片，对图片操作
};

void QuickDemo::colorSpace_Demo(Mat& image)
{
	Mat gray, hsv;//定义2个矩阵类的图像gray和hsv，
	cvtColor(image, hsv, COLOR_BGR2HSV);//图像转换函数，可以把image转成hsv，第三个参数是转成的类型
	cvtColor(image, gray, COLOR_BGR2GRAY);//图像转换函数，可以把image转成hsv，第三个参数是转成的类型
	imshow("HSV", hsv);
	imshow("灰度", gray);
	imwrite("E:\\VS2019_OpenCV\\IMG\\hsv.jpg", hsv);//保存图片，前面是保存图的地址，后面是保存图的名称
	imwrite("E:\\VS2019_OpenCV\\IMG\\gray.jpg", gray);
}

