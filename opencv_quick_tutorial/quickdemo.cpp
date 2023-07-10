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

void QuickDemo::channels_demo(Mat& image) {
	std::vector<Mat> mv; 
	split(image, mv);  //三通道分离
	imshow("Red", mv[0]);
	imshow("Green", mv[1]);
	imshow("Blue", mv[2]);

	Mat dst;
	mv[0] = 0;
	mv[2] = 0;
	merge(mv, dst);
	imshow("绿色", dst);

	int from_to[] = { 0,2,1,1,2,0 };
	mixChannels(&image, 1, &dst, 1, from_to, 3);
	imshow("通道混合", dst);
	imshow("original image", image);
}

void QuickDemo::inrange_demo(Mat& image) {
	Mat hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	Mat mask;
	inRange(hsv, Scalar(100, 43, 46), Scalar(124, 255, 255), mask);
	//imshow("mask", mask);  //msck为白底

	Mat redback = Mat::zeros(image.size(), image.type());
	redback = Scalar(40, 40, 200); //红色背景
	bitwise_not(mask, mask); //mask为黑底
	imshow("mask", mask);
	image.copyTo(redback, mask); //将mask中不为0部分(白色像素点)对应的原图 拷贝到 redback上，mask通过inRange得到
	imshow("roi区域提取", redback);
}

void QuickDemo::pixel_statistic_demo(Mat& image) {
	double minv, maxv;
	Point minLoc, maxLoc; //定义地址
	std::vector<Mat> mv; //可存放Mat类型的容器
	split(image, mv); //将多通道 拆分成 单通道（通道分离)
	for (int i = 0; i < mv.size(); i++) {

		//分别打印各个通道的数值
		minMaxLoc(mv[i], &minv, &maxv, &minLoc, &maxLoc, Mat());
		//求出图像的最大值和最小值及其位置
		//参数一：输入单通道的数组
		//参数二：返回最小值的指针
		//参数三：返回最大值的指针
		//参数四：返回最小值位置的指针
		//参数五：返回最大值位置的指针
		std::cout << "No.channels:" << i << "  minvalue:" << minv << "  maxvalue:" << maxv << std::endl;
		
	}

	Mat mean, stddev;
	meanStdDev(image, mean, stddev); //求出图像的均值 、方差
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
	addWeighted(image, 0.7, bg, 0.3, 0, dst); //融合两张图 image和bg
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
	RNG rng(12345); //产生随机数（12345为随机数的种子，默认的
	while (true) {
		int c = waitKey(100);
		if (c == 27) {
			break;
		}
		int x1 = rng.uniform(0, w), y1 = rng.uniform(0, h);
		int x2 = rng.uniform(0, w), y2 = rng.uniform(0, h);
		int r = rng.uniform(0, 255), g = rng.uniform(0, 255), b = rng.uniform(0, 255);
		line(canvas, Point(x1, y1), Point(x2, y2), Scalar(r, g, b), 4, LINE_AA, 0);
		imshow("随机绘制", canvas);
	}
}

void QuickDemo::polyline_drawing() {
	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
	Point p1(150, 100);//第一个点的坐标
	Point p2(350, 200);//  二
	Point p3(240, 300);//  三
	Point p4(150, 300);//  四
	Point p5(50, 200);//  五
	std::vector<Point> pts;//搞一个容器，用来装 点
	pts.push_back(p1);//将点放进容器内
	pts.push_back(p2);//因 未初始化数组容量，所以要用 push_back 操作
	pts.push_back(p3);//若 已初始化，可以用 数组下标 来操作
	pts.push_back(p4);
	pts.push_back(p5);
	//fillPoly(canvas, pts, Scalar(0, 255, 0), LINE_AA); //填充多边形
	//polylines(canvas, pts, true, Scalar(0, 0, 255), 2, LINE_AA); //绘制多边形
	//imshow("多边形绘制", canvas);

	std::vector<std::vector<Point>> contours; //搞一个容器，用来装 多边形的点集
	contours.push_back(pts); //将一个多边形的点集放进容器内，作为一个元素
	drawContours(canvas, contours, -1, Scalar(0, 0, 255), -1);
	//参数倒1：<0表示填充，>0表示线宽
	//参数二：多边形的点集
	//参数三：-1为绘制全部的多边形；0为绘制第一个，1为绘制第二个，以此类推
	imshow("多边形填充", canvas);
}


Point sp(-1, -1);
Point ep(-1, -1);
Mat temp;
static void on_draw(int event, int x, int y, int flags, void* userdata) {
	Mat image = *((Mat*)userdata);
	//若鼠标的左键按下
	if (event == EVENT_LBUTTONDOWN) {
		//此时鼠标的起始位置坐标
		sp.x = x;
		sp.y = y;
		std::cout << "Start Point : " << sp << std::endl;
	}
	//若鼠标的左键抬起
	else if (event == EVENT_LBUTTONUP) {
		//此时鼠标的结束位置坐标
		ep.x = x;
		ep.y = y;
		int dx = ep.x - sp.x;
		int dy = ep.y - sp.y;
		if (dx > 0 && dy > 0) {
			Rect box(sp.x, sp.y, dx, dy);
			if (ep.x <= 521 && ep.y <= 647) {
				temp.copyTo(image);
				imshow("ROI区域", image(box));
			}
			else std::cout << "Error region~~~" << std::endl;

			//rectangle(image, box, Scalar(0, 255, 0), 2, LINE_AA);
			//imshow("鼠标绘制", image);
			
			//复位，为下一次绘制做准备
			sp.x = -1;
			sp.y = -1;
		}
	}
	//若鼠标有移动过
	else if (event == EVENT_MOUSEMOVE) {
		if (sp.x > 0 && sp.y > 0) {
			ep.x = x;
			ep.y = y;
			int dx = ep.x - sp.x;
			int dy = ep.y - sp.y;
			if (dx > 0 && dy > 0) {
				Rect box(sp.x, sp.y, dx, dy);

				//OpenCV中的clone()和直接赋值（ = ）都会导致共享数据区
				//也就是相当于C++的引用(&)，使用copy，才会获取新的Mat
				//image = temp.clone();
				
				//为了不将鼠标移动过程中的框也显示出来
				//copyTo是实现图像roi操作的正确方法
				temp.copyTo(image); 

				//https://blog.csdn.net/yangshengwei230612/article/details/102758136

				rectangle(image, box, Scalar(0, 255, 0), 2, LINE_AA);
				
				imshow("鼠标绘制", image);
			}
		}
	}

}


void QuickDemo::mouse_drawing(Mat& image) {
	namedWindow("鼠标绘制", WINDOW_AUTOSIZE);
	setMouseCallback("鼠标绘制", on_draw, (void*)(&image));
	imshow("鼠标绘制", image);
	temp = image.clone();
}


void QuickDemo::norm_demo(Mat& image) {
	Mat dst;
	std::cout << image.type() << std::endl;  //16 -> CV_8UC3

	image.convertTo(image, CV_32F); //将image的数据转换成浮点型float32位数据  21 -> CV_32F
	std::cout << image.type() << std::endl;

	//进行归一化操作
	//参数一：要进行归一化的图片  参数二：归一化后要输出的图片
	//参数三：alpha   参数四：beta    参数五：归一化方法
	normalize(image, dst, 1.0, 0, NORM_MINMAX);
	std::cout << dst.type() << std::endl;
	imshow("图像数据归一化", dst);

	//CV_8UC3   原本为 3通道，每个通道8位的UC（无符号）类型
	//CV_32FC3  转换后 3通道，每个通道32位的浮点数类型
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
	M = getRotationMatrix2D(Point2f(w / 2, h / 2), 45.0, 1.0); //获得旋转矩阵 M
	 //参数一：原来图像的中心点位置参数二：旋转角度(逆时针)参数三：图像本身大小的放大缩小

	double cos = abs(M.at<double>(0, 0));//取绝对值
	double sin = abs(M.at<double>(0, 1));
	/*
	[w'] = [ cos  sin] * [w]
	[h']   [-sin  cos]   [h],
	M = [ cos  sin  0]
		[-sin  cos  0], （第三列用来控制平移）
	*/

	double nw = cos * w + sin * h;//旋转后图像所占矩形的宽
	double nh = sin * w + cos * h;//旋转后图像所占矩形的高

	//更新 新的中心  （将新中心平移到正确位置上）
	M.at<double>(0, 2) += (nw / 2 - w / 2);//将矩形的宽高 加上偏差量  （新M的第一列最后的值）
	M.at<double>(1, 2) += (nh / 2 - h / 2);//将矩形的宽高 加上偏差量  （新M的第二列最后的值）

	warpAffine(image, dst, M, Size(nw, nh), INTER_LINEAR, 0, Scalar(0, 255, 0)); //进行旋转
	//参数四：原来图像的中心点位置    参数五：插值方式
	//参数六：边缘的处理方式          参数七：边缘底图的颜色
	imshow("旋转演示", dst);
}


void QuickDemo::video_demo(Mat& image) {
	//VideoCapture capture(0); //调用电脑摄像头

	VideoCapture capture("C:/Users/18221/Desktop/code/漫威：这个男孩，他长大了.mp4");  //读取视频地址

	int frame_width = capture.get(CAP_PROP_FRAME_WIDTH); //获取视频的宽度
	int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT); //获取视频的高度
	int count = capture.get(CAP_PROP_FRAME_COUNT); //获取视频总的帧数
	//fps是衡量处理视频的能力 （一秒钟处理多少张图片的能力，处理速度越快则越好）
	double fps = capture.get(CAP_PROP_FPS);
	std::cout << "frame width：" << frame_width << std::endl;
	std::cout << "frame height：" << frame_height << std::endl;
	std::cout << "FPS：" << fps << std::endl;
	std::cout << "Number of frame：" << count << std::endl;

	VideoWriter writer("C:/Users/18221/Desktop/Images", capture.get(CAP_PROP_FOURCC), fps, Size(frame_width, frame_height), true);
	//参数一：保存地址	参数二：获取图片的格式(编码方式)
	//参数三：图片的帧数	参数四：视频宽高	参数五：与原来颜色保持一致
	//等全部运行完再去查看视频是否保存成功


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
	capture.release(); //释放相机内存资源
}

void QuickDemo::histogram_demo(Mat& image) {
	//三通道分离
	std::vector<Mat> bgr_plane;
	split(image, bgr_plane);
	//定义参数变量
	const int channels[1] = { 0 };
	const int bins[1] = { 256 };//总共 256 个灰度级别
	float hranges[2] = { 0,255 };//每个通道的取值范围是 0 到 255
	const float* ranges[1] = { hranges };
	Mat b_hist;
	Mat g_hist;
	Mat r_hist;
	//计算 Blue，Green，Red 通道的直方图
	calcHist(&bgr_plane[0], 1, 0, Mat(), b_hist, 1, bins, ranges);//第一个通道
	calcHist(&bgr_plane[1], 1, 0, Mat(), g_hist, 1, bins, ranges);
	calcHist(&bgr_plane[2], 1, 0, Mat(), r_hist, 1, bins, ranges);
	//参数一：要计算直方图的数据					参数二：1表示只有一张图(输入图像的格式)
	//参数三：需要统计直方图的第几个通道			参数四：掩模，mask必须是8位的数组且和参数一的大小一致
	//参数五：b_hist表示直方图的输出				参数六：1表示维度是一维的(输出直方图的维度dims)
	//参数七：直方图中每个维度需分成的区间个数		参数八：ranges表示直方图的取值范围(区间)

	//显示直方图
	int hist_w = 512;//设置 画布宽度 为512
	int hist_h = 400;//设置 画布高度 为400
	int bin_w = cvRound((double)hist_w / bins[0]);//每个 bin 占的宽度
	  //cvRound()四舍五入返回数值
	Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3);//创建画布

	//归一化直方图数据（归一化到大小一致的范围内）
	//histImage.rows是为了不超出画布许可的高度范围
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	//参数一：要进行归一化的图片		参数二：归一化后要输出的图片
	//参数三：alpha			参数四：beta			参数五：归一化方法

	//绘制直方图曲线
	for (int i = 1; i < bins[0]; i++) {//每个bin占2个像素的位置
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, 3, 0);
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, 3, 0);
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, 3, 0);
		//从前一个位置到当前位置连上一条线
	}
	//显示直方图
	namedWindow("Histogram Demo", WINDOW_AUTOSIZE);
	imshow("Histogram Demo", histImage);
}


void QuickDemo::histogram_2d_demo(Mat& image) {
	//2D直方图
	Mat hsv, hs_hist;
	cvtColor(image, hsv, COLOR_BGR2HSV);//先把RGB色彩空间转换到hsv的空间中
	int hbins = 30, sbins = 32;
	int hist_bins[] = { hbins, sbins };//h和s这两个维度需分成的 区间个数
	float h_range[] = { 0,180 };//h的取值范围
	float s_range[] = { 0,256 };//s的取值范围
	const float* hs_ranges[] = { h_range, s_range };
	int hs_channels[] = { 0,1 };
	//计算通道的直方图
	calcHist(&hsv, 1, hs_channels, Mat(), hs_hist, 2, hist_bins, hs_ranges, true, false);
	//参数一：要计算直方图的数据参数二：1表示只有一张图(输入图像的格式)
	//参数三：需要统计直方图的第几个通道(前两个)参数四：掩模，mask必须是8位的数组且和参数一的大小一致
	//参数五：b_hist表示直方图的输出参数六：2表示维度是二维的(输出直方图的维度dims)
	//参数七：直方图中每个维度需分成的区间个数参数八：hs_ranges表示直方图的取值范围(区间)
	//参数九：是否对得到的直方图进行归一化处理参数十：在多个图像时，是否累计计算像素值的个数
	double maxVal = 0;
	minMaxLoc(hs_hist, 0, &maxVal, 0, 0);//寻找最大值和最小值及其位置（这里先找到最大值）
	//参数一：输入单通道的数组
	//参数二：返回最小值的指针参数三：返回最大值的指针
	//参数四：返回最小值位置的指针参数五：返回最大值位置的指针
	int scale = 10;
	Mat hist2d_image = Mat::zeros(sbins * scale, hbins * scale, CV_8UC3);//创建空白图像
	for (int h = 0; h < hbins; h++) {
		for (int s = 0; s < sbins; s++) {
			float binVal = hs_hist.at<float>(h, s);
			int intensity = cvRound(binVal * 255 / maxVal);
			rectangle(hist2d_image, Point(h * scale, s * scale),
				Point((h + 1) * scale - 1, (s + 1) * scale - 1), Scalar::all(intensity), -1);
		}
	}
	//显示直方图
	//applyColorMap(hist2d_image, hist2d_image, COLORMAP_JET);//产生伪色彩图像
	namedWindow("H-S Histogram", WINDOW_AUTOSIZE);
	imshow("H-S Histogram", hist2d_image);
	//imwrite("F:/文件夹/C++/OPENCV4入门学习/图/hist_2d.png", hist2d_image);
}

void QuickDemo::histogram_eq_demo(Mat& image) {
	//Mat gray;
	//cvtColor(image, gray, COLOR_BGR2GRAY);
	//imshow("gray", gray);
	//Mat dst;
	//equalizeHist(gray, dst);
	//imshow("直方图均衡化演示", dst);
	////直方图均衡化 (目的是对比度拉伸，即 对比度会更强)
	////用途：用于图像增强，人脸检测，卫星遥感(提升图像质量)。
	////opencv中，均衡化的图像只支持单通道

	//对三通道的图像进行直方图均衡化
	Mat imageRGB[3];
	split(image, imageRGB);
	for (int i = 0; i < 3; i++)
	{
		equalizeHist(imageRGB[i], imageRGB[i]);
	}
	merge(imageRGB, 3, image);
	imshow("直方图均衡化图像增强效果", image);

}


void QuickDemo::blur_demo(Mat& image) {
	Mat dst;
	blur(image, dst, Size(5, 5), Point(-1, -1));
	//输出图像会变模糊，且卷积核尺寸越大则越模糊
	//参数三：卷积核的大小	参数四：卷积的起始点
	//Point(-1, -1)则默认取核的中心
	//参数三中：
	//Size(15, 1) 左右晃动的模糊  1行15列
	//Size(1, 15) 上下晃动的模糊  1列15行
	imshow("图像卷积操作", dst);
}

void QuickDemo::gaussian_blur_demo(Mat& image) {
	Mat dst;
	GaussianBlur(image, dst, Size(5, 5), 15);
	//高斯kernel中心值最大，离中心越远值越小
	//参数三：高斯矩阵的大小（正数且奇数）
	// Error: Assertion failed (ksize.width > 0 && ksize.width % 2 == 1 && 
	//			ksize.height > 0 && ksize.height % 2 == 1) in cv::createGaussianKernels 
	//参数四：sigmaX 和 sigmaY 为15 
	//参数三和四都 值越大则越模糊，且参数四的影响更明显
	imshow("高斯模糊操作", dst);
}

void QuickDemo::bifilter_demo(Mat& image) {
	Mat dst;
	bilateralFilter(image, dst, 0, 100, 10);
	//考虑空间临近信息与颜色相似信息，在滤除噪声、平滑图像的同时，又做到边缘保存
	//可做磨皮操作
	imshow("双边模糊", dst);
}

void QuickDemo::face_detection_demo() {
	//加载权重文件
	std::string root_dir = "C:/Users/18221/Desktop/Images/face_detector/";
	//读出一个网络文件（读取深度学习Tensorflow模型以及配置文件）
	//pb文件就是他的模型；pbtxt是配置文件
	dnn::Net net = dnn::readNetFromTensorflow(root_dir + "opencv_face_detector_uint8.pb", root_dir + "opencv_face_detector.pbtxt");

	VideoCapture capture(0);//加载视频
	//VideoCapture capture("E:/2021.9.26备份/图片/Camera Roll/人脸素材.mp4");//加载视频
	Mat frame;//定义一个二值化的 frame
	while (true) {
		capture.read(frame);
		flip(frame, frame, 1);// 1 左右翻转 y对称 （镜像）
		if (frame.empty())//如果读入失败
		{
			break;//若视频为空，则跳出操作
		}
		//读模型
		Mat blob = dnn::blobFromImage(frame, 1.0, Size(300, 300), Scalar(104, 177, 123), false, false);//对图像进行预处理
		net.setInput(blob);//准备数据（blob就是 NCHW n多少个 c通道数 h高度 w宽度
		//获取数据
		Mat probs = net.forward();//获取推理后的数据（完成推理）
		
		Mat detectionMat(probs.size[2], probs.size[3], CV_32F, probs.ptr<float>());//构建Mat图像

		std::cout << detectionMat << std::endl;
		/*
		输出：（得出的blob）
		第一个维度：有多少张图像，每张图有个编号；
		维度二：image对应第几批次第几张图；
		维度三：有多少个框
		维度四：每个框有7个值，有7列
		*/
		//解析结果
		for (int i = 0; i < detectionMat.rows; i++) {
			float confidence = detectionMat.at<float>(i, 2); //置信度
			if (confidence > 0.5) {//大于0.5就是人脸
			//获取矩形坐标（第3，4，5，6参数）
				//c++类型强制转换		static_cast<DataType>(Value)
				//c风格				(DataType)Value
				//预标准c++			DataType(Value)
				int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * frame.cols);
				int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * frame.rows);
				int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * frame.cols);
				int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * frame.rows);
				Rect box(x1, y1, x2 - x1, y2 - y1);
				rectangle(frame, box, Scalar(0, 255, 0), 2, 8, 0);
			}
		}
		imshow("人脸检测演示", frame);
		int c = waitKey(1);//等待10ms（1s = 1000ms），做视频处理都是1
		if (c == 27) {//按 esc 退出应用程序
			break;
		}
	}

}

