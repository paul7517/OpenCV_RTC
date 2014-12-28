#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace std;
using namespace cv;

//////////////////////////////////////////////////////////////////////////
// Global Variables
const char *cszFilePath = "..\\building.jpg";
Mat g_matSrc, g_matEdges;
Mat g_matGray;
Mat matStandardHough, matProbabilisticHough;
int nMinThreshold = 50;
int nMaxTrackbar = 150;
const char *cszStandardTitle = "Standard Hough Lines Demo";
const char *cszProbabilisticTitle = "Probabilistic Hough Lines Demo";
int nTrackbarS = nMaxTrackbar;
int nTrackbarP = nMaxTrackbar;

// Function Headers
void Standard_Hough(int, void*);
void Probabilistic_Hough(int, void*);

int main(int, char** argv) {
	// Load an image
	g_matSrc = imread(cszFilePath, 1);
	if (!g_matSrc.data) {
		cerr << "The input file " << cszFilePath << " error!" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	
	// Pass the image to gray
	cvtColor(g_matSrc, g_matGray, COLOR_RGB2GRAY);
	
	// Apply Canny edge detector
	Canny(g_matGray, g_matEdges, 50, 200, 3);
	
	// Create Trackbars for Thresholds
	char szThreshLabel[50];
	sprintf(szThreshLabel, "Thres: %d + input", nMinThreshold);
	
	namedWindow(cszStandardTitle, WINDOW_AUTOSIZE);
	createTrackbar(szThreshLabel, cszStandardTitle, &nTrackbarS, nMaxTrackbar, Standard_Hough);
	
	namedWindow(cszProbabilisticTitle, WINDOW_AUTOSIZE);
	createTrackbar(szThreshLabel, cszProbabilisticTitle, &nTrackbarP, nMaxTrackbar, Probabilistic_Hough);
	
	// Initialize
	Standard_Hough(0, 0);
	Probabilistic_Hough(0, 0);
	waitKey(0);
	return 0;
}


void Standard_Hough(int, void*) {
	vector<Vec2f> vSLines;
	g_matSrc.copyTo(matStandardHough);
	
	// 1. Use Standard Hough Transform
	HoughLines(g_matEdges, vSLines, 1, CV_PI / 180, nMinThreshold + nTrackbarS, 0, 0);
	
	// Show the result
	for (size_t i = 0; i < vSLines.size(); i++) {
		float r = vSLines[i][0], t = vSLines[i][1];
		double cos_t = cos(t), sin_t = sin(t);
		double x0 = r * cos_t, y0 = r * sin_t;
		double alpha = 1000;
		
		Point pt1(cvRound(x0 + alpha * (-sin_t)), cvRound(y0 + alpha * cos_t));
		Point pt2(cvRound(x0 - alpha * (-sin_t)), cvRound(y0 - alpha * cos_t));
		line(matStandardHough, pt1, pt2,
			 Scalar(0, 255, 0), 1, CV_AA); // CV_AA: antialiased line
	}
	imshow(cszStandardTitle, matStandardHough);
}

void Probabilistic_Hough(int, void*) {
	vector<Vec4i> vPLines;
	g_matSrc.copyTo(matProbabilisticHough);
	
	// 2. Use Probabilistic Hough Transform
	HoughLinesP(g_matEdges, vPLines, 1, CV_PI / 180, nMinThreshold + nTrackbarP, 30, 10);
	
	// Show the result
	for (size_t i = 0; i < vPLines.size(); i++) {
		line(matProbabilisticHough,
			 Point(vPLines[i][0], vPLines[i][1]), Point(vPLines[i][2], vPLines[i][3]),
			 Scalar(0, 255, 0), 1, CV_AA);
	}
	imshow(cszProbabilisticTitle, matProbabilisticHough);
}
