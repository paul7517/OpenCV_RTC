#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace cv;
using namespace std;

int main() {
	char* szImageName = "../HappyFish.jpg";
	
	Mat matImage;
	matImage = imread(szImageName, CV_LOAD_IMAGE_COLOR);
	
	if (!matImage.data) {
		cout << "No image data" << endl;
		system("pause");
		return -1;
	}
	
	Mat matGrayImage;
	cvtColor(matImage, matGrayImage, CV_BGR2GRAY);
	
	imwrite("../GrayImage.jpg", matGrayImage);
	
	namedWindow(szImageName, CV_WINDOW_AUTOSIZE);
	namedWindow("Gray image", CV_WINDOW_AUTOSIZE);	
	imshow(szImageName, matImage);
	imshow("Gray image", matGrayImage);	
	waitKey(0);
	return 0;
}
