#include "OpenCVHelloWorld.h"
#include "LoadAndDisplayAnImage.h"

int main(int argc, char** argv) {
	//////////////////////////////////////////////////////////////////////////
	// OpenCV HelloWorld!
 	COpencvHelloworld *cOpencvHellworld = new COpencvHelloworld();	

	//////////////////////////////////////////////////////////////////////////
	// Load and display an images
	char *szFilePath = "opencv-logo-white.png";
	char *szWindowTitle = "Display Window";
	CLoadAndDisplay *cLoadAndDisplay = new CLoadAndDisplay(szFilePath, szWindowTitle);
	cLoadAndDisplay->imLoadAndDisplay();

	//////////////////////////////////////////////////////////////////////////

	return EXIT_SUCCESS;
}