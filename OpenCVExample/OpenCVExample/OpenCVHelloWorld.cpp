#include "OpenCVHelloWorld.h"

COpencvHelloworld::COpencvHelloworld() {
	int nHeight = 500;
	int nWidth = 300;
	Mat image = Mat::zeros(nHeight, nWidth, CV_8UC3); // Initialize a matrix filled with zeros
		
	cout << "OpenCV HelloWorld!!" << endl;
	system("pause");
}

COpencvHelloworld::~COpencvHelloworld() {

}
