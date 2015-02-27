#include <math.h>
#include <string.h>
#include <cv.h>
#include <highgui.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/video/tracking.hpp>

using namespace cv;
using namespace std;

IplImage *img1, img1_temp;
CvPoint point;

Mat frame;
int drag = 0;
int *x_point[10],*width_point[10],*y_point[10],*height_point[10];
// CvCapture *capture = 0;
int key = 0;
CvRect rect;
Rect region_of_interest;
int test;
Mat src,src_gray,image,src_gray_prev,src1,src_gray1,copy,copy1,frames,copy2;
int maxCorners = 23;
RNG rng(12345);
vector<Point2f> corners,corners_prev,corners_temp;
double qualityLevel = 0.01;
double minDistance = 10;
int blockSize = 3;
bool useHarrisDetector = false;
double k = 0.04;
vector<uchar> status;
vector<float> err;
float x_cord[100];
float y_cord[100];
int size = 0;
void mouseHandler(int event, int x, int y, int flags, void* param)
{
    if (event == CV_EVENT_LBUTTONDOWN && !drag)
    {
        point = cvPoint(x, y);
        drag = 1;
    }
    
    if (event == CV_EVENT_MOUSEMOVE && drag)
    {
        img1_temp = frame;
        img1 = &img1_temp;
        cvRectangle(img1,point,cvPoint(x, y),CV_RGB(255, 0, 0),1,8,0);
        cvShowImage("result", img1);
    }
    
    if (event == CV_EVENT_LBUTTONUP && drag)
    {
        rect = cvRect(point.x,point.y,x-point.x,y-point.y);
		if(size<=9){
            x_point[size] = new int(point.x);
    		
            y_point[size] = new int(point.y);
    		width_point[size] = new int(x-point.x);
    		height_point[size] = new int(y-point.y);
            // cvShowImage("result", frame);
            size++;
        }
        imshow("result", frame);  

        drag = 0;
    }

    
    if (event == CV_EVENT_RBUTTONUP)
    {
        drag = 0;
    }
}

int main(int argc, char *argv[])
{
    VideoCapture capture("../dataset/sample3.dav");   //0 is the id of video device.0 if you have only one camera     
    cvNamedWindow( "result", CV_WINDOW_NORMAL );
	while( key != 'q' )
    {
        if(!capture.read(frame))
            break;
        if (rect.width>0)
		{	    int i;
                for( i=0; i<size; i++){
                    rectangle(frame, Point(*x_point[i], *y_point[i]), Point(*x_point[i] + *width_point[i], *y_point[i] + *height_point[i]), Scalar(0, 0, 0), -1);
                }
				
				
				IplImage test1 = frame;
			  	IplImage* test2 = &test1;
			    cvShowImage("result", test2);
    	}        

        cvSetMouseCallback("result", mouseHandler, NULL);
        key = cvWaitKey(10);
        imshow("result", frame);

    }
    cvDestroyWindow("result");
    cvReleaseImage(&img1);
    return 0;
}
