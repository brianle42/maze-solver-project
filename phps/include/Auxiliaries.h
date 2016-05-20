
/*******************************************************************************
 *
 * Auxiliaries.h - Class Header File
 *
 * Description	:	Moonlight Company
 *			Maze Solver Project
 *			Auxiliaries Class
 *
 * Modified	: 12.05.2016 by Utku Norman  ( norman.utku@metu.edu.tr  )
 * Created	: 12.05.2016 by Utku Norman  ( norman.utku@metu.edu.tr  )
 *
 * People	:	Doga Yucalan ( yucalan.doga@metu.edu.tr )
 *			Utku Norman  ( norman.utku@metu.edu.tr  )
 *
 *
 ******************************************************************************/

// http://www.cplusplus.com/forum/unices/10491/
#if defined(__WIN32__) 
	|| defined(_WIN32) 
	|| defined(WIN32) 
	|| defined(__WINDOWS__) 
	|| defined(__TOS_WIN__)

	#include <windows.h>

	inline void delay( unsigned long ms )
	{

		Sleep( ms );

	}

#else  /* presume POSIX */

	#include <unistd.h>

	inline void delay( unsigned long ms )
	{

		usleep( ms * 1000 );

	}

#endif