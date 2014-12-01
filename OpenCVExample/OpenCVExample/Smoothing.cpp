#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace std;
using namespace cv;

//////////////////////////////////////////////////////////////////////////
// Global Variables
const char *cszFilePath = "..\\lena.jpg";
char *cszWindowTitle = "Smoothing Demo";
int DELAY_CAPTION = 1500;
int DELAY_BLUR = 100;
int MAX_KERNEL_LENGTH = 31;
Mat g_matSrc, g_matDst;

// Function headers
int displayCaption(const char* caption);
int displayDst(int delay);

int main(void) {
	namedWindow(cszWindowTitle, WINDOW_AUTOSIZE);
	
	#pragma region Load the source image
	g_matSrc = imread(cszFilePath, CV_LOAD_IMAGE_COLOR);
	if (!g_matSrc.data) {
		cerr << "The input file " << cszFilePath << " error!" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	
	if (displayCaption("Original Image") != 0) { return 0; }
	
	g_matDst = g_matSrc.clone();
	if (displayDst(DELAY_CAPTION) != 0) {
		return 0;
	}
	#pragma endregion
	
	#pragma region Applying Homogeneous blur
	if (displayCaption("Homogeneous Blur") != 0) { return 0; }
	
	for (int i = 1; i < MAX_KERNEL_LENGTH; i += 2) {
		blur(g_matSrc, g_matDst, Size(i, i), Point(-1, -1));
		if (displayDst(DELAY_BLUR) != 0) {
			return 0;
		}
	}
	#pragma endregion
	
	#pragma region Applying Gaussian blur
	if (displayCaption("Gaussian Blur") != 0) { return 0; }
	
	for (int i = 1; i < MAX_KERNEL_LENGTH; i += 2) {
		GaussianBlur(g_matSrc, g_matDst, Size(i, i), 0, 0);
		if (displayDst(DELAY_BLUR) != 0) {
			return 0;
		}
	}
	#pragma endregion
	
	#pragma region Applying Median blur
	if (displayCaption("Median Blur") != 0) { return 0; }
	
	for (int i = 1; i < MAX_KERNEL_LENGTH; i += 2) {
		medianBlur(g_matSrc, g_matDst, i);
		if (displayDst(DELAY_BLUR) != 0) {
			return 0;
		}
	}
	#pragma endregion
	
	#pragma region Applying Bilateral Filter
	if (displayCaption("Bilateral Blur") != 0) { return 0; }
	
	for (int i = 1; i < MAX_KERNEL_LENGTH; i += 2) {
		bilateralFilter(g_matSrc, g_matDst, i, i * 2, i / 2);
		if (displayDst(DELAY_BLUR) != 0) {
			return 0;
		}
	}
	#pragma endregion
	
	// Wait until user press a key
	displayCaption("End: Press a key!");
	waitKey(0);
	return 0;
}

int displayCaption(const char *cszCaption) {
	g_matDst = Mat::zeros(g_matSrc.size(), g_matSrc.type());
	putText(g_matDst, cszCaption,
			Point(g_matSrc.cols / 4, g_matSrc.rows / 2),
			FONT_HERSHEY_DUPLEX, 1, Scalar(255, 255, 255));
			
	imshow(cszWindowTitle, g_matDst);
	int nKeyEvent = waitKey(DELAY_CAPTION);
	if (nKeyEvent >= 0) {
		return -1;
	}
	return 0;
}

int displayDst(int nDelay) {
	imshow(cszWindowTitle, g_matDst);
	int nKeyEvent = waitKey(nDelay);
	if (nKeyEvent >= 0) {
		return -1;
	}
	return 0;
}
