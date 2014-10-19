#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>
using namespace std;
using namespace cv;

//////////////////////////////////////////////////////////////////////////
// Global Variables
Mat matImageSrc;
Mat matImageDst;
double dwAlpha; // Simple contrast control
int nBeta;  // Simple brightness control 
//////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
	// Read image given by user
	char *szFilePath = "../lena.jpg";
	matImageSrc = imread(szFilePath, CV_LOAD_IMAGE_COLOR);
	if (!matImageSrc.data) {
		cout << "The image" << szFilePath << " could not be loaded." << endl;
		return -1;
	}
	matImageDst = Mat::zeros(matImageSrc.size(), matImageSrc.type());
	
	// Initialize values
	cout << " Basic Linear Transforms " << endl;
	cout << "-------------------------" << endl;
	cout << "* Enter the alpha value [1.0-3.0]: ";
	cin >> dwAlpha;
	cout << "* Enter the beta value [0-100]: ";
	cin >> nBeta;
	
	// Do the operation new_image(i,j) = alpha*image(i,j) + beta
	  for (size_t IdxRow = 0; IdxRow < matImageSrc.rows; IdxRow++) {
	      for (size_t IdxCol = 0; IdxCol < matImageSrc.cols; IdxCol++) {
	          for (size_t IdxCh = 0; IdxCh < 3; IdxCh++) {
	              matImageDst.at<Vec3b>(IdxRow, IdxCol)[IdxCh] =
	                  saturate_cast<uchar>(dwAlpha * (matImageSrc.at<Vec3b>(IdxRow, IdxCol)[IdxCh]) + nBeta);
	          }
	      }
	  }

	// Create Windows
	namedWindow("Original Image", 1);
	namedWindow("New Image", 1);
	
	// Show stuff
	imshow("Original Image", matImageSrc);
	imshow("New Image", matImageDst);
	
	// Wait until user press some key
	waitKey();
	return 0;
}