/*******************************************************************************
 *
 * CCHandler.h - Class Header File
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
 *
 ******************************************************************************/

#ifndef CCHANDLER_H
#define CCHANDLER_H

#include <opencv2/opencv.hpp> // Image Processing (OpenCV) header

#include "Packages.h"

class CCHandler
{
	public:

		/** @brief Constructor.
		 */
		CCHandler( void );


		/** @brief Destructor.
		 */
		 ~CCHandler( void );

		/** @brief Print and display the current state.
		 */
		bool initialize( 
			int delay  ,
			const cv::Mat image = cv::Mat()
			);

		/** @brief Handler.
		 */
		CCPacket handle(
			bool 	debugMode 	= false 
			) ;

		/** @brief Print and display the current state.
		 */
		void printState(
			bool printMode = false ,
			bool displayMode = false 
			);



	private:

		bool singleShotMode = false ;
		bool calibrateMode = true ; // false

		cv::Mat intrinsics , distortion;

		cv::Mat singleShotImage ;

		CCPacket state;

		cv::VideoCapture capturer;
		
		bool debugMode;
};

#endif // CCHANDLER_H
