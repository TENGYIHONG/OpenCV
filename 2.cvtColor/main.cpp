#include<opencv2/opencv.hpp>
#include<iostream>
#include<quickopencv.h>

using namespace std;
using namespace cv;
int main()
{

	Mat src = imread("E:\\VS2019_OpenCV\\IMG\\1.png", IMREAD_ANYCOLOR);//B,G,R实际上0-255三色。3通道
	//读取进来的数据以矩阵的形势,第二个参数代表显示一张灰度图像。
	if (src.empty())
	{
		printf("could not load image");//如果图片不存在 将无法读取，打印到终端。
		return -1;
	}
	//超过屏幕的图像无法显示时候调用此函数。

	namedWindow("输入窗口", WINDOW_FREERATIO);//创建了一个新窗口，参数1表示名称，第二个参数代表一个自由的比例
	imshow("输入窗口", src);//表示显示在新创建的输入窗口上，第一个参数表示窗口名称，src表示数据对象Mat 
//在主函数中调用之前创建的类对象	
	QuickDemo qd;
	qd.colorSpace_Demo(src);

	waitKey(0);//执行到这句，程序阻塞。参数表示延时时间。单位ms
	destroyAllWindows();//销毁前面创建的显示窗口
	return 0;
}
