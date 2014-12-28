#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace std;
using namespace cv;

//////////////////////////////////////////////////////////////////////////
// Global Variables
const char *cszFilePath = "..\\woah.png";
Mat g_matSrc, g_matGray;

// windows and trackbars name
const char *cszWindowName = "Hough Circle Detection Demo";
const char *cszCannyThresholdTrackbarName = "Canny threshold";
const char *cszAccumulatorThresholdTrackbarName = "Accumulator Threshold";

// initial and max values of the parameters of interests.
const int cannyThresholdInitialValue = 200;
const int accumulatorThresholdInitialValue = 50;
const int maxAccumulatorThreshold = 200;
const int maxCannyThreshold = 255;

void HoughDetection(const Mat &matGray, const Mat &matSrc,
					int nCannyThreshold, int nAccumulatorThreshold) {
	// will hold the results of the detection
	vector<Vec3f> vCircles;
	// runs the actual detection
	HoughCircles(matGray, vCircles, CV_HOUGH_GRADIENT, 1, matGray.rows / 8,
				 nCannyThreshold, nAccumulatorThreshold, 0, 0);
				 
	// clone the colour, input image for displaying purposes
	Mat matDst = matSrc.clone();
	for (size_t i = 0; i < vCircles.size(); i++) {
		Point center(cvRound(vCircles[i][0]), cvRound(vCircles[i][1]));
		int radius = cvRound(vCircles[i][2]);
		// circle center
		circle(matDst, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		// circle outline
		circle(matDst, center, radius, Scalar(0, 0, 255), 3, 8, 0);
	}
	
	// shows the results
	imshow(cszWindowName, matDst);
}


int main(int argc, char** argv) {
	// Load an image
	g_matSrc = imread(cszFilePath, 1);
	if (!g_matSrc.data) {
		cerr << "The input file " << cszFilePath << " error!" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	
	// Convert it to gray
	cvtColor(g_matSrc, g_matGray, COLOR_BGR2GRAY);
	
	// Reduce the noise so we avoid false circle detection
	GaussianBlur(g_matGray, g_matGray, Size(9, 9), 2, 2);
	
	//declare and initialize both parameters that are subjects to change
	int nCannyThreshold = cannyThresholdInitialValue;
	int nAccumulatorThreshold = accumulatorThresholdInitialValue;
	
	// create the main window, and attach the trackbars
	namedWindow(cszWindowName, WINDOW_AUTOSIZE);
	createTrackbar(cszCannyThresholdTrackbarName, cszWindowName,
				   &nCannyThreshold, maxCannyThreshold);
	createTrackbar(cszAccumulatorThresholdTrackbarName, cszWindowName,
				   &nAccumulatorThreshold, maxAccumulatorThreshold);
				   
	// infinite loop to display
	// and refresh the content of the output image
	// until the user presses q or Q
	int nKey = 0;
	while (nKey != 'q' && nKey != 'Q') {
		// those paramaters cannot be =0
		// so we must check here
		nCannyThreshold = max(nCannyThreshold, 1);
		nAccumulatorThreshold = max(nAccumulatorThreshold, 1);
		
		//runs the detection, and update the display
		HoughDetection(g_matGray, g_matSrc, nCannyThreshold, nAccumulatorThreshold);
		
		// get user key
		nKey = waitKey(10);
	}
	return 0;
}
