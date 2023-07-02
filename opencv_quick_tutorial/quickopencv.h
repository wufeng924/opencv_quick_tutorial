#pragma once

#include<opencv2/opencv.hpp>

using namespace cv;

class QuickDemo {
	public:
		void colorSpace_Demo(Mat& image);
		void mat_creation_demo(Mat& image);
		void pixel_visit_demo(Mat& image);
		void operators_demo(Mat& image);
		void tracking_bar_demo(Mat& image);
		void key_demo(Mat& image);
		void color_style_demo(Mat& image);
		void bitwise_demo(Mat& image);
};
