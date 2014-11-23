#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace std;
using namespace cv;

//////////////////////////////////////////////////////////////////////////
// Global Variables
Mat g_matSrc, g_matGray, g_matDst;
const char* cszFilePath = "..\\baboon.jpg";
int nThresholdValue = 0;
int nThresholdType = 3;
int nMaxVlue = 255;
int nMaxType = 4;
int nMaxBinaryValue = 255;
const char* szWindowTitle = "Threshold Demo";
const char* szTrackbarType = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
const char* szTrackbarValue = "Value";

// Function headers
void Threshold_Demo(int, void*);

int main(int, char** argv) {	
	// Load image
	g_matSrc = imread(cszFilePath, 1);
	if (!g_matSrc.data) {
		cerr << "The input file " << cszFilePath << " error!" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	
	// Convert the image to Gray
	cvtColor(g_matSrc, g_matGray, COLOR_RGB2GRAY);
	
	// Create a window to display results
	namedWindow(szWindowTitle, WINDOW_AUTOSIZE);
	
	// Create Trackbar to choose type of Threshold
	createTrackbar(szTrackbarType,
					szWindowTitle, &nThresholdType,
					nMaxType, Threshold_Demo);
					
	createTrackbar(szTrackbarValue,
					szWindowTitle, &nThresholdValue,
					nMaxVlue, Threshold_Demo);
					
	// Call the function to initialize
	Threshold_Demo(0, 0);
	
	waitKey();
	return EXIT_SUCCESS;
}

void Threshold_Demo(int, void*) {
// 	 0: Binary
// 	 1: Binary Inverted
// 	 2: Threshold Truncated
// 	 3: Threshold to Zero
// 	 4: Threshold to Zero Inverted	 	
	threshold(g_matGray, g_matDst, nThresholdValue, nMaxBinaryValue, nThresholdType);	
	imshow(szWindowTitle, g_matDst);
}
