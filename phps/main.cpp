/*******************************************************************************
 *
 * main.cpp - Source File
 *
 * Description	:	Moonlight Company
 *			Maze Solver Project
 *			Percept Handling and Planning Subsystem (PHPS)
 *			by Moonlight Company, 
 *			for the semesters Fall 2015 & Spring 2016 
 *			for the courses EE 493-494 Engineering Design I & II
 *
 * Modified	: 15.05.2016 by Doga Yucalan ( yucalan.doga@metu.edu.tr  )
 * Created	: 13.04.2016 by Utku Norman  ( norman.utku@metu.edu.tr  )
 *
 * People	:	Doga Yucalan ( yucalan.doga@metu.edu.tr )
 *			Utku Norman  ( norman.utku@metu.edu.tr  )
 * 
 * Style	:
 *
 *  http://geosoft.no/development/cppstyle.html#Include Files
 *
 * Associated code snippet sources :
 *
 *  http://opencv-code.com/tutorials/detecting-simple-shapes-in-an-image/
 *  https://github.com/bsdnoobz/opencv-code/blob/master/shape-detect.cpp
 *  http://stackoverflow.com/questions/20492152/
 *	how-to-find-no-of-inner-holes-using-cvfindcontours-and-hierarchy
 *  http://docs.opencv.org/2.4/doc/tutorials/
 *	imgproc/shapedescriptors/find_contours/find_contours.html
 *
 ******************************************************************************/

// Command Line I/O related headers
#include <cstddef>  			// std::nullptr
#include <iostream> 			// std::cout, std::cin, std::endl
#include <iomanip>  			// std::setw
#include <cstdlib>  			// EXIT_SUCCESS, EXIT_FAILURE

#include <opencv2/opencv.hpp> 		// Image Processing (OpenCV) header

// Handler descriptions for the parts of PHPS
#include "include/CCHandler.h"		// Camera Capture		(CC)
#include "include/IPHandler.h"		// Image Preprocessor		(IP)
#include "include/PSMHandler.h"		// Platform State Mapper	(PSM)
#include "include/LMHandler.h"		// Labyrinth Mapper		(LM)
#include "include/RPHandler.h"		// Route Planner		(RP)
#include "include/DDHandler.h"		// Direction Decider		(DD)
#include "include/CUHandler.h"		// Control Unit			(CU)
#include "include/CHandler.h"		// Communication		(C)
#include "include/Visualizer.h"		// Visualization header
#include "include/Auxiliaries.h"	// Other auxiliary methods header

#include "include/Packages.h"		// Other auxiliary methods header

#define METHOD_FATAL	-1
#define METHOD_SUCCESS	0
#define METHOD_FAILURE	1

//Initializer debugs modes
bool IPInitDebugMode		; //= false	;

// Handler debugs modes
bool CCHandlerDebugMode		; //= false	;
bool IPHandlerDebugMode		; //= false	;
bool PSMHandlerDebugMode	; //= false	;
bool LMHandlerDebugMode		; //= false	;
bool RPHandlerDebugMode		; //= false	;
bool DDHandlerDebugMode		; //= false	;
bool CUHandlerDebugMode		; //= false	;
bool CHandlerDebugMode		; //= false	;

// For the printStates
// Printer debugs modes
bool CCPrintDebugMode		; //= false	;
bool IPPrintDebugMode		; //= true	;
bool PSMPrintDebugMode		; //= true	;
bool LMPrintDebugMode		; //= true	;
bool RPPrintDebugMode		; //= true	;
bool DDPrintDebugMode		; //= true	;
bool CUPrintDebugMode		; //= true	;
bool CPrintDebugMode		; //= true	;

// Display debugs modes
bool CCDisplayDebugMode		; //= false	;
bool IPDisplayDebugMode		; //= false	;
bool PSMDisplayDebugMode 	; //= false	;
bool LMDisplayDebugMode		; //= true	;
bool RPDisplayDebugMode		; //= false	;
bool DDDisplayDebugMode		; //= false	;
bool CUDisplayDebugMode		; //= false	;
bool CDisplayDebugMode		; //= false	;

// Declare the main handlers
CCHandler	mainCCHandler	;
IPHandler	mainIPHandler	;
PSMHandler	mainPSMHandler	;
LMHandler	mainLMHandler	;
RPHandler	mainRPHandler	;
DDHandler	mainDDHandler	;
CUHandler	mainCUHandler	;
CHandler	mainCHandler	;

// Declare the packages to be passed in between the handlers
CCPacket	rawImageData	;
IPPacket	ppResults	;
PSMPacket	platformState	;
LMPacket	labyrinthState	;
RPPacket 	desiredPathData ;  //RPPacket	plan		;
DDPacket	errorInfo	;
CUPacket	commandInfo	;
CHPacket 	senseDataInfo 	;

//std::string	command		;
//std::string	senseData	;

// Construct horizontalImageData
CCPacket horizontalImageData	;
CCPacket topImageData	;
CCPacket bottomImageData	;

const std::string horizontalImagePath 	( "./images/mid.jpg" ) ; // by default
const std::string topImagePath		( "./images/max.jpg" ) ; // by default
const std::string bottomImagePath	( "./images/min.jpg" ) ; // by default

std::string cameraConfigFilename( "./out_camera_data.xml" ) ;
std::string configFilename( "./config.xml" ) ;

void calibrate( cv::Mat& distortfulImage );

void loadHorizontalImage( void );

void loadTopImage( void );

void loadBottomImage( void );

bool prepareCC( int argcData, char** argvData );

// Initialize the main IP
void prepareIP( );

int initAll( int argc , char** argv , bool debugMode ) ;

void waitMain( bool stepByStepMode );

void writeConfig( void ) ;

void readConfig( void ) ;

bool detectFailed( void ) ;

void interstepDeeds( void );

void printStates( void ); 	// Print the states for monitoring

bool stepByStepMode;

int stepNo;

int counter;

int failCount;

float failRate ;

int CCDelay ;

int mainLoopDelay ;

/*******************************************************************************
 *
 * main
 *
 ******************************************************************************/

int main( int argc , char** argv )
{

	initAll( argc , argv , true );

	/*********************
	 * Setup Loop
	 *********************/

	while( true )	// Labyrinth & Platform State Estimation Loop
	{

		break ;

	} 

	std::cout << "Begin the main loop. "		;
	std::cout << std::endl				;

	/*********************
	 * Maze Solving Loop
	 *********************/

	while( true )	// Maze Solving Loop
	{

		/*********************
		 * Main Body
		 *********************/

		// Run the main Camera Capture Handler
		rawImageData	= mainCCHandler.handle( CCHandlerDebugMode ) ;	
		mainCCHandler .printState( CCPrintDebugMode	,	CCDisplayDebugMode	)						;

		// Run the Image Preprocessor Handler
		ppResults	= mainIPHandler.handle( rawImageData , IPHandlerDebugMode ) ;
		mainIPHandler .printState( IPPrintDebugMode	,	IPDisplayDebugMode	)						;

		// Run the main Platform State Mapper Handler
		platformState	= mainPSMHandler.handle( ppResults.borderPoints , ppResults.calibrationData , PSMHandlerDebugMode ) 		;
		mainPSMHandler.printState( PSMPrintDebugMode	,	PSMDisplayDebugMode	)	;

		// Run the main Labyrinth Mapper Handler 	: hangi yyyy
		labyrinthState 	= mainLMHandler.handle( ppResults.borderPoints , ppResults.mazeData , LMHandlerDebugMode ) 			;
		mainLMHandler .printState( LMPrintDebugMode	,	LMDisplayDebugMode	)	;

		// Run the main Route Planner Handler 		: o yolda ne taraf CW - CCW - IN - OUT
		desiredPathData = mainRPHandler.handle( labyrinthState , RPHandlerDebugMode  ) 							;
		mainRPHandler .printState( RPPrintDebugMode	,	RPDisplayDebugMode	) ;

		// Run the main Direction Decider Handler	: ~ next robot state estimator - ne kadar yukarı ya da aşağı
		errorInfo	= mainDDHandler.handle(	platformState , labyrinthState.ballPositionAngle , desiredPathData , DDHandlerDebugMode) ;
		mainDDHandler .printState( DDPrintDebugMode	,	DDDisplayDebugMode	) ;

		// Run the main Controller Unit Handler		: WsWSWSWSSSSSWWWWWW <- T/B
		commandInfo	= mainCUHandler.handle( errorInfo , platformState , senseDataInfo , CUHandlerDebugMode ) 			;
		mainCUHandler .printState( CUPrintDebugMode	,	CUDisplayDebugMode	) ;

		// Run the main Communication Handler		: 
		senseDataInfo	= mainCHandler.handle( commandInfo , CHandlerDebugMode ) 							;
		mainCHandler  .printState( CPrintDebugMode	,	CDisplayDebugMode	)	;

		/*************************
		 * state prints 
		 ************************/
		//printStates( ) ;

		/*************************
		 * Interstep Processes
		 ************************/

		interstepDeeds( ) ;
		
	}

	return 0;
}

/*******************************************************************************
 *
 * Initialization Methods
 *
 ******************************************************************************/
int initAll( int argc , char** argv , bool debugMode = true )
{

	// Declare and initialize the global variables
	counter = 0;
	failCount = 0;
	failRate = 1.0 ;
	stepNo = 0 					;	// Step counter for the main loop
	CCDelay = 180 ;
	mainLoopDelay = 25 ;
	stepByStepMode = false ;

	if( false )
	{

		writeConfig( ) ; // Save debug info

		if( debugMode )
		{

			std::cout << "Config file writing complete. "	;
			std::cout << std::endl				;
		
		}

	}
	else
	{

		readConfig( ) ; // Load debug info

		if( debugMode )
		{

			std::cout << "Config file reading complete. "	;
			std::cout << std::endl				;
			std::cout << "CCDelay: " << CCDelay	;
			std::cout << std::endl				;
		
		}

	}

	

	if( debugMode )
	{

		std::cout << "Begin the preparations. "		;
		std::cout << std::endl				;
	
	}
	
	/*********************
	 * Initialization
	 ********************/

	loadHorizontalImage( )				;

	if( debugMode )
	{

		std::cout << "Horizontal image initialized. "	;
		std::cout << std::endl				;

	}

	//showImage( "Hori-calib", horizontalImageData.image );

	//cv::waitKey( 0 ) ;

	loadTopImage( )					;

	if( debugMode )
	{

		std::cout << "Top image initialized. "		;
		std::cout << std::endl				;

	}

	//showImage( "Top-calib", topImageData.image );

	//cv::waitKey( 0 ) ;

	loadBottomImage( )
					;
	if( debugMode )
	{

		std::cout << "Bottom image initialized. "	;
		std::cout << std::endl				;

	}

	//showImage( "Bottom-calib", bottomImageData.image );

	//cv::waitKey( 0 ) ;

	stepByStepMode = prepareCC( argc, argv )	;

	if( debugMode )
	{

		std::cout << "CC ready. "			;
		std::cout << std::endl				;

	}

	if( stepByStepMode )
	{

		std::cout << "stepByStepMode mode active: " 	;	
		std::cout << "Single image processing only. "	;
		std::cout << std::endl ;

	}
	else
	{

		std::cout << "stepByStepMode mode passive: " 	;
		std::cout << "Automatic capture is activated. " ;
		std::cout << std::endl ;


	}
	
	prepareIP( )					;

	std::cout << "IP ready. "			;
	std::cout << std::endl				;

}


/*******************************************************************************
 *
 * Helper Methods
 *
 ******************************************************************************/


void printStates( void ) 	// Print the states for monitoring
{

	mainCCHandler .printState( CCPrintDebugMode	,	CCDisplayDebugMode	)	;

	mainIPHandler .printState( IPPrintDebugMode	,	IPDisplayDebugMode	)	;

	mainPSMHandler.printState( PSMPrintDebugMode	,	PSMDisplayDebugMode	)	;

	mainLMHandler .printState( LMPrintDebugMode	,	LMDisplayDebugMode	)	;

	mainRPHandler .printState( RPPrintDebugMode	,	RPDisplayDebugMode	)	;

	mainDDHandler .printState( DDPrintDebugMode	,	DDDisplayDebugMode	)	;

	mainCUHandler .printState( CUPrintDebugMode	,	CUDisplayDebugMode	)	;

	mainCHandler  .printState( CPrintDebugMode	,	CDisplayDebugMode	)	;

}

void interstepDeeds( void )
{

		/*************************
		 * step tracking 
		 ************************/

		
		//std::cout << "||||||||||||||||" << std::endl		;
 		std::cout << "|||| Fail count: " << failCount 	;
		std::cout << std::endl					;
		std::cout << "|||| Fail rate: " << failRate 	;
		std::cout << std::endl					;
		//std::cout << "||||||||||||||||" << std::endl		;

		if( true ) //if( stepNo % 10 == 0 )
		{

			std::cout << "||||| Step no: " << stepNo		;
			std::cout << std::endl					;

		}

		counter++ ;
		stepNo++  ;

		/*************************
		 * error tracking 
		 ************************/

		if( detectFailed() )
		{

			failCount ++ ;

		}

		if( counter == 100 )
		{
			failRate = failCount / 100.0 ;

			/*if( detectFailed( ) )
			{

				failCount = failCount - 1 ;
			}*/

			//counter = counter - 1 ;

			counter = 0;

			failCount = 0;

		}
		
		waitMain( stepByStepMode ) ; // Pause

}

void readConfig( void )
{

	cv::FileStorage fsConf( configFilename , cv::FileStorage::READ );

	if( !fsConf.isOpened( ) )
	{
		std::cerr << "Debug config file not found. " ;
		std::cerr << std::endl 	; 

		std::exit( EXIT_FAILURE ) ;

	}

	fsConf[ "CCDelay" 		]	>> CCDelay		;
	fsConf[ "mainLoopDelay" 	]	>> mainLoopDelay	;

	// Initializer debugs modes
	fsConf[ "IPInitDebugMode" 	]	>> IPInitDebugMode	;
	// Handler debugs modes
	fsConf[ "CCHandlerDebugMode" 	]	>> CCHandlerDebugMode	;
	fsConf[ "IPHandlerDebugMode" 	]	>> IPHandlerDebugMode	;
	fsConf[ "PSMHandlerDebugMode" 	]	>> PSMHandlerDebugMode	;
	fsConf[ "LMHandlerDebugMode" 	]	>> LMHandlerDebugMode	;
	fsConf[ "RPHandlerDebugMode" 	]	>> RPHandlerDebugMode	;
	fsConf[ "DDHandlerDebugMode" 	]	>> DDHandlerDebugMode	;
	fsConf[ "CUHandlerDebugMode" 	]	>> CUHandlerDebugMode	;
	fsConf[ "CHandlerDebugMode" 	]	>> CHandlerDebugMode	;
	// Printer debugs modes
	fsConf[ "CCPrintDebugMode" 	]	>> CCPrintDebugMode	;
	fsConf[ "IPPrintDebugMode" 	]	>> IPPrintDebugMode	;
	fsConf[ "PSMPrintDebugMode" 	]	>> PSMPrintDebugMode	;
	fsConf[ "LMPrintDebugMode" 	]	>> LMPrintDebugMode	;
	fsConf[ "RPPrintDebugMode" 	]	>> RPPrintDebugMode	;
	fsConf[ "DDPrintDebugMode" 	]	>> DDPrintDebugMode	;
	fsConf[ "CUPrintDebugMode" 	]	>> CUPrintDebugMode	;
	fsConf[ "CPrintDebugMode" 	]	>> CPrintDebugMode	;
	// Display debugs modes  
	fsConf[ "CCDisplayDebugMode" 	]	>> CCDisplayDebugMode	;
	fsConf[ "IPDisplayDebugMode" 	]	>> IPDisplayDebugMode	;
	fsConf[ "PSMDisplayDebugMode" 	]	>> PSMDisplayDebugMode	;
	fsConf[ "LMDisplayDebugMode" 	]	>> LMDisplayDebugMode	;
	fsConf[ "RPDisplayDebugMode" 	]	>> RPDisplayDebugMode	;
	fsConf[ "DDDisplayDebugMode" 	]	>> DDDisplayDebugMode	;
	fsConf[ "CUDisplayDebugMode" 	]	>> CUDisplayDebugMode	;
	fsConf[ "CPrintDebugMode" 	]	>> CDisplayDebugMode	;

	fsConf.release( );

}

void writeConfig( void )
{

	cv::FileStorage fsConf( configFilename, cv::FileStorage::WRITE );


	if( !fsConf.isOpened() )
	{

		std::cerr << "Debug config file not found. " ;
		std::cerr << std::endl 	; 

		std::exit( EXIT_FAILURE ) ;


	}

	fsConf
		//
		<< "CCDelay"			<< CCDelay
		<< "mainLoopDelay"		<< mainLoopDelay
		// Initializer debugs modes
		<< "IPInitDebugMode"		<< IPInitDebugMode
		// Handler debugs modes
		<< "CCHandlerDebugMode"		<< CCHandlerDebugMode 
		<< "IPHandlerDebugMode"		<< IPHandlerDebugMode
		<< "PSMHandlerDebugMode"	<< PSMHandlerDebugMode
		<< "LMHandlerDebugMode"		<< LMHandlerDebugMode
		<< "RPHandlerDebugMode"		<< RPHandlerDebugMode
		<< "DDHandlerDebugMode"		<< DDHandlerDebugMode
		<< "CUHandlerDebugMode"		<< CUHandlerDebugMode
		<< "CHandlerDebugMode"		<< CHandlerDebugMode
		// Printer debugs modes
		<< "CCPrintDebugMode"		<< CCPrintDebugMode
		<< "IPPrintDebugMode"		<< IPPrintDebugMode
		<< "PSMPrintDebugMode"		<< PSMPrintDebugMode
		<< "LMPrintDebugMode"		<< LMPrintDebugMode
		<< "RPPrintDebugMode"		<< RPPrintDebugMode
		<< "DDPrintDebugMode"		<< DDPrintDebugMode
		<< "CUPrintDebugMode"		<< CUPrintDebugMode
		<< "CPrintDebugMode"		<< CPrintDebugMode
		// Display debugs modes     
		<< "CCDisplayDebugMode"		<< CCDisplayDebugMode
		<< "IPDisplayDebugMode"		<< IPDisplayDebugMode
		<< "PSMDisplayDebugMode"	<< PSMDisplayDebugMode
		<< "LMDisplayDebugMode"		<< LMDisplayDebugMode
		<< "RPDisplayDebugMode"		<< RPDisplayDebugMode
		<< "DDDisplayDebugMode"		<< DDDisplayDebugMode
		<< "CUDisplayDebugMode"		<< CUDisplayDebugMode
		<< "CDisplayDebugMode"		<< CDisplayDebugMode
	   ;

	   fsConf.release();

}

bool detectFailed( void )
{

	if( 
		IsNull( rawImageData )				||
		IsNull( ppResults ) 				||
		IsNull( ppResults.calibrationData )  		||
		IsNull( ppResults.mazeData ) 			||
		IsNull( labyrinthState ) 			||
		IsNull( labyrinthState.ballLocationData ) 	||
		IsNull( errorInfo )				||
		IsNull( commandInfo )
		)
	{

		return true; // failed	

	}
	else
	{

		return false; // OK!
	}
}


void waitMain( bool stepByStepMode )
{

	if( IsNull( ppResults ) )
	{

		return ;

	}

	int keyCode	;

	if( stepByStepMode )
	{

		keyCode = cv::waitKey( 0 ) ;

		if( keyCode == 27 )  			// 27 = ascii('ESC')
		{

			std::exit( EXIT_SUCCESS );

		}

	}
	else
	{
	
		keyCode = cv::waitKey( mainLoopDelay )	;	// Wait for a key for 25 ms

		if( keyCode == 80 || keyCode == 112 ) 	// 80 <-> 'P' , 112 <-> 'p'
		{

			keyCode = cv::waitKey( 100000 )	; // Wait long

		}
		
		if( keyCode == 27 )  			// 27 = ascii('ESC')
		{

			std::exit( EXIT_SUCCESS );

		}

	}
	
}


void calibrate( cv::Mat& distortfulImage )
{

	cv::FileStorage fsCam( cameraConfigFilename , cv::FileStorage::READ );

	if( !fsCam.isOpened( ) )
	{
		std::cerr << "Camera calibration file not found. " ,
		std::cerr << std::endl 	; 

		std::exit( EXIT_FAILURE ) ;

	}
	
	cv::Mat intrinsics , distortion;

	fsCam[ "camera_matrix"		 ]	>> intrinsics   ;

	fsCam[ "distortion_coefficients" ]	>> distortion   ;

	cv::Mat undistortedImage;

	cv::undistort( distortfulImage, undistortedImage, intrinsics, distortion );

	distortfulImage = undistortedImage.clone(); // now, undistorted

	fsCam.release( ) ;

	return; 

}

void loadHorizontalImage( void )
{

	horizontalImageData.image = cv::imread( 
		horizontalImagePath.c_str( ) , 1 ) ;
	
	// Check if image exists
	if ( !horizontalImageData.image.data )
	{

		std::cerr << "Unable to load horizontalImageData image!" ;
		std::cerr << std::endl 	; 

		std::cerr << "at path: " << horizontalImagePath.c_str( ) ,
		std::cerr << std::endl 	; 

		std::exit( EXIT_FAILURE );

	}

	//showImage("hori-uncal", horizontalImageData.image );
	//cv::waitKey( 0 );

	calibrate( horizontalImageData.image );

	//showImage("hori-cal", horizontalImageData.image );
	//cv::waitKey( 0 );

}

void loadTopImage( void )
{

	topImageData.image = cv::imread( topImagePath.c_str( ) , 1 ) ;
	
	// Check if image exists
	if ( !topImageData.image.data )
	{

		std::cerr << "Unable to load topImageData image!" ;
		std::cerr << std::endl 	; 

		std::cerr << "at path: " << topImagePath.c_str( ) ,
		std::cerr << std::endl 	; 

		std::exit( EXIT_FAILURE );

	}

	calibrate( topImageData.image );

}

void loadBottomImage( void )
{

	bottomImageData.image = cv::imread( bottomImagePath.c_str( ) , 1 ) ;
	
	// Check if image exists
	if ( !bottomImageData.image.data )
	{

		std::cerr << "Unable to load bottomImageData image!" ;
		std::cerr << std::endl 	; 

		std::cerr << "at path: " << bottomImagePath.c_str( ) ,
		std::cerr << std::endl 	; 

		std::exit( EXIT_FAILURE );

	}

	calibrate( bottomImageData.image );

}

bool prepareCC( int argcData, char** argvData )
{
	cv::Mat	image ;
	bool singleShotMode = false ;
	bool successFlag ;

	// Check for the correct number for arguments
	if ( argcData >= 2 )
	{

		// Load the image addressed in the second argument
		image = cv::imread( argvData[ 1 ] , 1 );

		// Check for validity of the image
		if ( !image.data )  // If successfully loaded
		{
			std::cerr <<"prepareCC: No image data" ;
			std::cerr << std::endl ;
			std::exit( EXIT_FAILURE );
		}

		singleShotMode = true;
		successFlag = mainCCHandler.initialize( CCDelay , image ) ;


	}
	else if( argcData == 1 )
	{

		singleShotMode = false;
		successFlag = mainCCHandler.initialize( CCDelay ) ;

	}
	else
	{

		std::cerr << "CCHandler: undefined usage. "		;
		std::cerr << std::endl ;

		std::cerr << "Usage-1: './mazeSolver'"			; 
		std::cerr << "for the main image stream from camera ";
		std::cerr << "and default horizontal image"	;
		std::cerr << std::endl ;

		std::cerr << "Usage-2: './mazeSolver <image-path>'" ;
		std::cerr << " to process one single image present in the <image-path>";
		std::cerr << "and default horizontal image"	;
		std::cerr << std::endl ;

		/*
		std::cerr << "Usage-3: './mazeSolver <image-path>' <horizontal-image-path>" 	;
		std::cerr << " to process one single image present in the <image-path>"			;
		std::cerr << "and the image in <horizontal-image-path> as the horizontal image"	;
		std::cerr << std::endl ;
		*/

		std::exit( EXIT_FAILURE );
	}

	if( !successFlag )
	{

		std::cerr << "mainCCHandler initialization failed."	;
		std::cerr << std::endl	;

		std::exit( EXIT_FAILURE );

	}

	return singleShotMode;

}

// Initialize the main IP
void prepareIP( )
{

	if ( !mainIPHandler.initialize( horizontalImageData , 'H', IPInitDebugMode ) ||
	     !mainIPHandler.initialize( topImageData , 'T', IPInitDebugMode ) ||  
	     !mainIPHandler.initialize( bottomImageData , 'B', IPInitDebugMode ))
	{

		std::cerr << "mainIPHandler initialization failed."	;
		std::cerr << std::endl	;

		std::exit( EXIT_FAILURE );

	}

}
