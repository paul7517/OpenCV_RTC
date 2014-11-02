#include "opencv/highgui.h"
#include "opencv/cv.h"
#include <iostream>

using namespace cv;
using namespace std;

//////////////////////////////////////////////////////////////////////////
// Global Variables
Mat matSrc, matDst;
Mat map_x; // index of col
Mat map_y; // index of row
const char* szWindowTitle = "Remap demo";
const char *szFilePath = "../lena.jpg";
int nflag = 0;

// Function Headers
void update_map(void);

int main(int, char** argv) {
	// Load the image
	matSrc = imread(szFilePath, 1);
	if (!matSrc.data) {
		cout << "The image" << szFilePath << " could not be loaded." << endl;
		system("pause");
		return -1;
	}

	// Create dst, map_x and map_y with the same size as src:
	matDst.create(matSrc.size(), matSrc.type());
	map_x.create(matSrc.size(), CV_32FC1);
	map_y.create(matSrc.size(), CV_32FC1);
	
	// Create window
	namedWindow(szWindowTitle, WINDOW_AUTOSIZE);
	imshow(szWindowTitle, matSrc);
	waitKey(100);
	
	// Loop
	while (true) {
		// Each 1 sec. Press ESC to exit the program
		int nKeyEvnet = waitKey(1000);
		if ((char)nKeyEvnet == 27) {
			break;
		}
		
		// Update map_x & map_y. Then apply remap
		update_map();
		remap(matSrc, matDst, map_x, map_y, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
		
		// Display results
		imshow(szWindowTitle, matDst);
	}
	return 0;
}

// Fill the map_x and map_y matrices with 3 types of mappings
void update_map(void) {
	nflag = nflag % 3;
	cout << "Flag = " << nflag << endl;
	
	for (int idxRow = 0; idxRow < matSrc.rows; idxRow++) {
		for (int idxCol = 0; idxCol < matSrc.cols; idxCol++) {
			switch (nflag) {
				case 0:
					map_x.at<float>(idxRow, idxCol) = (float)(matSrc.cols - idxCol);
					map_y.at<float>(idxRow, idxCol) = (float)(matSrc.rows - idxRow);
					break;
				case 1:
					map_x.at<float>(idxRow, idxCol) = (float)idxCol ;
					map_y.at<float>(idxRow, idxCol) = (float)(matSrc.rows - idxRow) ;
					break;
				case 2:
					map_x.at<float>(idxRow, idxCol) = (float)(matSrc.cols - idxCol) ;
					map_y.at<float>(idxRow, idxCol) = (float)idxRow ;
					break;					
			} // end of switch
		}
	}
	nflag++;
}
