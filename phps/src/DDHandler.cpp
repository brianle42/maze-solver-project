/*******************************************************************************
 *
 * DDHandler.cpp - Source File
 *
 * Description	:	Moonlight Company
 *			Maze Solver Project
 *			Direction Decider Handler Class
 *
 * Modified	: 15.05.2016 by Doga Yucalan ( yucalan.doga@metu.edu.tr )
 * Created	: 24.04.2016 by Utku Norman  ( norman.utku@metu.edu.tr  )
 *
 * People	:	Doga Yucalan ( yucalan.doga@metu.edu.tr )
 *			Utku Norman  ( norman.utku@metu.edu.tr  )
 *
 ******************************************************************************/

// Command Line I/O related headers
#include <cstddef>  			// std::nullptr
#include <iostream> 			// std::cout, std::cin, std::endl
#include <iomanip>  			// std::setw

#include "../include/DDHandler.h"

/*******************************************************************************
 *
 * Constructor
 *
 ******************************************************************************/
DDHandler::DDHandler( void )
{

}

/*******************************************************************************
 *
 * Public Methods
 *
 ******************************************************************************/
void DDHandler::printState(
	bool printMode 		,
	bool displayMode 
	)
{
	if( printMode )
	{
			
		std::cout << "<!---------------------------------------------" ;
		std::cout << std::endl ;
		std::cout << "DDHandler.printState() called. Printing state:" ;
		std::cout << std::endl ;

	}

	if ( IsNull( state ) )
	{

		std::cerr << "state is Null" ;	
		std::cerr << std::endl ;

		return;

	}
	else
	{

		if( printMode )
		{
		
			std::cout << std::endl			;

			std::cout << "Listing state: "		;
			std::cout << std::endl			;

			std::cout << "differentialHeight: "	;
			std::cout << state.nextState		;
			std::cout << std::endl;

		}

	}

	if( printMode )
	{
		
		std::cout << "---------------------------------------------->";
		std::cout << std::endl;
		std::cout << std::endl;

	}

}

DDPacket DDHandler::handle( 		
	PSMPacket	platformState		,
	float 		ballPositionAngle	,
	RPPacket	desiredPathData		,
	bool debugMode
	)
{

	if( debugMode )
	{
		
		std::cout << "<!---------------------------------------------";
		std::cout << std::endl;
		std::cout << "DDHandler.handle() called. handling..." ;
		std::cout << std::endl;
		std::cout << std::endl;

	}

	if ( IsNull( platformState ) )
	{

		std::cerr << "DDHandler: platformState of type PSMPacket is Null" ;
		std::cerr << std::endl ;

		return DDPacketNull ;

	}
	
	if ( ballPositionAngle <= 0 || ballPositionAngle > 360 )
	{

		std::cerr << "DDHandler: platformState of type PSMPacket is out of bounds!" ;
		std::cerr << std::endl ;

		return DDPacketNull ;

	}

	if ( IsNull( desiredPathData ) )
	{

		std::cerr << "DDHandler: desiredPathData of type RPPacket is Null" ;
		std::cerr << std::endl ;

		return DDPacketNull ;

	}
	
	if( desiredPathData.desiredBallDirection != IN	&&
	    desiredPathData.desiredBallDirection != OUT	&&
	    desiredPathData.desiredBallDirection != CW	&&
	    desiredPathData.desiredBallDirection != CCW	   )
	{
		std::cerr << "DDHandler: Unable to process desiredPathIndex!" ;
		std::cerr << std::endl 	;
		
		return DDPacketNull;
	}

	// Declare local variables
	float currentHeight		;
	float differentialHeight	;
	float ballAngle			;
	float actionAngle = 0		;
	int desiredPathIndex		;
	int sextantIndex		;
	int sextantHalved		;
	//int currentLevel = 0		; // 1 when above the mid level, 0 else
	
	float levelUDpos		; // up down increase level
	float levelUDneg		; // up down decrease level
	
	float levelRLpos		; // right left increase level
	float levelRLneg		; // right left decrease level
	
	float levelMAX			; // maximum level
	float levelMIN			; // minimum level
	
	// Initialize local variables
	currentHeight = platformState.heights[ 0 ] ;
	ballAngle = ballPositionAngle ;
	
	//if( currentHeight >= 0 )
	//	currentLevel = 1;
	
	levelMAX = HEIGHT_RANGE;
	levelMIN = -1 * HEIGHT_RANGE;
	
	levelUDpos = LEVEL_IN_OUT * HEIGHT_RANGE;
	levelUDneg = -1 * LEVEL_IN_OUT * HEIGHT_RANGE;
	
	levelRLpos = LEVEL_CW_CCW * HEIGHT_RANGE;
	levelRLneg = -1 * LEVEL_CW_CCW_DOWN * HEIGHT_RANGE;
	
	if( debugMode )
	{

		std::cout << "Begin finding action angle."	;
		std::cout << std::endl				;
		
	}
	
	switch ( desiredPathData.desiredBallDirection )
	{
		case IN:
		{
			// rotate 180 degree
			
			actionAngle = ( ballAngle >= 180 ? -180 : 180 ) + ballAngle;
			
			break;
		}
		case OUT:
		{
			// rotate 0 degree
			
			actionAngle = ballAngle;
			
			break;
		}
		case CW:
		{
			// rotate 90 degree
			
			actionAngle = ( ballAngle >= 90 ? -90 : 270 ) + ballAngle;
			
			break;
		}
		case CCW:
		{
			// rotate -90 degree
			
			actionAngle = ( ballAngle >= 270 ? -270 : 90 ) + ballAngle;
			
			break;
		}
	}
	
	if( debugMode )
	{

		std::cout << "Finding action angle complete."	;
		std::cout <<  std::endl					;
		
	}
	
	if( debugMode )
	{

		std::cout << "Associated direction: "			;
		std::cout << desiredPathData.desiredBallDirection	;
		std::cout << std::endl					;	
		std::cout << "Ball angle: "				;
		std::cout << ballAngle					;
		std::cout << std::endl					;
		std::cout << "Action angle: "				;
		std::cout << actionAngle				;
		std::cout << std::endl					;
		
	}
	
	
	// Find the octant the vector is in and the required height
		
	if ( actionAngle >= 0 && actionAngle < 60 )
	{
		sextantIndex = 0; // 0th sextant
		sextantHalved = 0; // not halved
		
		// go levelRLneg (below) , be below mid point
				
		differentialHeight = findDifferentialHeight( currentHeight , levelRLneg	, "below" );
	}
		
		
	else if ( actionAngle >= 60 && actionAngle < 90 )
	{
		sextantIndex = 1; // 1st sextant
		sextantHalved = 1; // halved, 1st half
		
		// go levelRLneg / 2 (below) , be below mid point
		
		differentialHeight = findDifferentialHeight( currentHeight , levelRLneg , "below" );
	}
		
	else if ( actionAngle >= 90 && actionAngle < 120 )
	{
		sextantIndex = 1; // 1st sextant
		sextantHalved = 2; // halved, 2nd half
		
		// go levelRLpos / 2 (above) , be below mid point
		
		differentialHeight = findDifferentialHeight( currentHeight , levelRLpos , "below" );
		
	}
	
	else if ( actionAngle >= 120 && actionAngle < 180 )
	{
		sextantIndex = 2; // 2nd sextant
		sextantHalved = 0; // not halved
		
		// go levelRLpos (above) , be below mid point
		
		differentialHeight = findDifferentialHeight( currentHeight , levelRLpos , "below" );
		
	}
	
	else if ( actionAngle >= 180 && actionAngle < 240 )
	{
		sextantIndex = 3; // 3rd sextant
		sextantHalved = 0; // not halved
		
		// go levelRLpos (above) , be above mid point
		
		differentialHeight = findDifferentialHeight( currentHeight , levelRLpos , "above" );
		
	}
	
	else if ( actionAngle >= 240 && actionAngle < 270 )
	{
		sextantIndex = 4; // 4th sextant
		sextantHalved = 1; // halved, 1st half
		
		// go levelRLpos / 2 (above) , be above mid point
		
		differentialHeight = findDifferentialHeight( currentHeight , levelRLpos , "above" );
		
	}
	
	else if ( actionAngle >= 270 && actionAngle < 300 )
	{
		sextantIndex = 4; // 4th sextant
		sextantHalved = 2; // halved, 1st half
		
		// go levelRLneg / 2 (below) , be above mid point
		
		differentialHeight = findDifferentialHeight( currentHeight , levelRLneg , "above" );
		
	}
	
	else if ( actionAngle >= 300 && actionAngle < 360 )
	{
		sextantIndex = 5; // 5th sextant
		sextantHalved = 0; // not halved
		
		// go levelRLneg (below) , be above mid point
		
		differentialHeight = findDifferentialHeight( currentHeight , levelRLneg , "above" );
		
	}
		
	// Check if we are out of bounds.
	
	if( differentialHeight >= levelMAX - currentHeight )
	{
	
		std::cerr << "DDHandler: Maximum height is exceeded! Rearranging the command..." ;
		std::cerr << std::endl;
		differentialHeight = levelUDpos - currentHeight;
	
	}
		
	if( differentialHeight <= levelMIN - currentHeight )
	{
	
		std::cout << "DDHandler: Minimum height is exceeded! Rearranging the command...";
		std::cerr << std::endl;
		differentialHeight = levelUDneg - currentHeight;
	
	}	
	
	if( debugMode )
	{

		std::cout << "Action is found to be in sextant " 		;
		std::cout << sextantIndex 					;
		
		if( sextantHalved )
			std::cout << " ; in half " << sextantHalved		;
		
		std::cout << std::endl ;
		std::cout << "Associated height: " 				;
		std::cout << differentialHeight << " . "			;
		std::cout << std::endl 						;

	}
	
	if( debugMode )
	{

		std::cout << "Begin state exporting." ;
		std::cout << std::endl;

	}
	
	////////////////////////////////////////////////////////
	/////////////////////// EXPORTING //////////////////////
	////////////////////////////////////////////////////////
	
	state.nextState = differentialHeight ;
	
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
	
	return state ;

}

/*******************************************************************************
 *
 * Private Methods 
 *
 ******************************************************************************/

float DDHandler::findDifferentialHeight(
	float currentHeight	,
	float levelToGo		,
	std::string desiredRegion		)
{
	
	int currentLevel = 0 ;
	float differentialHeight ;
	
	if( desiredRegion == "above" && currentHeight <= 0 )
		currentLevel = 1 ;
		
	if( desiredRegion == "below" && currentHeight >= 0 )
		currentLevel = 1 ;

	// if i need to be above but i am not
	// or
	// if i need to be below but i am not
	
	if( currentLevel ) 
	{
		
		differentialHeight = levelToGo - currentHeight;
	
	}
	
	// if i am good
	else
	{
		
		differentialHeight = levelToGo;
	
	}
	
	return differentialHeight;

}
