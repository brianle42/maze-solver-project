/*******************************************************************************
 *
 * DDHandler.h - Class Header File
 *
 * Description	:	Moonlight Company
 *			Maze Solver Project
 * 			Control Unit Handler Class
 *
 * Modified	: 30.04.2016 by Utku Norman  ( norman.utku@metu.edu.tr  )
 * Created	: 24.04.2016 by Utku Norman  ( norman.utku@metu.edu.tr  )
 *
 * People	:	Doga Yucalan ( yucalan.doga@metu.edu.tr )
 *			Utku Norman  ( norman.utku@metu.edu.tr  )
 *
 ******************************************************************************/

#ifndef CUHANDLER_H
#define CUHANDLER_H

#include <string>

#include "Packages.h"

class CUHandler
{
	public:


		std::string  commandUp			;

		std::string  commandDown		;

		std::string  senseDataTop		;

		std::string  senseDataInRange	;

		std::string  senseDataBottom	;

		/*
		CUPacket CommandUp			;

		CUPacket CommandDown		;

		CHPacket SenseDataTop		;

		CHPacket SenseDataInRange	;

		CHPacket SenseDataBottom	;
		*/

		/** @brief Constructor.
		 */
		CUHandler( void )		;

		/** @brief Handler.
		 */
		CUPacket handle(
			DDPacket errorInfo	,
			PSMPacket platformState	,
			CHPacket senseDataInfo	,
			bool debugMode	= false
			) ;

		/** @brief Print and display the current state.
		 */
		void printState(
			bool printMode = false , 
			bool displayMode = false 
			);

	private:

		CUPacket  state			;

		CHPacket  commandState		;

		bool debugMode			;

		/** @brief Applies thresholding and dilation on an image.
		@param image 		Input  image.
		grayscale
		 */
		void tt(		
			);
};

#endif // CUHANDLER_H
