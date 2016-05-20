/*******************************************************************************
 *
 * RPHandler.h - Class Header File
 *
 * Description	:	Moonlight Company
 *			Maze Solver Project
 * 			Route Planner Handler Class
 *
 * Modified	: 24.04.2016 by Utku Norman  ( norman.utku@metu.edu.tr  )
 * Created	: 24.04.2016 by Utku Norman  ( norman.utku@metu.edu.tr  )
 *
 * People	:	Doga Yucalan ( yucalan.doga@metu.edu.tr )
 *			Utku Norman  ( norman.utku@metu.edu.tr  )
 *
 ******************************************************************************/

#ifndef RPHANDLER_H
#define RPHANDLER_H

#include "Packages.h"

class RPHandler
{
	public:

		/** @brief Constructor.
		 */
		RPHandler( void )		;

		/** @brief Handler.
		 */
		RPPacket handle(
			LMPacket 	labyrinthState	,
			bool		debugMode	= false
			) ;

		/** @brief Print and display the current state.
		 */
		void printState(
			bool printMode = false , 
			bool displayMode = false 
			);
	private:
		RPPacket state			;

		bool debugMode			;

		/** @brief Applies thresholding and dilation on an image.
		@param image 		Input  image.
		grayscale
		 */
		void tt(		
			);
};

#endif // RPHANDLER_H
