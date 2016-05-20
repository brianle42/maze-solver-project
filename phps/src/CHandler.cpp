/*******************************************************************************
 *
 * CHandler.cpp - Source File
 *
 * Description	:	Moonlight Company
 *			Maze Solver Project
 *			Communication Handler Class
 *
 * Modified	: 12.05.2016 by Utku Norman  ( norman.utku@metu.edu.tr  )
 * Created	: 24.04.2016 by Utku Norman  ( norman.utku@metu.edu.tr  )
 *
 * People	:	Doga Yucalan ( yucalan.doga@metu.edu.tr )
 *			Utku Norman  ( norman.utku@metu.edu.tr  )
 *
 ******************************************************************************/
 
// Command Line I/O related headers
#include <cstddef>  					// std::nullptr
#include <iostream> 					// std::cout, std::cerr, std::cin, std::endl
#include <iomanip>  					// std::setw
#include <string>


#include "../include/serial/serial.h"	// Serial Communication Header

#include "../include/CHandler.h"

/*******************************************************************************
 *
 * Constructor
 *
 ******************************************************************************/

CHandler::CHandler( void )
{

	// Port details
	portName.assign( "/dev/ttyUSB0" );

	baudRate = 115200 ;

	serialPort.setPort( portName ) ;

	serialPort.setTimeout( serial::Timeout::max( ) , 20 , 0 , 25 , 0 ) ;

	serialPort.setBaudrate( baudRate ) ;


	try
	{

	serialPort.open( ) ;

	}
	catch ( std::exception &e ) 
	{

		std::cerr << "CHandler(): port open failed. ";
		// << e.what() << endl;
		std::cerr << std::endl;

	}

}

/*******************************************************************************
 *
 * Public Methods
 *
 ******************************************************************************/

void CHandler::printState(
	bool printMode 		, 
	bool displayMode 
	)
{

	if( printMode )
	{
			
		std::cout << "<!---------------------------------------------";
		std::cout << std::endl;
		std::cout << "CHandler.printState() called. Printing state:" ;
		std::cout << std::endl;

	}

	if ( IsNull( state ) )
	{

		std::cerr << "CHandler: state is Null";	
		std::cerr << std::endl;

		return;

	}
	else
	{

		if( printMode )
		{
		
			std::cout << std::endl					;

			std::cout << "Listing state: "			;
			std::cout << std::endl					;

			std::cout << "Data: "					;
			std::cout << state.data					;
			std::cout << std::endl					;
			

			std::cout << std::endl					;

			std::cout << "Listing port details: "	;
			std::cout << std::endl;

			std::cout << "PortName: " << serialPort.getPort() ;
			std::cout << std::endl ;

			std::cout << "PortIsOpen: " << serialPort.isOpen( ) ;
			std::cout << std::endl ;

			std::cout << "Baudrate: " << serialPort.getBaudrate() ;
			std::cout << std::endl ;

			std::cout << "Parity: " << serialPort.getParity() ;
			std::cout << std::endl ;

			std::cout << "Stopbits: " << serialPort.getStopbits() ;
			std::cout << std::endl ;

		}

	}

	if( printMode )
	{
		
		std::cout << "---------------------------------------------->";
		std::cout << std::endl;
		std::cout << std::endl;

	}

}

CHPacket CHandler::handle( 
	CUPacket commandInfo	,
	bool debugMode 
	)
{
	// Declare local variables
	std::string senseByte	;
	size_t numBytesWrote	;

	// Initialize the local variables
	senseByte.assign( "" )	;	
	numBytesWrote = 0	;

	// Check if the serial port is still open
  	if( !serialPort.isOpen( ) )
	{

		std::cerr << "CHandler.handle(): serialPort is not open!" ;
		std::cerr << std::endl ;

		//if( command.compare( "" ) == 0 ) // IsNull( command )
		if( IsNull( commandInfo ) )
		{

			std::cerr << "CHandler.handle(): command is null!" ;
			std::cerr << std::endl ;

		}

		return CHPacketNull;
		
	}

	// Write to the serial port
	numBytesWrote = serialPort.write( commandInfo.data ) ;

	if( debugMode )		// Inform on the progress
	{

		std::cout << "Bytes written: " 		;
		std::cout << numBytesWrote 		;
		std::cout << ", String written: '"	;
		std::cout <<  commandInfo.data		;
		std::cout << "'" << std::endl ;

	}

	// Read from the serial port
	senseByte = serialPort.read( ) ; // Read 1 character

	if( debugMode )		// Inform on the progress
	{

		std::cout << "Bytes read: " << senseByte.length( )  ;
		std::cout << ", String read: '" << senseByte << "'" ;
		std::cout << std::endl ;

	}

	// Export
	state.data.assign( senseByte ) ;

	return state ;

}

/*******************************************************************************
 *
 * Private Methods
 *
 ******************************************************************************/
