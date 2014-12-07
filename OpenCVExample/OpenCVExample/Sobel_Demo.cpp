#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace std;
using namespace cv;

//////////////////////////////////////////////////////////////////////////
// Global Variables
const char *cszFilePath = "..\\lena.jpg";
const char *cszWindowTitle = "Source Image";
const char *cszWindowTitleSobel = "Sobel Demo - Simple Edge Detector";
const char *cszWindowTitleScharr = "Scharr Demo - Simple Edge Detector";

int main( int, char** argv) {
	Mat matSrc, matGray, matGrad;	
	int nScale = 1;
	int nDelta = 0;
	int nDepth = CV_16S;
	// Create window	
	namedWindow(cszWindowTitle, WINDOW_AUTOSIZE);
	namedWindow(cszWindowTitleSobel, WINDOW_AUTOSIZE);
	namedWindow(cszWindowTitleScharr, WINDOW_AUTOSIZE);

	// Load an image
	matSrc = imread(cszFilePath, 1);	
	if(!matSrc.data) {
		cerr << "The input file " << cszFilePath << " error!" << endl;
		system("pause");
		return EXIT_FAILURE;
	}	
	imshow(cszWindowTitle, matSrc);

	// Blur the image
	GaussianBlur(matSrc, matSrc, Size(3, 3), 0, 0, BORDER_DEFAULT);	
	// Convert it to gray
	cvtColor(matSrc, matGray, COLOR_RGB2GRAY);		
	
	// Generate matGradX and matGradY
	Mat matGradX, matGradY;
	Mat matGradXAbs, matGradYAbs;
	
	//////////////////////////////////////////////////////////////////////////	
	// Calculate Sobel - Gradient X, Gradient Y
	Sobel(matGray, matGradX, nDepth, 1, 0, 3, nScale, nDelta, BORDER_DEFAULT);
	convertScaleAbs(matGradX, matGradXAbs);
	Sobel(matGray, matGradY, nDepth, 0, 1, 3, nScale, nDelta, BORDER_DEFAULT);	
	convertScaleAbs(matGradY, matGradYAbs);
	// Total Gradient(approximate)
	addWeighted(matGradXAbs, 0.5, matGradYAbs, 0.5, 0, matGrad);
	imshow(cszWindowTitleSobel, matGrad);

	//////////////////////////////////////////////////////////////////////////	
	// Calculate Scharr - Gradient X, Gradient Y
	Scharr(matGray, matGradX, nDepth, 1, 0, nScale, nDelta, BORDER_DEFAULT);
	convertScaleAbs(matGradX, matGradXAbs);
	Scharr(matGray, matGradY, nDepth, 0, 1, nScale, nDelta, BORDER_DEFAULT);
	convertScaleAbs(matGradY, matGradYAbs);
	// Total Gradient(approximate)
	addWeighted(matGradXAbs, 0.5, matGradYAbs, 0.5, 0, matGrad);	
	imshow(cszWindowTitleScharr, matGrad);

	waitKey(0);	
	return 0;
}
