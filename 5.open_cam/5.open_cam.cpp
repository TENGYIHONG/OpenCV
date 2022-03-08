
#include <iostream>
#include <opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
using namespace std;
using namespace cv;
int main()
{
	std::cout << "Hello World!\n";
	VideoCapture capture(0);    // 打开摄像头
	if (!capture.isOpened())    // 判断是否打开成功
	{
		cout << "open camera failed. " << endl;
		return -1;
	}

	while (true)
	{
		Mat frame;
		capture >> frame;    // 读取图像帧至frame
		if (!frame.empty())	// 判断是否为空
		{
			imshow("camera", frame);
		}

		if (waitKey(30) > 0)		// delay 30 ms等待按键
		{
			break;
		}
	}

	return 0;

}


