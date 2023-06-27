#include<quickopencv.h>

void QuickDemo::colorSpace_Demo(Mat &image) {
	Mat gray, hsv;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	cvtColor(image, hsv, COLOR_BGR2HSV);
	imshow("gray", gray);
	imshow("hsv", hsv);
	imwrite("C:/Users/18221/Desktop/Images/gray.jpg", gray);
	imwrite("C:/Users/18221/Desktop/Images/hsv.jpg", hsv);
}

void QuickDemo::mat_creation_demo(Mat &image) {
	/*Mat m1, m2;
	m1 = image.clone();
	image.copyTo(m2);*/

	//´´½¨¿Õ°×Í¼Ïñ
	Mat m3 = Mat::ones(Size(10, 10), CV_8UC3);
	m3 = Scalar(255, 0, 255);
	std::cout << "width: " << m3.cols << "  height: " << m3.rows << "  channels: " << m3.channels() << std::endl;
	std::cout << m3 << std::endl;
	/*imshow("m1", m1);
	imshow("m2", m2);*/

	Mat m4;
	m3.copyTo(m4);
	m4 = Scalar(0, 255, 255);
	imshow("m4", m4);
	imshow("m3", m3);
}

void QuickDemo::pixel_visit_demo(Mat& image) {
	int h = image.rows;
	int w = image.cols;
	int dims = image.channels();

	//for (int row = 0; row < h; row++) {
	//	for (int col = 0; col < w; col++) {
	//		if (dims == 1) {
	//			int pv = image.at<uchar>(row, col);
	//			image.at<uchar>(row, col) = 255 - pv;
	//		}
	//		if (dims == 3) {
	//			Vec3b bgr = image.at<Vec3b>(row, col);
	//			image.at<Vec3b>(row, col)[0] = 255 - bgr[0];
	//			image.at<Vec3b>(row, col)[1] = 255 - bgr[1];
	//			image.at<Vec3b>(row, col)[2] = 255 - bgr[2];
	//		}
	//	}
	//}

	for (int row = 0; row < h; row++) {
		uchar* current_row = image.ptr<uchar>(row);
		for (int col = 0; col < w; col++) {
			if (dims == 1) {
				int pv = *current_row;
				*current_row++ = 255 - pv;
			}
			if (dims == 3) {
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
			}
		}
	}

	namedWindow("pixel_visit_demo", WINDOW_FREERATIO);
	imshow("pixel_visit_demo", image);
}

void QuickDemo::operators_demo(Mat& image) {
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	//dst = image * m;
	m = Scalar(50, 50, 50);
	//multiply(image, m, dst);
	//add(image, m, dst);
	//subtract(image, m, dst);
	divide(image, m, dst);
	

	/*int h = image.rows;
	int w = image.cols;
	int dims = image.channels();

	for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			Vec3b p1 = image.at<Vec3b>(row, col);
			Vec3b p2 = m.at<Vec3b>(row, col);
			dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(p1[0] + p2[0]);
			dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(p1[1] + p2[1]);
			dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(p1[2] + p2[2]);
		}
	}*/

	imshow("root", image);
	imshow("add", dst);
}