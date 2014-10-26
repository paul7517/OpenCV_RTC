#include <opencv/cv.h>
#include <opencv/highgui.h>
using namespace std;
using namespace cv;

//////////////////////////////////////////////////////////////////////////
// Global Variables
const int cnAlphaSliderMax = 100;
int nAlphaSlider = 0; // Initialize values
double dwAlpha;
double dwBeta;
char *szTrackbarName = "Alpha:";
char *szWindowName = "Linear Blend";

// Matrices to store images
Mat matSrc1, matSrc2, matDst;
//////////////////////////////////////////////////////////////////////////

void on_trackbar(int, void*) {
	dwAlpha = (double)nAlphaSlider / cnAlphaSliderMax;
	dwBeta = (1.0 - dwAlpha);
	
	addWeighted(matSrc1, dwAlpha, matSrc2, dwBeta, 0.0, matDst);
	
	imshow(szWindowName, matDst);
}

int main(int argc, char** argv) {
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
	namedWindow(szWindowName, 1);
	
	// Create Trackbars	
	createTrackbar(szTrackbarName, szWindowName, &nAlphaSlider, cnAlphaSliderMax, on_trackbar);
	
	// Show some stuff
	on_trackbar(nAlphaSlider, 0);
	
	// Wait until user press some key
	waitKey(0);
	return 0;
}