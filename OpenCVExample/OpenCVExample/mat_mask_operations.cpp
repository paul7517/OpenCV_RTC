#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;

//////////////////////////////////////////////////////////////////////////
// Global Variables
const char *cszFilePath = "..\\baboon.jpg";
const char *cszWindowsTitleSrc = "Input";
const char *cszWindowsTitleDst = "filter2D";
double dwT = 0;

int main( int argc, char* argv[]) {
	Mat matSrc, matDst;
	matSrc = imread(cszFilePath, CV_LOAD_IMAGE_COLOR);
	if (!matSrc.data) {
		cerr << "The input file " << cszFilePath << " error!" << endl;
		system("pause");
		return EXIT_FAILURE;
	}	
	namedWindow(cszWindowsTitleSrc, WINDOW_AUTOSIZE);
	imshow(cszWindowsTitleSrc, matSrc);	
	
	Mat matKernel = (Mat_<char>(3, 3) <<
				0, -1,  0,
				-1,  5, -1,
				0, -1,  0);

	dwT = (double)getTickCount();
	filter2D(matSrc, matDst, matSrc.depth(), matKernel);
	dwT = ((double)getTickCount() - dwT) / getTickFrequency();
	cout << "Built-in filter2D time passed in seconds:      " << dwT << endl;
	
	namedWindow(cszWindowsTitleDst, WINDOW_AUTOSIZE);
	imshow(cszWindowsTitleDst, matDst);
	waitKey(0);
	return EXIT_SUCCESS;
}

