#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace std;
using namespace cv;

//////////////////////////////////////////////////////////////////////////
// Global Variables
Mat g_matSrc, g_matDst;
const char* cszFilePath = "..\\baboon.jpg";

int main(int, char** argv) {
	// Load image
	g_matSrc = imread(cszFilePath, 1);
	if (!g_matSrc.data) {
		cerr << "The input file " << cszFilePath << " error!" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	
	// Separate the image in 3 places (B, G and R)
	vector<Mat> vBGRPlanes;
	split(g_matSrc, vBGRPlanes);
	
	// Establish the number of bins
	int nHistSize = 256;
	
	// Set the ranges (for B,G,R))
	float flRange[] = {0, 256};
	const float *cflHistRange = {flRange};
	
	bool fUniform = true;
	bool fAccumulate = false;
	Mat matHistB, matHistG, matHistR;
	
	// Compute the histograms:
	calcHist(&vBGRPlanes[0], 1, 0, Mat(), matHistB, 1, &nHistSize, &cflHistRange, fUniform, fAccumulate);
	calcHist(&vBGRPlanes[1], 1, 0, Mat(), matHistG, 1, &nHistSize, &cflHistRange, fUniform, fAccumulate);
	calcHist(&vBGRPlanes[2], 1, 0, Mat(), matHistR, 1, &nHistSize, &cflHistRange, fUniform, fAccumulate);
	
	//////////////////////////////////////////////////////////////////////////
	// Draw the histograms for B, G and R
	int nHistWidth = 512;
	int nHistHeight = 400;
	int nBinWidth = cvRound((double) nHistWidth / nHistSize);
	
	Mat matHistImage(nHistHeight, nHistWidth, CV_8UC3, Scalar(0, 0, 0));
	
	// Normalize the result to [ 0, matHistImage.rows ]
	normalize(matHistB, matHistB, 0, matHistImage.rows, NORM_MINMAX, -1, Mat());
	normalize(matHistG, matHistG, 0, matHistImage.rows, NORM_MINMAX, -1, Mat());
	normalize(matHistR, matHistR, 0, matHistImage.rows, NORM_MINMAX, -1, Mat());
	
	// Draw for each channel
	for (int i = 1; i < nHistSize; i++) {
		line(matHistImage, Point(nBinWidth * (i - 1), nHistHeight - cvRound(matHistB.at<float>(i - 1))) ,
			 Point(nBinWidth * (i), nHistHeight - cvRound(matHistB.at<float>(i))),
			 Scalar(255, 0, 0), 2, 8, 0 );
		line(matHistImage, Point(nBinWidth * (i - 1), nHistHeight - cvRound(matHistG.at<float>(i - 1))) ,
			 Point(nBinWidth * (i), nHistHeight - cvRound(matHistG.at<float>(i))),
			 Scalar(0, 255, 0), 2, 8, 0 );
		line(matHistImage, Point(nBinWidth * (i - 1), nHistHeight - cvRound(matHistR.at<float>(i - 1))) ,
			 Point(nBinWidth * (i), nHistHeight - cvRound(matHistR.at<float>(i))),
			 Scalar(0, 0, 255), 2, 8, 0 );
	}
	
	// Display
	namedWindow("calcHist Demo", WINDOW_AUTOSIZE);
	imshow("calcHist Demo", matHistImage);
	waitKey(0);
	return 0;
}
