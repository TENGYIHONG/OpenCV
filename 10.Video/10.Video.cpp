#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/objdetect.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char * argv[])
{
    CascadeClassifier faceCascade;
    string faceCascadeName = "resources\\haarcascade_frontalface_alt.xml";
    if (!faceCascade.load(faceCascadeName))
    {
        cerr << "Error loading cascade file. Exiting!" << endl;
        return -1;
    }

    Mat faceMask = imread("resources\\mask.jpg");

    if (!faceMask.data)
    {
        cerr << "Error loading mask image. Exiting!" << endl;
    }

    // Current frame
    Mat frame, frameGray;
    Mat frameROI, faceMaskSmall;
    Mat grayMaskSmall, grayMaskSmallThresh, grayMaskSmallThreshInv;
    Mat maskedFace, maskedFrame;

    // Create the capture object
    // 0 -> input arg that specifies it should take the input from the webcam
    VideoCapture cap("http://192.168.31.117/jpg");

    // If you cannot open the webcam, stop the execution!
    if (!cap.isOpened())
        return -1;

    //create GUI windows
    namedWindow("Frame");

    // 缩放因子来调整来自网络摄像头的输入帧的大小  
    float scalingFactor = 1;

    vector<Rect> faces;

    // Iterate until the user presses the Esc key
    while (true)
    {
        VideoCapture cap("http://192.168.31.117/jpg");
        cap >> frame;   // 捕获当前帧

        // 调整的框架
        resize(frame, frame, Size(), scalingFactor, scalingFactor, INTER_AREA);

        // 转换为灰度图
        cvtColor(frame, frameGray, COLOR_BGR2GRAY);

        // 平衡直方图
        equalizeHist(frameGray, frameGray);

        // 检测人脸
        faceCascade.detectMultiScale(frameGray, faces, 1.1, 2, 0 | 2, Size(30, 30));

        // 在脸周围画一个绿色的矩形
        for (auto& face : faces)
        {
            Rect faceRect(face.x, face.y, face.width, face.height);

            // 自定义参数，使面具适合您的脸。 您可能需要反复使用它们，以确保它有效。 
            int x = face.x - int(0.1 * face.width);
            int y = face.y - int(0.1 * face.height);
            int w = int(1.1 * face.width);
            int h = int(1.3 * face.height);

            // 提取感兴趣区域(ROI)覆盖您的脸  
            frameROI = frame(Rect(x, y, w, h));

            //根据上述ROI的尺寸调整面罩图像的大小  
            resize(faceMask, faceMaskSmall, Size(w, h));

            // 将上面的图像转换为灰度
            cvtColor(faceMaskSmall, grayMaskSmall, COLOR_BGR2GRAY);

            // 对上面的图像设置阈值，以隔离与遮罩相关的像素  
            threshold(grayMaskSmall, grayMaskSmallThresh, 230, 255, THRESH_BINARY_INV);

            //通过反转上面的图像创建蒙版(因为我们不希望背景影响覆盖)  
            bitwise_not(grayMaskSmallThresh, grayMaskSmallThreshInv);

            // 使用逐位“与”运算符精确提取面膜的边界  
            bitwise_and(faceMaskSmall, faceMaskSmall, maskedFace, grayMaskSmallThresh);

            //使用按位“AND”运算符来覆盖面罩  
            bitwise_and(frameROI, frameROI, maskedFrame, grayMaskSmallThreshInv);

            // 添加上述蒙面图像，并将其放置在原始帧ROI中，以创建最终的图像  
            if (x > 0 && y > 0 && x + w < frame.cols && y + h < frame.rows)
                add(maskedFace, maskedFrame, frame(Rect(x, y, w, h)));
            waitKey(30
            );

        }

        // Show the current frame
        imshow("Frame", frame);

        // Get the keyboard input and check if it's 'Esc'
        // 27 -> ASCII value of 'Esc' key
        auto ch = waitKey(30);
        if (ch == 27) {
            break;
        }
    }

    // Release the video capture object
    cap.release();

    // Close all windows
    destroyAllWindows();

    return 1;
}