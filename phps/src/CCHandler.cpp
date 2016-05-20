/*******************************************************************************
 *
 * CCHandler.cpp - Source File
 *
 * Description	:	Moonlight Company
 *			Maze Solver Project
 *			Camera Capture Handler Class
 *
 * Modified	: 12.05.2016 by Utku Norman  ( norman.utku@metu.edu.tr  )
 * Created	: 24.04.2016 by Utku Norman  ( norman.utku@metu.edu.tr  )
 *
 * People	:	Doga Yucalan ( yucalan.doga@metu.edu.tr )
 *			Utku Norman  ( norman.utku@metu.edu.tr  )
 *
 ******************************************************************************/

// Command Line I/O related headers
#include <cstddef>  				// std::nullptr
#include <iostream> 				// std::cout, std::cin, std::endl
#include <iomanip>  				// std::setw

#include <fstream>      			// std::fstream

#include <opencv2/opencv.hpp> 		// Image Processing (OpenCV) header

#include "../include/CCHandler.h"

#include "../include/Visualizer.h"

/*******************************************************************************
 *
 * Constructor
 *
 ******************************************************************************/

CCHandler::CCHandler( void )
{

	//capturer.set( 4 , 480 )	;	// width
	//capturer.set( 3 , 640 )	;	// height

	//double dWidth;
	//double dHeight;

	//get the width of frames of the video
	//dWidth = capturer.get( CV_CAP_PROP_FRAME_WIDTH ); 

	//get the height of frames of the  vide
	//dHeight = capturer.get( CV_CAP_PROP_FRAME_HEIGHT );

	capturer.open( 1 )	;	// open the web-camera

	std::string filename( "./out_camera_data.xml" )	;

	cv::FileStorage fs( filename , cv::FileStorage::READ );

	fs[ "camera_matrix" ] 			>> intrinsics	;

	fs[ "distortion_coefficients" ] 	>> distortion 	;

}

/*******************************************************************************
 *
 * Destructor
 *
 ******************************************************************************/
CCHandler::~CCHandler( void )
{

	if( capturer.isOpened( ) ) // check if we succeeded
	{

		capturer.release( );

	}

}

		/*

		Mat&  
		Mat&  cameraMatrix
		Mat&  distCoeffs
		cv::undistort(singleShotImage, singleShotImage, cameraMatrix, distCoeffs);

		// http://docs.opencv.org/2.4/modules/core/doc/xml_yaml_persistence.html
		*/


/*

//create source matrix
cv::Mat srcImg(res.first, res.second, cvFormat, const_cast<char*>(pImg));

//fill matrices
cv::Mat cam(3, 3, cv::DataType<float>::type);
cam.at<float>(0, 0) = 528.53618582196384f;
cam.at<float>(0, 1) = 0.0f;
cam.at<float>(0, 2) = 314.01736116032430f;

cam.at<float>(1, 0) = 0.0f;
cam.at<float>(1, 1) = 532.01912214324500f;
cam.at<float>(1, 2) = 231.43930864205211f;

cam.at<float>(2, 0) = 0.0f;
cam.at<float>(2, 1) = 0.0f;
cam.at<float>(2, 2) = 1.0f;

cv::Mat dist(5, 1, cv::DataType<float>::type);  
dist.at<float>(0, 0) = -0.11839989180635836f;
dist.at<float>(1, 0) = 0.25425420873955445f;
dist.at<float>(2, 0) = 0.0013269901775205413f;
dist.at<float>(3, 0) = 0.0015787467748277866f;
dist.at<float>(4, 0) = -0.11567938093172066f;

cv::Mat map1, map2;
cv::initUndistortRectifyMap(cam, dist, cv::Mat(), cam, cv::Size(res.second, res.first), CV_32FC1, map1, map2);

cv::remap(srcImg, *m_undistImg, map1, map2, cv::INTER_CUBIC);
//http://stackoverflow.com/questions/30913746/right-use-of-initundistortrectifymap-and-remap-from-opencv
*/


/*******************************************************************************
 *
 * Public Methods
 *
 ******************************************************************************/
 
void CCHandler::printState(
	bool printMode 		, 
	bool displayMode 
	)
{

	if( printMode )
	{

		std::cout << "<!---------------------------------------------";
		std::cout << std::endl;
		std::cout << "CCHandler.printState() called. Printing state:" ;
		std::cout << std::endl;

	}

	if ( IsNull( state ) )
	{

		std::cerr << "CCHandler: state is Null";	
		std::cerr << std::endl;

		return;

	}
	else
	{

		if( printMode )
		{
			std::cout << "Single shot mode: " << singleShotMode;
			std::cout << std::endl;

			std::cout << "Showing state image (CC-rawImage): ";
			std::cout << std::endl;

		}

		if( displayMode )
		{

			showImage( "CC-rawImage" , state.image );

		}

	}

	if( printMode )
	{

		std::cout << "---------------------------------------------->";
		std::cout << std::endl;
		std::cout << std::endl;

	}

}

bool CCHandler::initialize(
	int delay  ,
	const cv::Mat image
	)
{

	if( image.data )
	{

		singleShotMode = true 				;

		singleShotImage = image.clone( ) 	;

		/*
		std::string filename( "./out_camera_data.xml" )	;

		cv::FileStorage fs( filename , cv::FileStorage::READ );

		cv::Mat intrinsics , distortion;

		fs[ "camera_matrix" ] 			>> intrinsics	;

		fs[ "distortion_coefficients" ] 	>> distortion 	;

		showImage("CC.init: recv", image );
		cv::Mat imageUndistorted; // Will be the undistorted version of the above image.

		cv::undistort(image, imageUndistorted, intrinsics, distortion);

		singleShotImage = imageUndistorted.clone();

		showImage("CC.init: undist", singleShotImage );
		*/

	}
	else
	{

		singleShotMode = false ;
		
		cv::Mat dummyImage ;

		if( !capturer.isOpened( ) ) // check if we succeeded
		{
			std::cerr << "Capture is not open!" ;
			std::cerr << std::endl ;
			return false ;
		}

		std::cout << "Camera initialization in progress. Waiting..." ;
		std::cout << std::endl ;

		for( int i = 0 ; i < delay ; i++) //200
		{

			capturer >> dummyImage; // get a new frame from camera

		}

		std::cout << "Camera initialized" ;
		std::cout << std::endl ;

	}

	return true ;

}

CCPacket CCHandler::handle( 
	bool debugMode
	)
{

	if( debugMode )
	{
		std::cout << std::endl	;
		std::cout << "<!---------------------------------------------"	;
		std::cout << std::endl	;
		std::cout << "CCHandler.handle() called. handling..."	;
		std::cout << std::endl	;

	}

	if( singleShotMode )
	{

		state.image = singleShotImage;

		return state;

	}

	if( !capturer.isOpened( ) ) // check if we succeeded
	{
		std::cerr << "Capture is not open!" ;
		std::cerr << std::endl ;
		return CCPacketNull ;
	}

	if( debugMode )
	{

		std::cout << "Capturing image." << std::endl;

	}

	capturer >> state.image; // get a new frame from camera

	if( calibrateMode )
	{

		cv::Mat imageUndistorted; // Will be the undistorted version of the above image.

		cv::undistort( state.image, imageUndistorted, intrinsics, distortion );

		state.image = imageUndistorted.clone();

	}
	
	if( debugMode )
	{

		std::cout << "Camera capture complete." << std::endl;

	}

	//showImage("CCC" , state.image );

	//cv::waitKey( 0 );


	if( debugMode )
	{

		std::cout << "---------------------------------------------->";
		std::cout << std::endl;
		std::cout << std::endl;

	}

	return state;

}

/*******************************************************************************
 *
 * Private Methods
 *
 ******************************************************************************/