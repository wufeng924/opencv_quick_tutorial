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

	//创建空白图像
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
	subtract(image, m, dst);
	//divide(image, m, dst);
	

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

//Mat dst, m, src;
//int lightness = 50;
//
//static void on_track(int, void*) {
//	m = Scalar(lightness, lightness, lightness);
//	add(src, m, dst);
//	imshow("亮度调整", dst);
//}
//
//void QuickDemo::tracking_bar_demo(Mat& image) {
//	namedWindow("亮度调整", WINDOW_FREERATIO);
//	dst = Mat::zeros(image.size(), image.type());
//	m = Mat::zeros(image.size(), image.type());
//	int max_value = 100;
//	src = image;
//	namedWindow("原图", WINDOW_FREERATIO);
//	imshow("原图", image);
//	createTrackbar("Value Bar:", "亮度调整", &lightness, max_value, on_track);
//	on_track(50, 0);
//}

static void on_lightness(int b, void* userdata) {
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	m = Scalar(b, b, b);
	addWeighted(image, 1.0, m, 0, b, dst);  //融合两张图 dst = image * 1.0 + m * 0 + b
	imshow("亮度与对比度调整", dst);
}

static void on_contrast(int b, void* userdata) {
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	double contrast = b / 100.0;
	addWeighted(image, contrast, m, 0.0, 0, dst);
	imshow("亮度与对比度调整", dst);
}

void QuickDemo::tracking_bar_demo(Mat& image) {
	namedWindow("亮度与对比度调整", WINDOW_FREERATIO);
	int lightness = 50;
	int max_value = 100;
	int contrast_value = 100;

	namedWindow("原图", WINDOW_FREERATIO);
	imshow("原图", image);
	createTrackbar("Value Bar:", "亮度与对比度调整", &lightness, max_value, on_lightness, (void*)(&image));
	createTrackbar("Contrast Bar:", "亮度与对比度调整", &contrast_value, 200, on_contrast, (void*)(&image));
	on_lightness(50, &image);
}


void QuickDemo::key_demo(Mat& image) {
	Mat dst = Mat::zeros(image.size(), image.type());
	while (true) {

		int c = waitKey(100);
		if (c == 27) {
			break;
		}
		if (c == 49) {
			std::cout << "You enter key # 1" << std::endl;
			cvtColor(image, dst, COLOR_BGR2GRAY);

		}
		if (c == 50) {
			std::cout << "You enter key # 2" << std::endl;
			cvtColor(image, dst, COLOR_BGR2HSV);
		}
		if (c == 51) {
			std::cout << "You enter key # 3" << std::endl;
			dst = Scalar(50, 50, 50);
			add(image, dst, dst);
		}
		imshow("键盘响应", dst);
	}
}

void QuickDemo::color_style_demo(Mat& image) {
	int colormap[] = {//共19种
		COLORMAP_AUTUMN,
		COLORMAP_BONE,
		COLORMAP_CIVIDIS,
		COLORMAP_DEEPGREEN,
		COLORMAP_HOT,
		COLORMAP_HSV,
		COLORMAP_INFERNO,
		COLORMAP_JET,
		COLORMAP_MAGMA,
		COLORMAP_OCEAN,
		COLORMAP_PINK,
		COLORMAP_PARULA,
		COLORMAP_RAINBOW,
		COLORMAP_SPRING,
		COLORMAP_TWILIGHT,
		COLORMAP_TURBO,
		COLORMAP_TWILIGHT,
		COLORMAP_VIRIDIS,
		COLORMAP_TWILIGHT_SHIFTED,
		COLORMAP_WINTER
	};
	Mat dst;
	int index = 0; //初始化为指向0的位置
	while (true) {
		char c = waitKey(2000);//等待半秒（1s = 1000ms），做视频处理都是1
		if (c == 27) {//按 esc 退出应用程序
			break;
		}
		if (c == 49) {//key#1 按下按键1时。保存图片到指定位置
			std::cout << "you enter key #1" << std::endl;
			imwrite("C:/Users/18221/Desktop/Images/save_images/颜色表的成果.jpg", dst);
		}
		applyColorMap(image, dst, colormap[index % 19]);//循环展示19种图片（产生伪色彩图像）
		index++;
		imshow("循环播放", dst);
	}

}

void QuickDemo::bitwise_demo(Mat& image) {
	Mat m1 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat m2 = Mat::zeros(Size(256, 256), CV_8UC3);
	rectangle(m1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), -1, LINE_8, 0);
	rectangle(m2, Rect(150, 150, 80, 80), Scalar(0, 255, 255), -1, LINE_8, 0);
	imshow("m1", m1);
	imshow("m2", m2);
	Mat dst;
	bitwise_not(m1, dst);
	imshow("像素位操作",dst);
}