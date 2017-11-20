// Program description ( AccelDemo ):
//      Demo of stepper motor using accel library 
//
//      Features
//           Control via the serial monitor or other terminal program
//              Special software in:  russ-hensel/python_smart_terminal: A smart serial terminal written in python
//                                    https://github.com/russ-hensel/python_smart_terminal
//
//
// History/Status:  ( most recent at top * done ! pending )
//        Summary:  ver1 most important parts work
//         * start Aug 2017
//         
//
//
// Compile info
//        
//      Sketch uses 8,500 bytes (26%) of program storage space. Maximum is 32,256 bytes.
//      Global variables use 567 bytes (27%) of dynamic memory, leaving 1,481 bytes for local variables. Maximum is 2,048 bytes.
//
//
//
//
// Environment:  
//    Arduino, compile with arduino.exe  1.60
//              Developed on Windows 10 64 bit
//              To run this:
//              
//                   use a terminal emulator on the PC side, or the arduino serial monitor,
//                   my python smart terminal program
//                   For configuation info see header file (.h), comm rates, ports....  ( for program version see VERSION_ID )
//                         
//
//
// Author:      russ_hensel http://www.opencircuits.com/User:Russ_hensel
//              
// Uses this library:
//      http://www.airspayce.com/mikem/arduino/AccelStepper/index.html
//
// ============================= easy modification using #define 's ================================

#include "AccelDemo.h"        // #defines for this project
#include "SerialCmd.h"        // for command interperter 

// ============================= globals variables ========

SerialCmd    serialCmd;

#include <AccelStepper.h>

//  Number of pins to interface to. Integer values are supported, but it is preferred to use the MotorInterfaceType symbolic names. 
//  AccelStepper::DRIVER (1) means a stepper driver (with Step and Direction pins). If an enable line is also needed, call setEnablePin() after construction. 
//  You may also invert the pins using setPinsInverted(). AccelStepper::FULL2WIRE (2) means a 2 wire stepper (2 pins required). 
//  AccelStepper::FULL3WIRE (3) means a 3 wire stepper, such as HDD spindle (3 pins required). AccelStepper::FULL4WIRE (4) means a 4 wire stepper (4 pins required). 
//  AccelStepper::HALF3WIRE (6) means a 3 wire half stepper, such as HDD spindle (3 pins required) AccelStepper::HALF4WIRE (8) means a 4 wire half stepper (4 pins required)
//  Defaults to AccelStepper::FULL4WIRE (4) pins.

// Define some steppers and the pins the will use this version is for 2 wire driver 
// AccelStepper stepper1( AccelStepper::DRIVER, STEPPER1_STEP_PIN, STEPPER1_DIR_PIN );
 
AccelStepper   stepper1( STEPPER_DRIVE_TYPE, STEPPER1_PIN_A, STEPPER1_PIN_B, STEPPER1_PIN_C, STEPPER1_PIN_D, true ); 

// ----------------------------------------------------------------
// help just a little intro for the program -- summary of commands and version 
void rptHelp( void ) {
  Serial.println( F( "" ) );                                // setup   loop
  Serial.print( F( "Help for:  ") );  
  Serial.println( VERSION_ID  );   
  Serial.println( F( "ann   setAcceleration" ) );           // setAcc       void AccelStepper::setAcceleration  ( float   acceleration  ) 
  Serial.println( F( "enn   examples" ) );                  // case 'e':    ex_nn       
  Serial.println( F( "mnn   moveToNow " ) );                // case 'm':    moveToNow    moveToNow(    // moveTo     not   void AccelStepper::moveTo  ( long  absolute  ) 
  Serial.println( F( "nnn   nudgePos " ) );                 // case 'n':    nudge()
  Serial.println( F( "tnn   set Top or MaxSpeed" ) );       // setMaxSpeed  void AccelStepper::setMaxSpeed  ( float   speed ) 
  Serial.println( F( "v     Version of software" ) );       // rptVersion
  Serial.println( F( "w     whatIsStatus" ) );              // statusReport
  Serial.println( F( "z     ZeroCurrent pos" ) );           //  case 'z':       zeroCurrent           
  Serial.println( F( "?     Help" ) );                      // rptHelp

  return;
}

// ---------- Main ----------   
void loop()   {
    
    unsigned char   debugStr;
    unsigned char   locCmd;
    long            cmdPriorNbr;
    uint8_t         z_pin;    // pin for z command 

    serialCmd.tryRecCmd( );
    
    if ( serialCmd.gotCmd  )   {

      locCmd   = serialCmd.cmdPrior[0];     // in case access is expensive
      // lower case the command as necessary // combine with above and make sub, possibly inline -- beware special char 
      if ( ( locCmd < 97 ) && ( locCmd > 64 ) ) {
          locCmd += 32;
      } 
      cmdPriorNbr   = serialCmd.parseCmdNbr( serialCmd.cmdPrior );   
      // decode command....
      switch ( locCmd )  {
     
        case 'a':  // 
            setAcc( cmdPriorNbr );
            break;
            
        case 'e':  // 
            ex_nn( cmdPriorNbr );
            break;
            
        case 'm':  // 
            moveToNow( cmdPriorNbr );
            break;
            
        case 'n':  // 
            nudge( cmdPriorNbr );
            break;
            
        case 'p':  // 
            setPower( cmdPriorNbr );
            break;
           
//        case 's':  // 
//            setSpeed( cmdPriorNbr );
//            break;

        case 't':  // 
            setMaxSpeed( cmdPriorNbr );
            break;            
                                                         
         case 'v':  // report version 
            rptVersion();
            break; 

         case 'w':  // 
            statusReport( );    
            break;

         case 'z':  // 
            zeroCurrent( );    
            break;
            
         case '?':  // report help
            rptHelp();
            break; 
                                                  
        default:
          Serial.print( F( "!Bad Command = " ) );
          Serial.println( locCmd );
        } 
      Serial.println( "ok" );
      serialCmd.gotCmd    = 0;
    }           
}

// ---------------------------------------------- 
// setSpeed ( float   speed ) [in]  speed The desired maximum speed in steps per second. Must be > 0.
// in hundredths of a step per second ( avoid ui floats )  
void setSpeedxxx( long arg_speed ) {
      float speed;
      float ret_float;
      //Serial.println( arg_speed );
      speed           = arg_speed / 100.;
      // last_max_speed  = speed;
      stepper1.setSpeed( speed );
      Serial.print( F( "setSpeed " )  );
      Serial.println( speed );
      ret_float = stepper1.speed();              // float AccelStepper::speed  (   )                 The most recently set speed
      Serial.print( F( "Speed setting: ") ); 
      Serial.println(  ret_float ); 
}

// ---------------------------------------------- 
//  void AccelStepper::setCurrentPosition  ( long  position  ) 
void zeroCurrent(  ) {
      long current;
      current   = stepper1.currentPosition(); 
      Serial.println(  current ); 
      stepper1.setCurrentPosition( 0 );              //
      Serial.println( F( "Current position set to Zero") ); 
      // Serial.println(  ret_float ); 
      current   = stepper1.currentPosition(); 
      Serial.println(  current ); 
}

// ---------------------------------------------- 
// in hundredths of a step per second ( avoid ui floats )  
void setMaxSpeed( long arg_speed ) {
      float speed;
      float ret_float;
      Serial.println( arg_speed );
      speed           = arg_speed / 10.;
      stepper1.setMaxSpeed( speed );           // setMaxSpeed ( float   speed ) [in]  speed The desired maximum speed in steps per second. Must be > 0.
      Serial.print( F( "setMaxSpeed " )  );
      Serial.println( speed );
      ret_float = stepper1.maxSpeed();            
      Serial.print( F( "MaxSpeed setting: ") ); 
      Serial.println(  ret_float ); 
}

// ----------------------------------------------
// note arg_acc may be scaled  
void setAcc( long arg_acc ) {
      float acc;
      acc  = arg_acc / 10.;
      //last_acc  = acc;
      stepper1.setAcceleration( acc );  // setAcceleration( 200.0 ); ( float  )
      Serial.print( F( "setAcc " ) );
      Serial.println( acc );
}

//// ----------------------------------------------
//// boolean AccelStepper::run (   ) 
//void runLoop(  ) {
//
//      long  ret_long;
//      Serial.println( F( "begin runLoop " ) );
//      statusReport();
//      Serial.println( F( "run..... " ) );
//      stepper1.moveTo( next_target_position );
//      while ( stepper1.run() ) {
//
//        // consider print for slow loops 
//        
//      }
//      ret_long = stepper1.currentPosition();     //  long AccelStepper::currentPosition (   )      The currently motor position.
//      Serial.print( F( "Current Position: ") ); 
//      Serial.println(  ret_long ); 
//      Serial.println( F( "end runLoop " ) );
//}

// ----------------------------------------------
// setPower( 0 or not 0 );   or enable 0 1 
// arg really false or not using an int  
void setPower( int arg_power ) {
      if ( arg_power == 0 ) {
           stepper1.disableOutputs(  );
           Serial.println( F( "setPower off " ) );
      } else {
           stepper1.enableOutputs(  );
           Serial.println( F( "setPower ON " ) );
      }
}

// ----------------------------------------------
// void AccelStepper::moveTo ( long  absolute  )   
// think this sets position no actual move -- might want to change prints   
void moveToxxx( long arg_pos ) {
      Serial.print( F( "set moveTo " ) );
      Serial.println(  arg_pos );
      stepper1.moveTo( arg_pos );
}

// ----------------------------------------------
//  moves to a position 
void moveToNow( long arg_pos ) {
      long ret_long;
      Serial.print( F( "moveToNow: " ) );
      Serial.println(  arg_pos );
      stepper1.moveTo( arg_pos );                // void AccelStepper::moveTo ( long  absolute  )   
      while ( stepper1.run() ) {
        // consider print for slow loops 
      }
      ret_long = stepper1.currentPosition();     //  long AccelStepper::currentPosition (   )      The current motor position.
      Serial.print( F( "end moveToNow -- Current Position: ") ); 
      Serial.println(  ret_long ); 
}

// ----------------------------------------------
// moves by the amount specified a delta position 
void nudge( long arg_pos ) {
      long ret_long;
      Serial.print( F( "nudge by : " ) );
      Serial.println(  arg_pos );
      ret_long = stepper1.currentPosition();
      ret_long += arg_pos;
      stepper1.moveTo( ret_long );               // void AccelStepper::moveTo ( long  absolute  )   
      while ( stepper1.run() ) {
        // consider print for slow loops 
      }
      ret_long = stepper1.currentPosition();     //  long AccelStepper::currentPosition (   )      The current motor position.
      Serial.print( F( "end nudge -- Current Position: ") ); 
      Serial.println(  ret_long ); 
}

// ----------------------------------------------
// run one of the examples of code at the accel site see ex_1.... 
void ex_nn( int arg_ex ) {
      Serial.print( F( "ex_nn = " ) );
      Serial.println( arg_ex );
      switch ( arg_ex )  {
     
        case 1:  // 
            ex_1();
            break;
        case 2:  // 
            ex_2();
            break;

        case 3:  // 
            ex_3();
            break;
            
        default:
            Serial.println( F( "!Bad ex_nn = " ) );
      }
      Serial.println( F( "ex_nn done" ) );
}

// ----------------------------------------------
// "ex_1 -> Bounce.pde: loop forever"
// close serial port to reset 
void ex_1(  ) {
      Serial.println( F( "ex_1 -> Bounce.pde: loop forever" ) );
      stepper1.setMaxSpeed(100);
      stepper1.setAcceleration(20);
      stepper1.moveTo(500);
      while ( 1 )  {
        if (stepper1.distanceToGo() == 0)
          stepper1.moveTo(-stepper1.currentPosition());
          stepper1.run();
      }
}

// ----------------------------------------------
// "ex_2 -> ConstantSpeed.pde: loop forever"
// close serial port to reset 
void ex_2(  ) {
     Serial.println( F( "ex_2 -> ConstantSpeed.pde: loop forever" ) );
     stepper1.setMaxSpeed(1000);
     stepper1.setSpeed(50);
     while( 1 )  {
         stepper1.runSpeed();
      }
}

// ----------------------------------------------
// "ex_3 -> Overshoot.pde: loop forever"
// close serial port to reset  
void ex_3(  ) {
      Serial.println( F( "ex_3 -> Overshoot.pde: loop forever" ) );
      stepper1.setMaxSpeed( 150 );
      stepper1.setAcceleration(100);
      while( 1 )  {
          stepper1.moveTo( 500 );
          while (stepper1.currentPosition() != 300) {  // Full speed up to 300
                stepper1.run();
          }
          stepper1.runToNewPosition( 0 ); // Cause an overshoot then back to 0
        }
}

// ----------------------------------------------
//  possible future expansion 
void ex_4(  ) {
      Serial.println( F( "ex_4 " ) );
      
}

// ----------------------------------------------------------------
// lots of status info 
void statusReport( void ) {
    long     ret_long;
    float    ret_float;
    
    Serial.println( F( "" ) );
    Serial.println( F( "Status") );  
    Serial.println( VERSION_ID  );
    
    ret_long = stepper1.targetPosition(   );   //  long AccelStepper::targetPosition (   ) 
    Serial.print( F( "Target Position: ") ); 
    Serial.println(  ret_long ); 

    ret_long = stepper1.currentPosition();     //  long AccelStepper::currentPosition (   )   The currently motor position.
    Serial.print( F( "Current Position: ") ); 
    Serial.println(  ret_long ); 

    ret_long = stepper1.distanceToGo();        // long AccelStepper::distanceToGo (   )       The distance from the current position to the target position.
    Serial.print( F( "distanceToGo: ") ); 
    Serial.println(  ret_long ); 

    ret_long = stepper1.isRunning();           // bool AccelStepper::isRunning  (   )         Checks to see if the motor is currently running to a target
    Serial.print( F( "Is Running: ") ); 
    Serial.println(  ret_long ); 

    ret_float = stepper1.speed();               // float AccelStepper::speed  (   )           The most recently set speed
    Serial.print( F( "Speed setting: ") ); 
    Serial.println(  ret_float ); 

    ret_float = stepper1.maxSpeed ();          // float AccelStepper::maxSpeed ()             The most recently set max speed
    Serial.print( F( "MaxSpeed setting: ") ); 
    Serial.println(  ret_float ); 
    
    // Serial.println( F( "ann   setAcceleration" ) ); 
}
// ------------------------------------------------------
void rptVersion( )   {
    Serial.println( VERSION_ID  );
}

// ----------------------------------------------------------------

// ---------- begin setup ----------
void setup()   {
  
      Serial.begin( BAUD_RATE );
      
      serialCmd             = SerialCmd();
      serialCmd.resetCmd(  );
 
      delay( 1000 );     // setup time, may or may not be needed 
      stepper1.setMaxSpeed(100);        
      stepper1.setAcceleration(20.0);
      rptVersion();
      Serial.println( F( "Ready..." ) );
      Serial.println( F( "Ok" ) );
}


// ======================= eof ==============================







