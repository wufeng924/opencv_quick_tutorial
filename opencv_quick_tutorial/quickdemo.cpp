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
	split(image, mv);  //��ͨ������
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
			if (ep.x <= 521 && ep.y <= 647) {
				temp.copyTo(image);
				imshow("ROI����", image(box));
			}
			else std::cout << "Error region~~~" << std::endl;

			//rectangle(image, box, Scalar(0, 255, 0), 2, LINE_AA);
			//imshow("������", image);
			
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


void QuickDemo::norm_demo(Mat& image) {
	Mat dst;
	std::cout << image.type() << std::endl;  //16 -> CV_8UC3

	image.convertTo(image, CV_32F); //��image������ת���ɸ�����float32λ����  21 -> CV_32F
	std::cout << image.type() << std::endl;

	//���й�һ������
	//����һ��Ҫ���й�һ����ͼƬ  ����������һ����Ҫ�����ͼƬ
	//��������alpha   �����ģ�beta    �����壺��һ������
	normalize(image, dst, 1.0, 0, NORM_MINMAX);
	std::cout << dst.type() << std::endl;
	imshow("ͼ�����ݹ�һ��", dst);

	//CV_8UC3   ԭ��Ϊ 3ͨ����ÿ��ͨ��8λ��UC���޷��ţ�����
	//CV_32FC3  ת���� 3ͨ����ÿ��ͨ��32λ�ĸ���������
}

void QuickDemo::resize_demo(Mat& image) {
	Mat zoomin, zoomout;
	int h = image.rows;
	int w = image.cols;
	resize(image, zoomin, Size(w / 2, h / 2), 0, 0, INTER_LINEAR);
	imshow("zoomin", zoomin);
	resize(image, zoomout, Size(w * 2, h * 2), 0, 0, INTER_LINEAR);
	imshow("zoomout", zoomout);
}

void QuickDemo::flip_demo(Mat& image) {
	Mat dst;
	flip(image, dst, 1);  // -1  0  1 
	imshow("flip", dst);
}

void QuickDemo::rotate_demo(Mat& image) {
	Mat dst, M;
	int h = image.rows;
	int w = image.cols;
	M = getRotationMatrix2D(Point2f(w / 2, h / 2), 45.0, 1.0); //�����ת���� M
	 //����һ��ԭ��ͼ������ĵ�λ�ò���������ת�Ƕ�(��ʱ��)��������ͼ�����С�ķŴ���С

	double cos = abs(M.at<double>(0, 0));//ȡ����ֵ
	double sin = abs(M.at<double>(0, 1));
	/*
	[w'] = [ cos  sin] * [w]
	[h']   [-sin  cos]   [h],
	M = [ cos  sin  0]
		[-sin  cos  0], ����������������ƽ�ƣ�
	*/

	double nw = cos * w + sin * h;//��ת��ͼ����ռ���εĿ�
	double nh = sin * w + cos * h;//��ת��ͼ����ռ���εĸ�

	//���� �µ�����  ����������ƽ�Ƶ���ȷλ���ϣ�
	M.at<double>(0, 2) += (nw / 2 - w / 2);//�����εĿ�� ����ƫ����  ����M�ĵ�һ������ֵ��
	M.at<double>(1, 2) += (nh / 2 - h / 2);//�����εĿ�� ����ƫ����  ����M�ĵڶ�������ֵ��

	warpAffine(image, dst, M, Size(nw, nh), INTER_LINEAR, 0, Scalar(0, 255, 0)); //������ת
	//�����ģ�ԭ��ͼ������ĵ�λ��    �����壺��ֵ��ʽ
	//����������Ե�Ĵ���ʽ          �����ߣ���Ե��ͼ����ɫ
	imshow("��ת��ʾ", dst);
}


void QuickDemo::video_demo(Mat& image) {
	//VideoCapture capture(0); //���õ�������ͷ

	VideoCapture capture("C:/Users/18221/Desktop/code/����������к�����������.mp4");  //��ȡ��Ƶ��ַ

	int frame_width = capture.get(CAP_PROP_FRAME_WIDTH); //��ȡ��Ƶ�Ŀ��
	int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT); //��ȡ��Ƶ�ĸ߶�
	int count = capture.get(CAP_PROP_FRAME_COUNT); //��ȡ��Ƶ�ܵ�֡��
	//fps�Ǻ���������Ƶ������ ��һ���Ӵ��������ͼƬ�������������ٶ�Խ����Խ�ã�
	double fps = capture.get(CAP_PROP_FPS);
	std::cout << "frame width��" << frame_width << std::endl;
	std::cout << "frame height��" << frame_height << std::endl;
	std::cout << "FPS��" << fps << std::endl;
	std::cout << "Number of frame��" << count << std::endl;

	VideoWriter writer("C:/Users/18221/Desktop/Images", capture.get(CAP_PROP_FOURCC), fps, Size(frame_width, frame_height), true);
	//����һ�������ַ	����������ȡͼƬ�ĸ�ʽ(���뷽ʽ)
	//��������ͼƬ��֡��	�����ģ���Ƶ���	�����壺��ԭ����ɫ����һ��
	//��ȫ����������ȥ�鿴��Ƶ�Ƿ񱣴�ɹ�


	Mat frame;
	while (true) {
		capture.read(frame);

		int h = frame.rows;
		int w = frame.cols;
		resize(frame, frame, Size(w / 2, h / 2), 0, 0, INTER_LINEAR);
		flip(frame, frame, 1);
		cvtColor(frame, frame, COLOR_BGR2GRAY);

		if (frame.empty()) {
			break;
		}
		imshow("frame", frame);
		writer.write(frame);
		int c = waitKey(1);
		if (c == 27) {
			break;
		}
	}
	writer.release();
	capture.release(); //�ͷ�����ڴ���Դ
}

void QuickDemo::histogram_demo(Mat& image) {
	//��ͨ������
	std::vector<Mat> bgr_plane;
	split(image, bgr_plane);
	//�����������
	const int channels[1] = { 0 };
	const int bins[1] = { 256 };//�ܹ� 256 ���Ҷȼ���
	float hranges[2] = { 0,255 };//ÿ��ͨ����ȡֵ��Χ�� 0 �� 255
	const float* ranges[1] = { hranges };
	Mat b_hist;
	Mat g_hist;
	Mat r_hist;
	//���� Blue��Green��Red ͨ����ֱ��ͼ
	calcHist(&bgr_plane[0], 1, 0, Mat(), b_hist, 1, bins, ranges);//��һ��ͨ��
	calcHist(&bgr_plane[1], 1, 0, Mat(), g_hist, 1, bins, ranges);
	calcHist(&bgr_plane[2], 1, 0, Mat(), r_hist, 1, bins, ranges);
	//����һ��Ҫ����ֱ��ͼ������					��������1��ʾֻ��һ��ͼ(����ͼ��ĸ�ʽ)
	//����������Ҫͳ��ֱ��ͼ�ĵڼ���ͨ��			�����ģ���ģ��mask������8λ�������ҺͲ���һ�Ĵ�Сһ��
	//�����壺b_hist��ʾֱ��ͼ�����				��������1��ʾά����һά��(���ֱ��ͼ��ά��dims)
	//�����ߣ�ֱ��ͼ��ÿ��ά����ֳɵ��������		�����ˣ�ranges��ʾֱ��ͼ��ȡֵ��Χ(����)

	//��ʾֱ��ͼ
	int hist_w = 512;//���� ������� Ϊ512
	int hist_h = 400;//���� �����߶� Ϊ400
	int bin_w = cvRound((double)hist_w / bins[0]);//ÿ�� bin ռ�Ŀ��
	  //cvRound()�������뷵����ֵ
	Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3);//��������

	//��һ��ֱ��ͼ���ݣ���һ������Сһ�µķ�Χ�ڣ�
	//histImage.rows��Ϊ�˲�����������ɵĸ߶ȷ�Χ
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	//����һ��Ҫ���й�һ����ͼƬ		����������һ����Ҫ�����ͼƬ
	//��������alpha			�����ģ�beta			�����壺��һ������

	//����ֱ��ͼ����
	for (int i = 1; i < bins[0]; i++) {//ÿ��binռ2�����ص�λ��
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, 3, 0);
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, 3, 0);
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, 3, 0);
		//��ǰһ��λ�õ���ǰλ������һ����
	}
	//��ʾֱ��ͼ
	namedWindow("Histogram Demo", WINDOW_AUTOSIZE);
	imshow("Histogram Demo", histImage);
}


void QuickDemo::histogram_2d_demo(Mat& image) {
	//2Dֱ��ͼ
	Mat hsv, hs_hist;
	cvtColor(image, hsv, COLOR_BGR2HSV);//�Ȱ�RGBɫ�ʿռ�ת����hsv�Ŀռ���
	int hbins = 30, sbins = 32;
	int hist_bins[] = { hbins, sbins };//h��s������ά����ֳɵ� �������
	float h_range[] = { 0,180 };//h��ȡֵ��Χ
	float s_range[] = { 0,256 };//s��ȡֵ��Χ
	const float* hs_ranges[] = { h_range, s_range };
	int hs_channels[] = { 0,1 };
	//����ͨ����ֱ��ͼ
	calcHist(&hsv, 1, hs_channels, Mat(), hs_hist, 2, hist_bins, hs_ranges, true, false);
	//����һ��Ҫ����ֱ��ͼ�����ݲ�������1��ʾֻ��һ��ͼ(����ͼ��ĸ�ʽ)
	//����������Ҫͳ��ֱ��ͼ�ĵڼ���ͨ��(ǰ����)�����ģ���ģ��mask������8λ�������ҺͲ���һ�Ĵ�Сһ��
	//�����壺b_hist��ʾֱ��ͼ�������������2��ʾά���Ƕ�ά��(���ֱ��ͼ��ά��dims)
	//�����ߣ�ֱ��ͼ��ÿ��ά����ֳɵ�������������ˣ�hs_ranges��ʾֱ��ͼ��ȡֵ��Χ(����)
	//�����ţ��Ƿ�Եõ���ֱ��ͼ���й�һ���������ʮ���ڶ��ͼ��ʱ���Ƿ��ۼƼ�������ֵ�ĸ���
	double maxVal = 0;
	minMaxLoc(hs_hist, 0, &maxVal, 0, 0);//Ѱ�����ֵ����Сֵ����λ�ã��������ҵ����ֵ��
	//����һ�����뵥ͨ��������
	//��������������Сֵ��ָ����������������ֵ��ָ��
	//�����ģ�������Сֵλ�õ�ָ������壺�������ֵλ�õ�ָ��
	int scale = 10;
	Mat hist2d_image = Mat::zeros(sbins * scale, hbins * scale, CV_8UC3);//�����հ�ͼ��
	for (int h = 0; h < hbins; h++) {
		for (int s = 0; s < sbins; s++) {
			float binVal = hs_hist.at<float>(h, s);
			int intensity = cvRound(binVal * 255 / maxVal);
			rectangle(hist2d_image, Point(h * scale, s * scale),
				Point((h + 1) * scale - 1, (s + 1) * scale - 1), Scalar::all(intensity), -1);
		}
	}
	//��ʾֱ��ͼ
	//applyColorMap(hist2d_image, hist2d_image, COLORMAP_JET);//����αɫ��ͼ��
	namedWindow("H-S Histogram", WINDOW_AUTOSIZE);
	imshow("H-S Histogram", hist2d_image);
	//imwrite("F:/�ļ���/C++/OPENCV4����ѧϰ/ͼ/hist_2d.png", hist2d_image);
}

void QuickDemo::histogram_eq_demo(Mat& image) {
	//Mat gray;
	//cvtColor(image, gray, COLOR_BGR2GRAY);
	//imshow("gray", gray);
	//Mat dst;
	//equalizeHist(gray, dst);
	//imshow("ֱ��ͼ���⻯��ʾ", dst);
	////ֱ��ͼ���⻯ (Ŀ���ǶԱȶ����죬�� �ԱȶȻ��ǿ)
	////��;������ͼ����ǿ��������⣬����ң��(����ͼ������)��
	////opencv�У����⻯��ͼ��ֻ֧�ֵ�ͨ��

	//����ͨ����ͼ�����ֱ��ͼ���⻯
	Mat imageRGB[3];
	split(image, imageRGB);
	for (int i = 0; i < 3; i++)
	{
		equalizeHist(imageRGB[i], imageRGB[i]);
	}
	merge(imageRGB, 3, image);
	imshow("ֱ��ͼ���⻯ͼ����ǿЧ��", image);

}


void QuickDemo::blur_demo(Mat& image) {
	Mat dst;
	blur(image, dst, Size(5, 5), Point(-1, -1));
	//���ͼ����ģ�����Ҿ���˳ߴ�Խ����Խģ��
	//������������˵Ĵ�С	�����ģ��������ʼ��
	//Point(-1, -1)��Ĭ��ȡ�˵�����
	//�������У�
	//Size(15, 1) ���һζ���ģ��  1��15��
	//Size(1, 15) ���»ζ���ģ��  1��15��
	imshow("ͼ��������", dst);
}

void QuickDemo::gaussian_blur_demo(Mat& image) {
	Mat dst;
	GaussianBlur(image, dst, Size(5, 5), 15);
	//��˹kernel����ֵ���������ԽԶֵԽС
	//����������˹����Ĵ�С��������������
	// Error: Assertion failed (ksize.width > 0 && ksize.width % 2 == 1 && 
	//			ksize.height > 0 && ksize.height % 2 == 1) in cv::createGaussianKernels 
	//�����ģ�sigmaX �� sigmaY Ϊ15 
	//���������Ķ� ֵԽ����Խģ�����Ҳ����ĵ�Ӱ�������
	imshow("��˹ģ������", dst);
}

void QuickDemo::bifilter_demo(Mat& image) {
	Mat dst;
	bilateralFilter(image, dst, 0, 100, 10);
	//���ǿռ��ٽ���Ϣ����ɫ������Ϣ�����˳�������ƽ��ͼ���ͬʱ����������Ե����
	//����ĥƤ����
	imshow("˫��ģ��", dst);
}

void QuickDemo::face_detection_demo() {
	//����Ȩ���ļ�
	std::string root_dir = "C:/Users/18221/Desktop/Images/face_detector/";
	//����һ�������ļ�����ȡ���ѧϰTensorflowģ���Լ������ļ���
	//pb�ļ���������ģ�ͣ�pbtxt�������ļ�
	dnn::Net net = dnn::readNetFromTensorflow(root_dir + "opencv_face_detector_uint8.pb", root_dir + "opencv_face_detector.pbtxt");

	VideoCapture capture(0);//������Ƶ
	//VideoCapture capture("E:/2021.9.26����/ͼƬ/Camera Roll/�����ز�.mp4");//������Ƶ
	Mat frame;//����һ����ֵ���� frame
	while (true) {
		capture.read(frame);
		flip(frame, frame, 1);// 1 ���ҷ�ת y�Գ� ������
		if (frame.empty())//�������ʧ��
		{
			break;//����ƵΪ�գ�����������
		}
		//��ģ��
		Mat blob = dnn::blobFromImage(frame, 1.0, Size(300, 300), Scalar(104, 177, 123), false, false);//��ͼ�����Ԥ����
		net.setInput(blob);//׼�����ݣ�blob���� NCHW n���ٸ� cͨ���� h�߶� w���
		//��ȡ����
		Mat probs = net.forward();//��ȡ���������ݣ��������
		
		Mat detectionMat(probs.size[2], probs.size[3], CV_32F, probs.ptr<float>());//����Matͼ��

		std::cout << detectionMat << std::endl;
		/*
		��������ó���blob��
		��һ��ά�ȣ��ж�����ͼ��ÿ��ͼ�и���ţ�
		ά�ȶ���image��Ӧ�ڼ����εڼ���ͼ��
		ά�������ж��ٸ���
		ά���ģ�ÿ������7��ֵ����7��
		*/
		//�������
		for (int i = 0; i < detectionMat.rows; i++) {
			float confidence = detectionMat.at<float>(i, 2); //���Ŷ�
			if (confidence > 0.5) {//����0.5��������
			//��ȡ�������꣨��3��4��5��6������
				//c++����ǿ��ת��		static_cast<DataType>(Value)
				//c���				(DataType)Value
				//Ԥ��׼c++			DataType(Value)
				int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * frame.cols);
				int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * frame.rows);
				int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * frame.cols);
				int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * frame.rows);
				Rect box(x1, y1, x2 - x1, y2 - y1);
				rectangle(frame, box, Scalar(0, 255, 0), 2, 8, 0);
			}
		}
		imshow("���������ʾ", frame);
		int c = waitKey(1);//�ȴ�10ms��1s = 1000ms��������Ƶ������1
		if (c == 27) {//�� esc �˳�Ӧ�ó���
			break;
		}
	}

}

