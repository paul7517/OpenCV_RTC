#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace std;
using namespace cv;

//////////////////////////////////////////////////////////////////////////
// Global Variables
const char *cszFilePath = "..\\lena.jpg";
const char *cszWindowTitle = "Edge Map";
Mat g_matSrc, g_matGray;
Mat g_matDst, g_matDetectedEdges;
int nEdgeThresh = 1;
int nLowThreshold;
int const cnMax_lowThreshold = 100;
int nRatio = 3;
int nKernelSize = 3;

// Canny thresholds input with a ratio 1:3
static void CannyThreshold(int, void*) {
	// Reduce noise with a kernel 3x3
	blur(g_matGray, g_matDetectedEdges, Size(3, 3));
	
	// Canny detector
	Canny(g_matDetectedEdges, g_matDetectedEdges, nLowThreshold,
		  nLowThreshold * nRatio, nKernelSize);
		  
	// Using Canny's output as a mask, we display our result
	g_matDst = Scalar::all(0);
	g_matSrc.copyTo(g_matDst, g_matDetectedEdges);
	imshow(cszWindowTitle, g_matDst);
}

int main(int, char** argv) {
	// Load an image
	g_matSrc = imread(cszFilePath, 1);
	if (!g_matSrc.data) {
		cerr << "The input file " << cszFilePath << " error!" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	
	// Create a matrix of the same type and size as src (for dst)
	g_matDst.create(g_matSrc.size(), g_matSrc.type());
	
	// Convert the image to grayscale
	cvtColor(g_matSrc, g_matGray, COLOR_BGR2GRAY);
	
	// Create a window
	namedWindow(cszWindowTitle, WINDOW_AUTOSIZE);
	
	// Create a Trackbar for user to enter threshold
	createTrackbar("Min Threshold:", cszWindowTitle, &nLowThreshold, cnMax_lowThreshold, CannyThreshold);
	
	// Show the image
	CannyThreshold(0, 0);
	
	// Wait until user exit program by pressing a key
	waitKey(0);
	return EXIT_SUCCESS;
}
