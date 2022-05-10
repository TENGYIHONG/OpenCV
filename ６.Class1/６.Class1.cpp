#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

/*
*task1: 读取图片并显示
*/
static Mat readImage(String filename)
{
	Mat mat = imread(filename);//读取进来的数据以矩阵的形势,第二个参数代表显示一张灰度图像。
	if (mat.empty())
	{
		cout << "could not" << filename << endl;
	}
	//超过屏幕的图像无法显示时候调用此函数。
	namedWindow("输入窗口");//创建了一个新窗口，参数1表示名称，第二个参数代表一个自由的比例
	imshow("输入窗口", mat);//表示显示在新创建的输入窗口上，第一个参数表示窗口名称，src表示数据对象Mat 
	return mat;
}

/*
*task2: 读取视频并播放
*/
static int readVideo(String videoFile)
{
	//String videoFile = "E:\\VS2019_OpenCV\\IMG\\test.mp4";
	VideoCapture video;
	if (!video.open(videoFile))
	{
		cout << "can't open video" << videoFile << endl;
		return -1;
	}
	//loop 
	int fps = video.get(CAP_PROP_FPS);
	double delay = 1000/fps;
	int iVideoTime = video.get(CAP_PROP_FRAME_COUNT) / fps;
	Mat frame;
	namedWindow("videoWindows");
	while (true)
	{
		if (!video.read(frame))	// frame是否为空
		{
			break;
		}
		imshow("videoWindows", frame);
		cout << "time" << iVideoTime << "s" << endl;
		waitKey(delay);
	}		
	
	return 0;

}

/*
*task3: 打开摄像头并播放
*/
static int opencamera()
{
	//打开默认的摄像头--0

	//string url = "http://192.168.31.117/capture?_cb=1651244514429";
	const std::string videoStreamAddress = "http://192.168.31.117/capture?_cb=1651328374468.jpg";

	string outputVideoPath = "E:\\VS2019_OpenCV\\IMG\\test.avi"; //视频保存位置
	Mat capture;
	
	VideoCapture camera(videoStreamAddress);
		if (!camera.isOpened())
		{
			cout << "****can't open camera****\n" << endl;
				return -1;
		}
	Mat frame;
	while (true)
	{
		VideoCapture camera(videoStreamAddress);
		camera >> frame;    // 读取图像帧至frame
		if (!frame.empty())	// 判断是否为空
		{
			imshow("camera", frame);
			capture = frame;

			//2.1 mean smooth
			Mat blurMat;
			blur(capture, blurMat, Size(3, 3));
			//imshow("mean blur", blurMat);
			//2.2 guass smooth
			Mat guassMat;
			GaussianBlur(blurMat, guassMat, Size(3, 3), 1, 1);
			//imshow("guass blur", guassMat);
			//media smooth
			Mat mediaMat;
			medianBlur(guassMat, mediaMat, 3);

			imshow("median blur", mediaMat);

			
		}
		int key=waitKey(1.);//必须加延时
		//key==32 space key ASCII 32
		if (key==32)
		{
			break;
		}

	}
	
}


/*
*task4:usage of Mat 
*/
static int usageOfMat()
{
	//1.赋值初始化
	//Mat mat=imread("XXX.jpg");
	//2.常见矩阵初始化
	Mat zero=Mat::zeros(3, 3, CV_8UC1);//unsigned 8bit single channel 
	cout << "3*3 zero matrix:\n" << zero << endl;
	//
	Mat ones = Mat::ones(3, 3, CV_8UC1);
	cout << "3*3 ones matrix:\n" << ones << endl;

	//单位矩阵
	Mat eye = Mat::eye(3, 3, CV_8UC1);
	cout << "3*3 single channels matrix:\n" << eye << endl;
	
	//创建自定义矩阵
	Mat mat(2, 4, CV_8UC1,Scalar(5));
	cout << "2*4 eye matrix:\n" << mat << endl;

	Mat mat1(2, 4, CV_8UC3, Scalar(1,2,3));
	cout << "2*4 3 channels matrix:\n" << mat1 << endl;

	int a[] = { 1,2,3,4,5,6,7,8,9 };
	Mat mat3(3, 3, CV_32SC1, a);
	cout << "3*3 single channels matrix:\n" << mat3<< endl;

	//访问单通道矩阵数据
	cout << "mat3[2,1]:\n" << mat3.at<int>(2,1) << endl;// 矩阵有0

	//访问多通道矩阵数据
	int b[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18 };
	Mat mat4(2, 3, CV_32SC3, b);
	cout << "2*3 3 channels matrix:\n" << mat4 << endl;
	cout << "mat4[1,2]:\n" << mat4.at<Vec3i>(1,2) << endl;// 矩阵有0
	cout << "mat4[1,2][0]:\n" << mat4.at<Vec3i>(1,2)[0] << endl;// 矩阵有0
	cout << "mat4[1,2][1]:\n" << mat4.at<Vec3i>(1,2)[1] << endl;// 矩阵有0
	cout << "mat4[1,2][2]:\n" << mat4.at<Vec3i>(1,2)[2] << endl;// 矩阵有0


	return 0;

}	
/*不使用opencv的函数*/
/* convert a color photo to blackwhite photo */
int converColor2bw(String filename)
{	/* 1.read a color photo
	 * 2.go over all pixels
	 * 3.conver every color pixel to gray
	 * 加权平均灰度处理
	 *gray=0.299R+0.587G+0.144B
	*/
	Mat colorMat = imread(filename);
	if (colorMat.empty())
	{
		cout << "could not" << filename << endl;
		return -1;
	}
	if (colorMat.channels() != 3)
	{
		cout << "NOT 3 channels IMG"<< endl;
		return -2;
	}
	imshow("输入窗口",colorMat);
	int rows = colorMat.rows;
	int cols = colorMat.cols;
	//获取colorMat矩阵类型
	int depth = colorMat.depth();
	cout << "depth==" << depth << endl;
	Mat gray(rows, cols, depth); //according colorMat
	



	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{	//gray=0.299R+0.587G+0.144B
			int B = colorMat.at<Vec3b>(i, j)[0];
			int G = colorMat.at<Vec3b>(i, j)[1];
			int R = colorMat.at<Vec3b>(i, j)[2];
			int P = 0.299 * R + 0.587 * G + 0.144 * B;
			gray.at<unsigned char>(i, j) = P;
		}
	

	}

	
	//超过屏幕的图像无法显示时候调用此函数。
	namedWindow("gray", WINDOW_FREERATIO);//创建了一个新窗口，参数1表示名称，第二个参数代表一个自由的比例
	imshow("gray", gray);//表示显示在新创建的输入窗口上，第一个参数表示窗口名称，src表示数据对象Mat 
	return 0;
}
/*task6 ：draw
*/
void draw()
{
	
	//1.create a white paint-board 创建白色的画板
	Mat board(600, 800, CV_8UC3, Scalar(255, 255, 255));
	//2.draw a point 
	Point P1(20, 50), P2(220, 100);
	circle(board, P1, 2, Scalar(255, 0, 0),2); 
	circle(board, P2, 2, Scalar(0, 255, 0), 2);
	
	//3.line
	line(board,P1, P2, Scalar(0, 0, 255));

	//4.circle
	circle(board, P1, 20, Scalar(255, 0, 0), 2);
	circle(board, P2, 50, Scalar(0, 255, 0), 2);
	
	//5.rectangle 矩形
	Rect rect1(20, 50, 100, 200), rect2(P1, P2);
	rectangle(board, rect1, Scalar(0, 255, 0));
	rectangle(board, rect2, Scalar(0, 0, 255));

	//6.write text
	putText(board, "My rectangle", P2, 1, 1, Scalar(0, 0, 0));
	//imshow("MyPIc", board);

	//7.draw a robot
	Mat robot(600, 800, CV_8UC3, Scalar(255, 255, 255));
	Point nose(400, 160);
	circle(robot, nose, 2, Scalar(0, 255, 0), 2);
	circle(robot, nose, 140, Scalar(0, 255, 0), 2);
	//eye
	Point leftEye(350, 110), rightEye(450, 110);
	circle(robot, leftEye, 4, Scalar(0, 255, 0), 2);
	circle(robot, leftEye, 20, Scalar(0, 255, 0), 2);
	circle(robot, rightEye, 4, Scalar(0, 255, 0), 2);
	circle(robot, rightEye, 20, Scalar(0, 255, 0), 2);
	//mouth
	Point mouth(400, 220);
	circle(robot, mouth, 40, Scalar(0, 255, 0), 2);
	//ear
	Point leftEar(260, 140), rightEar(540, 140);
	circle(robot, leftEar, 40, Scalar(0, 255, 0), 2);
	circle(robot, rightEar, 40, Scalar(0, 255, 0), 2);
	//body
	Rect body(220, 300, 360, 200);
	rectangle(robot, body, Scalar(0, 255, 0),2);
	

	imshow("MY ROBOT", robot);

}

//task 7 :image improvement
void makeNoise(Mat &mat,int n)
{
	srand(time(NULL));//随机种子
	for (int k = 0; k < n; k++)
	{

		int i = rand() % mat.rows;
		int j = rand() % mat.cols;
		mat.at<Vec3b>(i, j)[0] = 255;
		mat.at<Vec3b>(i, j)[1] = 255; 
		mat.at<Vec3b>(i, j)[2] = 255;
	}

}


int ImageImprovement(String filename) {
	//1.read a image
	Mat mat = imread(filename);//读取进来的数据以矩阵的形势,第二个参数代表显示一张灰度图像。
	if (mat.empty())
	{
		cout << "could not" << filename << endl;
		return -1;
	}
	//超过屏幕的图像无法显示时候调用此函数。
	//namedWindow("输入窗口", WINDOW_FREERATIO);//创建了一个新窗口，参数1表示名称，第二个参数代表一个自由的比例
	imshow("输入窗口", mat);//表示显示在新创建的输入窗口上，第一个参数表示窗口名称，src表示数据对象Mat 
	//smooth process(blur)

	//2.0 make noise
	// 
	makeNoise(mat,0);

	//2.1 mean smooth
	Mat blurMat;
	blur(mat, blurMat, Size(3, 3));
	imshow("mean blur", blurMat);
	//2.2 guass smooth
	Mat guassMat;
	GaussianBlur(mat, guassMat, Size(3, 3), 1, 1);
	imshow("guass blur", guassMat);
	//media smooth
	Mat mediaMat;
	medianBlur(mat, mediaMat, 3);
	imshow("median blur", mediaMat);
}
//task 8 sharpening process  锐化

int sharpening(String filename)
{
	//1.read a image
	Mat mat = imread(filename);//读取进来的数据以矩阵的形势,第二个参数代表显示一张灰度图像。
	if (mat.empty())
	{
		cout << "could not" << filename << endl;
		return -1;
	}
	//超过屏幕的图像无法显示时候调用此函数。
	//namedWindow("输入窗口", WINDOW_FREERATIO);//创建了一个新窗口，参数1表示名称，第二个参数代表一个自由的比例
	imshow("输入窗口", mat);//表示显示在新创建的输入窗口上，第一个参数表示窗口名称，src表示数据对象Mat 

	//2.create a template algoorithm :laplacian algorithm 拉普拉斯算子
	// 3*3 laplacian algorithm
	Mat kernel = (Mat_<float>(3, 3) <<0,-1,0,-1,4,-1,0,-1,0);
	Mat laplacMat;
	filter2D(mat, laplacMat, mat.depth(), kernel);

	imshow("laplace", laplacMat);
	//origin image +laplacian change
	Mat kernel_plus = (Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	Mat laplacMat_plus;
	filter2D(mat, laplacMat_plus, mat.depth(), kernel_plus);
	imshow("image+laplace", laplacMat_plus);
}

/* task 9 calcuate histogram 直方图
*/
int calHistogram(String filename)
{
	//1. read a image

	Mat mat = imread(filename);//读取进来的数据以矩阵的形势,第二个参数代表显示一张灰度图像。
	if (mat.empty())
	{
		cout << "could not" << filename << endl;
		return -1;
	}
	imshow("输入窗口", mat);//表示显示在新创建的输入窗口上，第一个参数表示窗口名称，src表示数据对象Mat 

	//2.计算每一个灰度值的数值
	Mat gray,hist;
	const int histSize = 256;
	const float ranges[] = {0,255};
	const float* pRange = ranges;

	cvtColor(mat, gray, COLOR_BGR2GRAY); //彩色转换为黑白
	calcHist(&gray,1,0,Mat(),hist,1,&histSize,&pRange);
	cout << "hist Size: " << hist.size() << endl;
	cout << "hist mat---------" << endl;
	cout << hist << endl;

	//3.归一化(为画直方图做处理)
	//600*512 Mat
	int h = 400;
	int w = 512;
	Mat board(h, w, CV_8UC3,Scalar(255,255.255));
	//src dst min max type
	normalize(hist, hist,0,255,NORM_MINMAX);//正则化
	cout << hist << endl;
	cout << "hist mat---------" <<hist.type()<< endl;
	//4.画直方图
	for (int i = 0; i < histSize; i++)
	{
		int y = hist.at <float>(i);
		line(board,Point(2*i,0), Point(2 * i,y ),Scalar(255, 0, 0));
		//line(board, Point(2 * i, 10), Point(2 * i, 310), Scalar(0, 0, 255));
		//line(board, Point(4 * i, 10), Point(4 * i, 310), Scalar(0, 0, 255));
		
	}
	imshow("直方图", board);
	return 0;
}

/*task 10 */

//// 执行侵蚀 erode
Mat performErosion(Mat inputImage, int erosionElement, int erosionSize)
{
	Mat outputImage;
	int erosionType;
	/*
	* 0 腐蚀类型 矩形
	* 1 十字形
	* 2 椭圆形
	*/
	if (erosionElement == 0)
		erosionType = MORPH_RECT;

	else if (erosionElement == 1)
		erosionType = MORPH_CROSS;

	else if (erosionElement == 2)
		erosionType = MORPH_ELLIPSE;

	// Create the structuring element for erosion
	Mat element = getStructuringElement(erosionType, Size(2 * erosionSize + 1, 2 * erosionSize + 1), Point(erosionSize, erosionSize));

	// Erode the image using the structuring element
	erode(inputImage, outputImage, element);

	// Return the output image
	return outputImage;
}

// 执行膨胀dilation
Mat performDilation(Mat inputImage, int dilationElement, int dilationSize)
{
	Mat outputImage;
	int dilationType;

	if (dilationElement == 0)
		dilationType = MORPH_RECT;

	else if (dilationElement == 1)
		dilationType = MORPH_CROSS;

	else if (dilationElement == 2)
		dilationType = MORPH_ELLIPSE;

	// Create the structuring element for dilation
	Mat element = getStructuringElement(dilationType, Size(2 * dilationSize + 1, 2 * dilationSize + 1), Point(dilationSize, dilationSize));

	// Dilate the image using the structuring element
	dilate(inputImage, outputImage, element);

	// Return the output image
	return outputImage;
}

/*********task 11***************/
/*
	图像修复技术
	1.图像修复原理
	2.INPAINT_TELEA 的 FMM
	3. INPAINT_NS
	代码思路
	=>读照片=>设置修复区域=>算法填充=>显示修复后的图片

*/


int main(int argc,char const*argv[])
{

	Mat inputImage, outputImage, outputImage1;
	String filename = "E:\\VS2019_OpenCV\\IMG\\num.png";
	//String videoname = "E:\\VS2019_OpenCV\\IMG\\test.mp4";
	inputImage=readImage(filename);
	//Mat laplaceMat;
	//Laplacian(inputImage, laplaceMat, inputImage.depth());
	//readVideo(videoname);
	//opencamera();
	//usageOfMat();
	//converColor2bw(filename);
	//draw();
	//ImageImprovement(filename);
	//sharpening(filename);
	//calHistogram(filename);

	// Dilate the image
	outputImage =performDilation(inputImage, 2, 1);
	imshow("Output image after dilation", inputImage);

	// Erode the image
	outputImage1 = performErosion(inputImage, 2, 1);
	//绘制边界
	imshow("Output image", outputImage - outputImage1);
	// Display the output image
	imshow("Output image after erosion", outputImage);
	waitKey(0);//执行到这句，程序阻塞。参数表示延时时间。单位ms
	destroyAllWindows();//销毁前面创建的显示窗口
	return 0;
}
