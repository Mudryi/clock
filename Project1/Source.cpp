#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <map>
using namespace cv;
using namespace std;

char window_name[] = "Watch";
int lines = 1;
int dilation_size = 1;


struct Right_Left_contour_sorter // 'less' for contours
{
	bool operator ()(const vector<Point>& a, const vector<Point> & b)
	{
		Rect ra(boundingRect(a));
		Rect rb(boundingRect(b));
		return (ra.x < rb.x);
	}
};

bool compareContourAreas(std::vector<cv::Point> contour1, std::vector<cv::Point> contour2) {
	double i = fabs(contourArea(cv::Mat(contour1)));
	double j = fabs(contourArea(cv::Mat(contour2)));
	return (i > j);
}

void removeSmallContours(std::vector<std::vector<cv::Point>>& contours, vector<cv::Vec4i>& hierarchy)
{
	int i = 0;
	for (auto it = contours.begin(); it != contours.end();) {

		const auto& contour = *it;

		const bool isLarge = (cv::boundingRect(contour).area() > 300);

		if (isLarge) {
			++it;
			++i;
		}
		else {
			it = contours.erase(it);
			hierarchy.erase(hierarchy.begin() + i);
		}
	}
}
vector<Rect> getparts(Mat C)
{
	Rect upper;
	upper.x = 0;
	upper.y = 0;
	upper.width = C.cols;
	upper.height = int(C.rows*0.095);

	Rect upper_left;
	upper_left.x = 0;
	upper_left.y = 0;
	upper_left.width = int(C.cols*0.35);
	upper_left.height = int(C.rows / 2);

	Rect upper_rigth;
	upper_rigth.x = C.cols - int(C.cols*0.4);
	upper_rigth.y = 0;
	upper_rigth.width = int(C.cols*0.35);
	upper_rigth.height = int(C.rows / 2*0.8);

	Rect center;
	center.x = 0;
	center.y = int(C.rows / 2) - int(C.rows *0.03);
	center.width = C.cols;
	center.height = int(C.rows *0.1);

	Rect down_left;
	down_left.x = 0;
	down_left.y = int(C.rows / 2);
	down_left.width = int(C.cols*0.35);
	down_left.height = C.rows - int(C.rows / 2);

	Rect down_right;
	down_right.x = C.cols - int(C.cols*0.4);
	down_right.y = int(C.rows / 2);
	down_right.width = int(C.cols*0.35);
	down_right.height = int(C.rows / 2 * 0.8);

	Rect down;
	down.x = 0;
	down.y = C.rows - int(C.rows*0.095);
	down.width = C.cols;
	down.height = int(C.rows*0.095);
	vector<Rect> parts = { upper,upper_left,upper_rigth,center,down_left,down_right,down };
	return parts;
}



int main(int argc, char** argv)
{

	int hours, minutes;

	Mat src, src_black, src_gray, edges;
	src = imread("./Images/watchtest10.jpg");

	std::map<vector<int>, int> numbers;
	numbers[{1, 1, 1, 0, 1, 1, 1}] = 0;
	numbers[{0, 0, 1, 0, 0, 1, 0}] = 1;
	numbers[{1, 0, 1, 1, 1, 0, 1}] = 2;
	numbers[{1, 0, 1, 1, 0, 1, 1}] = 3;
	numbers[{0, 1, 1, 1, 0, 1, 0}] = 4;
	numbers[{1, 1, 0, 1, 0, 1, 1}] = 5;
	numbers[{1, 1, 0, 1, 1, 1, 1}] = 6;
	numbers[{1, 0, 1, 0, 0, 1, 0}] = 7;
	numbers[{1, 1, 1, 1, 1, 1, 1}] = 8;
	numbers[{1, 1, 1, 1, 0, 1, 1}] = 9;

	std::map<int, vector<int>> numbersBin;
	numbersBin[0] = { 1, 1, 1, 0, 1, 1, 1 };
	numbersBin[1] = { 0, 0, 1, 0, 0, 1, 0 };
	numbersBin[2] = { 1, 0, 1, 1, 1, 0, 1 };
	numbersBin[3] = { 1, 0, 1, 1, 0, 1, 1 };
	numbersBin[4] = { 0, 1, 1, 1, 0, 1, 0 };
	numbersBin[5] = { 1, 1, 0, 1, 0, 1, 1 };
	numbersBin[6] = { 1, 1, 0, 1, 1, 1, 1 };
	numbersBin[7] = { 1, 0, 1, 0, 0, 1, 0 };
	numbersBin[8] = { 1, 1, 1, 1, 1, 1, 1 };
	numbersBin[9] = { 1, 1, 1, 1, 0, 1, 1 };

	imshow("Video", src);
	waitKey(0);

	resize(src, src, Size(640, 480));
	cv::cvtColor(src, src_black, COLOR_BGR2GRAY);
	cv::GaussianBlur(src_black, src_gray, cv::Size(7, 7), 0);
	cv::Canny(src_gray, edges, 50, 200);

	std::vector<std::vector<cv::Point>> contours1;
	std::vector<cv::Vec4i> hierarchy1;

	findContours(edges, contours1, hierarchy1, cv::RetrievalModes::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	removeSmallContours(contours1, hierarchy1);
	sort(contours1.begin(), contours1.end(), compareContourAreas);



	vector<Point> ekran;
	for (auto i = 0; i < contours1.size(); i++) {
		double perimetr = arcLength(contours1[i], true);
		approxPolyDP(contours1[i], contours1[i], 0.05*perimetr, true);
		if (contourArea(contours1[i]) / (minAreaRect(contours1[i]).size.height*minAreaRect(contours1[i]).size.width) > 0.8) {
			ekran = contours1[i];
			break;
		}
	}



	Mat clock = src(boundingRect(ekran));
	imshow("Video", clock);
	waitKey(0);
	cvtColor(clock, clock, COLOR_BGR2GRAY);
	//threshold(clock, clock, 55, 255, cv::THRESH_BINARY);
	threshold(clock, clock, 90, 255, cv::THRESH_BINARY);
	morphologyEx(clock, clock, MORPH_DILATE, cv::getStructuringElement(MORPH_RECT, cv::Size(3, 3)));
	morphologyEx(clock, clock, MORPH_OPEN, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3)));


	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	Mat A, DD = cv::Mat::zeros(clock.size(), CV_8UC3);

	findContours(clock, contours, hierarchy, cv::RetrievalModes::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	for (size_t i = 0; i < contours.size();)
	{
		cv::Scalar color = cv::Scalar(0, 255, 0);
		drawContours(A, contours, (int)i, color, 2, cv::LINE_4, hierarchy, 0, cv::Point());
		if (hierarchy[i][0] == -1) {
			contours.erase(contours.begin() + i);
			hierarchy.erase(hierarchy.begin() + i);
		}
		else
			i++;
	}

	for (size_t i = 0; i < contours.size(); i++)
	{
		cv::Scalar color = cv::Scalar(0, 255, 0);
		drawContours(DD, contours, (int)i, color, 2, cv::LINE_4, hierarchy, 0, cv::Point());
	}


	vector<Rect> boundRect(contours.size());
	Mat B = cv::Mat::zeros(clock.size(), CV_8UC3);

	for (size_t i = 0; i < contours.size();)
	{
		boundRect[i] = boundingRect(contours[i]);
		if (boundRect[i].height < 25 || boundRect[i].height>120 || boundRect[i].width > 80)
			contours.erase(contours.begin() + i);
		else i++;
	}

	sort(contours.begin(), contours.end(), Right_Left_contour_sorter());



	Mat AA = cv::Mat::zeros(src.size(), CV_8UC3);

	for (size_t i = 0; i < contours.size(); i++)
	{
		cv::Scalar color = cv::Scalar(0, 255, 0);
		drawContours(AA, contours, (int)i, color, 2, cv::LINE_4, hierarchy, 0, cv::Point());
	}

	for (size_t i = 0; i < contours.size(); i++)
	{
		cv::Scalar color = cv::Scalar(0, 0, 255);
		boundRect[i] = boundingRect(contours[i]);
		rectangle(B, boundRect[i].tl(), boundRect[i].br(), color, 2);
	}



	vector<int> time;
	for (int i = 0; i < contours.size(); i++) {

		Mat C = clock(boundingRect(contours[i]));
		Mat cols = cv::Mat::zeros(C.rows, int(C.cols / 10), CV_8UC1);
		hconcat(C, cols, C);
		hconcat(cols, C, C);

		imshow("Video", C);
		waitKey(0);

		vector<Rect> parts = getparts(C);
		std::vector<int> number(7);
		for (int j = 0; j < 7; j++) {
			Mat D = C(parts[j]);
			double part = countNonZero(D);
			if (part / double(parts[j].area()) > 0.5) {
				number[j] = 1;
			}
		}

		cout << numbers[number];
		time.push_back(numbers[number]);
	}

	hours = time[0] * 10 + time[1];
	minutes = time[2] * 10 + time[3];
	if (hours > 12) {
		hours -= 12;
	}

	float min_angle = minutes * 6 + 270;
	float hour_angle = (hours * 30) + (minutes*.5) + 270;
	if (min_angle > 360)min_angle = min_angle - 360;
	if (hour_angle > 360)hour_angle = hour_angle - 360;


	Mat analog(640, 640, CV_8UC3);
	Point cent(int(analog.rows / 2), int(analog.cols / 2));
	Point perim(int(analog.rows / 2), 0);
	//Draw hour markings
	int h1[12][2] = { { 320,45 },{ 458,82 },{ 558,183 },{ 595,320 },{ 558,458 },{ 458,558 },{ 320,595 },{ 183,558 }, \
	{82,458},{ 45,320 },{ 82,183 },{ 182,82 } };
	int h2[12][2] = { { 320,5 },{ 478,47 },{ 593,163 },{ 635,320 },{ 593,478 },{ 478,593 },{ 320,635 },{ 163,593 }, \
	{47,478},{ 5,320 },{ 47,163 },{ 162,47 } };

	for (int i = 0; i < 12; i++) {
		line(analog, Point(h1[i][0], h1[i][1]), Point(h2[i][0], h2[i][1]), Scalar(0, 255, 0, 0), 4, CV_AA, 0);
	}

	//Fond out the co-ordinates on the circle perimeter for minute and draw the line from center
	perim.x = (int)round(cent.x + (320 - 65) * cos(min_angle * CV_PI / 180.0));
	perim.y = (int)round(cent.y + (320 - 65) * sin(min_angle * CV_PI / 180.0));
	line(analog, cent, perim, Scalar(0, 255, 255, 0), 4, CV_AA, 0);


	//Fond out the co-ordinates on the circle perimeter for hour and draw the line from center
	perim.x = (int)round(cent.x + (320 - 90) * cos(hour_angle * CV_PI / 180.0));
	perim.y = (int)round(cent.y + (320 - 90) * sin(hour_angle * CV_PI / 180.0));
	line(analog, cent, perim, Scalar(0, 255, 255, 0), 8, CV_AA, 0);

	imshow("Video", analog);
	waitKey(0);
	destroyAllWindows();
	return 0;
}