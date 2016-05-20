/*******************************************************************************
 *
 * IPHandler.cpp - Source File
 *
 * Description	:	Moonlight Company
 *			Maze Solver Project
 *			Image Preprocessor Handler Class
 *
 * Modified	: 12.05.2016 by Utku Norman  ( norman.utku@metu.edu.tr  )
 * Created	: 18.04.2016 by Utku Norman  ( norman.utku@metu.edu.tr  )
 *
 * People	:	Doga Yucalan ( yucalan.doga@metu.edu.tr )
 *			Utku Norman  ( norman.utku@metu.edu.tr  )
 *
 * Associated code snippet sources :
 *
 *  https://solarianprogrammer.com/2015/05/08/detect-red-circles-image-using-opencv/
 *  http://docs.opencv.org/3.1.0/df/d9d/tutorial_py_colorspaces.html#gsc.tab=0
 *
 *  http://stackoverflow.com/questions/
 * 	1882047/convention-result-and-code-error-c-int-foo
 *
 ******************************************************************************/

// Command Line I/O related headers
#include <cstddef>			// std::nullptr
#include <iostream>			// std::cout, std::cin, std::endl
#include <iomanip>			// std::setw
#include <string>			// std::to_string

#include <opencv2/opencv.hpp>		// Image Processing (OpenCV) header

#include "../include/IPHandler.h"
#include "../include/Visualizer.h"

#define METHOD_FATAL	-1
#define METHOD_SUCCESS	0
#define METHOD_FAILURE	1

/*******************************************************************************
 *
 * Constructor
 *
 ******************************************************************************/

IPHandler::IPHandler( void )
{

	if( dilation_elem == 0 ){ dilation_type = cv::MORPH_RECT; }
	else if( dilation_elem == 1 ){ dilation_type = cv::MORPH_CROSS; }
	else if( dilation_elem == 2) { dilation_type = cv::MORPH_ELLIPSE; }

	dilationElement = cv::getStructuringElement( 
		dilation_type,
		//Size( 2*dilation_size + 1, 2*dilation_size+1 ),
		cv::Size( dilation_size + 1 , dilation_size + 1 ),
		cv::Point( dilation_size , dilation_size ) 
		);


	if( erosion_elem == 0 ){ erosion_type = cv::MORPH_RECT; }
	else if( erosion_elem == 1 ){ erosion_type = cv::MORPH_CROSS; }
	else if( erosion_elem == 2) { erosion_type = cv::MORPH_ELLIPSE; }

	erosionElement = cv::getStructuringElement( 
		erosion_type,
		//Size( 2*erosion_size + 1, 2*erosion_size+1 ),
		cv::Size( erosion_size + 1, erosion_size + 1 ),
		cv::Point( erosion_size, erosion_size ) 
		);

	/*
	borderPoints[ 0 ].x = 0 ;
	borderPoints[ 0 ].y = 0 ;
	borderPoints[ 1 ].x = 0 ;
	borderPoints[ 1 ].y = 0 ;
	borderPoints[ 2 ].x = 0 ;
	borderPoints[ 2 ].y = 0 ;
	*/

}

/*******************************************************************************
 *
 * Public Methods
 *
 ******************************************************************************/

void IPHandler::printState(
	bool printMode 		, 
	bool displayMode 
	)
{
	if( printMode )
	{

		std::cout << "<!---------------------------------------------";
		std::cout << std::endl				;
		std::cout << "IPHandler.printState() called. Printing state:" ;
		std::cout << std::endl				;

	}

	if ( IsNull( state ) )
	{

		std::cerr << "IPHandler: state is Null"		;	
		std::cerr << std::endl			;

		return;

	}
	else
	{
		if( printMode )
		{

			std::cout << std::endl			;
			std::cout << "Listing borderPoints: "	;
			std::cout << std::endl;

			for( int i = 0 ; i < 3 ; i++ )
			{	

				std::cout << std::setw( 4 )	;
				std::cout << "[" << i << "] :"	;

				std::cout <<  state.borderPoints[ i ] ;

				std::cout << std::endl;

			}

		}

		if ( IsNull( state.calibrationData ) )
		{

			std::cerr << "IPHandler: state.calibrationData is Null"	 ;	
			std::cerr << std::endl			;

			return;

		}
		else
		{	
			if( printMode )
			{


				std::cout << "Listing calibrationData: ";
				std::cout << std::endl			;

				std::cout << "pointsHori: "		;
				std::cout << std::endl			;

				for( int i = 0 ; i < 3 ; i++ )
				{	
					std::cout << std::setw( 4 )	;
					std::cout << "[" << i << "] :" 	;

					std::cout << state.calibrationData.pointsHori[ i ] ;
					std::cout << std::endl		;

				}

				std::cout << "pointsTop: "		;
				std::cout << std::endl			;

				for( int i = 0 ; i < 3 ; i++ )
				{	
					std::cout << std::setw( 4 )	;
					std::cout << "[" << i << "] :" 	;

					std::cout << state.calibrationData.pointsTop[ i ] ;
					std::cout << std::endl		;

				}

				std::cout << "pointsBot: "		;
				std::cout << std::endl			;

				for( int i = 0 ; i < 3 ; i++ )
				{	
					std::cout << std::setw( 4 )	;
					std::cout << "[" << i << "] :" 	;

					std::cout << state.calibrationData.pointsBot[ i ] ;
					std::cout << std::endl		;

				}

			}

		}
			
		if ( IsNull( state.mazeData ) )
		{

			std::cerr << "IPHandler: state.mazeData is Null"	 ;	
			std::cerr << std::endl			;

		}
		else
		{

			std::cout << std::endl			;
			std::cout << "Listing mazeData: "	;	
			std::cout << std::endl			;

			std::cout << "image: " 			;

			std::cout << std::endl;



			if ( !state.mazeData.image.data )
			{

				std::cerr << "IPHandler: No mazeImage data!" ;
				std::cerr << std::endl 		;

			}
			else
			{

				if( printMode )
				{

					std::cout << "Showing (IP-mazeImage): "	;
					std::cout << std::endl			;

				}

				if( displayMode )
				{

					showImage( "IP-mazeImage" , state.mazeData.image );

				}

			}

			if( printMode )
			{

				std::cout << "mazePoints: "	;
				std::cout << std::endl		;

				for( int i = 0 ; i < 3 ; i++ )
				{	

					std::cout << std::setw( 4 )		;
					std::cout << "[" << i << "] :"		;

					std::cout << state.mazeData.mazePoints[ i ]	;
					std::cout << std::endl			;

				}

			}
	

		}

		if ( !annotatedImage.data )
		{

			std::cerr <<"IPHandler: No annotatedImage data!" ;
			std::cerr << std::endl ;

		}
		else
		{
			if ( printMode )
			{

				std::cout << "Showing (IP-annotatedImage): ";
				std::cout << std::endl;

			}

			if ( displayMode )
			{

				showImage( "IP-annotatedImage" , annotatedImage );

			}

		}

	} // end-of-if ( IsNull( state ) )

	if( printMode )
	{
		
		std::cout << "---------------------------------------------->";
		std::cout << std::endl;
		std::cout << std::endl;

	}

}

bool IPHandler::initialize( 
	CCPacket& imageData,
	char imageID,
	bool debugMode )
{

	if( debugMode )
	{

		std::cout << "<!---------------------------------------------";
		std::cout << std::endl;
		std::cout << "IPHandler initialize called." ;
		std::cout << std::endl;

	}

	if(imageID == 'H')
	{
		std::cout << "Horizontal image is being preprocessed." ;
		std::cout << std::endl;	
	}
	else if(imageID == 'T')
	{
		std::cout << "Top image is being preprocessed." ;
		std::cout << std::endl;	
	}
	else if(imageID == 'B')
	{
		std::cout << "Bottom image is being preprocessed." ;
		std::cout << std::endl;	
	}


	if ( IsNull( imageData ) )
	{
		std::cerr << "IPHandler: imageData of type CCPacket is Null"	;
		std::cerr << std::endl	;
		return false	;
	}

	// Check for validity of the image
	if ( !imageData.image.data )  // If successfully loaded
	{
		std::cerr << "IPHandler init: No imageData data" ;
		std::cerr << std::endl ;
		return false ;
	}

	if( debugMode )
	{
		std::cout << "Showing mazeImage: "	;
		std::cout << std::endl			;
		showImage( "IP-imageData" , imageData.image ) ;
	}

	cv::Mat inputImage = imageData.image.clone()	;
	cv::Mat annotatedImage = inputImage.clone()	;

	// image packet
	std::vector< cv::Point > vertices	;

	if( debugMode )
	{

		std::cout << "State importing complete." ;
		std::cout << std::endl;

		std::cout << std::endl;
		std::cout << "Begin processing the image." ;
		std::cout << std::endl;

	}

	// Get vertices of image
	if( preHandle(imageData, inputImage, annotatedImage, vertices, debugMode)
		== METHOD_FAILURE )
	{

		if( debugMode )
		{

			std::cerr << "IPHandler.initialize: Pre-handling failed!" ;
			std::cerr << std::endl ;

		}

		return false ;

	}

	if( debugMode )
	{

		std::cout << "Getting vertices complete." ;
		std::cout << std::endl;

	}

	////////////////////////////////////////////////////////
	/////////////////////// EXPORTING //////////////////////
	////////////////////////////////////////////////////////

	if(imageID == 'H')
	{
		state.calibrationData.pointsHori[ 0 ] = cv::Point2f( vertices[ 0 ] )	;
		state.calibrationData.pointsHori[ 1 ] = cv::Point2f( vertices[ 1 ] )	;
		state.calibrationData.pointsHori[ 2 ] = cv::Point2f( vertices[ 2 ] )	;
	}
	else if(imageID == 'T')
	{
		state.calibrationData.pointsTop[ 0 ] = cv::Point2f( vertices[ 0 ] )	;
		state.calibrationData.pointsTop[ 1 ] = cv::Point2f( vertices[ 1 ] )	;
		state.calibrationData.pointsTop[ 2 ] = cv::Point2f( vertices[ 2 ] )	;
	}
	else if(imageID == 'B')
	{
		state.calibrationData.pointsBot[ 0 ] = cv::Point2f( vertices[ 0 ] )	;
		state.calibrationData.pointsBot[ 1 ] = cv::Point2f( vertices[ 1 ] )	;
		state.calibrationData.pointsBot[ 2 ] = cv::Point2f( vertices[ 2 ] )	;
	}

	////////////////////////////////////////////////////////
	////////////////// EXPORTING COMPLETE //////////////////
	////////////////////////////////////////////////////////

	if( debugMode )
	{

		std::cout << "State exporting complete." ;
		std::cout << std::endl	;

		std::cout << "---------------------------------------------->";
		std::cout << std::endl;
		std::cout << std::endl;

	}

	// Successfully completed
	return true ;


}

IPPacket IPHandler::handle( 
	CCPacket& rawImageData,
	bool debugMode )
{

	if( debugMode )
	{
		std::cout << std::endl	;
		std::cout << "<!---------------------------------------------"	;
		std::cout << std::endl	;
		std::cout << "IPHandler.handle() called. handling..."	;
		std::cout << std::endl	;

	}

	if ( IsNull( rawImageData ) )
	{
		std::cerr << "IPHandler: rawImageData of type CCPacket is Null"	;
		std::cerr << std::endl	;
		return IPPacketNull	;
	}

	if ( !rawImageData.image.data )
	{

		std::cerr << "IPHandler: No rawImageData.image data!" ;
		std::cerr << std::endl 	;
		return IPPacketNull	;

	}

	// Declare local variables
	cv::Mat sourceImage			;
	cv::Mat grayImage			;
	cv::Mat processingImage			;
	cv::Mat resultingImage			;

	cv::Mat annotatedImage			;

	std::vector< cv::Point > vertices	;

	cv::Point2f centerStart			;
	cv::Point2f centerEnd			;
	cv::Point2f centerBall			;

	float radiusStart			;
	float radiusEnd				;
	float radiusBall			;

	// Initialize local variables
	sourceImage 	= rawImageData.image.clone()	;
	annotatedImage 	= sourceImage.clone()		;

	// Initialize private variables
	this -> debugMode = debugMode		;

	if( debugMode )
	{

		std::cout << std::endl	;
		std::cout << "Begin processing the raw image."	;
		std::cout << std::endl	;

	}

	// Get vertices of sourceImage
	if( preHandle( rawImageData , sourceImage , annotatedImage , vertices, debugMode )
		== METHOD_FAILURE )
	{

		if( debugMode )
		{

			std::cerr << "IPHandler: Pre-handling failed!" ;
			std::cerr << std::endl ;

		}

		return IPPacketNull ;

	}

	//showImage( "IP-inputImage--", inputImage );
	//showImage( "IP-annotatedImage--", annotatedImage );

	// Find the start area for input image
	if( thresholdingForFeaturePoints(sourceImage, annotatedImage,'R',centerStart, radiusStart)
		== METHOD_FAILURE )
	{

		std::cerr << "IPHandler: 'R' search failed!" ;
		std::cerr << std::endl ;

		return IPPacketNull ;

	}


	// Find the end area for input image
	if( thresholdingForFeaturePoints(sourceImage, annotatedImage,'G',centerEnd, radiusEnd)
		== METHOD_FAILURE )
	{

		std::cerr << "IPHandler: 'G' search failed!" ;
		std::cerr << std::endl		;

		return IPPacketNull		;

	}

	// Find the ball for input image
	if( thresholdingForFeaturePoints(sourceImage, annotatedImage,'B',centerBall, radiusBall)
		== METHOD_FAILURE )
	{

		std::cerr << "IPHandler: 'G' search failed!"		;
		std::cerr << std::endl					;

		return IPPacketNull					;

	}

	if( debugMode )
	{

		std::cout << "R & G search complete."			;
		std::cout << std::endl					;

	}


	// maze image generation


	resultingImage.create( sourceImage.size() , sourceImage.type( ) ) ;

	adjustImageColor( sourceImage, grayImage , CV_BGR2GRAY ) ;

	cv::dilate( grayImage, processingImage , dilationElement );
   
	cv::erode( processingImage, processingImage , erosionElement );

	cv::Canny( processingImage , processingImage , edgeThresh1 , edgeThresh2 , 3 ) ;

	resultingImage = cv::Scalar::all( 0 );


	sourceImage.copyTo( resultingImage , processingImage );


	/* 0: Binary
	1: Binary Inverted
	2: Threshold Truncated
	3: Threshold to Zero
	4: Threshold to Zero Inverted

	*/
	int const threshold_type = 0		;
	int const max_BINARY_value = 255	;
	int const threshold_value = 5 		;
	//threshold( src_gray, dst, threshold_value, max_BINARY_value,threshold_type );
	threshold( resultingImage, resultingImage, threshold_value , max_BINARY_value,threshold_type ) ;

	//for( int i = 0 ; i < dilation_iterations ; i++ )
	//{
	if( dilation_iterations != 0 )
	{

		cv::dilate(resultingImage,resultingImage, 
			cv::Mat(),
			cv::Point(-1,-1),
			dilation_iterations,  // iterations
			1 ,  // borderType=BORDER_CONSTANT
			1 ); // borderValue=morphologyDefaultBorderValue() 
			//printf("hallo\n");

	}

	////////////////////////////////////////////////////////
	/////////////////////// EXPORTING //////////////////////
	////////////////////////////////////////////////////////

	state.borderPoints[ 0 ] = cv::Point2f( vertices[ 0 ] )	;
	state.borderPoints[ 1 ] = cv::Point2f( vertices[ 1 ] )	;
	state.borderPoints[ 2 ] = cv::Point2f( vertices[ 2 ] )	;

	state.mazeData.mazePoints[ 0 ] = centerStart			;
	state.mazeData.mazePoints[ 1 ] = centerEnd			;
	state.mazeData.mazePoints[ 2 ] = centerBall			;

	state.mazeData.image = resultingImage.clone( )		;

	// Export private variables
	this -> annotatedImage = annotatedImage.clone( )		;

	////////////////////////////////////////////////////////
	////////////////// EXPORTING COMPLETE //////////////////
	////////////////////////////////////////////////////////

	if( debugMode )
	{

		std::cout << "State exporting complete." ;
		std::cout << std::endl;

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

int IPHandler::preHandle(
	CCPacket imageData			,
	cv::Mat& inputImage			,
	cv::Mat& annotatedImage			,
	std::vector< cv::Point >& vertices	,
	bool debugMode
	)
{

	cv::Mat thresholdedImage				;
	cv::Mat colorAdjustedImage 				;

	std::vector< std::vector< cv::Point > > contours	;
	std::vector< cv::Vec4i > hierarchy			;
	
	// Adjust colors
	adjustImageColor( inputImage, colorAdjustedImage , CV_BGR2GRAY ) ;

	/*
	if( debugMode )
	{
		std::cout << "Prehandling: adjustImageColor complete" ;
		std::cout << std::endl;
	}
	*/

	// Do thresholding
	thresholdImage( colorAdjustedImage , thresholdedImage )	;

	/*
	if( debugMode )
	{
		std::cout << "Prehandling: thresholdImage complete" ;
		std::cout << std::endl;
	}
	*/

	// Find contours (and hierarchy - just to draw)
	extractContours( thresholdedImage.clone() , contours , hierarchy ) ;

	/*
	if( debugMode )
	{
		std::cout << "Prehandling: extractContours complete" ;
		std::cout << std::endl;
	}
	*/

	/*
	if( debugMode )
	{

		std::cout << "Showing contours:" ;
		std::cout << std::endl;

		displayContours(
			"IP-contours" , 
			annotatedImage.clone() , contours , hierarchy ,
			false );

	}*/

	// Find board vertices & extract the image inside the triangle
	if( findBoardVertices( inputImage , annotatedImage , contours , vertices ) 
		== METHOD_FAILURE )
	{

		if( debugMode )
		{

			std::cerr << "IPHandler: Finding board vertices failed!" ;
			std::cerr << std::endl ;
		
		}

		return METHOD_FAILURE ;

	}

	if( debugMode )
	{

		std::cout << "Pre-handling completed." ;
		std::cout << std::endl;

	}

}

void IPHandler::adjustImageColor(
	const cv::Mat inputImage	,
	cv::Mat& outputImage		, 
	int colorCode
	)
{

	cv::cvtColor( inputImage , outputImage , colorCode ) ;

}

// ..
void IPHandler::thresholdImage(
	const cv::Mat inputImage	,
	cv::Mat& outputImage	
	)
{

	// Apply thresholding, thresholds may be adjusted
	cv::Canny (inputImage , outputImage , 100 , 500 ) ;

}

void IPHandler::applyDilation(
	const cv::Mat inputImage	,
	cv::Mat& outputImage	
	)
{

	cv::dilate( inputImage , outputImage , cv::Mat( ) ) ;

}

// Find contours and hierarchy
void IPHandler::extractContours(
	const cv::Mat image ,
	std::vector< std::vector< cv::Point > >& contours ,
	std::vector< cv::Vec4i >& hierarchy
	)
{

	//  1st: CV_RETR_CCOMP, CV_RETR_EXTERNAL, CV_RETR_TREE
	//  2nd: CV_CHAIN_APPROX_NONE, CV_CHAIN_APPROX_SIMPLE
	// CV_CHAIN_APPROX_TC89_L1,CV_CHAIN_APPROX_TC89_KCOS
	//cv::findContours( image , contours , hierarchy , CV_RETR_CCOMP , CV_CHAIN_APPROX_SIMPLE )	;

	cv::findContours( image , contours , hierarchy , 
		CV_RETR_EXTERNAL , CV_CHAIN_APPROX_NONE )	;

}



// Method for finding board vertices and extracting image inside the triangle
int IPHandler::findBoardVertices(
	cv::Mat& inputImage					,
	cv::Mat& annotatedImage					,
	std::vector< std::vector< cv::Point > > contours	,
	std::vector< cv::Point >& vertices)
{

	std::vector< cv::Point > approxContour	; // Dummy contour to hold an approximate contour
	std::vector< cv::Point > desiredContour	; // ...
	std::vector< cv::Point > desiredApproxContour	; // ...
	bool triangleFound = false	;
	double comparedMeasure = -1.0 ;// = cv::arcLength( contours[ i ] , true ) ; //* 0.02 ;
	int greatestID ;
	
	if( debugMode )
	{
		std::cout << "findBoardVertices begins" ;
		std::cout << std::endl;
	}

	//displayMatConvention( annotatedImage );
	//showImage("IP-convention", annotatedImage );
	//cv::waitKey( 0 );


	for ( int i = 0 ; i < contours.size() ; i++ )
	{
		// Approximate contour with accuracy proportional to the contour perimeter

		//double epsilon = cv::arcLength( contours[ i ] , true ) * 0.15 ; //* 0.02 ;
		double epsilon = cv::arcLength( contours[ i ] , true ) * 0.03 ; //* 0.02 ;

		cv::approxPolyDP( contours[ i ] , approxContour , epsilon , true ) ;

		// Skip small or non-convex objects 
		//if (std::fabs(cv::contourArea(contours[i]))<200 || !cv::isContourConvex(approxContour))
		//	continue;
		// Skip small only
		//if ( std::fabs( cv::contourArea( contours[ i ] ) ) < 1000 )
		if ( std::fabs( cv::contourArea( approxContour ) ) < 1000 )
		{

			continue;

		}

		// If the approximation curve is a triangle
		if ( approxContour.size( ) == 3 )
		{
	
			triangleFound = true	; // Assert that a border candidate is found

			if( false ) //debugMode )
			{
				std::cout << "!!!!!!!!!!! triangleFound!" ;
				std::cout << std::endl;
			}

			if( comparedMeasure > cv::contourArea( contours[ i ] ) ) // a smaller contour is found
			{

				continue;

			}
			else
			{
					
				comparedMeasure =  cv::contourArea( contours[ i ] ) ;

				desiredApproxContour = approxContour ;

				vertices = contours[ i ] ;
				desiredContour =  contours[ i ] ; //approxContour ;

			}

			//if( comparedMeasure == -1 )

			// DEBUG: Annote all vertices of the triangle 
			/*
			if(debugMode)
				for( std::vector< cv::Point >::size_type j = 0;j != contours[ i ].size( ) ; j++ ) 
					setLabel( annotatedImage , "H" , contours[ i ][ j ] );
			*/
		}
		/*
		else if ( approxContour.size( ) >= 3 && cv::contourArea( contours[ i ] ) > vertices)		
		{

			std::vector<cv::Point > furtherApproxContour;
			// Convention:
			// vertices (myRobotArea, otherRobotArea, top)
			// xMin -> myRobotArea
			// xMax	-> otherRobotArea
			// yMin -> top

			//find the xMin -> myRobotArea

			int selectedID = 0;

			int pixelNo = approxContour[ 0 ].x ;

			for( std::vector< cv::Point >::size_type m = 1 ; m != approxContour.size() ; m++ ) 
			{

				if( approxContour[ m ].x < pixelNo )
				{

					selectedID = m ;

					pixelNo = approxContour[ m ].x;

				}

			}

			furtherApproxContour.push_back( approxContour[ selectedID ] ) ;

			approxContour.erase( approxContour.begin() + selectedID ) ;

			// xMax	-> otherRobotArea

			selectedID = 0 ;

			pixelNo = approxContour[ 0 ].x ;

			for( std::vector< cv::Point >::size_type m = 1 ; m != approxContour.size() ; m++ ) 
			{

				if( approxContour[ m ].x > pixelNo  )
				{

					selectedID = m ;

					pixelNo = approxContour[ m ].x ;

				}

			}

			furtherApproxContour.push_back( approxContour[ selectedID ] ) ;

			approxContour.erase( approxContour.begin() + selectedID ) ;

			// find the yMin -> top

			selectedID = 0 ;

			pixelNo = approxContour[ 0 ].y ;

			for( std::vector< cv::Point >::size_type m = 1 ; m != approxContour.size() ; m++ ) 
			{

				if( approxContour[ m ].y < pixelNo )
				{

					selectedID = m ;

					pixelNo = approxContour[ m ].x ;

				}

			}

			furtherApproxContour.push_back( approxContour[ selectedID ] ) ;

			approxContour.erase( approxContour.begin() + selectedID ) ;


			//double newMeasure = cv::arcLength( furtherApproxContour , true );
			double newMeasure = cv::contourArea( furtherApproxContour ) ;

			if( !triangleFound )
			{

				triangleFound = true	;  // Assert that a border candidate is found

				measure = newMeasure ;

				greatestID = i ;

				vertices = furtherApproxContour ;
			
			}
			else if( measure < newMeasure )
			{

				measure = newMeasure	;

				greatestID = i ;

				vertices = furtherApproxContour ;

			}
			
	    	} 	// end-of-if ( approxContour.size( ) >= 3 )
	    	*/

	}		// end-of-for each contour

	cv::Mat dummyImage	;

	// Delete everything outside the triangle
	cv::Mat mask = cv::Mat::zeros( inputImage.size( ) , CV_8UC1 );

	std::vector< std::vector< cv::Point > > dummyContours ;
	dummyContours.push_back( vertices );

	cv::drawContours( mask , dummyContours , 0 ,  cv::Scalar( 255 ) , CV_FILLED );

	inputImage    .copyTo( dummyImage , mask ) ;
	inputImage 	= dummyImage.clone( ) ;

	annotatedImage.copyTo( dummyImage , mask ) ;
	annotatedImage 	= dummyImage.clone( ) ;


	// Annote all vertices of the approximation curve vector and extract the vertices
	/*
	for( std::vector< cv::Point >::size_type i = 0 ; i != vertices.size() ; i++ ) 
	{

		setLabel( annotatedImage , "V" , vertices[ i ] );

		//vertices = vertices;

	}*/


	if( triangleFound )
	{

		if( debugMode )
		{
			std::cout << "findBoardVertices continues. Setting labels:" ;
			std::cout << std::endl;
		}

		//find the xMin -> myRobotArea

		int myRobotAreaID = 0;

		int pixelNo = desiredApproxContour[ 0 ].x ;

		for( std::vector< cv::Point >::size_type m = 1 ; m != 3 ; m++ ) 
		{

			if( desiredApproxContour[ m ].x < pixelNo )
			{

				myRobotAreaID = m ;

				pixelNo = desiredApproxContour[ m ].x;

			}

		}

		// xMax	-> otherRobotArea

		int otherRobotAreaID = 0 ;

		pixelNo = desiredApproxContour[ 0 ].x ;

		for( std::vector< cv::Point >::size_type m = 1 ; m != 3 ; m++ ) 
		{

			if( desiredApproxContour[ m ].x > pixelNo  )
			{

				otherRobotAreaID = m ;

				pixelNo = desiredApproxContour[ m ].x ;

			}

		}

		int sumID = myRobotAreaID + otherRobotAreaID ;
		int topID ;

		switch( sumID )
		{	

			case 1:
				topID = 2 ;
				break ;
			case 2:
				topID = 1 ;
				break ;
			case 3: 
				topID = 0 ;
				break ;

		}

		if( debugMode )
		{

			std::cout << "Search for the board vertices is completed." ;
			std::cout << std::endl ;
			std::cout << "Candidate found of size: " << desiredApproxContour.size() ;
			std::cout << std::endl ;

		}

		std::vector< cv::Point > orderedApproxContour;

		orderedApproxContour.push_back( desiredApproxContour[ myRobotAreaID 	]	) ;
		orderedApproxContour.push_back( desiredApproxContour[ otherRobotAreaID 	]	) ;
		orderedApproxContour.push_back( desiredApproxContour[ topID 		]	) ;
	
		if( debugMode )
		{

			std::cout << "myRobotArea    : ID = " << myRobotAreaID ;
			std::cout << "Point: " << desiredApproxContour[ myRobotAreaID ] << "==" <<  orderedApproxContour[ 0 ] ;
			std::cout << std::endl ;

			std::cout << "otherRobotArea : ID = " << myRobotAreaID ;
			std::cout << "Point: " << desiredApproxContour[ otherRobotAreaID ] << "==" <<  orderedApproxContour[ 1 ] ;
			std::cout << std::endl ;

			std::cout << "top            : ID = " << myRobotAreaID ;
			std::cout << "Point: " << desiredApproxContour[ topID ] << "==" <<  orderedApproxContour[ 2 ] ;
			std::cout << std::endl ;

		}



		// vertices (myRobotArea, otherRobotArea, top)
		// M xMin 	-> myRobotArea
		// O xMax		-> otherRobotArea
		// T third 	-> top
		setLabel( annotatedImage , "M" , orderedApproxContour[ 0 ] );
		setLabel( annotatedImage , "O" , orderedApproxContour[ 1 ] );
		setLabel( annotatedImage , "T" , orderedApproxContour[ 2 ] );

		if( debugMode )
		{

			std::cout << "Ordering complete." ;
			std::cout << std::endl ;

			std::cout << "Candidate found of size: " << orderedApproxContour.size() ;
			std::cout << std::endl ;

			std::cout << "Candidate found of area: " ; 
			std::cout << cv::contourArea( orderedApproxContour ) ;
			std::cout << std::endl ;

		}

		if( false ) //displayMode )
		{

			showImage( "IP-findboard-inputImage" , inputImage );
			showImage( "IP-findboard-annotatedImage" , annotatedImage );
			cv::waitKey( 0 );

		}


		vertices = orderedApproxContour;	//export

		if( debugMode )
		{

			std::cout << "Exporting complete." ;
			std::cout << std::endl ;

			std::cout << "vertices of size: " << vertices.size() ;
			std::cout << std::endl ;


			std::cout << "vertices of elements: " << vertices[ 0 ] << vertices[ 1 ] << vertices[ 2 ] ;
			std::cout << std::endl ;

		}



		return METHOD_SUCCESS	; 

	}
	else
	{

		std::cerr << "IPHandler: Border not found!" ;
		std::cerr << std::endl ;

		return METHOD_FAILURE	; 
	}

}

// Method for detecting red ("start"), green ("end") and blue ("ball")
// return 
int IPHandler::thresholdingForFeaturePoints(
	cv::Mat& inputImage		,
	cv::Mat& annotatedImage		,
	const char colorID		,
	cv::Point2f& center		,
	float& radius
	)
{

	// Set Label "colorID" to center
	std::string colorName	;
 	colorName += colorID	; // Cast char to string

	if( debugMode )
	{

		std::cout << "thresholdingForFeaturePoints called for color: " ;
		std::cout << colorName << std::endl 	;

	}

	cv::Mat colorImage 	;
	cv::Mat hsvImage	;
	cv::Mat dummy 		;
	cv::Mat tDummy 		; 	// thresholded dummy
	cv::Mat dDummy		; 	// dilated thresholded dummy

	std::vector< std::vector< cv::Point > > contours;
    	std::vector< cv::Vec4i > hierarchy;

	std::vector< std::vector< cv::Point > > dummyContour( 1 );

	adjustImageColor( inputImage , hsvImage , CV_BGR2HSV );

	switch( colorID )// Apply filtering for the specific color ID
	{
		
		case 'R': // If RED
		{

			// Hsv of the color 'red': (0, 255, 255)
			// Hue margin is selected to be +10, -20, it may be changed
			int hue_lo_1 	= 0	, hue_hi_1 	= 10	;
			int hue_lo_2 	= 160	, hue_hi_2 	= 179	;
			int sat_lo 	= 100	, sat_hi 	= 255	;			
			int val_lo 	= 100	, val_hi 	= 255	;
	
			cv::Scalar lowerLim1( hue_lo_1 , sat_lo , val_lo );
			cv::Scalar upperLim1( hue_hi_1 , sat_hi , val_hi );

			cv::Scalar lowerLim2( hue_lo_2 , sat_lo , val_lo );
			cv::Scalar upperLim2( hue_hi_2 , sat_hi , val_hi );


			cv::Mat lowerDummy;
			cv::Mat upperDummy;
	
			// Threshold in between above limits, save image to *Dummy and then combine 'em
			cv::inRange( hsvImage , lowerLim1 , upperLim1 , lowerDummy );
			cv::inRange( hsvImage , lowerLim2 , upperLim2 , upperDummy );	

			cv::addWeighted( lowerDummy , 1.0 , upperDummy , 1.0 , 0.0 , dummy );

			/*
			// DEBUG: Show the dummy image of red
			if( debugMode )
			{
				showImage("Rdummy", dummy);
			}
			*/

			break ;
		}

		case  'G': // If GREEN
		{

			// Hsv of the color 'green': (80, 255, 255)
			// Hue margin is selected to be +-10, it may be changed
			int hue_lo 	= 70	, hue_hi 	= 90	;
			int sat_lo 	= 100	, sat_hi 	= 255	;			
			int val_lo 	= 100	, val_hi 	= 255	;

			cv::Scalar lowerLim( hue_lo , sat_lo , val_lo )	;
			cv::Scalar upperLim( hue_hi , sat_hi , val_hi )	;

			// Threshold in between above limits, save image to dummy
			cv::inRange(hsvImage,lowerLim,upperLim,dummy)	;

			/*
			// DEBUG: Show the dummy image of green
			if( debugMode )
			{
				showImage("Gdummy", colorImage);
			}
			*/

			break ;
		}

		case  'B': // If BLUE
		{

			// Hsv of the color 'blue': (115, 255, 255)
			// Hue margin is selected to be +-5, it may be changed
			int hue_lo 	= 110 , hue_hi 	= 120	;
			int sat_lo 	= 120 , sat_hi 	= 255	;			
			int val_lo 	= 120 , val_hi 	= 255	;

			cv::Scalar lowerLim( hue_lo , sat_lo , val_lo )	;
			cv::Scalar upperLim( hue_hi , sat_hi , val_hi )	;

			// Threshold in between above limits, save image to dummy
			cv::inRange( hsvImage , lowerLim , upperLim , dummy )	;

			// DEBUG: Show the dummy image of blue
			/*
			if( debugMode )
			{
				showImage("Bdummy", dummy);
			}
			*/

			break ;
		}
		default: // If colorID is not listed
		{

			std::cerr << "IPHandler: Undefined color." << std::endl;

		}
	}

	if ( !dummy.data )
	{

		std::cerr <<"IPHandler: No dummy data!" ;
		std::cerr << std::endl ;

	}

	if( debugMode )
	{

		std::cout << "R,G,B switching complete." ;
		std::cout << std::endl;

	}
	

	// Threshold and dilate the dummy, find contours

	thresholdImage( dummy , tDummy )			;

	applyDilation( tDummy , dDummy )			;

	extractContours( dDummy , contours , hierarchy )	;

	if( debugMode )
	{

		std::cout << "Threshold, dilate & contours extraction complete."	;
		std::cout << std::endl	;

	}
	
	if ( contours.size() != 0 ) // Select the contour with maximum area => the true one!
	{
		
		dummyContour[ 0 ] = contours[ 0 ]	;


	}
	else
	{

		std::cerr << "IPHandler: thresholdingForFeaturePoints, contour not found!"	;
		std::cerr << std::endl			;

		return ( METHOD_FAILURE );
	}

  	for( int i = 1 ; i < contours.size( ) ; i++ )
  	{

		if( cv::contourArea( contours[ i ] ) > cv::contourArea( dummyContour[ 0 ] ) )
		{

			dummyContour[ 0 ] = contours[ i ]	;

		}

  	}

	// Find the minimum enclosing circle
	cv::minEnclosingCircle( dummyContour[ 0 ] , center , radius );

	setLabel( annotatedImage , colorName , center );

	// Create mask
	cv::Mat mask = cv::Mat::zeros(inputImage.size(), CV_8UC1);
	cv::drawContours( mask , dummyContour , 0 , cv::Scalar( 255 ) , CV_FILLED );

	inputImage.copyTo( colorImage , mask );

	// ??
	inRange(colorImage.clone(), cv::Scalar(1,1,1), cv::Scalar(255,255,255), colorImage);


	if ( !mask.data )
	{

		std::cerr <<"IPHandler: No mazeImage data!" ;
		std::cerr << std::endl ;

	}


	if( debugMode )
	{

		std::cout << "Showing color mask for '"	;
		std::cout << colorName <<"':" 		;
		std::cout << std::endl			;

		std::string msg("IP-")			;
		msg += colorName			;
		showImage( msg , mask )			;

	}

	return ( METHOD_SUCCESS );

}
