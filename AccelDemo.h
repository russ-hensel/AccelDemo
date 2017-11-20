#define    VERSION_ID         F( "AccelDemo v1 2017 11 19.0" )


#ifndef accel_demo_h

#define accel_demo_h

// #include "WProgram.h" 
// #  https://github.com/adafruit/DHT-sensor-library/issues/1   changed 2015 Feb 21  this include is in several of the files
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// including 9600 19200 38400       
#define    BAUD_RATE          19200           

// ---------------  configure hardware setup -------------  

//#define STEPPER_DRIVE_TYPE   AccelStepper::FULL4WIRE    // 100 steps per rev on my neema 17 motors 
#define STEPPER_DRIVE_TYPE   AccelStepper::HALF4WIRE


//  use   D:\Russ\0000\python00\python3\_projects\misc_progs\make_perms.py to help generate perms


// perm 0 set 1
#define STEPPER1_PIN_A 5
#define STEPPER1_PIN_B 6
#define STEPPER1_PIN_C 7
#define STEPPER1_PIN_D 8

//// perm 0 set 2
//#define STEPPER1_PIN_A 9
//#define STEPPER1_PIN_B 10
//#define STEPPER1_PIN_C 11
//#define STEPPER1_PIN_D 12

// perm 0 set 2
// ==========================================
//// perm 1
//#define STEPPER1_PIN_A 4
//#define STEPPER1_PIN_B 5
//#define STEPPER1_PIN_C 7
//#define STEPPER1_PIN_D 6

//// perm 2  (4, 6, 5, 7)
//#define STEPPER1_PIN_A 4
//#define STEPPER1_PIN_B 6
//#define STEPPER1_PIN_C 5
//#define STEPPER1_PIN_D 7

//// perm 3 (4, 6, 7, 5)
//#define STEPPER1_PIN_A 4
//#define STEPPER1_PIN_B 6
//#define STEPPER1_PIN_C 7
//#define STEPPER1_PIN_D 5

// and so on 

//#define    LIGHT_PIN          3 

// =============== LCD if used ===================
                              // old names
#define LCD_RS         13     // register select, pin to digital pin 12
#define LCD_ENABLE     12     // pin to digital pin 11
#define LCD_D4         8      // pin to digital pin 5
#define LCD_D5         9      // pin to digital pin 4
#define LCD_D6         10     // pin to digital pin 3
#define LCD_D7         11     // pin to digital pin 2

// ----------------------------------

// used in formatting python code output, see subroutine below
// redefinition: if you want more or fewer values per line
//#define PY_VAL_PER_LINE    10
//#define PY_LINE_CONTINUE   "  \x5c\n"  
//#define PY_LINE_INDENT      F("             ")
//#define PY_COMMENT_PREFIX   F("# ")
    
#endif     // from the top
    





