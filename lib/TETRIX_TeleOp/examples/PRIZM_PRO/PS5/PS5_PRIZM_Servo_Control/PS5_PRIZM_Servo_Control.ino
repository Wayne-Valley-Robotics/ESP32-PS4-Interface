/* Example Sketch demonstrating how to control four TETRIX standard servo motors using a SONY PS5 gaming controller.
 * Hardware: TETRIX PRIZM PRO, TeleOp module and SONY PS5 gaming controller.
 * Servo 1 is controlled by Left Joystick X axis
 * Servo 2 is controlled by Right Joystick X axis
 * Servo 3 is controlled by L2 analog trigger button
 * Servo 4 is controlled by R2 analog trigger button
 * Date: 03/17/2025
 * Author: PWU
 *
 * Be sure to set "USB CDC on Boot" option under Tools menu to Enabled when using Serial Monitor
 */

#include <TELEOP.h>       // TETRIX TeleOp module Library
#include <PRIZM_PRO.h>    // TETRIX PRIZM PRO Library

PRIZM prizm;          // Create an instance within the PRIZM PRO Library class named prizm
PS5 ps5;              // Create an instance within the PS5 Library class named ps5

int Servo1 = 90;      // variables for each servo channel set initially to 90
int Servo2 = 90;
int Servo3 = 90;
int Servo4 = 90;


void setup() {

  prizm.PrizmBegin();                 // Intializes the PRIZM PRO controller and waits here for press of green start button

  prizm.setServoPosition(1, Servo1);  // send each servo to position 90 on program begin
  prizm.setServoPosition(2, Servo2);
  prizm.setServoPosition(3, Servo3);
  prizm.setServoPosition(4, Servo4);

  ps5.setDeadZone(LEFT, 5);           // Sets a Left Joystick Dead Zone axis range of +/- 5 about center stick. This eliminates servo jitter when joysticks are at center (neutral) position 
  ps5.setDeadZone(RIGHT,5);           // Sets a Right Joystick Dead Zone axis range of +/- 5 about center stick. This eliminates servo jitter when joysticks are at center (neutral) position
}

void loop() {

   ps5.getPS5();                                    // Get (read) PS5 connection status and all PS5 button and joystick data values

    if(ps5.Connected){                              // If PS5 controller has been succesfully connected, control servo motors
        
        Servo1 = ps5.Servo(LX);                     // get the Left Stick X axis value mapped to servo range
        prizm.setServoPosition(1, Servo1);

        Servo2 = ps5.Servo(RX);                     // get the Right Stick X axis value mapped to servo range
        prizm.setServoPosition(2, Servo2);

        Servo3 = ps5.Servo(L2T);                    // get the Left annalog trigger button value mapped to servo range
        prizm.setServoPosition(3, Servo3);

        Servo4 = ps5.Servo(R2T);                    // get the Right annalog trigger button value mapped to servo range
        prizm.setServoPosition(4, Servo4);
      
      }
      else{                                         // If PS5 is not connected, set Servo's to center position (90)
          prizm.setServoPosition(1,90);
          prizm.setServoPosition(2,90);
          prizm.setServoPosition(3,90);
          prizm.setServoPosition(4,90);
      }   
  
}
