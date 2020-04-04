#include "StudentPreProcessing.h"
#include <iostream>
#include <array>
#include "HereBeDragons.h"
#include "ImageFactory.h"

using namespace std;

IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
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

	return newimg;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	return nullptr;
}