#include <opencv2/opencv.hpp>
#include <iostream>
#include <quickopencv.h>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("C:/Users/18221/Desktop/Images/3.jpg");
	if (src.empty()) {
		cout<<"could not load image...\n";
		return -1;
	}
	/*namedWindow("input", WINDOW_FREERATIO);
	imshow("input", src);*/

	QuickDemo qd;
	//qd.colorSpace_Demo(src);
	//qd.mat_creation_demo(src);
	//qd.pixel_visit_demo(src);
	qd.operators_demo(src);
	waitKey(0);
	destroyAllWindows();
	return 0;
}