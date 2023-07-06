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

	//�����հ�ͼ��
	Mat m3 = Mat::ones(Size(10, 10), CV_8UC3);
	m3 = Scalar(255, 0, 0);
	std::cout << "width: " << m3.cols << "  height: " << m3.rows << "  channels: " << m3.channels() << std::endl;
	std::cout << m3 << std::endl;
	/*imshow("m1", m1);
	imshow("m2", m2);*/

	Mat m4;
	m3.copyTo(m4);
	//m4 = m3.clone();
	m4 = Scalar(0, 0, 255);
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
//	imshow("���ȵ���", dst);
//}
//
//void QuickDemo::tracking_bar_demo(Mat& image) {
//	namedWindow("���ȵ���", WINDOW_FREERATIO);
//	dst = Mat::zeros(image.size(), image.type());
//	m = Mat::zeros(image.size(), image.type());
//	int max_value = 100;
//	src = image;
//	namedWindow("ԭͼ", WINDOW_FREERATIO);
//	imshow("ԭͼ", image);
//	createTrackbar("Value Bar:", "���ȵ���", &lightness, max_value, on_track);
//	on_track(50, 0);
//}

static void on_lightness(int b, void* userdata) {
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	m = Scalar(b, b, b);
	addWeighted(image, 1.0, m, 0, b, dst);  //�ں�����ͼ dst = image * 1.0 + m * 0 + b
	imshow("������Աȶȵ���", dst);
}

static void on_contrast(int b, void* userdata) {
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	double contrast = b / 100.0;
	addWeighted(image, contrast, m, 0.0, 0, dst);
	imshow("������Աȶȵ���", dst);
}

void QuickDemo::tracking_bar_demo(Mat& image) {
	namedWindow("������Աȶȵ���", WINDOW_FREERATIO);
	int lightness = 50;
	int max_value = 100;
	int contrast_value = 100;

	namedWindow("ԭͼ", WINDOW_FREERATIO);
	imshow("ԭͼ", image);
	createTrackbar("Value Bar:", "������Աȶȵ���", &lightness, max_value, on_lightness, (void*)(&image));
	createTrackbar("Contrast Bar:", "������Աȶȵ���", &contrast_value, 200, on_contrast, (void*)(&image));
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
		imshow("������Ӧ", dst);
	}
}

void QuickDemo::color_style_demo(Mat& image) {
	int colormap[] = {//��19��
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
	int index = 0; //��ʼ��Ϊָ��0��λ��
	while (true) {
		char c = waitKey(2000);//�ȴ����루1s = 1000ms��������Ƶ������1
		if (c == 27) {//�� esc �˳�Ӧ�ó���
			break;
		}
		if (c == 49) {//key#1 ���°���1ʱ������ͼƬ��ָ��λ��
			std::cout << "you enter key #1" << std::endl;
			imwrite("C:/Users/18221/Desktop/Images/save_images/��ɫ��ĳɹ�.jpg", dst);
		}
		applyColorMap(image, dst, colormap[index % 19]);//ѭ��չʾ19��ͼƬ������αɫ��ͼ��
		index++;
		imshow("ѭ������", dst);
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
	imshow("����λ����",dst);
}

void QuickDemo::channels_demo(Mat& image) {
	std::vector<Mat> mv;
	split(image, mv);
	imshow("Red", mv[0]);
	imshow("Green", mv[1]);
	imshow("Blue", mv[2]);

	Mat dst;
	mv[0] = 0;
	mv[2] = 0;
	merge(mv, dst);
	imshow("��ɫ", dst);

	int from_to[] = { 0,2,1,1,2,0 };
	mixChannels(&image, 1, &dst, 1, from_to, 3);
	imshow("ͨ�����", dst);
	imshow("original image", image);
}

void QuickDemo::inrange_demo(Mat& image) {
	Mat hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	Mat mask;
	inRange(hsv, Scalar(100, 43, 46), Scalar(124, 255, 255), mask);
	//imshow("mask", mask);  //msckΪ�׵�

	Mat redback = Mat::zeros(image.size(), image.type());
	redback = Scalar(40, 40, 200); //��ɫ����
	bitwise_not(mask, mask); //maskΪ�ڵ�
	imshow("mask", mask);
	image.copyTo(redback, mask); //��mask�в�Ϊ0����(��ɫ���ص�)��Ӧ��ԭͼ ������ redback�ϣ�maskͨ��inRange�õ�
	imshow("roi������ȡ", redback);
}

void QuickDemo::pixel_statistic_demo(Mat& image) {
	double minv, maxv;
	Point minLoc, maxLoc; //�����ַ
	std::vector<Mat> mv; //�ɴ��Mat���͵�����
	split(image, mv); //����ͨ�� ��ֳ� ��ͨ����ͨ������)
	for (int i = 0; i < mv.size(); i++) {

		//�ֱ��ӡ����ͨ������ֵ
		minMaxLoc(mv[i], &minv, &maxv, &minLoc, &maxLoc, Mat());
		//���ͼ������ֵ����Сֵ����λ��
		//����һ�����뵥ͨ��������
		//��������������Сֵ��ָ��
		//���������������ֵ��ָ��
		//�����ģ�������Сֵλ�õ�ָ��
		//�����壺�������ֵλ�õ�ָ��
		std::cout << "No.channels:" << i << "  minvalue:" << minv << "  maxvalue:" << maxv << std::endl;
		
	}

	Mat mean, stddev;
	meanStdDev(image, mean, stddev); //���ͼ��ľ�ֵ ������
	std::cout << "mean:" << mean << std::endl;
	std::cout << "stddev:" << stddev << std::endl;
}

void QuickDemo::drawing_demo(Mat& image) {
	Rect rect;
	rect.x = 45;
	rect.y = 40;
	rect.width = 160;
	rect.height = 90;
	Mat bg = Mat::zeros(image.size(), image.type());
	rectangle(bg, rect, Scalar(0, 0, 255), -1);
	//circle(image, Point(125, 85), 70, Scalar(0, 255, 0), 2);
	Mat dst;
	addWeighted(image, 0.7, bg, 0.3, 0, dst); //�ں�����ͼ image��bg
	line(bg, Point(45, 40), Point(205, 130), Scalar(0, 255, 0), 4, LINE_AA, 0);
	RotatedRect rrt;
	rrt.center = Point(125, 85);
	rrt.angle = 90;
	rrt.size = Size(100, 200);
	ellipse(bg, rrt, Scalar(255, 0, 0), 2);
	imshow("output", bg);
}

void QuickDemo::randow_drawing() {
	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
	int h = canvas.rows;
	int w = canvas.cols;
	RNG rng(12345); //�����������12345Ϊ����������ӣ�Ĭ�ϵ�
	while (true) {
		int c = waitKey(100);
		if (c == 27) {
			break;
		}
		int x1 = rng.uniform(0, w), y1 = rng.uniform(0, h);
		int x2 = rng.uniform(0, w), y2 = rng.uniform(0, h);
		int r = rng.uniform(0, 255), g = rng.uniform(0, 255), b = rng.uniform(0, 255);
		line(canvas, Point(x1, y1), Point(x2, y2), Scalar(r, g, b), 4, LINE_AA, 0);
		imshow("�������", canvas);
	}
}

void QuickDemo::polyline_drawing() {
	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
	Point p1(150, 100);//��һ���������
	Point p2(350, 200);//  ��
	Point p3(240, 300);//  ��
	Point p4(150, 300);//  ��
	Point p5(50, 200);//  ��
	std::vector<Point> pts;//��һ������������װ ��
	pts.push_back(p1);//����Ž�������
	pts.push_back(p2);//�� δ��ʼ����������������Ҫ�� push_back ����
	pts.push_back(p3);//�� �ѳ�ʼ���������� �����±� ������
	pts.push_back(p4);
	pts.push_back(p5);
	//fillPoly(canvas, pts, Scalar(0, 255, 0), LINE_AA); //�������
	//polylines(canvas, pts, true, Scalar(0, 0, 255), 2, LINE_AA); //���ƶ����
	//imshow("����λ���", canvas);

	std::vector<std::vector<Point>> contours; //��һ������������װ ����εĵ㼯
	contours.push_back(pts); //��һ������εĵ㼯�Ž������ڣ���Ϊһ��Ԫ��
	drawContours(canvas, contours, -1, Scalar(0, 0, 255), -1);
	//������1��<0��ʾ��䣬>0��ʾ�߿�
	//������������εĵ㼯
	//��������-1Ϊ����ȫ���Ķ���Σ�0Ϊ���Ƶ�һ����1Ϊ���Ƶڶ������Դ�����
	imshow("��������", canvas);
}


Point sp(-1, -1);
Point ep(-1, -1);
Mat temp;
static void on_draw(int event, int x, int y, int flags, void* userdata) {
	Mat image = *((Mat*)userdata);
	//�������������
	if (event == EVENT_LBUTTONDOWN) {
		//��ʱ������ʼλ������
		sp.x = x;
		sp.y = y;
		std::cout << "Start Point : " << sp << std::endl;
	}
	//���������̧��
	else if (event == EVENT_LBUTTONUP) {
		//��ʱ���Ľ���λ������
		ep.x = x;
		ep.y = y;
		int dx = ep.x - sp.x;
		int dy = ep.y - sp.y;
		if (dx > 0 && dy > 0) {
			Rect box(sp.x, sp.y, dx, dy);
			rectangle(image, box, Scalar(0, 255, 0), 2, LINE_AA);
			imshow("������", image);
			imshow("ROI����", image(box));
			//��λ��Ϊ��һ�λ�����׼��
			sp.x = -1;
			sp.y = -1;
		}
	}
	//��������ƶ���
	else if (event == EVENT_MOUSEMOVE) {
		if (sp.x > 0 && sp.y > 0) {
			ep.x = x;
			ep.y = y;
			int dx = ep.x - sp.x;
			int dy = ep.y - sp.y;
			if (dx > 0 && dy > 0) {
				Rect box(sp.x, sp.y, dx, dy);

				//OpenCV�е�clone()��ֱ�Ӹ�ֵ�� = �����ᵼ�¹���������
				//Ҳ�����൱��C++������(&)��ʹ��copy���Ż��ȡ�µ�Mat
				//image = temp.clone();
				
				//Ϊ�˲�������ƶ������еĿ�Ҳ��ʾ����
				//copyTo��ʵ��ͼ��roi��������ȷ����
				temp.copyTo(image); 

				//https://blog.csdn.net/yangshengwei230612/article/details/102758136

				rectangle(image, box, Scalar(0, 255, 0), 2, LINE_AA);
				
				imshow("������", image);
			}
		}
	}

}


void QuickDemo::mouse_drawing(Mat& image) {
	namedWindow("������", WINDOW_AUTOSIZE);
	setMouseCallback("������", on_draw, (void*)(&image));
	imshow("������", image);
	temp = image.clone();
}