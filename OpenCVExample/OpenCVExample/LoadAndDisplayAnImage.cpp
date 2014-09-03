#include "LoadAndDisplayAnImage.h"

CLoadAndDisplay::CLoadAndDisplay(char *szFilePath, char *szWindowTitle) {
	m_szFilePath = szFilePath;
	m_szWindowTitle = szWindowTitle;
}

CLoadAndDisplay::~CLoadAndDisplay() {
	delete m_szWindowTitle;
	delete m_szFilePath;
}

int CLoadAndDisplay::imLoadAndDisplay() {
	Mat image;
	image = imread(m_szFilePath, CV_LOAD_IMAGE_COLOR); // Read the file
	
	// Check for invalid input
	if (!image.data) {                           
		cout <<  "Could not open or find the image" << endl;
		return EXIT_FAILURE;
	}

	namedWindow(m_szWindowTitle, WINDOW_AUTOSIZE); // Create a window for display.	
	imshow(m_szWindowTitle, image ); // Show our image inside it.	
	waitKey(0); // Wait for a keystroke in the window                                          
	return EXIT_SUCCESS;
}