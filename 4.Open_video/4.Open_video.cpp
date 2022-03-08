
#include <iostream>
#include <opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
using namespace std;
using namespace cv;
int main()
{
    std::cout << "Hello World!\n"; 
	VideoCapture video;
	video.open("E:\\VS2019_OpenCV\\IMG\\test.mp4");    // 打开视频文件
 
	if(!video.isOpened())    // 判断是否打开成功
	{
		cout << "open video file failed. " << endl;
		return -1;
	}
	
	while(true)
	{
		Mat frame;
		video >> frame;    // 读取图像帧至frame
		if(!frame.empty())	// frame是否为空
		{
			imshow("video", frame);    // 显示图像
		}
 
		if(waitKey(30) > 0)		// delay 30 ms 等待是否按键
		{
			break;
		}
	}
 
    return 0;




}


