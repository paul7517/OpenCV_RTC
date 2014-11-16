#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat matSrcBase, matHsvBase;
	Mat matSrcTest1, matHsvTest1;
	Mat matSrcTest2, matHsvTest2;
	Mat matHsvHalfDown;
	
	// Load three images with different environment settings
	matSrcBase = imread("../hand_sample1.jpg", 1);
	matSrcTest1 = imread("../hand_sample2.jpg", 1);
	matSrcTest2 = imread("../hand_sample3.jpg", 1);
	
	// Convert to HSV
	cvtColor(matSrcBase, matHsvBase, COLOR_BGR2HSV);
	cvtColor(matSrcTest1, matHsvTest1, COLOR_BGR2HSV);
	cvtColor(matSrcTest2, matHsvTest2, COLOR_BGR2HSV);
	matHsvHalfDown = matHsvBase(Range(matHsvBase.rows / 2, matHsvBase.rows - 1), Range(0, matHsvBase.cols - 1));
	
	// Using 50 bins for hue and 60 for saturation
	int nBinsHue = 50;
	int nBinsSaturation = 60;
	int nHistSize[] = {nBinsHue, nBinsSaturation};
	
	// hue varies from 0 to 179, saturation from 0 to 255
	float flRangesHue[] = {0, 180};
	float flRangesSaturation[] = {0, 256};
	const float *flRanges[] = {flRangesHue, flRangesSaturation};
	
	// Use the 0-th and 1-st channels
	int nChannels[] = {0, 1};
	
	// Histograms
	Mat matHistBase, matHistHalfDown, matHistTest1, matHistTest2;
	bool fUniform = true;
	bool fAccumulate = false;
	
	// Calculate the histograms for the HSV images
	calcHist(&matHsvBase, 1, nChannels, Mat(), matHistBase, 2, nHistSize, flRanges, fUniform, fAccumulate);
	calcHist(&matHsvHalfDown, 1, nChannels, Mat(), matHistHalfDown, 2, nHistSize, flRanges, fUniform, fAccumulate);
	calcHist(&matHsvTest1, 1, nChannels, Mat(), matHistTest1, 2, nHistSize, flRanges, fUniform, fAccumulate);
	calcHist(&matHsvTest2, 1, nChannels, Mat(), matHistTest2, 2, nHistSize, flRanges, fUniform, fAccumulate);
	
	// Normalize the result to [ 0, 1 ]
	normalize(matHistBase, matHistBase, 0, 1, NORM_MINMAX, -1, Mat());
	normalize(matHistHalfDown, matHistHalfDown, 0, 1, NORM_MINMAX, -1, Mat());
	normalize(matHistTest1, matHistTest1, 0, 1, NORM_MINMAX, -1, Mat());
	normalize(matHistTest2, matHistTest2, 0, 1, NORM_MINMAX, -1, Mat());
	
	// Apply the histogram comparison methods
	cout << "Perfect, Base-Half, Base-Test(1), Base-Test(2)" << endl;
	for (int i = 0; i < 4; i++) {
		int nCompareMethod = i;
		double dwBaseBase = compareHist(matHistBase, matHistBase, nCompareMethod);
		double dwBaseHalf = compareHist(matHistBase, matHistHalfDown, nCompareMethod);
		double dwBaseTest1 = compareHist(matHistBase, matHistTest1, nCompareMethod);
		double dwBaseTest2 = compareHist(matHistBase, matHistTest2, nCompareMethod);
		
		cout << "\n === Method [" << i << "] ===" << endl;
		cout << dwBaseBase << " \t "
			 << dwBaseHalf << " \t "
			 << dwBaseTest1 << " \t "
			 << dwBaseTest2 << endl;
	}	
	system("pause");
	return 0;
}
