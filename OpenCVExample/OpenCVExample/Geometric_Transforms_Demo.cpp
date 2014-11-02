#include "opencv/highgui.h"
#include "opencv/cv.h"
#include <iostream>
using namespace cv;
using namespace std;

// Global variables
const char *szWindowSource = "Source image";
const char* szWindowWarp = "Warp";
const char* WindowWarpRotate = "Warp + Rotate";
const char *szFilePath = "../lena.jpg";

int main(int, char** argv) {
	Point2f srcTri[3];
	Point2f dstTri[3];	
	Mat matRot(2, 3, CV_32FC1);
	Mat matWarp(2, 3, CV_32FC1);
	Mat matSrc, matWarpDst, matWarpRotateDst;
	
	// Load the image
	matSrc = imread(szFilePath, 1);
	if (!matSrc.data) {
		cout << "The image" << szFilePath << " could not be loaded." << endl;
		system("pause");
		return -1;
	}

	// Set the dst image the same type and size as src
	matWarpDst = Mat::zeros(matSrc.rows, matSrc.cols, matSrc.type());
	
	// Set your 3 points to calculate the  Affine Transform
	srcTri[0] = Point2f(0, 0);
	srcTri[1] = Point2f(matSrc.cols - 1.f, 0);
	srcTri[2] = Point2f(0, matSrc.rows - 1.f);
	
	dstTri[0] = Point2f(matSrc.cols * 0.0f, matSrc.rows * 0.33f);
	dstTri[1] = Point2f(matSrc.cols * 0.85f, matSrc.rows * 0.25f);
	dstTri[2] = Point2f(matSrc.cols * 0.15f, matSrc.rows * 0.7f);
	
	// Get the Affine Transform
	matWarp = getAffineTransform(srcTri, dstTri);
	
	// Apply the Affine Transform just found to the src image
	warpAffine(matSrc, matWarpDst, matWarp, matWarpDst.size());
	
	//////////////////////////////////////////////////////////////////////////	
	// Rotating the image after Warp
	
	// Compute a rotation matrix with respect to the center of the image
	Point center = Point(matWarpDst.cols / 2, matWarpDst.rows / 2);
	double angle = -50.0;
	double scale = 0.6;
	
	// Get the rotation matrix with the specifications above
	matRot = getRotationMatrix2D(center, angle, scale);
	
	// Rotate the warped image
	warpAffine(matWarpDst, matWarpRotateDst, matRot, matWarpDst.size());
		
	// Show what you got
	namedWindow(szWindowSource, WINDOW_AUTOSIZE);
	imshow(szWindowSource, matSrc);
	
	namedWindow(szWindowWarp, WINDOW_AUTOSIZE);
	imshow(szWindowWarp, matWarpDst);
	
	namedWindow(WindowWarpRotate, WINDOW_AUTOSIZE);
	imshow(WindowWarpRotate, matWarpRotateDst);
	
	// Wait until user exits the program
	waitKey(0);	
	return 0;
}
