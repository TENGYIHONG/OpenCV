#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

using namespace cv;
using namespace std;


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

int main()
{
	cv::VideoCapture vcap;
	cv::Mat image;
	//网络摄像头地址
	//const std::string videoStreamAddress = "http://192.168.31.117/capture?_cb";
	
	std::string videoStreamAddress = "http://192.168.31.117/capture?_cb=1651328374468.jpg";

	//open the video stream and make sure it's opened
	if (!vcap.open(videoStreamAddress)) {
		std::cout << "Error opening video stream or file" << std::endl;
		return -1;
	}

	cv::namedWindow("Output Window");

	for (;;) {
		if (!vcap.read(image)) {
			std::cout << "No frame" << std::endl;
			cv::waitKey();
		}
		cv::imshow("Output Window", image);
		if (cv::waitKey(1) >= 0) break;
	}
}
