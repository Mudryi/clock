//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/highgui.hpp"
//#include "opencv2/imgproc.hpp"
//#include <iostream>
//#include <mutex>
//using namespace cv;
//using namespace std;
//
//char window_name[] = "Watch";
//int lines = 1;
//int dilation_size = 1;
//
//
//void removeSmallContours(std::vector<std::vector<cv::Point>>& contours, vector<cv::Vec4i>& hierarchy)
//{
//	int i = 0;
//	for (auto it = contours.begin(); it != contours.end();) {
//
//		const auto& contour = *it;
//
//		const bool isLarge = (cv::boundingRect(contour).area() > 1000);
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
//
//int main(int argc, char** argv)
//{
//	namedWindow(window_name, WINDOW_NORMAL);
//
//	Mat src;
//
//	src = imread("./Images/square3.jpg");
//
//	morphologyEx(src, src, MORPH_DILATE, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3)));
//
//	Mat src_gray, edges;
//
//	cv::cvtColor(src, src_gray, COLOR_BGR2GRAY);
//	//cv::GaussianBlur(src_gray, src_gray, cv::Size(9, 9), 3);
//
//	cv::threshold(src_gray, src_gray, 160, 255, cv::THRESH_BINARY_INV);
//
//	//cv::morphologyEx(src_gray, src_gray, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9, 9)));
//	cv::Canny(src_gray, edges, 127, 255);
//	cv::GaussianBlur(edges, edges, cv::Size(3, 3), 1);
//
//	std::vector<std::vector<cv::Point>> contours;
//	std::vector<cv::Vec4i> hierarchy;
//
//	Mat A = cv::Mat::zeros(src.size(), CV_8UC3);
//
//	findContours(edges, contours, hierarchy, cv::RetrievalModes::RETR_TREE, cv::CHAIN_APPROX_TC89_L1, cv::Point(0, 0));
//	
//
//	//delete extend contours
//
//	for (auto j = 0; j < hierarchy.size();) {
//		if (hierarchy[j][2] == -1) 
//			++j;
//		else {
//			contours.erase(contours.begin()+j);
//			hierarchy.erase(hierarchy.begin()+j);
//		}
//	}
//	
//	//delete contours without father
//
//	for (auto j = 0; j < hierarchy.size();) {
//		if (hierarchy[j][3] != -1)
//			++j;
//		else {
//			contours.erase(contours.begin() + j);
//			hierarchy.erase(hierarchy.begin() + j);
//		}
//	}
//
//	for (size_t i = 0; i< contours.size(); i++)
//	{
//		cv::Scalar color = cv::Scalar(0, 255, 0);
//		drawContours(A, contours, (int)i, color, 5, cv::LINE_4, hierarchy, 0, cv::Point());
//	}
//
//	removeSmallContours(contours,hierarchy);
//
//	//vector<vector<Point> >hull(contours.size());
//	//for (size_t i = 0; i < contours.size(); i++)
//	//{
//	//	convexHull(contours[i], hull[i]);
//	//}
//
//
//	//draw
//
//	
//
//	for (size_t i = 0; i< contours.size(); i++)
//	{
//		cv::Scalar color = cv::Scalar(0, 255, 0);
//		drawContours(src, contours, (int)i, color, 5, cv::LINE_4, hierarchy, 0, cv::Point());
//		drawContours(A, contours, (int)i, color, 5, cv::LINE_4, hierarchy, 0, cv::Point());
//	}
//
//
//
//
//	cv::cvtColor(A, A, COLOR_BGR2GRAY);
//
//	vector<Vec4i> lines;
//	HoughLinesP(A, lines, 7, CV_PI / 180, 450,50,10);
//	for (size_t i = 0; i < lines.size(); i++)
//	{
//		Vec4i l = lines[i];
//		line(src, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
//
//	}
//
//		Vec4i l = lines[1];
//		Vec4i t = lines[3];
//		Point p1, p2, p11, p12;
//		p1 = Point(l[0], l[1]);
//		p2 = Point(l[2], l[3]);
//		p11 = Point(t[0], t[1]);
//		p12 = Point(t[2], t[3]);
//		float S = (p2.y - p1.y) / static_cast<float>(p2.x - p1.x);
//		float B = p1.y - p1.x*(p2.y - p1.y) / static_cast<float>(p2.x - p1.x);
//		float C = (p12.y - p11.y) / static_cast<float>(p12.x - p11.x);
//		float D = p11.y - p11.x*(p12.y - p11.y) / static_cast<float>(p12.x - p11.x);
//		int X = (D - B) / (S - C);
//		int Y = S*(D-B)/(S-C)+B;
//
//		circle(src, Point(X,Y), 32, Scalar(0, 0, 255),1,8);
//
//
//
//
//
//	//angle
//
//	for (size_t i = 0; i < lines.size(); i++)
//	{
//		Vec4i l = lines[i];
//		Point p1, p2;
//		p1 = Point(l[0], l[1]);
//		p2 = Point(l[2], l[3]);
//		//radian __ degrees  * 180 / PI
//		float angle = atan2(p1.y - p2.y, p1.x - p2.x)*180/CV_PI;
//		cout << angle<<" ";
//	}
//
//	imshow(window_name, src);
//
//	waitKey(0);
//	return 0;
//}