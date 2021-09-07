
#include "stdio.h"
#include<iostream> 
#include <opencv2/core.hpp> 
#include <opencv2/highgui.hpp> 
using namespace cv;
int main()
{
    Mat img = imread("1.PNG");
    namedWindow("测试opencv");
    imshow("测试opencv", img);

    imwrite("save.jpg", img);
    cvWaitKey(6000);
}

