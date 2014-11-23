#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace std;
using namespace cv;

//////////////////////////////////////////////////////////////////////////
// Global Variables
Mat g_matSrc, g_matGray, g_matDst;
const char* cszFilePath = "..\\baboon.jpg";

int main(int, char** argv) {
	const char* szSourceWindow = "Source Image";
	const char* szEqualizedWindow = "Equalized Image";
	
	// Load image
	g_matSrc = imread(cszFilePath, 1);
	if (!g_matSrc.data) {
		cerr << "The input file " << cszFilePath << " error!" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	
	// Convert to grayscale
	cvtColor(g_matSrc, g_matGray, COLOR_BGR2GRAY);
	
	// Apply Histogram Equalization
	equalizeHist(g_matGray, g_matDst);
	
	// Display results
	namedWindow(szSourceWindow, WINDOW_AUTOSIZE);
	namedWindow(szEqualizedWindow, WINDOW_AUTOSIZE);
	imshow(szSourceWindow, g_matGray);
	imshow(szEqualizedWindow, g_matDst);

	Mat matNor;
	normalize(g_matGray, matNor, 0, 255, NORM_MINMAX, -1, Mat());
	namedWindow("Normal Image", WINDOW_AUTOSIZE);
	imshow("Normal Image", matNor);
		
	//////////////////////////////////////////////////////////////////////////
	// Establish the number of bins
	int nHistSize = 256;
	
	// Set the ranges
	float flRange[] = {0, 256};
	const float *cflHistRange = { flRange };
	
	bool fUniform = true;
	bool fAccumulate = false;
	Mat matHistGray, matHistDst;
	
	// Compute the histograms:
	calcHist(&g_matGray, 1, 0, Mat(), matHistGray, 1, &nHistSize, &cflHistRange, fUniform, fAccumulate);
	calcHist(&g_matDst, 1, 0, Mat(), matHistDst, 1, &nHistSize, &cflHistRange, fUniform, fAccumulate);
	
	// Draw the histograms
	int nHistWidth = 512;
	int nHistHeight = 400;
	int nBinWidth = cvRound((double)nHistWidth / nHistSize);
	Mat matHistImage(nHistHeight, nHistWidth, CV_8UC3, Scalar(0, 0, 0));
	
	// Normalize the result to [ 0, matHistImage.rows ]
	normalize(matHistGray, matHistGray, 0, matHistImage.rows, NORM_MINMAX, -1, Mat());
	normalize(matHistDst, matHistDst, 0, matHistImage.rows, NORM_MINMAX, -1, Mat());
	
	// Draw for each channel
	for (int i = 1; i < nHistSize; i++) {
		line(matHistImage, Point(nBinWidth * (i - 1), nHistHeight - cvRound(matHistGray.at<float>(i - 1))),
			 Point(nBinWidth * (i), nHistHeight - cvRound(matHistGray.at<float>(i))),
			 Scalar(0, 0, 255), 2, 8, 0);
			 
		line(matHistImage, Point(nBinWidth * (i - 1), nHistHeight - cvRound(matHistDst.at<float>(i - 1))),
			 Point(nBinWidth * (i), nHistHeight - cvRound(matHistDst.at<float>(i))),
			 Scalar(0, 255, 0), 1, 8, 0);
	}
	// Display
	namedWindow("EqualHist Demo", WINDOW_AUTOSIZE);
	imshow("EqualHist Demo", matHistImage);
	
	// Wait until user exits the program
	waitKey(0);
	return EXIT_SUCCESS;
}
