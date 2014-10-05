/*  For description look into the help() function. */

#include "opencv/cv.h"
#include "opencv/highgui.h"
#include <iostream>

using namespace std;
using namespace cv;

static void help() {
    cout
            << "\n--------------------------------------------------------------------------" << endl
            << "This program shows how to create matrices(cv::Mat) in OpenCV and its serial"
            << " out capabilities"                                                            << endl
            << "That is, cv::Mat M(...); M.create and cout << M. "                            << endl
            << "Shows how output can be formated to OpenCV, python, numpy, csv and C styles." << endl           
            << "--------------------------------------------------------------------------"   << endl
            << endl;
}

int main(int, char**) {
    help();
	//////////////////////////////////////////////////////////////////////////	
    // create by using the constructor
    Mat M(2, 2, CV_8UC3, Scalar(0, 0, 255));
    cout << "M = " << endl << " " << M << endl << endl;
	// 	M = [0, 0, 255, 0, 0, 255;
	//	 	 0, 0, 255, 0, 0, 255]

	// and now turn M to a 4*4 2-channel 8-bit matrix
	// The old content will be deallocated
	M.create(4, 4, CV_8UC(2));
	cout << "M = " << endl << " " << M << endl << endl;

	//////////////////////////////////////////////////////////////////////////
	Mat A;
	cout << "*refcount = " << (*M.refcount) << " should be 1" << endl;
	A = M;
	cout << "*refcount = " << (*M.refcount) << " should be 2" << endl;
	Mat B(M);
	cout << "*refcount = " << (*M.refcount) << " should be 3" << endl;
	M.release();
	cout << "refcount ptr = " << (M.refcount) << " should be 0" << endl;
	system("pause");

	//////////////////////////////////////////////////////////////////////////	
	// 	Mat M(row,
	// 		column,
	// 		specify the data type to use for storing the elements and the number of channels per matrix point,
	// 		pixel)
	Mat matImage(300, 230, CV_8UC(3), Scalar(0, 0, 255));
	imshow("matImage", matImage);
	waitKey(0);
    
	//////////////////////////////////////////////////////////////////////////
	// create a 10*10*10 8-bit matrix
	int sz[] = { 10, 10, 10 };
	Mat L(3, sz, CV_8U, Scalar::all(0));
		
	//////////////////////////////////////////////////////////////////////////	      
    // Create using MATLAB style eye, ones or zero matrix
    Mat E = Mat::eye(4, 4, CV_64F);
    cout << "E = " << endl << " " << E << endl << endl;
	// 	E = [1, 0, 0, 0;
	// 		 0, 1, 0, 0;
	// 		 0, 0, 1, 0;
	// 		 0, 0, 0, 1]
    
    Mat O = Mat::ones(2, 2, CV_32F);
    cout << "O = " << endl << " " << O << endl << endl;
	// 	O = [0, 0;
	// 		 0, 0]
    
    Mat Z = Mat::zeros(3, 3, CV_8UC1);
    cout << "Z = " << endl << " " << Z << endl << endl;
	// 	Z = [1, 1, 1;
	// 		 1, 1, 1;
	// 		 1, 1, 1]
    
	//////////////////////////////////////////////////////////////////////////	
    // create a 3x3 double-precision identity matrix (Only for 2 dimension)
    Mat C = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    cout << "C = " << endl << " " << C << endl << endl;
	// 	C = [0, -1, 0;
	// 		 -1, 5, -1;
	// 		 0, -1, 0]
    
	// clone & copyTo
    Mat RowClone = C.row(1).clone();
    cout << "RowClone = " << endl << " " << RowClone << endl << endl;
	C.row(1).copyTo(RowClone);
	cout << "RowClone = " << endl << " " << RowClone << endl << endl;

	//////////////////////////////////////////////////////////////////////////
	// add the 2-nd row, multiplied by 3 to the 3-rd row
	M.row(3) = M.row(3) + M.row(2) * 3;
	// copy the 4-th column to the 1-st column
	Mat M1 = M.col(1);
	M.col(2).copyTo(M1);

	//////////////////////////////////////////////////////////////////////////	
    // Fill a matrix with random values
    Mat R = Mat(3, 2, CV_8UC3);
    randu(R, Scalar::all(0), Scalar::all(255));
    
    // Demonstrate the output formating options
    cout << "R (default) = " << endl <<        R           << endl << endl;
    cout << "R (python)  = " << endl << format(R, "python") << endl << endl;
    cout << "R (numpy)   = " << endl << format(R, "numpy" ) << endl << endl;
    cout << "R (csv)     = " << endl << format(R, "csv"   ) << endl << endl;
    cout << "R (c)       = " << endl << format(R, "C"     ) << endl << endl;
    
	//////////////////////////////////////////////////////////////////////////	
    Point2f P(5, 1);
    cout << "Point (2D) = " << P << endl << endl;
    
    Point3f P3f(2, 6, 7);
    cout << "Point (3D) = " << P3f << endl << endl;
    
    //////////////////////////////////////////////////////////////////////////    
    vector<float> v;
    v.push_back( (float)CV_PI);
    v.push_back(2);
    v.push_back(3.01f);
    
    cout << "Vector of floats via Mat = " << Mat(v) << endl;
	cout << "v[0] = " << v[0] << endl;
	cout << "v[1] = " << v[1] << endl;
	cout << "v[2] = " << v[2] << endl << endl;
    
	//////////////////////////////////////////////////////////////////////////	
    vector<Point2f> vPoints(20);
    for (size_t i = 0; i < vPoints.size(); ++i)
        vPoints[i] = Point2f((float)(i * 5), (float)(i % 7));
        
    cout << "A vector of 2D Points = " << vPoints << endl << endl;
    system("pause");
    return 0;
}
