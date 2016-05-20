/************************************************************************
 *
 * mazeSover-MCU.ino - .INO Source File
 *
 * Description: Playground for image processing
 *
 * Modified : 28.04.2016 by Utku Norman  ( norman.utku@metu.edu.tr  )
 * Created  : 13.04.2016 by Utku Norman  ( norman.utku@metu.edu.tr  )
 *
 * People :   Doga Yucalan ( yucalan.doga@metu.edu.tr )
 *            Utku Norman  ( norman.utku@metu.edu.tr  )
 *
 * Hardware: ES-prototype-1
 *
 *  Connections:
 *
 *      - Power related
 *          - 100uF capacitor between GND - VMOT
 *
 *      - MCU to Driver board / A4988
 *        - DIR     <-> D7
 *        - STEP    <-> D6*
 *        - MS1     <-> A0  //D2
 *        - MS2     <-> A2  //D3*
 *        - MS3     <-> D5*
 *        - ENABLE' <-> D4
 *
 *      - MCU to limit switches
 *        - END     <-> D2  // MINIMUM
 *        - MID     <-> D3* // MAXIMUM
 *
 *      - Driver board / A4988 to Motor
 *        - A1 <-> RED
 *        - A2 <-> GRN
 *        - B1 <-> YEL
 *        - B2 <-> BLU 
 *
 *  Notes:
 *
 *  Microstepping mode: 1,2,4,8,16 or 32(DRV8834 only)
 *  Mode 1 is full speed.
 *  Mode 32 is 32 microsteps per step.
 *  The motor should rotate just as fast (set RPM),
 *  but movement precision is increased.
 *
 *********************************************************************/

#include <Arduino.h>
#include "A4988.h"

///////////////////////////////////////////////////////////////////////
// Define Main Loop Parameters

#define MAIN_LOOP_DELAY   0   // 500

///////////////////////////////////////////////////////////////////////
// Define Serial Communication Details

#define BAUD ( 115200 )

int incomingByte = 0          ;   // 

///////////////////////////////////////////////////////////////////////
// Stepper Characteristics

// Set direction convention
#define DIR_UP          -1      // ..
#define DIR_DOWN        1       // ..

// Set stepper driving parameters
#define STEPS_PER_REV   1       // using a 200-step motor
#define MAX_RPM         5000    // maximum rounds-per-minute
#define MICROSTEPS      16      // Microstepping coefficient

// Set stepper motor pins
#define PIN_DIR         7       // DIR
#define PIN_STEP        6       // STEP
#define PIN_MS1         A0      // MS1
#define PIN_MS2         A2      // MS2
#define PIN_MS3         5       // MS3
#define PIN_EN          4       // ENABLE', active low

// Define the stepper
// "Fully wired. 
//  All the necessary control pins for A4988 are connected."
A4988 stepper(
    STEPS_PER_REV ,             // Steps / Revolution 
    PIN_DIR       ,             // DIR
    PIN_STEP      ,             // STEP
    PIN_MS1       ,             // MS1
    PIN_MS2       ,             // MS2
    PIN_MS3                     // MS3
    );

const int numSteps = 5 ; // Num. of full-steps to take per command

enum class Direction { up , down } ; // Directions

///////////////////////////////////////////////////////////////////////
// Set pins for the other peripherals
#define PIN_LED         13      // 
#define PIN_MIN         3//2       // Limit switch minimum
#define PIN_MAX         2//3       // Limit switch maximum

///////////////////////////////////////////////////////////////////////
// Set mode
#define DEBUG_MODE      false    //
#define FEEDBACK_MODE   true     // ..

///////////////////////////////////////////////////////////////////////
// Interrupt Related Definitions for Limit Switches

const int debouncingInterval = 150      ;

volatile bool minStopFlag = false       ;
volatile bool maxStopFlag = false       ;

// Variables to keep track of the timing of recent interrupts
volatile unsigned long minTime      = 0 ;  
volatile unsigned long lastMinTime  = 0 ; 
volatile unsigned long maxTime      = 0 ;  
volatile unsigned long lastMaxTime  = 0 ;

///////////////////////////////////////////////////////////////////////
// Other Variables
//const bool debugMode      = false       ; //true ;
//const bool feedbackMode   = true       ; //true ;

//
//     #if defined(ARDUINO) && ARDUINO >= 100
//        Serial.print("B");  // Botto
//      #else
//       // old
//      #endif

///////////////////////////////////////////////////////////////////////
// Helper Methods

// Enable the stepper
void enableStepper( void )
{

  digitalWrite( PIN_EN , LOW  )  ; // ENABLE', active low

}

// Disable the stepper
void disableStepper( void )
{

  digitalWrite( PIN_EN , HIGH )  ; // ENABLE', active low

}

///////////////////////////////////////////////////////////////////////
// Setup Procedure
void setup( void ) 
{
  
  // Assert the auxiliary pin directions
  pinMode(PIN_LED,OUTPUT)     ;           // Led pin is output

  // Configure the limit switch ISRs
  // pinMode( PIN_SW1 , INPUT_PULLUP );
  pinMode( PIN_MIN , INPUT ) ;            // Switch 1 pin direction
  attachInterrupt(                        // Init and bind ISR
    digitalPinToInterrupt( PIN_MIN )  ,   //
    switchMinISR                      ,   //
    CHANGE
    //RISING                                // pin goes from low to high
    ) ;
  pinMode( PIN_MAX , INPUT ) ;            // Switch 2 pin direction
  attachInterrupt(                        // Init and bind ISR
    digitalPinToInterrupt( PIN_MAX )  ,   //
    switchMaxISR                      ,   //
    CHANGE
    //RISING                                // pin goes from low to high
    ) ;
  
  // Configure the stepper
  stepper.setRPM( MAX_RPM )           ;   // Set stepper RPM
  stepper.setMicrostep( MICROSTEPS )  ;   // Set full speed mode 1:1

  // Configure the serial communcation module
   // Initialize serial communication
  Serial.begin( BAUD );

  enableStepper();

  #if DEBUG_MODE == true

    Serial.print("Ready. Press a key to continue.. ");

    while( Serial.available() == 0 )  ;               // Wait for input

    Serial.flush( );

    Serial.println("Waiting for command. 'w' for up, 's' for down.");

  #endif

}

///////////////////////////////////////////////////////////////////////
// Interrupt Service Routines

// External Interrupt ISR for the limit switch min
void switchMinISR( void )
{  

  minTime = millis();

  if ( minTime - lastMinTime > debouncingInterval )
  {

    if( !minStopFlag )      // Rising edge, since rising does not precede
    {

      minStopFlag = true;

      #if FEEDBACK_MODE == true

        Serial.print("B");  // Bottom

      #endif
      
    }
    else                    //  Falling edge. Rising edge precedes.
    {

      minStopFlag = false;  

      #if FEEDBACK_MODE == true

        Serial.print("N"); // Nominal

      #endif
        
    }

    lastMinTime = minTime;

  }
  
  //Serial.println("Min switch pressed.");
  //Serial.println("Min switch released.");

}

// External Interrupt ISR for the limit switch max
void switchMaxISR( void )
{

  maxTime = millis();

  if ( maxTime - lastMaxTime > debouncingInterval )
  {

    if( !maxStopFlag )      // Rising edge, since rising does not precede
    {

      maxStopFlag = true;

      #if FEEDBACK_MODE == true

        Serial.print("T");  // Top

      #endif

    }
    else                    //  Falling edge. Rising edge precedes.
    {

      maxStopFlag = false;

    #if FEEDBACK_MODE == true

        Serial.print("N"); // Nominal

    #endif

    }

    lastMaxTime = maxTime;

  }

}

///////////////////////////////////////////////////////////////////////
// Adjust Procedure

void driveStepper( Direction dir ) 
{
  if( dir == Direction::up )
     for( int i = 0 ; i < numSteps * MICROSTEPS ; i++ )
      {

        checkEndstops( ) ;

        if ( maxStopFlag )
        {

          break;

        } 

        stepper.move( DIR_UP );

      }
  else if( dir == Direction::down )
  {

      for ( int i = 0 ; i < numSteps * MICROSTEPS ; i++ )
      {

        checkEndstops( ) ;

        if ( minStopFlag )
        {

          break;

        }

        stepper.move( DIR_DOWN );

      }
  }

}

///////////////////////////////////////////////////////////////////////
// Adjust Procedure

void checkEndstops( void )
{

  if( !digitalRead( PIN_MAX ) && maxStopFlag )
  {

    maxTime = millis();

    if ( maxTime - lastMaxTime > debouncingInterval )
    {

      maxStopFlag = false;

      #if FEEDBACK_MODE == true

          Serial.print("N"); // Nominal

      #endif

      lastMaxTime = maxTime;

    }

  } // EoI if( !digitalRead( PIN_MAX ) && maxStopFlag )

  if( !digitalRead( PIN_MIN ) && minStopFlag )
  {

    minTime = millis();

    if ( minTime - lastMinTime > debouncingInterval )
    {

      minStopFlag = false;

      #if FEEDBACK_MODE == true

          Serial.print("N"); // Nominal

      #endif

      lastMinTime = minTime;

    }

  } // EoI if( !digitalRead( PIN_MIN ) && minStopFlag )

}


/*
void checkEndstops( void )
{
  if( !digitalRead( PIN_MAX ) )
  {


    maxStopFlag = false;

  }

  if( !digitalRead( PIN_MIN ) )
  {

    minStopFlag = false;
    
  }
}
*/

///////////////////////////////////////////////////////////////////////
// Main Loop Procedure
void loop( void ) 
{

  #if DEBUG_MODE == true

      Serial.println("Waiting for command.");

  #endif

  while( Serial.available() == 0 )  ;

  incomingByte = Serial.read( )     ;

  switch ( incomingByte )
  {
    case 'w':
    case 'W':
      driveStepper( Direction::up );
      break;

    case 's':
    case 'S':
      driveStepper( Direction::down );
      break;

    case 'e':
    case 'E':

      enableStepper();

      break;

    case 'd':
    case 'D':

      disableStepper();

      break;

    default:

      #if DEBUG_MODE == true

        Serial.println("Unknown command.");

      #endif

      break;
  }
  
  //checkEndstops( );

  if ( MAIN_LOOP_DELAY > 0 )
  {

    Serial.println("Pause");

  }

  delay( MAIN_LOOP_DELAY );       // pause for half a second

}