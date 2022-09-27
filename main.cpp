#if 0

#include<opencv2/opencv.hpp>
#include<iostream>
#include<opencv2/core/utils/logger.hpp>

using namespace std;
using namespace cv;

void color_op();
void color_grayscale();
void color_split();
void my_split(Mat& src);

int main()
{
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);

	//color_op();
	//color_grayscale();
	color_split();
	//my_split();
	return 0;
}

void my_split(Mat& src)
{
	Mat b(src.rows, src.cols, CV_8UC1);
	Mat g(src.rows, src.cols, CV_8UC1);
	Mat r(src.rows, src.cols, CV_8UC1);

	int k = 0;

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			Vec3b& p1 = src.at<Vec3b>(j, i);
			b.at<uchar>(j, i) = p1[0];
			g.at<uchar>(j, i) = p1[1];
			r.at<uchar>(j, i) = p1[2];
		}
	}
	k = k + 1;
	imshow("src", src);
	imshow("b", b);
	imshow("g", g);
	imshow("r", r);
	waitKey();
	destroyAllWindows();
}

void color_split()
{
	Mat src = imread("candies.png", IMREAD_COLOR);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	vector<Mat> bgr_planes;
	split(src, bgr_planes);
	imshow("src", src);
	imshow("B_plane", bgr_planes[0]);
	imshow("G_plane", bgr_planes[1]);
	imshow("R_plabe", bgr_planes[2]);
	waitKey();
	destroyAllWindows();
	my_split(src);
}

void color_grayscale()
{
	Mat src = imread("butterfly.jpg", IMREAD_COLOR);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	Mat dst1;
	cvtColor(src, dst1, COLOR_BGR2GRAY);
	imshow("src", src);
	imshow("dst1", dst1);
	waitKey();
	destroyAllWindows();

	Mat dst2(src.rows, src.cols, CV_8UC1);
	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			Vec3b& p1 = src.at<Vec3b>(j, i);
			uchar& p2 = dst2.at<uchar>(j, i);
			p2 = 0.114*p1[0] + 0.587*p1[1] + 0.299*p1[2];
		}
	}
	//  cvtColor(dst1, dst2, COLOR_GRAY2BGR);   // gray 에서 cvtColor를 통해 칼러 값으로 바꿔줘도 회색이 그대로 나온다.(1byte -> 3byte 로 바뀜), 값은 바뀌나 각 BGR에 적용이 안된다고 한다.
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	waitKey();
	destroyAllWindows();
}

void color_op()
{
	Mat img = imread("butterfly.jpg", IMREAD_COLOR);

	if (img.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Vec3b& pixel = img.at<Vec3b>(0, 0);
	Vec3b* p = &pixel;

	/*
	for (int i = 0; i < img.cols; i++) {
		Vec3b& pixel = img.at<Vec3b>(0, i);
		uchar* p = (uchar*)(&pixel);

		p[0] = 0;
		p[1] = 0;
		p[2] = 255;
	}
	*/

	//   이미지 테두리에 픽셀값 조정해보기
	for (int j = 0; j < 30; j++) {
		for (int i = 0; i < img.cols; i++) {
			Vec3b& pixel = img.at<Vec3b>(j, i);

			pixel[0] = 255;
			pixel[1] = 0;
			pixel[2] = 255;
		}

		for (int i = 0; i < img.cols; i++) {
			Vec3b& pixel = img.at<Vec3b>(img.rows - j - 1, i);

			pixel[0] = 255;
			pixel[1] = 0;
			pixel[2] = 255;
		}

		for (int i = 0; i < img.rows; i++) {
			Vec3b& pixel = img.at<Vec3b>(i, j);

			pixel[0] = 255;
			pixel[1] = 0;
			pixel[2] = 255;
		}

		for (int i = 0; i < img.rows; i++) {
			Vec3b& pixel = img.at<Vec3b>(i, img.cols - j - 1);

			pixel[0] = 255;
			pixel[1] = 0;
			pixel[2] = 255;
		}
	}

	Vec3b* ptr = img.ptr<Vec3b>(0);

	/*
	Vec3b& pixel2 = img.at<Vec3b>(0, 1);
	pixel2[0] = 0;
	pixel2[1] = 0;
	pixel2[2] = 255;

	Vec3b& pixel3 = img.at<Vec3b>(0, 2);
	pixel3[0] = 0;
	pixel3[1] = 0;
	pixel3[2] = 255;

	Vec3b& pixel4 = img.at<Vec3b>(0, 3);
	pixel4[0] = 0;
	pixel4[1] = 0;
	pixel4[2] = 255;

	Vec3b& pixel5 = img.at<Vec3b>(0, 4);
	pixel5[0] = 0;
	pixel5[1] = 0;
	pixel5[2] = 255;
	*/

	//cout << "b1: " << (int)b1 << "g1: " << (int)g1 << "r1: " << (int)r1 << endl;

	imshow("src", img);
	waitKey();
	destroyAllWindows();

	Mat dst(img.rows, img.cols, img.type());

	for (int j = 0; j < img.rows; j++) {
		for (int i = 0; i < img.cols; i++) {
			Vec3b& p1 = img.at<Vec3b>(j, i);
			Vec3b& p2 = dst.at<Vec3b>(j, i);

			p2[0] = 255 - p1[0];
			p2[1] = 255 - p1[1];
			p2[2] = 255 - p1[2];
		}
	}
	imshow("src", img);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();

	img = ~img;
	imshow("src", img);
	waitKey();
	destroyAllWindows();

}

#endif


#if 0
#include <opencv2/opencv.hpp>
#include <iostream>
#include<opencv2/core/utils/logger.hpp>

using namespace cv;
using namespace std;

int main()
{
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);

	Mat src = imread("pepper.bmp", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	vector<Mat> bgr_planes;
	split(src, bgr_planes);

	equalizeHist(bgr_planes[0], bgr_planes[0]);
	equalizeHist(bgr_planes[1], bgr_planes[1]);
	equalizeHist(bgr_planes[2], bgr_planes[2]);

	Mat bgr_dst;
	merge(bgr_planes, bgr_dst);

	imshow("src", src);
	imshow("bgr_dst", bgr_dst);
	waitKey();

	Mat src_ycrcb;

	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);

	vector<Mat> ycrcb_planes;
	split(src_ycrcb, ycrcb_planes);

	equalizeHist(ycrcb_planes[0], ycrcb_planes[0]);

	Mat dst_ycrcb;
	merge(ycrcb_planes, dst_ycrcb);
	Mat dst;
	cvtColor(dst_ycrcb, dst, COLOR_YCrCb2BGR);

	imshow("src", src);
	imshow("dst", dst);
	waitKey();

	return 0;
}

#endif


#if 0
#include <opencv2/opencv.hpp>
#include <iostream>
#include<opencv2/core/utils/logger.hpp>
using namespace std;
using namespace cv;
int lower_hue = 40, upper_hue = 80;
Mat src, src_hsv, mask;
void on_hue_changed(int pos, void *) {
	Scalar lowerb(lower_hue, 100, 0);
	Scalar upperb(upper_hue, 255, 255);
	inRange(src_hsv, lowerb, upperb, mask);
	imshow("mask", mask);
}
int main()
{
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);
	Mat src = imread("candies.png", IMREAD_COLOR);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}
	cvtColor(src, src_hsv, COLOR_BGR2HSV);
	imshow("src", src);
	namedWindow("mask");
	createTrackbar("Lower Hue", "mask", &lower_hue, 179, on_hue_changed);
	createTrackbar("Upper Hue", "mask", &upper_hue, 179, on_hue_changed);
	on_hue_changed(0, 0);
	waitKey();
	destroyAllWindows();
	return 0;
}
#endif

#if 1
#include "opencv2/opencv.hpp"
#include <iostream>
#include<opencv2/core/utils/logger.hpp>

using namespace cv;
using namespace std;

int main()
{
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);
	// Calculate CrCb histogram from a reference image

	Mat ref, ref_ycrcb, mask;
	ref = imread("ref.png", IMREAD_COLOR);
	mask = imread("mask.bmp", IMREAD_GRAYSCALE);
	cvtColor(ref, ref_ycrcb, COLOR_BGR2YCrCb);

	Mat hist;
	int channels[] = { 1, 2 };
	int cr_bins = 128; int cb_bins = 128;
	int histSize[] = { cr_bins, cb_bins };
	float cr_range[] = { 0, 256 };
	float cb_range[] = { 0, 256 };
	const float* ranges[] = { cr_range, cb_range };

	calcHist(&ref_ycrcb, 1, channels, mask, hist, 2, histSize, ranges);
	imshow("ref", ref);
	imshow("mask", mask);
	imshow("hist", hist);
	waitKey();

	// Apply histogram backprojection to an input image

	Mat src, src_ycrcb;
	src = imread("kids.png", IMREAD_COLOR);
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);

	Mat backproj;
	calcBackProject(&src_ycrcb, 1, channels, hist, backproj, ranges, 1, true);

	imshow("src", src);
	imshow("backproj", backproj);
	waitKey();


	return 0;
}

#endif


#if 0
#include <opencv2/opencv.hpp>
#include <iostream>
#include<opencv2/core/utils/logger.hpp>
using namespace std;
using namespace cv;
int main()
{
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);
	Mat ref, ref_ycrcb, mask;
	ref = imread("ref.png", IMREAD_COLOR);
	mask = imread("mask.bmp", IMREAD_GRAYSCALE);
	cvtColor(ref, ref_ycrcb, COLOR_BGR2YCrCb);
	Mat hist;
	int channels[] = { 1, 2 };
	int cr_bins = 128; // bin -> 막대그래프
	int cb_bins = 128;
	int histSize[] = { cr_bins, cb_bins };
	float cr_range[] = { 0, 256 };
	float cb_range[] = { 0, 256 };
	const float* ranges[] = { cr_range, cb_range };
	calcHist(&ref_ycrcb, 1, channels, mask, hist, 2, histSize, ranges);
	imshow("ref", ref);
	imshow("mask", mask);
	imshow("hist", hist);
	waitKey();
	destroyAllWindows();
	return 0;
}
#endif