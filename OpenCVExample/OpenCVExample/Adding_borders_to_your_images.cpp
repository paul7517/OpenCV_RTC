#include "opencv/cv.h"
#include "opencv/highgui.h"
#include <iostream>
using namespace std;
using namespace cv;

//////////////////////////////////////////////////
// Global Variables
Mat matImageSrc, matImageDst;
int nTop, nBottom, nLeft, nRight;
int nBorderType;
Scalar value;
char* szWindowName = "copyMakeBorder Demo";
RNG rng; // random number generator
int nKeyEvent;
float flBoardRatio = 0.05;
char *szFilePath = "../lena.jpg";

int main(int argc, char** argv) {	
	// Load an image
	matImageSrc = imread(szFilePath);
	
	if (!matImageSrc.data) {
		cout << "The image" << szFilePath << " could not be loaded." << endl;
		system("pause");
		return -1;
	}
	
	// Brief how-to for this program
	printf("\n \t copyMakeBorder Demo: \n");
	printf("\t -------------------- \n");
	printf(" ** Press 'c' to set the border to a random constant value \n");
	printf(" ** Press 'r' to set the border to be replicated \n");
	printf(" ** Press 'ESC' to exit the program \n");
	
	// Create window
	namedWindow(szWindowName, CV_WINDOW_AUTOSIZE);
	
	// Initialize arguments for the filter
	nTop = (int)(flBoardRatio * matImageSrc.rows);
	nBottom = (int)(flBoardRatio * matImageSrc.rows);
	nLeft = (int)(flBoardRatio * matImageSrc.cols);
	nRight = (int)(flBoardRatio * matImageSrc.cols);
	matImageDst = matImageSrc;
	
	imshow(szWindowName, matImageDst);	
	while (true) {
		nKeyEvent = waitKey(500);		
		if ((char)nKeyEvent == 27) { // ESC
			break;
		} else if ((char)nKeyEvent == 'c') {
			nBorderType = BORDER_CONSTANT;
		} else if ((char)nKeyEvent == 'r') {
			nBorderType = BORDER_REPLICATE;
		}		
		value = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		copyMakeBorder(matImageSrc, matImageDst, nTop, nBottom, nLeft, nRight, nBorderType, value);
		imshow(szWindowName, matImageDst);
	}
	return 0;
}