//#include <iostream>
//#include <string>
//#include <vector>
//#include <algorithm>
//#include <map>
//
//#include <opencv2\core.hpp>
//#include <opencv2\highgui.hpp>
//#include <opencv2\imgproc.hpp>
//
//using namespace std;
//using namespace cv;
//
//const string ImageFolder = "C:\\Users\\Administrator\\Desktop\\TarasIzhyk\\WatchIm\\";
//
//int main()
//{
//	int threshold_value = 145;
//	int threshold_type = 0;
//	int const max_BINARY_value = 255;
//
//	const char* window_name1 = "Demo1";
//	const char* window_name2 = "Demo2";
//
//	//Mat watch = imread(ImageFolder + "watch24.jpg"); // Loads image form disk
//
//	Mat watch = imread("./Images/square2.jpg"); // Loads image form disk
//	if (watch.empty())
//	{
//		return -1;
//	}
//	
//	int size_x = 225 / 2;
//	int size_y = 225 / 2;
//
//	Mat watch_image = watch.clone(); // Creates full copy of imageA
//
//
//	//resize(watch_image, watch_image, cv::Size(640, 480));
//
//	namedWindow(window_name1, WINDOW_AUTOSIZE); // Create a window to display results	
//	namedWindow(window_name2, WINDOW_AUTOSIZE); // Create a window to display results
//
//	cvtColor(watch_image, watch_image, COLOR_BGR2GRAY); // Convert the image to Gray
//	
//	threshold(watch_image, watch_image, threshold_value, max_BINARY_value, threshold_type);
//	
//	blur(watch_image, watch_image, Size(3, 3));
//
//	imshow(window_name1, watch_image);
//
//	int morph_elem = 1;
//	int morph_size = 2;
//	int morph_operator = 1;
//		
//	Mat element = getStructuringElement(morph_elem, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));
//	morphologyEx(watch_image, watch_image, morph_operator, element);
//
//	imshow(window_name2, watch_image);
//
//	//blur(watch_image, watch_image, Size(3, 3));
//
//	//morphologyEx(watch_image, watch_image, 0, element);
//	
//	Mat dst, cdst, cdstP,img;
//
//	Canny(watch_image, dst, 50, 200, 3);
//	GaussianBlur(dst, dst, Size(3, 3),1);
//
//	// Copy edges to the images that will display the results in BGR
//	cvtColor(watch_image, cdst, COLOR_GRAY2BGR);
//	
//	cdstP = cdst.clone();
//
//
//
//
//	cv::threshold(watch, img, 127, 255, cv::THRESH_BINARY);
//	cv::Mat skel(img.size(), CV_8UC1, cv::Scalar(0));
//	cv::Mat temp;
//	cv::Mat eroded;
//
//	cv::Mat element2 = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
//
//	bool done;
//	do
//	{
//		cv::erode(img, eroded, element2);
//		cv::dilate(eroded, temp, element2); // temp = open(img)
//		cv::subtract(img, temp, temp);
//		cv::bitwise_or(skel, temp, skel);
//		eroded.copyTo(img);
//
//		done = (cv::countNonZero(img) == 0);
//	} while (!done);
//
//
//
//
//
//	// Probabilistic Line Transform
//
//	vector<Vec4i> linesP; // will hold the results of the detection
//
//	HoughLinesP(dst, linesP, 1, CV_PI / 180, 130, 85, 10); // runs the actual detection
//	
//		for (size_t i = 0; i < linesP.size(); i++){
//		Vec4i l = linesP[i];
//		Point pt1(l[0], l[1]);
//		Point pt2(l[2], l[3]);
//		cout << norm(pt1 - pt2) << " ";
//		line(watch, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 255, 0), 3, LINE_AA);
//		}
//
//
//
//
//	
//	Vec4i l = linesP[0];
//	Point pt11(l[0], l[1]);
//	Point pt12(l[2], l[3]);
//	Point midlle1, midlle2;
//	midlle1.x = (pt11.x + pt12.x) / 2;
//	midlle1.y = (pt11.y + pt12.y) / 2;
//	
//	int minute;
//	int hour;
//
//	
//	//line(cdstP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);  // Draw the lines
//
//
//			
//		int angle = atan2(pt11.x - pt12.x, pt11.y - pt12.y) * 180 / CV_PI + 1;
//		
//		Vec4i t = linesP[2];
//		Point pt21(t[0], t[1]);
//		Point pt22(t[2], t[3]);
//		
//		float S = (pt12.y - pt11.y) / static_cast<float>(pt12.x - pt11.x);
//		float B = pt11.y - pt11.x*(pt12.y - pt11.y) / static_cast<float>(pt12.x - pt11.x);
//		float C = (pt22.y - pt21.y) / static_cast<float>(pt22.x - pt21.x);
//		float D = pt21.y - pt21.x*(pt22.y - pt21.y) / static_cast<float>(pt22.x - pt21.x);
//		int X = (D - B) / (S - C);
//		int Y = S * (D - B) / (S - C) + B;
//
//		circle(cdstP, Point(X, Y), 32, Scalar(0, 0, 255), 1, 8);
//
//		if (midlle1.y < size_y && midlle1.x < size_x) {
//			angle = abs(angle) + 180;
//			minute = angle / 6;
//		}
//		else if (midlle1.y < size_y && midlle1.x > size_x) {
//			angle = abs(angle);
//			minute = angle / 6; 
//		}
//		else if (midlle1.y > size_y && midlle1.x < size_x) {
//			angle = abs(angle) + 180;
//			minute = angle / 6;
//		}
//		else {
//			angle = abs(angle);
//			minute = angle / 6;
//		}
//
//		midlle2.x = (pt21.x + pt22.x) / 2;
//		midlle2.y = (pt21.y + pt22.y) / 2;
//		
//		int angle2 = atan2(pt21.x - pt22.x, pt21.y - pt22.y) * 180 / CV_PI + 1;
//
//		if (midlle2.y < size_y && midlle2.x < size_x) {
//			angle2 = abs(angle2) + 180;
//		}
//		else if (midlle2.y < size_y && midlle2.x > size_x) {
//			angle2 = abs(angle2);
//		}
//		else if (midlle2.y > size_y && midlle2.x < size_x) {
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
//		
//		int len1 = norm(pt11 - pt12);
//		int len2 = norm(pt21 - pt22);
//
//		//arrow.insert(pair<int, Vec4i>(len, l));
//	
//		line(cdstP, Point(t[0], t[1]), Point(t[2], t[3]), Scalar(0, 0, 255), 2, LINE_AA);
//	//}
//
//	cout << endl << "  " << hour << ":" << minute << endl;
//	
//	// Show results
//	imshow("Source", watch_image);
//	imshow("Detected Lines (in red) - Probabilistic Line Transform", cdstP);
//
//
// 	waitKey(0);
//
//	return 0;
//}
