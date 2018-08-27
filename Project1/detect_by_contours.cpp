//#include <iostream>
//#include <string>
//#include <vector>
//#include <algorithm>
//#include <map>
//
//#include <opencv2\core.hpp>
//#include <opencv2\highgui.hpp>
//#include <opencv2\imgproc.hpp>
//#include "opencv2/opencv.hpp"
//using namespace std;
//using namespace cv;
//
//void removeSmallContours(std::vector<std::vector<cv::Point>>& contours, vector<cv::Vec4i>& hierarchy)
//{
//	int i = 0;
//	for (auto it = contours.begin(); it != contours.end();) {
//
//		const auto& contour = *it;
//
//		const bool isLarge = (cv::boundingRect(contour).area() > 400);
//
//		if (isLarge) {
//			++it;
//			++i;
//		}
//		else {
//			it = contours.erase(it);
//			hierarchy.erase(hierarchy.begin() + i);
//		}
//	}
//}
//
//int ArrangeMinuteAndHour(vector<int> &arr_of_values)
//{
//	int result = 0, count_max = 0;
//	int count1 = 0, count2 = 0, value, max1, max2;
//	bool flag = 0;
//
//	sort(arr_of_values.begin(), arr_of_values.end());
//
//	for (int i = 0; i < arr_of_values.size() - 1; ++i)
//	{
//		value = arr_of_values[i];
//		if (flag == 0)
//		{
//			if (value == arr_of_values[i + 1])
//			{
//				count1++;
//				max1 = value;
//			}
//			else
//			{
//				flag = 1;
//			}
//		}
//		else {
//			if (value == arr_of_values[i + 1])
//			{
//				count2++;
//				max2 = value;
//			}
//			else
//			{
//				if (count1 > count2)
//				{
//					if (count_max > count1)
//						;
//					else {
//						count_max = count1;
//						result = max1;
//					}
//				}
//				else
//				{
//					if (count_max > count2)
//						;
//					else {
//						count_max = count2;
//						result = max2;
//					}
//				}
//			}
//			flag = 0;
//		}
//	}
//
//	if (count1 > count2)
//	{
//		if (count_max > count1)
//			;
//		else {
//			count_max = count1;
//			result = max1;
//		}
//	}
//	else
//	{
//		if (count_max > count2)
//			;
//		else {
//			count_max = count2;
//			result = max2;
//		}
//	}
//	return result;
//}
//
//void OutPutDigitalWatch(Mat &frame, int &hour, int &minute)
//{
//	if (hour == 0) {
//		hour = 12;
//	}
//
//	string text;
//	stringstream strhour, strminute;
//
//	strhour << hour;
//	strminute << minute;
//
//	if (minute < 10)
//	{
//		text = strhour.str() + ":0" + strminute.str();
//	}
//	else
//	{
//		text = strhour.str() + ":" + strminute.str();
//	}
//
//	putText(frame, text, Point(5, 60), FONT_HERSHEY_PLAIN, 5.0, CV_RGB(255, 0, 0), 5);
//}
//
//int main(int, char**)
//{
//	int arrange = 0;
//	vector<int> arr_of_hours(11);
//	vector<int> arr_of_minutes(11);
//	bool flag_hour = 0;
//	
//	VideoCapture cap(0); // open the default camera
//	if (!cap.isOpened())  // check if we succeeded
//		return -1;
//
//	namedWindow("Video", 1);
//	while (1)
//	{
//		Mat frame, src, edges;
//		cap >> frame;         // get a new frame from camera
//
//		//frame = imread("./Images/watchtest2.jpg");
//
//		Mat watch_grey;
//		//frame *= 1.5;
//		cvtColor(frame, watch_grey, COLOR_BGR2GRAY);
//
//		GaussianBlur(watch_grey, watch_grey, cv::Size(9, 9), 3);
//		adaptiveThreshold(watch_grey, src, 255, ADAPTIVE_THRESH_GAUSSIAN_C, 0, 11, 5);
//
//		
//		Mat element = getStructuringElement(0, Size(2 * 3 + 1, 2 * 3 + 1), Point(3, 3));
//		morphologyEx(src, src, MORPH_DILATE, getStructuringElement(1, Size(2 * 1 + 1, 2 * 1 + 1), Point(1, 1)));
//
//		Canny(src, edges, 50, 200, 3);
//		morphologyEx(edges, edges, MORPH_CLOSE, element);
//
//		std::vector<std::vector<cv::Point>> contours;
//		std::vector<cv::Vec4i> hierarchy;
//
//		Mat Contours1 = cv::Mat::zeros(src.size(), CV_8UC3);
//		Mat Contours2 = cv::Mat::zeros(src.size(), CV_8UC3);
//		Mat Contours3 = cv::Mat::zeros(src.size(), CV_8UC3);
//		findContours(edges, contours, hierarchy, cv::RetrievalModes::RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
//
//		removeSmallContours(contours, hierarchy);
//
//		for (size_t i = 0; i < contours.size(); i++)
//		{
//			cv::Scalar color = cv::Scalar(0, 255, 0);
//			cv::Scalar color2 = cv::Scalar(255, 0, 0);
//			
//			drawContours(Contours1, contours, (int)i, color2, CV_FILLED);
//			drawContours(Contours1, contours, (int)i, color, 5, cv::LINE_4, hierarchy, 0, cv::Point());
//		}
//
//
//		//delete extend contours
//
//		for (auto j = 0; j < hierarchy.size();) {
//			if (hierarchy[j][2] == -1)
//				++j;
//			else {
//				contours.erase(contours.begin() + j);
//				hierarchy.erase(hierarchy.begin() + j);
//			}
//		}
//
//		for (size_t i = 0; i < contours.size(); i++)
//		{
//			cv::Scalar color = cv::Scalar(0, 255, 0);
//			drawContours(Contours2, contours, (int)i, color, 5, cv::LINE_4, hierarchy, 0, cv::Point());
//		}
//
//	
//			//delete contours without father
//
//			for (auto j = 0; j < hierarchy.size();) {
//				if (hierarchy[j][3] != -1)
//					++j;
//				else {
//					contours.erase(contours.begin() + j);
//					hierarchy.erase(hierarchy.begin() + j);
//				}
//			}
//
//		for (size_t i = 0; i < contours.size(); i++)
//		{
//			cv::Scalar color = cv::Scalar(0, 255, 0);
//			drawContours(Contours3, contours, (int)i, color, 3, cv::LINE_4, hierarchy, 0, cv::Point());
//		}
//
//		vector<Vec4i> linesP;
//
//		GaussianBlur(Contours3, Contours3, Size(3, 3), 0, 0);
//		cvtColor(Contours3, Contours3, COLOR_BGR2GRAY);
//
//
//		HoughLinesP(Contours3, linesP, 1, CV_PI / 180, 90, 70, 15); // runs the actual detection
//
//		for (size_t i = 0; i < linesP.size(); i++) {
//			Vec4i l = linesP[i];
//			Point pt1(l[0], l[1]);
//			Point pt2(l[2], l[3]);
//		}
//
//		size_t maxi = 0;
//		size_t mini = 0;
//
//		if (linesP.size() > 1) {
//
//			Point p1(linesP[0][0], linesP[0][1]);
//			Point p2(linesP[0][2], linesP[0][3]);
//			double max = norm(p1 - p2);
//			double min = norm(p1 - p2);
//			int maxi = 0;
//			int mini = 0;
//			for (size_t i = 0; i < linesP.size(); i++) {
//				Vec4i l = linesP[i];
//				Point pt1(l[0], l[1]);
//				Point pt2(l[2], l[3]);
//				int len = norm(pt1 - pt2);
//				if (len > max) {
//					maxi = i;
//					max = len;
//				}
//				if (len < min) {
//					mini = i;
//					min = len;
//				}
//			}
//		
//		int minute, hour;
//
//		Vec4i minuteA = linesP[maxi];
//		Vec4i hourA = linesP[mini];
//		Point pt11(minuteA[0], minuteA[1]);
//		Point pt12(minuteA[2], minuteA[3]);
//		Point pt21(hourA[0], hourA[1]);
//		Point pt22(hourA[2], hourA[3]);
//		line(frame, Point(minuteA[0], minuteA[1]), Point(minuteA[2], minuteA[3]), Scalar(0, 255, 0), 3, LINE_AA);
//		line(frame, Point(hourA[0], hourA[1]), Point(hourA[2], hourA[3]), Scalar(0, 0, 255), 3, LINE_AA);
//		Point midlle1, midlle2;
//		midlle1.x = (pt11.x + pt12.x) / 2;
//		midlle1.y = (pt11.y + pt12.y) / 2;
//		midlle2.x = (pt21.x + pt22.x) / 2;
//		midlle2.y = (pt21.y + pt22.y) / 2;
//
//		//float A1 = (pt12.y - pt11.y) / static_cast<float>(pt12.x - pt11.x);
//		//float B1 = pt11.y - pt11.x*(pt12.y - pt11.y) / static_cast<float>(pt12.x - pt11.x);
//		//float A2 = (pt22.y - pt21.y) / static_cast<float>(pt22.x - pt21.x);
//		//float B2 = pt21.y - pt21.x*(pt22.y - pt21.y) / static_cast<float>(pt22.x - pt21.x);
//		int X = ((pt21.y - pt21.x*(pt22.y - pt21.y) / static_cast<float>(pt22.x - pt21.x)) - (pt11.y - pt11.x*(pt12.y - pt11.y) / static_cast<float>(pt12.x - pt11.x))) / (((pt12.y - pt11.y) / static_cast<float>(pt12.x - pt11.x)) - ((pt22.y - pt21.y) / static_cast<float>(pt22.x - pt21.x)));
//		int Y = ((pt12.y - pt11.y) / static_cast<float>(pt12.x - pt11.x)) * ((pt21.y - pt21.x*(pt22.y - pt21.y) / static_cast<float>(pt22.x - pt21.x)) - (pt11.y - pt11.x*(pt12.y - pt11.y) / static_cast<float>(pt12.x - pt11.x))) / (((pt12.y - pt11.y) / static_cast<float>(pt12.x - pt11.x)) - ((pt22.y - pt21.y) / static_cast<float>(pt22.x - pt21.x)) + (pt11.y - pt11.x*(pt12.y - pt11.y) / static_cast<float>(pt12.x - pt11.x)));
//
//		//circle(frame, Point(X, Y), 32, Scalar(0, 0, 255), 1, 8);
//
//		double angle = atan2(pt11.x - pt12.x, pt11.y - pt12.y) * 180 / CV_PI + 1;
//
//		if ((midlle1.y < Y && midlle1.x < X) || (midlle1.y > Y && midlle1.x < X)) {
//			angle = abs(angle) + 180;
//			minute = angle / 6;
//		}
//		else {
//			angle = abs(angle);
//			minute = angle / 6;
//		}
//		double angle2 = atan2(pt21.x - pt22.x, pt21.y - pt22.y) * 180 / CV_PI + 1;
//
//		if ((midlle2.y < Y && midlle2.x < X) || (midlle2.y > Y && midlle2.x < X)) {
//			angle2 = abs(angle2) + 180;
//		}
//		else {
//			angle2 = abs(angle2);
//		}
//
//		if (angle2 >= 0 && angle2 < 30) {
//			hour = 12;
//		}
//		else if (angle2 >= 30 && angle2 < 60) {
//			hour = 1;
//		}
//		else if (angle2 >= 60 && angle2 < 90) {
//			hour = 2;
//		}
//		else if (angle2 >= 90 && angle2 < 120) {
//			hour = 3;
//		}
//		else if (angle2 >= 120 && angle2 < 150) {
//			hour = 4;
//		}
//		else if (angle2 >= 150 && angle2 < 180) {
//			hour = 5;
//		}
//		else if (angle2 >= 180 && angle2 < 210) {
//			hour = 6;
//		}
//		else if (angle2 >= 210 && angle2 < 240) {
//			hour = 7;
//		}
//		else if (angle2 >= 240 && angle2 < 270) {
//			hour = 8;
//		}
//		else if (angle2 >= 270 && angle2 < 300) {
//			hour = 9;
//		}
//		else if (angle2 >= 300 && angle2 < 330) {
//			hour = 10;
//		}
//		else if (angle2 >= 330 && angle2 < 360) {
//			hour = 11;
//		}
//
//		if (arrange <= 5) {
//			arr_of_hours[arrange] = hour;
//			arr_of_minutes[arrange] = minute;
//		}
//		else {
//			arr_of_hours[arrange] = hour;
//			arr_of_minutes[arrange] = minute;
//			flag_hour = 1;
//		}
//
//		if (arrange % 5 == 0 && flag_hour == 1)
//		{
//			hour = ArrangeMinuteAndHour(arr_of_hours);
//			minute = ArrangeMinuteAndHour(arr_of_minutes);
//		}
//
//		if (arrange < 11) {
//			arrange++;
//		}
//		else {
//			arrange = 0;
//		}
//
//
//		OutPutDigitalWatch(frame, hour, minute);
//
//	}
//		imshow("Video", frame);
//
//		// Press 'c' to escape
//		if (waitKey(200) == 'c') break;
//	}
//	return 0;
//}