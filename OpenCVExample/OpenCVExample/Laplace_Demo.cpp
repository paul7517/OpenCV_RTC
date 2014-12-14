#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace std;
using namespace cv;

//////////////////////////////////////////////////////////////////////////
// Global Variables
const char *cszFilePath = "..\\lena.jpg";
const char *cszWindowTitle = "Source Image";
const char *cszWindowTitleCanny = "Laplace Demo - Simple Edge Detector";

int main(int, char** argv) {
	Mat matSrc, matGray, matDst;
	int nKernelSize = 3;
	int nScale = 1;
	int nDelta = 0;
	int nDstDepth = CV_16S;
	
	// Load an image
	matSrc = imread(cszFilePath, 1);
	if (!matSrc.data) {
		cerr << "The input file " << cszFilePath << " error!" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	namedWindow(cszWindowTitle, WINDOW_AUTOSIZE);
	imshow(cszWindowTitle, matSrc);
	
	// Remove noise by blurring with a Gaussian filter
	GaussianBlur(matSrc, matSrc, Size(3, 3), 0, 0, BORDER_DEFAULT);	
	// Convert the image to grayscale
	cvtColor(matSrc, matGray, COLOR_RGB2GRAY);	
	
	// Apply Laplace function
	Mat matDstAbs;	
	Laplacian(matGray, matDst, nDstDepth, nKernelSize, nScale, nDelta, BORDER_DEFAULT);
	convertScaleAbs(matDst, matDstAbs);
	
	// Show what you got
	namedWindow(cszWindowTitleCanny, WINDOW_AUTOSIZE);
	imshow(cszWindowTitleCanny, matDstAbs);	
	waitKey(0);	
	return EXIT_SUCCESS;
}
