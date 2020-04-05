#include "StudentPreProcessing.h"
#include <iostream>
#include <array>
#include "HereBeDragons.h"
#include "ImageFactory.h"
#include <chrono>
#include <ctime>

using namespace std;

IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	auto start = std::chrono::system_clock::now();
	cv::Mat input_matrix;
	HereBeDragons::HerLoveForWhoseDearLoveIRiseAndFall(image, input_matrix);

	cv::Mat kernel_x1 = (cv::Mat_<float>(3, 3) <<
		-1, 0, 1,
		-2, 0, 2,
		-1, 0, 1);

	cv::Mat kernel_x2 = (cv::Mat_<float>(3, 3) <<
		1, 0, -1,
		2, 0, -2,
		1, 0, -1);

	cv::Mat kernel_y1 = (cv::Mat_<float>(3, 3) << 
		-1, -2, -1,
		 0,  0,  0,
		 1,  2,  1);

	cv::Mat kernel_y2 = (cv::Mat_<float>(3, 3) <<
		 1,  2,  1,
		 0,  0,  0,
		-1, -2, -1);

	cv::Mat output_matrix;
	cv::Mat x;
	cv::Mat y;
	cv::Mat output_x1;
	cv::Mat output_x2;
	cv::Mat output_y1;
	cv::Mat output_y2;

	filter2D(input_matrix, output_x1, CV_8U, kernel_x1, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
	filter2D(input_matrix, output_x2, CV_8U, kernel_x2, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
	filter2D(input_matrix, output_y1, CV_8U, kernel_y1, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
	filter2D(input_matrix, output_y2, CV_8U, kernel_y2, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);

	addWeighted(output_x1, 1.0, output_x2, 1.0, 0, x);
	addWeighted(output_y1, 1.0, output_y2, 1.0, 0, y);
	addWeighted(x, 1.0, y, 1.0, 0, output_matrix);

	IntensityImage* newimg = ImageFactory::newIntensityImage();
	HereBeDragons::NoWantOfConscienceHoldItThatICall(output_matrix, *newimg);

	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	std::cout << "Elapsed time Detection: " << elapsed_seconds.count() << "s\n";
	return newimg;
}

IntensityImage* StudentPreProcessing::stepThresholding(const IntensityImage& image) const {
	auto start = std::chrono::system_clock::now();
	cv::Mat input_matrix;
	int w = image.getWidth();
	int h = image.getHeight();

	input_matrix.create(h, w, CV_8UC1);

	for (int x = 0; x < input_matrix.cols; x++) {
		for (int y = 0; y < input_matrix.rows; y++) {
			Intensity old_pixel = image.getPixel(x, y);
			if (old_pixel > 110) {
				input_matrix.at<uchar>(y, x) = 0;
			}
			else {
				input_matrix.at<uchar>(y, x) = 255;
			}
		}
	}

	IntensityImage* newimg = ImageFactory::newIntensityImage();
	HereBeDragons::NoWantOfConscienceHoldItThatICall(input_matrix, *newimg);

	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	std::cout << "Elapsed time Tresholding: " << elapsed_seconds.count() << "s\n";
	return newimg;
}