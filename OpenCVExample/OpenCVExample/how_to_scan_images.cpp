#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>

using namespace std;
using namespace cv;

static void help() {
	cout
			<< "\n--------------------------------------------------------------------------" << endl
			<< "This program shows how to scan image objects in OpenCV (cv::Mat). As use case"
			<< " we take an input image and divide the native color palette (255) with the "  << endl
			<< "input. Shows C operator[] method, iterators and at function for on-the-fly item address calculation." << endl			
			<< "--------------------------------------------------------------------------"   << endl
			<< endl;
}

Mat& ScanImageAndReduceC(Mat& I, const uchar* table);
Mat& ScanImageAndReduceIterator(Mat& I, const uchar* table);
Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar * table);

int main( int argc, char* argv[]) {
	help();
	Mat matI, matJ;
	const int cnTimes = 100;
	double dwT;

	//////////////////////////////////////////////////////////////////////////
	char *szFilePath = "../lena.jpg";
	matI = imread(szFilePath, CV_LOAD_IMAGE_COLOR);
	if (!matI.data) {
		cout << "The image" << szFilePath << " could not be loaded." << endl;
		return -1;
	}
	imshow("Input Image", matI);
	waitKey(0);

	//////////////////////////////////////////////////////////////////////////	
	int nDivideWith = 32;  	
	if (nDivideWith <= 0) {
		cout << "Invalid number entered for dividing. " << endl;
		system("pause");
		return -1;
	}

	//////////////////////////////////////////////////////////////////////////	
	uchar bTable[256];
	for (int i = 0; i < 256; ++i)
		bTable[i] = (uchar)(nDivideWith * (i / nDivideWith));		
	
	//////////////////////////////////////////////////////////////////////////
#pragma region reducing with the C operator []
	dwT = (double)getTickCount();
	
	for (int i = 0; i < cnTimes; ++i) {
		cv::Mat clone_i = matI.clone();
		matJ = ScanImageAndReduceC(clone_i, bTable);
	}
	
	dwT = 1000 * ((double)getTickCount() - dwT) / getTickFrequency();
	dwT /= cnTimes;
	
	cout << "Time of reducing with the C operator [] (averaged for "
		 << cnTimes << " runs): " << dwT << " milliseconds." << endl;
#pragma endregion

	//////////////////////////////////////////////////////////////////////////	
#pragma region reducing with the iterator
	dwT = (double)getTickCount();
	
	for (int i = 0; i < cnTimes; ++i) {
		cv::Mat clone_i = matI.clone();
		matJ = ScanImageAndReduceIterator(clone_i, bTable);
	}
	
	dwT = 1000 * ((double)getTickCount() - dwT) / getTickFrequency();
	dwT /= cnTimes;
	
	cout << "Time of reducing with the iterator (averaged for "
		 << cnTimes << " runs): " << dwT << " milliseconds." << endl;
#pragma endregion

	//////////////////////////////////////////////////////////////////////////		
#pragma region reducing with the on-the-fly address generation - at function
	dwT = (double)getTickCount();
	
	for (int i = 0; i < cnTimes; ++i) {
		cv::Mat clone_i = matI.clone();
		ScanImageAndReduceRandomAccess(clone_i, bTable);
	}
	
	dwT = 1000 * ((double)getTickCount() - dwT) / getTickFrequency();
	dwT /= cnTimes;
	
	cout << "Time of reducing with the on-the-fly address generation - at function (averaged for "
		 << cnTimes << " runs): " << dwT << " milliseconds." << endl;
#pragma endregion

	//////////////////////////////////////////////////////////////////////////	
#pragma region reducing with the LUT function
	Mat lookUpTable(1, 256, CV_8U);
	uchar* p = lookUpTable.data;
	for ( int i = 0; i < 256; ++i)
		p[i] = bTable[i];
		
	dwT = (double)getTickCount();
	
	for (int i = 0; i < cnTimes; ++i)
		LUT(matI, lookUpTable, matJ);
		
	dwT = 1000 * ((double)getTickCount() - dwT) / getTickFrequency();
	dwT /= cnTimes;
	
	cout << "Time of reducing with the LUT function (averaged for "
		 << cnTimes << " runs): " << dwT << " milliseconds." << endl;
#pragma endregion

	system("pause");
	return 0;
}

Mat& ScanImageAndReduceC(Mat& I, const uchar* const table) {
	// accept only char type matrices
	CV_Assert(I.depth() != sizeof(uchar));
	
	int channels = I.channels();
	
	int nRows = I.rows;
	int nCols = I.cols * channels;
	
	if (I.isContinuous()) {
		nCols *= nRows;
		nRows = 1;
	}
	
	int i, j;
	uchar* p;
	for ( i = 0; i < nRows; ++i) {
		p = I.ptr<uchar>(i);
		for ( j = 0; j < nCols; ++j) {
			p[j] = table[p[j]];
		}
	}
	return I;
}

Mat& ScanImageAndReduceIterator(Mat& I, const uchar* const table) {
	// accept only char type matrices
	CV_Assert(I.depth() != sizeof(uchar));
	
	const int channels = I.channels();
	switch (channels) {
		case 1: {
				MatIterator_<uchar> it, end;
				for ( it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
					*it = table[*it];
				break;
			}
		case 3: {
				MatIterator_<Vec3b> it, end;
				for ( it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it) {
					(*it)[0] = table[(*it)[0]];
					(*it)[1] = table[(*it)[1]];
					(*it)[2] = table[(*it)[2]];
				}
				break;
			}
	}
	
	return I;
}

Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar* const table) {
	// accept only char type matrices
	CV_Assert(I.depth() != sizeof(uchar));
	
	const int channels = I.channels();
	switch (channels) {
		case 1: {
				for ( int i = 0; i < I.rows; ++i)
					for ( int j = 0; j < I.cols; ++j )
						I.at<uchar>(i, j) = table[I.at<uchar>(i, j)];
				break;
			}
		case 3: {
				Mat_<Vec3b> _I = I;
				
				for ( int i = 0; i < I.rows; ++i)
					for ( int j = 0; j < I.cols; ++j ) {
						_I(i, j)[0] = table[_I(i, j)[0]];
						_I(i, j)[1] = table[_I(i, j)[1]];
						_I(i, j)[2] = table[_I(i, j)[2]];
					}
				I = _I;
				break;
			}
	}
	
	return I;
}
