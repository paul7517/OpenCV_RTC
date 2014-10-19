#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>
using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	double dwAlpha = 0.5;
	double dwBeta;
	double dwInput;
	
	Mat matSrc1, matSrc2, matDst;
	
	// Ask the user enter alpha
	cout << " Simple Linear Blender " << endl;
	cout << "-----------------------" << endl;
	cout << "* Enter alpha [0-1]: ";
	cin >> dwInput;
	
	// We use the alpha provided by the user if it is between 0 and 1
	if (dwInput >= 0.0 && dwInput <= 1.0) {
		dwAlpha = dwInput;
	}
	
	// Read image ( same size, same type )
	matSrc1 = imread("../LinuxLogo.jpg");
	matSrc2 = imread("../WindowsLogo.jpg");
	
	if (!matSrc1.data) {
		printf("Error loading src1 \n");
		return -1;
	}
	if (!matSrc2.data) {
		printf("Error loading src2 \n");
		return -1;
	}
	
	// Create Windows
	namedWindow("Linear Blend", 1);
	
	dwBeta = (1.0 - dwAlpha);
	addWeighted(matSrc1, dwAlpha, matSrc2, dwBeta, 0.0, matDst);
	
	imshow("Linear Blend", matDst);
	
	waitKey(0);
	return 0;
}