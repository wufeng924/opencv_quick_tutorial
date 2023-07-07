#include <opencv2/opencv.hpp>
#include <iostream>
#include <quickopencv.h>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("C:/Users/18221/Desktop/Images/9.jpg");
	if (src.empty()) {
		cout<<"could not load image...\n";
		return -1;
	}
	/*namedWindow("input", WINDOW_FREERATIO);
	imshow("input", src);*/

	QuickDemo qd;

	//imshow("JPG", src);

	//qd.colorSpace_Demo(src);
	//qd.mat_creation_demo(src);
	//qd.pixel_visit_demo(src);
	//qd.operators_demo(src);
	//qd.tracking_bar_demo(src);
	//qd.key_demo(src);
	//qd.color_style_demo(src);
	//qd.bitwise_demo(src);
	//qd.channels_demo(src);
	//qd.inrange_demo(src); //À¶µ×±ä»»  11.jpg
	//qd.pixel_statistic_demo(src);
	//qd.drawing_demo(src);
	//qd.randow_drawing();
	//qd.polyline_drawing();
	//qd.mouse_drawing(src);
	qd.norm_demo(src);
	waitKey(0);
	destroyAllWindows();
	return 0;
}