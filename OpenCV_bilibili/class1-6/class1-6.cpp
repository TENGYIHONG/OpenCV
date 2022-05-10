#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;
//task 1 show a img
int app_show_img(String file);
//task 2
int save_img(String file);
//task 3 图像对象的创建与赋值
int creation(String file);
//task 4 图像像素的读写操作
int pixel_visit(String file);

//task 6 滚动条演示操作-调整图片亮度
void on_track(int, void*);
void tracking_bar_demo(Mat& image);

int main()
{
	string file = "E:\\VS2019_OpenCV\\IMG\\capture (3).jpg";
	Mat Image = imread(file);
	tracking_bar_demo(Image);

	waitKey(0);//执行到这句，程序阻塞。参数表示延时时间。单位ms
	destroyAllWindows();//销毁前面创建的显示窗口
	return 0;
}

//task 1 show a img
int app_show_img(String file)
{
	//Mat src = imread("E:\\VS2019_OpenCV\\IMG\\capture (3).jpg", IMREAD_GRAYSCALE);//读取进来的数据以矩阵的形势,第二个参数代表显示一张灰度图像。
	Mat src = imread(file, IMREAD_GRAYSCALE);//读取进来的数据以矩阵的形势,第二个参数代表显示一张灰度图像。
	if (src.empty())
	{
		printf("could not load image");//如果图片不存在 将无法读取，打印到终端。
	}
	//超过屏幕的图像无法显示时候调用此函数。
	namedWindow("输入窗口", WINDOW_FREERATIO);//创建了一个新窗口，参数1表示名称，第二个参数代表一个自由的比例
	imshow("输入窗口", src);//表示显示在新创建的输入窗口上，第一个参数表示窗口名称，src表示数据对象Mat
	return 0;
}

//task 2 图像的保存
int save_img(String file)
{
	//app_show_img(file);
	Mat image=imread(file);
	imwrite("E:\\VS2019_OpenCV\\IMG\\hsv.jpg", image);//保存图片，前面是保存图的地址，后面是保存图的名称
	return 0;
}

//task 3 图像对象的创建与赋值
int creation(String file)
{
	app_show_img(file);
	Mat image = imread(file);
	std::cout << "width:" << image.cols << "     height: " << image.rows << "    channels: " << image.channels() << std::endl;

	return 0;
}

//task 4 图像像素的读写操作
int pixel_visit(String file)
{
	app_show_img(file);
	Mat image = imread(file);
	std::cout << "width:" << image.cols << "     height: " << image.rows << "    channels: " << image.channels() << std::endl;
	int dims = image.channels();
	int h = image.rows;
	int w = image.cols;
	for (int row = 0; row < h; row++)
	{
		for (int col = 0; col < w; col++)
		{
			if (dims == 1) //单通道的灰度图像
			{
				int pv = image.at<uchar>(row, col);//得到像素值
				image.at<uchar>(row, col) = 255 - pv;//给像素值重新赋值

			}
			if (dims == 3) //三通道的彩色图像
			{
				Vec3b bgr = image.at<Vec3b>(row, col); //opencv特定的类型，获取三维颜色，3个值
				image.at<Vec3b>(row, col)[0] = 255 - bgr[0];
				image.at<Vec3b>(row, col)[1] = 255 - bgr[1];
				image.at<Vec3b>(row, col)[2] = 255 - bgr[2];//对彩色图像读取它的像素值，并且对像素值进行改写。
			}
		}
	}
	namedWindow("像素读写演示", WINDOW_FREERATIO);
	imshow("像素读写演示", image);

	return 0;
}

//task 6 滚动条演示操作-调整图片亮度
/* createTrackbar来设置一个进度条，实现图片的亮度调节。 */
Mat  src, dst, m;
int lightness = 50;//定义初始的亮度为50

void on_track(int, void*)
{
	m = Scalar(lightness, lightness, lightness);//创建调整亮度的数值
	subtract(src, m, dst);//定义亮度变化为减
	imshow("亮度调整", dst);//显示调整亮度之后的图片
}


void tracking_bar_demo(Mat& image)
{

	namedWindow("亮度调整", WINDOW_AUTOSIZE);
	dst = Mat::zeros(image.size(), image.type());//图片的初始化创建一个和image大小相等，种类相同的图像
	m = Mat::zeros(image.size(), image.type());//图片的初始化创建一个和image大小相等，种类相同的图像
	src = image;//给src赋值
	int max_value = 100;//定义最大值为100
	createTrackbar("Value Bar:", "亮度调整", &lightness, max_value, on_track);//调用函数实现功能。
	on_track(50, 0);
}


