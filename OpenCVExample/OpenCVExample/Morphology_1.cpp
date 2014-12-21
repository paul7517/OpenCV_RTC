#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace std;
using namespace cv;

//////////////////////////////////////////////////////////////////////////
// Global Variables
const char *cszFilePath = "..\\lena.jpg";
const char *cszWindowTitle = "Dilation & Erosion";
Mat g_matSrc, g_matErosionDst, g_matDilationDst;
int nErosionElem = 0;
int nErosionSize = 0;
int nDilationElem = 0;
int nDilationSize = 0;
int const nMaxElem = 2;
int const nMaxKernelSize = 21;

// Function Headers
void Erosion(int, void*);
void Dilation(int, void*);

int main(int, char** argv) {
	// Load an image
	g_matSrc = imread(cszFilePath, 1);
	if (!g_matSrc.data) {
		cerr << "The input file " << cszFilePath << " error!" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	
	// Create windows
	namedWindow("Erosion Demo", WINDOW_AUTOSIZE);
	namedWindow("Dilation Demo", WINDOW_AUTOSIZE);
	moveWindow("Dilation Demo", g_matSrc.cols, 0);
	
	//////////////////////////////////////////////////////////////////////////
	// Create Erosion Trackbar
	createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erosion Demo",
					&nErosionElem, nMaxElem, 
					Erosion);
					
	createTrackbar("Kernel size:\n 2n +1", "Erosion Demo",
					&nErosionSize, nMaxKernelSize,
					Erosion);
					
	//////////////////////////////////////////////////////////////////////////
	// Create Dilation Trackbar
	createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Dilation Demo",
					&nDilationElem, nMaxElem,
					Dilation);
					
	createTrackbar("Kernel size:\n 2n +1", "Dilation Demo",
					&nDilationSize, nMaxKernelSize,
					Dilation);
					
	//////////////////////////////////////////////////////////////////////////
	// Default start
	Erosion(0, 0);
	Dilation(0, 0);	
	waitKey(0);
	return 0;
}

void Erosion(int, void*) {
	int nErosionType = 0;
	if (nErosionElem == 0) {
		nErosionType = MORPH_RECT;
	} else if (nErosionElem == 1) {
		nErosionType = MORPH_CROSS;
	} else if (nErosionElem == 2) {
		nErosionType = MORPH_ELLIPSE;
	}
	
	Mat matElement = getStructuringElement(nErosionType,
										 Size(2 * nErosionSize + 1, 2 * nErosionSize + 1),
										 Point(nErosionSize, nErosionSize));
	// Apply the erosion operation
	erode(g_matSrc, g_matErosionDst, matElement);
	imshow("Erosion Demo", g_matErosionDst);
}

void Dilation(int, void*) {
	int nDilationType = 0;
	if (nDilationElem == 0) {
		nDilationType = MORPH_RECT;
	} else if (nDilationElem == 1) {
		nDilationType = MORPH_CROSS;
	} else if (nDilationElem == 2) {
		nDilationType = MORPH_ELLIPSE;
	}
	
	Mat matElement = getStructuringElement(nDilationType,
										 Size(2 * nDilationSize + 1, 2 * nDilationSize + 1),
										 Point(nDilationSize, nDilationSize));
	// Apply the dilation operation
	dilate(g_matSrc, g_matDilationDst, matElement);
	imshow("Dilation Demo", g_matDilationDst);
}
