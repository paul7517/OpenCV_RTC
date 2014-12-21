#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace std;
using namespace cv;

//////////////////////////////////////////////////////////////////////////
// Global Variables
const char *cszFilePath = "..\\baboon.jpg";
const char *cszWindowTitle = "Morphology Transformations Demo";

// Global variables
Mat g_matSrc, g_matDst;
int nMorphElem = 0;
int nMorphSize = 0;
int nMorphOperator = 0;
int const nMaxOperator = 4;
int const nMaxElem = 2;
int const nMaxKernelSize = 21;

// Function Headers
void Morphology_Operations(int, void*);

int main(int, char** argv) {
	// Load an image
	g_matSrc = imread(cszFilePath, 1);
	if (!g_matSrc.data) {
		cerr << "The input file " << cszFilePath << " error!" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	
	// Create window
	namedWindow(cszWindowTitle, WINDOW_AUTOSIZE);
	
	// Create Trackbar to select Morphology operation
	createTrackbar("Operator:\n 0: Opening - 1: Closing  \n 2: Gradient - 3: Top Hat \n 4: Black Hat", 
		cszWindowTitle, &nMorphOperator, nMaxOperator, 
		Morphology_Operations);
	
	// Create Trackbar to select kernel type
	createTrackbar("Element:\n 0: Rect - 1: Cross - 2: Ellipse", cszWindowTitle,
					&nMorphElem, nMaxElem,
					Morphology_Operations);
					
	// Create Trackbar to choose kernel size
	createTrackbar("Kernel size:\n 2n +1", cszWindowTitle,
					&nMorphSize, nMaxKernelSize,
					Morphology_Operations);
					
	// Default start
	Morphology_Operations(0, 0);	
	waitKey(0);
	return 0;
}

void Morphology_Operations(int, void*) {
	// Since MORPH_X : 2,3,4,5 and 6
	int nOperation = nMorphOperator + 2;
	
	Mat matElement = getStructuringElement(nMorphElem, 
		Size(2 * nMorphSize + 1, 2 * nMorphSize + 1), 
		Point(nMorphSize, nMorphSize));
	
	/// Apply the specified morphology operation
	morphologyEx(g_matSrc, g_matDst, nOperation, matElement);
	imshow(cszWindowTitle, g_matDst);
}
