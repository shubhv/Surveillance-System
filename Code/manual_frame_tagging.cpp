#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/ml.h>
#include <opencv/cxcore.h>  

// #include <cv.h>
// #include <opencv2/opencv.hpp> 
// #include <opencv2/highgui/highgui.hpp>
#include <fstream>

using namespace std;

int main( int argc, char** argv ) {
ofstream myfile;
int frameno = 0;
myfile.open ( argv[2] );
cvNamedWindow( "DisplayVideo", CV_WINDOW_NORMAL );
CvCapture* capture = cvCreateFileCapture( argv[1] );
IplImage* frame;
while(1) {
frame = cvQueryFrame( capture );
if( !frame ) break;
cvShowImage( "DisplayVideo", frame );
char c = cvWaitKey(0);
if( c == 27 ){
   myfile.close();
 break;
}
if(c == 'f' || c == 'b')
	frameno++;
	myfile<<c<<"\t"<<frameno<<endl;
 
}
cvReleaseCapture( &capture );
cvDestroyWindow("DisplayVideo" );
}