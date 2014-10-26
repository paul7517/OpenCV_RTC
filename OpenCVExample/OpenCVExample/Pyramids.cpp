#include "opencv/cv.h"
#include "opencv/highgui.h"
using namespace cv;

//////////////////////////////////////////////////////////////////////////
// Global variables
Mat matSrc, matDst, matTemp;
int nKeyEvent;
const char* szWindowName = "Pyramids Demo";
const char* szFileName = "../chicky_512.png";

int main( void ) {
	// General instructions
	printf( "\n Zoom In-Out demo  \n " );
	printf( "------------------ \n" );
	printf( " * [u] -> Zoom in  \n" );
	printf( " * [d] -> Zoom out \n" );
	printf( " * [ESC] -> Close program \n \n" );
	
	// Test image - Make sure it s divisible by 2^{n}
	matSrc = imread( szFileName );
	if ( !matSrc.data ) {
		printf(" No data! -- Exiting the program \n");
		system("pause");
		return -1;
	}
	
	matTemp = matSrc;
	matDst = matTemp;
	
	// Create window
	namedWindow( szWindowName, WINDOW_AUTOSIZE );
	imshow( szWindowName, matDst );
	
	while (true) {		
		nKeyEvent = waitKey(10);		
		if ( (char)nKeyEvent == 27 ) { //ESC
			break;
		}
		if ( (char)nKeyEvent == 'u' ) {
			pyrUp( matTemp, matDst, Size( matTemp.cols * 2, matTemp.rows * 2 ) );
			printf( "** Zoom In: Image x 2 \n" );
		} else if ( (char)nKeyEvent == 'd' ) {
			pyrDown( matTemp, matDst, Size( matTemp.cols / 2, matTemp.rows / 2 ) );
			printf( "** Zoom Out: Image / 2 \n" );
		}
		
		imshow( szWindowName, matDst );
		matTemp = matDst;
	}	
	return 0;
}
