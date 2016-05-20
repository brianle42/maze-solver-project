/*******************************************************************************
 *
 * Visualizer.cpp - Source File
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
 * Associated code snippet sources :
 *
 *  http://opencv-code.com/tutorials/detecting-simple-shapes-in-an-image/
 *  https://github.com/bsdnoobz/opencv-code/blob/master/shape-detect.cpp
 *  http://stackoverflow.com/questions/
 * 	1882047/convention-result-and-code-error-c-int-foo
 *
 ******************************************************************************/

// Command Line I/O related headers
#include <cstddef>  			// std::nullptr
#include <iostream> 			// std::cout, std::cin, std::endl
#include <iomanip>  			// std::setw
#include <string>

#include <opencv2/opencv.hpp>

// show image - helper function
void showImage(
	const std::string label ,
	cv::Mat image
	)
{
	// CV_WINDOW_AUTOSIZE
	// CV_WINDOW_NORMAL
	cv::namedWindow( label , CV_WINDOW_NORMAL )	;
    	cv::imshow( label , image )			;
}


// display text in the center of a contour - helper function
void setLabelMid(
	cv::Mat& im 			,
	const std::string label 	,
	std::vector<cv::Point>& contour
	)
{
	int fontface 	= cv::FONT_HERSHEY_SIMPLEX	;
	double scale 	= 0.4 	;
	int thickness 	= 1 	;
	int baseline 	= 0 	;

	cv::Size text = cv::getTextSize(label, fontface, scale, thickness, &baseline);
	cv::Rect r = cv::boundingRect(contour);

	cv::Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
	cv::rectangle(im, pt + cv::Point(0, baseline), pt + cv::Point(text.width, -text.height), CV_RGB(255,255,255), CV_FILLED);
	cv::putText(im, label, pt, fontface, scale, CV_RGB(0,0,0), thickness, 8);
}

// display text at a point - helper function
void setLabel(
	cv::Mat& im,
	const std::string label,
	cv::Point& point)
{
	int fontface = cv::FONT_HERSHEY_SIMPLEX;
	double scale = 0.2;
	int thickness = 1;
	int baseline = 0;

	cv::Size text = cv::getTextSize(label, fontface, scale, thickness, &baseline);
	//cv::Rect r = cv::boundingRect(contour);
	cv::Rect r = cv::Rect( point , text );

	cv::Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
	cv::rectangle(im, pt + cv::Point(0, baseline), pt + cv::Point(text.width, -text.height), CV_RGB(255,255,255), CV_FILLED);
	cv::putText(im, label, pt, fontface, scale, CV_RGB(0,0,0), thickness, 8);
} 

// display text in the center of a contour - helper function
void setLabel(
	cv::Mat& im,
	const std::string label,
	std::vector<cv::Point>& points)
{

	for( std::vector< cv::Point >::size_type i = 0 ; i != points.size() ; i++ ) 
	{

		setLabel( im , label , points[ i ] );

	}

}

// display text at a point - helper function
void setLabel(
	cv::Mat& im,
	const std::string label,
	cv::Point2f& poynt)
{
	cv::Point point = (cv::Point)poynt;

	int fontface = cv::FONT_HERSHEY_SIMPLEX;
	double scale = 0.4;
	int thickness = 1;
	int baseline = 0;

	cv::Size text = cv::getTextSize(label, fontface, scale, thickness, &baseline);
	//cv::Rect r = cv::boundingRect(contour);
	cv::Rect r = cv::Rect( point , text );

	cv::Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
	cv::rectangle(im, pt + cv::Point(0, baseline), pt + cv::Point(text.width, -text.height), CV_RGB(255,255,255), CV_FILLED);
	cv::putText(im, label, pt, fontface, scale, CV_RGB(0,0,0), thickness, 8);
} 


//draw contours - helper function (not mine but still)
void displayContours(
	const std::string label,
	const cv::Mat image,
	std::vector< std::vector< cv::Point > > contours,
	std::vector< cv::Vec4i > hierarchy,
	bool enumerateMode , bool contoursOnlyMode )
{

	cv::RNG rng(12345);

	cv::Mat drawing;

	if( contoursOnlyMode )
	{

		drawing = cv::Mat::zeros(image.size(),CV_8UC3);

	}
	else
	{

		drawing = image.clone();

	}

	for( int i = 0 ; i < contours.size() ; i++ )
	{

		cv::Scalar color = cv::Scalar(rng.uniform(0, 255),rng.uniform(0,255),rng.uniform(0,255));

		cv::drawContours(drawing,contours,i, color,1,8,hierarchy,0,cv::Point());

		if( enumerateMode )
		{

			setLabel( drawing , std::to_string(i) , contours[i] ) ;

		}

	}

	//showImage("contours", drawing);

	showImage( label , drawing ) ;

}

// average contours - helper function
cv::Point averageContour(
	std::vector< cv::Point >& v)
{
	cv::Point return_value( 0.0 , 0.0 );
	int n = v.size( );
	for( std::vector< cv::Point >::size_type i = 0; i != v.size( ) ; i++ )
	{
	return_value += v[ i ];
	}
	return_value /= ( int )( v.size() );
	return ( return_value );
}

// Method for displaying mat convention
void displayMatConvention(
	cv::Mat& image
	)	
{

	cv::Point point ;

	int horizontalSize 	= image.size().width	;	// x
	int verticalSize	= image.size().height	;	// y

	std::cout << "displayMatConvention called. Printing:" ;
	std::cout << std::endl;
	std::cout << "horizontalSize = " << std::to_string( horizontalSize );
	std::cout << std::endl;
	std::cout << "verticalSize   = " << std::to_string( verticalSize );
	std::cout << std::endl;

	int offset 	= 10 ;
	horizontalSize 	= horizontalSize - offset ;
	verticalSize  	= verticalSize 	 - offset ;

	// create a new 320x240 image //Mat img(Size(320,240),CV_8UC3);

	point.x = offset ;
	point.y = offset ;
	setLabel( image , "--" , point ) ;	// 00

	point.x = offset ;
	point.y = verticalSize - offset ;
	setLabel( image , "-+" , point ) ;	// 01

	point.x = horizontalSize - offset ;
	point.y = horizontalSize - offset ;
	setLabel( image , "+-" , point ) ;	// 10

	point.x = horizontalSize - offset ;
	point.y = verticalSize 	 - offset ;
	setLabel( image , "++" , point ) ;	// 11
	
}