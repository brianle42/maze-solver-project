/*******************************************************************************
 *
 * DDHandler.h - Class Header File
 *
 * Description	:	Moonlight Company
 *			Maze Solver Project
 * 			Communication Handler Class
 *
 * Modified	: 25.04.2016 by Utku Norman  ( norman.utku@metu.edu.tr  )
 * Created	: 24.04.2016 by Utku Norman  ( norman.utku@metu.edu.tr  )
 *
 * People	:	Doga Yucalan ( yucalan.doga@metu.edu.tr )
 *			Utku Norman  ( norman.utku@metu.edu.tr  )
 *
 ******************************************************************************/

#ifndef CHANDLER_H
#define CHANDLER_H

#include <string>

#include "serial/serial.h" // Serial Communication Methods Header

#include "Packages.h"

class CHandler
{
	public:

		/** @brief Constructor.
		 */
		CHandler( void )							;

		/** @brief Handler.
		 */
		CHPacket handle( 
			CUPacket commandInfo	,
			bool debugMode	= false 
			) ;

		/** @brief Print and display the current state.
		 */
		void printState(
			bool printMode = false , 
			bool displayMode = false 
			);


	private:

		CHPacket state				;

		serial::Serial serialPort	;

		bool debugMode				;

		std::string portName;
 		unsigned long baudRate;

		/** @brief Applies thresholding and dilation on an image.
		@param image 		Input  image.
		@param tImage 		Output thresholded image.
		@param dImage 		Output dilated image.
		grayscale
		 */
		void tt(		
			);

};

#endif // CHANDLER_H
