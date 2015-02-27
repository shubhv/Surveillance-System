#include "opencv\cv.h"
#include "opencv\highgui.h"
#include "opencv\ml.h"
#include "opencv\cxcore.h"



int main( int argc, char** argv ) {
cvNamedWindow( "DisplayVideo", CV_WINDOW_AUTOSIZE );
CvCapture* capture = cvCreateFileCapture( argv[1] );
IplImage* frame;
while(1) {
frame = cvQueryFrame( capture );
if( !frame ) break;
cvShowImage( "DisplayVideo", frame );
char c = cvWaitKey(33);
if( c == 27 ) break;
}
cvReleaseCapture( &capture );
cvDestroyWindow("DisplayVideo" );
}