/*******************************************************************************
 *
 * Visualizer.h - Class Header File
 *
 * Description	:	Moonlight Company
 *			Maze Solver Project
 *			Visualizer Class
 *
 * Modified	: 12.05.2016 by Utku Norman  ( norman.utku@metu.edu.tr  )
 * Created	: 19.04.2016 by Utku Norman  ( norman.utku@metu.edu.tr  )
 *
 * People	:	Doga Yucalan ( yucalan.doga@metu.edu.tr )
 *			Utku Norman  ( norman.utku@metu.edu.tr  )
 *
 *
 ******************************************************************************/

#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <stdio.h>

#include <opencv2/opencv.hpp>

// show image - helper function
void showImage(
	const std::string label,
	cv::Mat image) ;


//draw contours - helper function

void displayContours(
	const std::string label,
	cv::Mat image,
	std::vector< std::vector< cv::Point > > contours,
	std::vector< cv::Vec4i > hierarchy,
	bool enumerateMode = false, 
	bool contoursOnlyMode = true  ) ;

// display text in the center of a contour - helper function
void setLabelMid(
	cv::Mat& im,
	const std::string label,
	std::vector<cv::Point>& contour) ;

// display text at each point of a vector of points - helper function
void setLabel(
	cv::Mat& im,
	const std::string label,
	std::vector<cv::Point>& points) ;

// display text at a point - helper function
void setLabel(
	cv::Mat& im,
	const std::string label,
	cv::Point& point) ;

// display text at a "floating" point - helper function
void setLabel(
	cv::Mat& im,
	const std::string label,
	cv::Point2f& poynt) ;

// average contours - helper function
cv::Point averageContour(
	std::vector< cv::Point >& v) ;

// Method for displaying mat convention  - helper function
void displayMatConvention(
	cv::Mat& image
	) ;


#endif // VISUALIZER_H
