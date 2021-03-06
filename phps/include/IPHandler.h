/*******************************************************************************
 *
 * IPHandler.h - Class Header File
 *
 * Description	:	Moonlight Company
 *			Maze Solver Project
 * 			Image Preprocessor Handler Class
 *
 * Modified	: 12.05.2016 by Utku Norman  ( norman.utku@metu.edu.tr  )
 * Created	: 18.04.2016 by Doga Yucalan ( yucalan.doga@metu.edu.tr )
 *
 * People	:	Doga Yucalan ( yucalan.doga@metu.edu.tr )
 *			Utku Norman  ( norman.utku@metu.edu.tr  )
 *
 ******************************************************************************/

#ifndef IPHANDLER_H
#define IPHANDLER_H

#include <opencv2/opencv.hpp>

#include "Packages.h"

class IPHandler
{
	public:

		/** @brief Constructor.
		 */
		IPHandler( void ) ;
		
		/** @brief Initializer.
		 */
		bool initialize(
			CCPacket& imageData	,
			char imageID,
			bool debugMode = false 
			) ;

		/** @brief Handler.
		 */
		IPPacket handle( 
			CCPacket& rawImageData	,
			bool debugMode = false 
			) ;

		/** @brief Print and display the current state.
		 */
		void printState(
			bool printMode = false , 
			bool displayMode = false 
			) ;
	private:	
		IPPacket state			;

		cv::Mat annotatedImage		;

		cv::Mat dilationElement		;
		cv::Mat erosionElement		;

		int erosion_elem = 2		; // 0
		int erosion_size = 2		; // 0
		int erosion_type 		;

		int dilation_elem = 2		; // 0
		int dilation_size = 1		; // 0
		int dilation_type		;

		int const max_elem = 2		;
		int const max_kernel_size = 21	; //21;c

		int dilation_iterations = 1	; // 0 1 2 
		int const max_iteration = 30	;

		int edgeThresh1 = 130		; // 1 // 120 180
		int edgeThresh2 = 295		; // 1 // 300 385

		bool debugMode	;

		int preHandle(
			CCPacket imageData 		,
			cv::Mat& inputImage		,
			cv::Mat& annotatedImage		,
			std::vector< cv::Point >& v 	, // vertices
			bool debugMode
			);		

		void thresholdImage(
			const cv::Mat inputImage	,
			cv::Mat& outputImage
			);

		void adjustImageColor(
			const cv::Mat inputImage	,
			cv::Mat& outputImage		,
			int colorCode
			);

		void applyDilation(
			const cv::Mat inputImage	,
			cv::Mat& outputImage
			);


		/** @brief Estimates contours on a given image.
		@param image   		Input  image on which contours are to be detected.
		@param contours 	Output contours found.
		@param hierarchy 	Output hierarchy of the contours.
		find contours
		 */
		void extractContours(
			const cv::Mat image,
			std::vector< std::vector< cv::Point > >& contours,
			std::vector< cv::Vec4i >& hierarchy
			);

		/** @brief Converts draw curves, set labels, get board vertices
		@param rImage 		Input  raw image.
		@param tImage 		Output thresholded image.
		@param dImage		Output dilated image.
		*/
		int findBoardVertices(
			cv::Mat& inputImage,
			cv::Mat& annotatedImage,
			std::vector< std::vector< cv::Point > > contours,
			std::vector< cv::Point >& vertices
			);

		/** @brief Converts draw curves, set labels, get board vertices
		@param rImage Input  raw image.
		@param tImage Output thresholded image.
		@param dImage Output dilated image.
		detecting red ("start"), green ("end") as of now, will try blue ("ball")
		*/
		int thresholdingForFeaturePoints(
			cv::Mat& inputImage,
			cv::Mat& annotatedImage,
			const char colorID,
			cv::Point2f& center,
			float& radius
			);
};

#endif // IPHANDLER_H
