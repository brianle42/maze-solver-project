////////////////////////////////////////////////////////////////////////////////
//
// PSMHandler.cpp - Source File
//
// Description: Moonlight Company
//              Maze Solver Project
//              Platform State Mapper (PSM) Class
//
// Modified : 09.05.2016 by Doga Yucalan ( yucalan.doga@metu.edu.tr  )
// Created  : 16.04.2016 by Utku Norman  ( norman.utku@metu.edu.tr )
//
// Style:
//  http://geosoft.no/development/cppstyle.html#Include Files
//
// Associated code-snippet sources:
// https://solarianprogrammer.com/2015/05/08/detect-red-circles-image-using-opencv/
// http://docs.opencv.org/3.1.0/df/d9d/tutorial_py_colorspaces.html#gsc.tab=0
//
////////////////////////////////////////////////////////////////////////////////

// Command Line I/O related headers
#include <cstddef>  // std::nullptr
#include <iostream> // std::cout, std::cin, std::endl
#include <iomanip>  // std::setw

// Image Processing (OpenCV) header
#include <opencv2/opencv.hpp>

// Include class-related definitions 
//	such as the struct PSMPacket
#include "../include/PSMHandler.h"

// Visualization header
#include "../include/Visualizer.h"

////////////////////////////////////////////////////////////////////////////////
/* Constructor */
PSMHandler::PSMHandler( void )
{
}

////////////////////////////////////////////////////////////////////////////////
/* Public Methods */

void PSMHandler::printState(
	bool printMode 		, 
	bool displayMode 
	)
{

	if( printMode )
	{

		std::cout << "<!---------------------------------------------";
		std::cout << std::endl;
		std::cout << "PSMHandler.printState() called. Printing state:" ;
		std::cout << std::endl;

	}
	

	if ( IsNull( state ) )
	{

		std::cerr << "state is Null";	
		std::cerr << std::endl;

		return;

	}
	else
	{

		if( printMode )
		{
			std::cout << std::endl			;
			std::cout << "Listing rotations: "	;
			std::cout << std::endl;

			for( int i = 0 ; i < 2 ; i++ )
			{	

				std::cout << "[" << i << "] :"	;

				std::cout <<  state.heights[ i ] ;

				std::cout << std::endl;

			}
		}

	}

	if( printMode )
	{
		
		std::cout << "---------------------------------------------->";
		std::cout << std::endl;
		std::cout << std::endl;

	}

}

PSMPacket PSMHandler::handle( 
	cv::Point2f borderPoints[ 3 ]	,
	FeatureData calibrationData		,
	bool debugMode
	)
{

	if( debugMode )
	{
		std::cout << std::endl	;
		std::cout << "<!---------------------------------------------"	;
		std::cout << std::endl	;
		std::cout << "PSMHandler.handle() called. handling..."	;
		std::cout << std::endl	;

	}

	if ( IsNull(calibrationData) )
	{
		std::cerr << "PSMHandler: featureData of type IPPacket is Null";
		std::cerr << std::endl;
		return PSMPacketNull;
	}
	
	// Declare local variables
	cv::Point2f vertices[3]; // myRobotArea, otherRobotArea, top
	cv::Point2f verticesHori[3]; // myRobotArea, otherRobotArea, top
	cv::Point2f verticesTop[3]; // myRobotArea, otherRobotArea, top
	cv::Point2f verticesBot[3]; // myRobotArea, otherRobotArea, top

	float edgeLength[2] = {0, 0};
	float edgeLengthHori[2] = {0, 0};

	int whereAmI = -1;
	int whereIsOther = -1;

	// fitLine arrays: (m1, c1, m2, c2) where y = m*x+c
	// m1 & c1 represents the upper fit, m2 & c2 represent the lower fit 
	float fitLineMy [4] = {0, 0, 0, 0};
	float fitLineOther[4] = {0, 0, 0, 0};

	float fitMy = 0;
	float fitOther = 0;

	// Initialize local variables
	for(int i = 0; i < 3; i++)
	{
		vertices[i] = borderPoints[i];
		verticesHori[i] = calibrationData.pointsHori[i];
		verticesTop[i] = calibrationData.pointsTop[i];
		verticesBot[i] = calibrationData.pointsBot[i];
	}
	
	if( debugMode )
	{
		
		std::cout << std::endl	;
		std::cout << "vertices can be listed as follows:"	;
		std::cout << std::endl	;


		std::cout << "vertices:" ;

		for(int i = 0; i < 3; i++)
		{
			std::cout << "| i : " << i << ": " ;;
			std::cout << vertices[i] << ", ";

		}

		std::cout << std::endl	;
		std::cout << "verticesHori:" ;

		for(int i = 0; i < 3; i++)
		{
			std::cout << "| i : " << i << ": " ;
			std::cout << verticesHori[i] << ", ";
		}
		
		std::cout << std::endl	;
		std::cout << "verticesTop:" ;

		for(int i = 0; i < 3; i++)
		{
			std::cout << "| i : " << i << ": " ;
			std::cout << verticesTop[i] << ", ";

		}

		std::cout << std::endl	;
		std::cout << "verticesBot:" ;

		for(int i = 0; i < 3; i++)
		{
			std::cout << "| i : " << i << ": " ;
			std::cout << verticesBot[i] << ", ";

		}

		std::cout << std::endl	;

		std::cout << "Begin extracting the rotations."	;
		std::cout << std::endl	;

	}	

	// Get edge lengths
	if( getEdgeLength(vertices, edgeLength, debugMode)
		== METHOD_FAILURE )
	{

		if( debugMode )
		{

			std::cerr << "PSMHandler: Getting edge lengths of image incomplete!" ;
			std::cerr << std::endl ;

		}

		return PSMPacketNull ;

	}

	if( debugMode )
	{

		std::cout << "Getting edge lengths of image complete." ;
		std::cout << std::endl;

	}

	if( debugMode )
	{
		std::cout << "edgeLength :"		;
		std::cout << std::endl;

		for( int i = 0 ; i < 2 ; i++ )
		{	

		std::cout << std::setw( 4 )		;
		std::cout << "[" << i << "] :"		;

		std::cout << edgeLength[ i ]	;
		std::cout << std::endl			;
		
		}
	}

	if( getEdgeLength(verticesHori, edgeLengthHori, debugMode)
		== METHOD_FAILURE )
	{

		if( debugMode )
		{

			std::cerr << "PSMHandler: Getting edge lengths of horizontal image incomplete!" ;
			std::cerr << std::endl ;

		}

		return PSMPacketNull ;

	}

	if( debugMode )
	{

		std::cout << "Getting edge lengths of horizontal image complete." ;
		std::cout << std::endl;

	}

	if( debugMode )
	{
		std::cout << "edgeLengthHori :"		;
		std::cout << std::endl;

		for( int i = 0 ; i < 2 ; i++ )
		{	

		std::cout << std::setw( 4 )		;
		std::cout << "[" << i << "] :"		;

		std::cout << edgeLengthHori[ i ]	;
		std::cout << std::endl			;
		
		}
	}

	// Set Fit
	if( setFit(edgeLengthHori, verticesTop, verticesBot, fitLineMy, fitLineOther, debugMode)
		== METHOD_FAILURE )
	{

		if( debugMode )
		{

			std::cerr << "PSMHandler: Setting fit incomplete!" ;
			std::cerr << std::endl ;

		}

		return PSMPacketNull ;

	}

	if( debugMode )
	{

		std::cout << "Setting fit complete." ;
		std::cout << std::endl;

	}
	
	if ( debugMode )
	{ 
		std::cout << "fitLineMy properties :"		;
		std::cout << std::endl;

		std::cout << "Upper line: y = "		;
		std::cout << fitLineMy[ 0 ]	;
		std::cout << " * x + "		;
		std::cout << fitLineMy[ 1 ]	;
		std::cout << std::endl		;

		std::cout << "Lower line: y = "		;
		std::cout << fitLineMy[ 2 ]	;
		std::cout << " * x + "		;
		std::cout << fitLineMy[ 3 ]	;
		std::cout << std::endl		;

		std::cout << "fitLineOther properties :"		;
		std::cout << std::endl;

		std::cout << "Upper line: y = "		;
		std::cout << fitLineOther[ 0 ]	;
		std::cout << " * x + "		;
		std::cout << fitLineOther[ 1 ]	;
		std::cout << std::endl		;

		std::cout << "Lower line: y = "		;
		std::cout << fitLineOther[ 2 ]	;
		std::cout << " * x + "		;
		std::cout << fitLineOther[ 3 ]	;
		std::cout << std::endl		;
	}

	// Where is everyone?
	whereIsIt(edgeLength, edgeLengthHori, whereAmI, whereIsOther);
	
	if ( debugMode )
	{ 
		std::cout << "whereIsIt :"		;
		std::cout << std::endl;

		std::cout << "whereAmI: "		;
		std::cout << whereAmI			;
		std::cout << std::endl			;
		
		std::cout << "whereIsOther: "		;
		std::cout << whereAmI			;
		std::cout << std::endl			;
	}

	// Get fit results
	getFitResult(edgeLength, fitLineMy, whereAmI, fitLineOther, whereIsOther, fitMy, fitOther);
	
	if( fitMy > 100 || fitMy < -100  || fitOther > 100 || fitOther < -100 )
	{
	
			std::cout << std::endl			;
			std::cout << "Listing rotations: "	;
			std::cout << std::endl;

			std::cout << "FitMy: "	;
			std::cout <<  fitMy ;
			std::cout << std::endl;

			std::cout << "FitOther: "	;
			std::cerr <<  fitOther ;
			std::cerr << std::endl;
		
		std::cerr << "PSMHandler: Fit results are out of bounds!";
		std::cerr << std::endl;
		
		return PSMPacketNull;
	
	}

	if( debugMode )
	{
			std::cout << std::endl			;
			std::cout << "Listing rotations: "	;
			std::cout << std::endl;

			std::cout << "FitMy: "	;
			std::cout <<  fitMy ;
			std::cout << std::endl;

			std::cout << "FitOther: "	;
			std::cout <<  fitOther ;
			std::cout << std::endl;
	}

	if( debugMode )
	{

		std::cout << "Begin state exporting." ;
		std::cout << std::endl;
	}

	////////////////////////////////////////////////////////
	/////////////////////// EXPORTING //////////////////////

	state.heights[ 0 ] = fitMy;			
	state.heights[ 1 ] = fitOther;				

	//////////////////// EXPORTING ENDED ///////////////////
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

////////////////////////////////////////////////////////////////////////////////
/* Private Methods */

int PSMHandler::getEdgeLength(
	cv::Point2f* vertices,	
	float* edgeLength,
	bool debugMode)
{
	cv::Point2f length;

	length.x = std::fabs(vertices[2].x - vertices[0].x); // top - my edge
	length.y = std::fabs(vertices[2].y - vertices[0].y);
	edgeLength[0] = std::sqrt(length.x * length.x + length.y * length.y);
	
	length.x = std::fabs(vertices[2].x - vertices[1].x); // top - other edge
	length.y = std::fabs(vertices[2].y - vertices[1].y);
	edgeLength[1] = std::sqrt(length.x * length.x + length.y * length.y);

	if( !edgeLength[0] || !edgeLength[1])
	{
		std::cout << "PSMHandler::getEdgeLength is not successful!";
		std::cout << std::endl;
		return METHOD_FAILURE;
	}
	else
	{
		if ( debugMode )
		{
			std::cout << "PSMHandler::getEdgeLength is successful.";
			std::cout << std::endl;
		}
		return METHOD_SUCCESS;
	}
}

int PSMHandler::setFit(
	float* edgeLengthHori,
	cv::Point2f* verticesTop,
	cv::Point2f* verticesBot,
	float* lineMy,
	float* lineOther,
	bool debugMode)
{
	float edgeLengthTop[2];
	float edgeLengthBot[2];

	// Get edge lengths
	if( getEdgeLength(verticesTop, edgeLengthTop, debugMode)
		== METHOD_FAILURE )
	{

		if( debugMode )
		{

			std::cerr << "PSMHandler::setFit: Getting edge length of top image incomplete!" ;
			std::cerr << std::endl ;

		}

		return METHOD_FAILURE ;

	}

	

	if ( debugMode )
	{
		std::cout << "edgeLengthTop :"		;
		std::cout << std::endl;

		for( int i = 0 ; i < 2 ; i++ )
		{	

		std::cout << std::setw( 4 )		;
		std::cout << "[ " << i << " ] ";
		std::cout << edgeLengthTop[ i ]	;
		std::cout << std::endl			;
		
		}
	}

	if( 	getEdgeLength(verticesBot, edgeLengthBot, debugMode)
		== METHOD_FAILURE )
	{

		if( debugMode )
		{

			std::cerr << "PSMHandler::setFit: Getting edge length of bottom image incomplete!" ;
			std::cerr << std::endl ;

		}

		return METHOD_FAILURE ;

	}

	if ( debugMode )
	{
		std::cout << "edgeLengthBot :"		;
		std::cout << std::endl;

		for( int i = 0 ; i < 2 ; i++ )
		{	

		std::cout << std::setw( 4 )		;
		std::cout << "[ " << i << " ] ";
		std::cout << edgeLengthBot[ i ]	;
		std::cout << std::endl			;
		
		}
	}

	// Find fit line

	// line arrays: (m1, c1, m2, c2) where y = m*x+c
	// m1 & c1 represents the upper fit, m2 & c2 represent the lower fit 
	lineMy[0] = HEIGHT_RANGE/(edgeLengthTop[0] - edgeLengthHori[0]);
	lineMy[1] = -1 * edgeLengthHori[0] * lineMy[0];

	lineMy[2] = HEIGHT_RANGE/(edgeLengthHori[0] - edgeLengthBot[0]);
	lineMy[3] = -1 * edgeLengthHori[0] * lineMy[2];

	lineOther[0] = HEIGHT_RANGE/(edgeLengthTop[1] - edgeLengthHori[1]);
	lineOther[1] = -1 * edgeLengthHori[1] * lineOther[0];

	lineOther[2] = HEIGHT_RANGE/(edgeLengthHori[1] - edgeLengthBot[1]);
	lineOther[3] = -1 * edgeLengthHori[1] * lineOther[2];


	if( !lineMy[0] || !lineMy[1] || !lineMy[2] || !lineMy[3])
	{
		std::cout << "PSMHandler::setFit for lineMy is not successful!";
		std::cout << std::endl;
		return METHOD_FAILURE;
	}
	else if( !lineOther[0] || !lineOther[1] || !lineOther[2] || !lineOther[3])
	{
		std::cout << "PSMHandler::setFit for lineOther is not successful!";
		std::cout << std::endl;
		return METHOD_FAILURE;
	}
	else
	{
		if ( debugMode )
		{
			std::cout << "PSMHandler::setFit is successful.";
			std::cout << std::endl;
		}
		return METHOD_SUCCESS;
	}

}		

void PSMHandler::whereIsIt(
	float* edgeLength,
	float* edgeLengthHori,
	int& whereAmI,
	int& whereIsOther)
{
	if(edgeLength[0] <= edgeLengthHori[0]) // I am below the horizontal line
		whereAmI = 0;
	else // I am above the horizontal line
		whereAmI = 2;

	if(edgeLength[1] >= edgeLengthHori[1]) // Other robot is above the horizontal line
		whereIsOther = 0;
	else // Other robot is below the horizontal line
		whereIsOther = 2;
}

void PSMHandler::getFitResult(
	float* edgeLength,
	float* lineMy,
	int whereAmI,
	float* lineOther,
	int whereIsOther,
	float& fitMy,
	float& fitOther)
{

	fitMy = lineMy[whereAmI]*edgeLength[0] + lineMy[whereAmI+1];
	
	fitOther = lineOther[whereIsOther]*edgeLength[1] + lineOther[whereIsOther+1];

	if(fitMy < 0.01 && fitMy > -0.01)
		fitMy = 0;

	if(fitOther < 0.01 && fitOther > -0.01)
		fitOther = 0;
}
