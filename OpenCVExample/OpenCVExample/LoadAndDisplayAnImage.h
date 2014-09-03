// In this tutorial you will learn how to:
//  - Load an image (using imread)
// 	- Create a named OpenCV window (using namedWindow)
// 	- Display an image in an OpenCV window (using imshow)

#ifndef LOAD_AND_DISPLAY_AN_IMAGE_H
#define LOAD_AND_DISPLAY_AN_IMAGE_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class CLoadAndDisplay {
public:
	CLoadAndDisplay(char *, char *);
	~CLoadAndDisplay();
	int imLoadAndDisplay();

private:
	char *m_szFilePath;
	char *m_szWindowTitle;
};

#endif