////////////////////////////////////////////////////////////////////////////////
//
// PSMHandler.h - Class Header File
//
// Description: Moonlight Company
//              Maze Solver Project
//              Platform State Mapper (PSM) Class
//
// Modified : 09.05.2016 by Doga Yucalan ( yucalan.doga@metu.edu.tr  )
// Created  : 13.04.2016 by Utku Norman  ( norman.utku@metu.edu.tr  )
//
// People	: 	Doga Yucalan ( yucalan.doga@metu.edu.tr )
//			Utku Norman  ( norman.utku@metu.edu.tr  )
//
// Style:
//  http://geosoft.no/development/cppstyle.html#Include Files
//
// Associated code-snippet sources:
// https://solarianprogrammer.com/2015/05/08/detect-red-circles-image-using-opencv/
// http://docs.opencv.org/3.1.0/df/d9d/tutorial_py_colorspaces.html#gsc.tab=0
//
////////////////////////////////////////////////////////////////////////////////


#ifndef PSMHANDLER_H
#define PSMHANDLER_H

#include <opencv2/opencv.hpp>

// Descriptions for the struct FeatureData
#include "PSMHandler.h"
#include "Packages.h"

class PSMHandler
{
	public:

		/** @brief Constructor.
		 */
		PSMHandler( void )		;

		/** @brief Handler.
		 */
		PSMPacket handle(
			cv::Point2f borderPoints[ 3 ]	,
			FeatureData calibrationData		, 

			//cv::Point2f	const 	borderPoints[ 3 ]	,
			//FeatureData	const 	calibrationData		, 
			bool debugMode 	= false
			) ;

		/** @brief Print and display the current state.
		 */
		void printState(
			bool printMode 		, 
			bool displayMode 
			) ;

		
		cv::Mat rotationMatrixToEulerAngles(
			cv::Mat R
			);

	private:
		PSMPacket state			;
		bool debugMode			;

		int getEdgeLength(
			cv::Point2f* vertices,	
			float* edgeLength,
			bool debugMode
			);

		int setFit(
			float* edgeLengthHori,
			cv::Point2f* verticesTop,
			cv::Point2f* verticesBot,
			float* lineMy,
			float* lineOther,
			bool debugMode
			);

		void whereIsIt(
			float* edgeLength,
			float* edgeLengthHori,
			int& whereAmI,
			int& whereIsOther
			);

		void getFitResult(
			float* edgeLength,
			float* lineMy,
			int whereAmI,
			float* lineOther,
			int whereIsOther,
			float& fitMy,
			float& fitOther
			);
};

#endif // PSMHANDLER_H
