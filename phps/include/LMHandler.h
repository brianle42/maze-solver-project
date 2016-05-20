/*******************************************************************************
 *
 * LMHandler.h - Class Header File
 *
 * Description	:	Moonlight Company
 *			Maze Solver Project
 * 			Labyrinth Mapper Handler Class
 *
 * Modified	: 12.05.2016 by Utku Norman  ( norman.utku@metu.edu.tr  )
 * Created	: 16.03.2016 by Doga Yucalan ( yucalan.doga@metu.edu.tr )
 *
 * People	:	Doga Yucalan ( yucalan.doga@metu.edu.tr )
 *			Utku Norman  ( norman.utku@metu.edu.tr  )
 *
 * Style:
 *  http://geosoft.no/development/cppstyle.html#Include Files
 *
 * Associated code-snippet sources:
 * https://solarianprogrammer.com/2015/05/08/
 * 	detect-red-circles-image-using-opencv/
 * http://docs.opencv.org/3.1.0/df/d9d/tutorial_py_colorspaces.html#gsc.tab=0
 *
 ******************************************************************************/

#ifndef LMHANDLER_H
#define LMHANDLER_H

#include "Packages.h"

class LMHandler
{
	public:

		/** @brief Constructor.
		 */
		LMHandler( void )	;

		/** @brief Handler.
		 */
		LMPacket handle(
			cv::Point2f 	borderPoints[ 3 ]	,
			MazeData 	mazeData		, 
			bool 		debugMode 	= false
			) ;

		/** @brief Print and display the current state.
		 */
		void printState(
			bool printMode		= false ,
			bool displayMode 	= false 
			);
	private:
		LMPacket state			;

		cv::Mat annotatedImage	;

		bool debugMode			;

		/** @brief Applies thresholding and dilation on an image.
		@param image 		Input  image.
		grayscale
		 */
		void annotateState( 
			cv::Mat& mat	, 
			MazeData state 
			) ;

		/*
		int findBoundingTriangle( 
			const std::vector< std::vector< cv::Point > >& contours 
			);
		*/

			
		void extractContours(
			const cv::Mat inputImage,
			cv::Mat& outputImage,
			std::vector< std::vector< cv::Point > >& contours,
			std::vector< std::vector< cv::Point > >& approxContours,
			std::vector< cv::Vec4i >& hierarchy
			);
		
		cv::Point2f findMidPoint(
			cv::Point2f vertex1,
			cv::Point2f vertex2
			);
			
		float findRelativeAngle(
			cv::Point2f start,
			cv::Point2f end
			);
} ;


#endif // LMHANDLER_H
