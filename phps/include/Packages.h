/*******************************************************************************
 *
 * Packages.h - Header File
 *
 * Description	:	Moonlight Company
 *			Maze Solver Project
 *			Declarations for packages passed in between handlers
 *
 * Modified	: 15.05.2016 by Doga Yucalan ( yucalan.doga@metu.edu.tr  )
 * Created	: 12.05.2016 by Utku Norman  ( norman.utku@metu.edu.tr  )
 *
 * People	:	Doga Yucalan ( yucalan.doga@metu.edu.tr )
 *			Utku Norman  ( norman.utku@metu.edu.tr  )
 *
 ******************************************************************************/

#ifndef PACKAGES_H
#define PACKAGES_H

#include <opencv2/opencv.hpp> // Image Processing (OpenCV) header

/*******************************************************************************
 *
 * Constant Variable Definitions
 *
 ******************************************************************************/
 
// very constant indeed 
#define PI 3.14159265

#define METHOD_FATAL	-1
#define METHOD_SUCCESS	0
#define METHOD_FAILURE	1

#define HEIGHT_RANGE 100

#define LEVEL_IN_OUT 0.8
#define LEVEL_CW_CCW 0.3
#define LEVEL_CW_CCW_DOWN 0.5

/*******************************************************************************
 *
 * Type Definitions
 *
 ******************************************************************************/

#define BALL_DIRECTION_SIZE 	4
 enum ball_directions_t { CW = 0 , CCW = 1 , IN  = 2 , OUT  = 3 }; // Sub-programs
//enum BallDirection { CW , CCW , IN , OUT }; // Sub-programs

#define TRAVERSE_DIRECTION_SIZE 2
//enum TraverseDirection { FORWARD , REVERSE }; // Sub-programs
 enum traverse_directions_t { FORWARD = 0 , REVERSE  = 1 }; // Sub-programs

/*
enum class Days { Saturday,Sunday,Tuesday,Wednesday,Thursday,Friday};
Days day = Days.Saturday;
if(day == Days.Saturday)

enum Days { Saturday,Sunday,Tuesday,Wednesday,Thursday,Friday};
Days day = Saturday;
if(day == Saturday)
*/

//int myInteger = 0;
//Test myValue = (Test)myInteger;


/*******************************************************************************
 *
 * Package Definitions
 *
 ******************************************************************************/

typedef struct CCPacket 	// CCHandler return package
{

	cv::Mat	image;

} CCPacket ;

typedef struct FeatureData 	// ....

{
	cv::Point2f	pointsHori[ 3 ]		; // vertices (myRobotArea, otherRobotArea, top)
	
	cv::Point2f	pointsTop[ 3 ]		; // vertices (myRobotArea, otherRobotArea, top)
	
	cv::Point2f	pointsBot[ 3 ]		; // vertices (myRobotArea, otherRobotArea, top)

} FeatureData ;

typedef struct MazeData 
{

	cv::Mat		image			;
	
	cv::Point2f	mazePoints[ 3 ]		; // start, end, ball

} MazeData ;

typedef struct IPPacket 	// IPHandler return package
{

	FeatureData	calibrationData	; // top , hori , bottom 
	
	MazeData	mazeData		;

	cv::Point2f	borderPoints[ 3 ]	; // vertices (myRobotArea, otherRobotArea, top)

} IPPacket ;

typedef struct PSMPacket  	// PSMHandler return package
{

	float heights[ 2 ]			; // rotations of edges, in [MIN_ROT, MAX_ROT]

} PSMPacket ;

typedef struct BallLocationData 
{

	int currentPathNo				;

	bool wayBlocked[ BALL_DIRECTION_SIZE ]		; // vertices (IN OUT, otherRobotArea, top)

} BallLocationData ;

typedef struct LMPacket 	// LMHandler return package
{

	float ballPositionAngle				;

	BallLocationData ballLocationData 		;

} LMPacket ;

typedef struct RPPacket 	// RPHandler return package
{

	int desiredBallDirection			; // ball_directions_t

} RPPacket ;

typedef struct DDPacket 	// DDHandler return package
{

	float nextState					;

} DDPacket ;

typedef struct CUPacket 	// CUHandler return package
{

	std::string data 				;

} CUPacket ;

typedef struct CHPacket 	// CHandler return package
{

	std::string data 				;

} CHPacket ;

/*******************************************************************************
 *
 * Null Check Methods
 *
 ******************************************************************************/

static CCPacket 	CCPacketNull		;

static FeatureData	FeatureDataNull		;

static MazeData		MazeDataNull		;

static cv::Point2f*	Point2fNull		;

static IPPacket		IPPacketNull	
	{ 
		FeatureDataNull ,
		MazeDataNull , 
		{ cv::Point2f(0,0) , cv::Point2f(0,0) , cv::Point2f(0,0) } 

	} ;

	//IPPacketNull.mazeData =  MazeDataNull;
	//IPPacketNull.calibrationData = FeatureDataNull ;

static PSMPacket	PSMPacketNull		;

static BallLocationData	BallLocationDataNull	;

static LMPacket 	LMPacketNull
	{ 
		-1.0				,
		BallLocationDataNull
	
	} ;

	//LMPacketNull.ballPositionAngle =  -1.0;
	//LMPacketNull.ballLocationData = BallLocationDataNull ;

static RPPacket 	RPPacketNull		;

static DDPacket 	DDPacketNull		;

static CUPacket 	CUPacketNull		;

static CHPacket 	CHPacketNull		;


static bool IsNull( const CCPacket& test) 
{

	return &test == &CCPacketNull;

}

static bool IsNull( const FeatureData& test	)
{

	return &test == &FeatureDataNull	;

}

static bool IsNull( const MazeData& test	)
{

	return &test == &MazeDataNull		;

}

/*
static bool IsNull( const cv::Point2f*& test) 
{

	return &test == &Point2fNull;

}
*/

static bool IsNull( const IPPacket& test	)
{

	return &test == &IPPacketNull		;
	
}

static bool IsNull( const PSMPacket& test )
{

	return &test == &PSMPacketNull		;

}

static bool IsNull( const BallLocationData& test )
{

	return &test == &BallLocationDataNull	;

}

static bool IsNull( const LMPacket& test )
{

	return &test == &LMPacketNull		;

}

static bool IsNull( const RPPacket& test	)
{

	return &test == &RPPacketNull	;

}

static bool IsNull( const DDPacket& test	)
{

	return &test == &DDPacketNull	;

}

static bool IsNull( const CUPacket& test	)
{

	return &test == &CUPacketNull		;

}

static bool IsNull( const CHPacket& test	)
{

	return &test == &CHPacketNull		;

}

static bool IsNull(const std::string& test) 
{

	return test.compare( "" ) == 0;
	
}

#endif // PACKAGES_H
