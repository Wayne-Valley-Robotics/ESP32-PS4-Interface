/* Example Sketch demonstrating how to control four TETRIX standard servo motors using a SONY PS4 gaming controller.
 * Hardware: TETRIX PULSE, TeleOp module and SONY PS4 gaming controller.
 * Servo 1 is controlled by Left Joystick X axis
 * Servo 2 is controlled by Right Joystick X axis
 * Servo 3 is controlled by L2 analog trigger button
 * Servo 4 is controlled by R2 analog trigger button
 * Date: 09/26/2018
 * Author: PWU
 */

#include <TELEOP.h>   // TETRIX TeleOp module Library
#include <PULSE.h>    // TETRIX PULSE Library

PULSE pulse;          // Create an instance within the PULSE Library class named pulse
PS4 ps4;              // Create an instance within the PS4 Library class named ps4

int Servo1 = 90;      // variables for each servo channel set initially to 90
int Servo2 = 90;
int Servo3 = 90;
int Servo4 = 90;


void setup() {

  pulse.PulseBegin();                 // Intializes the PULSE controller and waits here for press of green start button

  pulse.setServoPosition(1, Servo1);  // send each servo to position 90 on program begin
  pulse.setServoPosition(2, Servo2);
  pulse.setServoPosition(3, Servo3);
  pulse.setServoPosition(4, Servo4);

  ps4.setDeadZone(LEFT, 5);           // Sets a Left Joystick Dead Zone axis range of +/- 5 about center stick. This eliminates servo jitter when joysticks are at center (neutral) position 
  ps4.setDeadZone(RIGHT,5);           // Sets a Right Joystick Dead Zone axis range of +/- 5 about center stick. This eliminates servo jitter when joysticks are at center (neutral) position
}

void loop() {

   ps4.getPS4();                                    // Get (read) PS4 connection status and all PS4 button and joystick data values

    if(ps4.Connected){                              // If PS4 controller has been succesfully connected, control servo motors
        
        Servo1 = ps4.Servo(LX);                     // get the Left Stick X axis value mapped to servo range
        pulse.setServoPosition(1, Servo1);

        Servo2 = ps4.Servo(RX);                     // get the Right Stick X axis value mapped to servo range
        pulse.setServoPosition(2, Servo2);

        Servo3 = ps4.Servo(L2T);                    // get the Left annalog trigger button value mapped to servo range
        pulse.setServoPosition(3, Servo3);

        Servo4 = ps4.Servo(R2T);                    // get the Right annalog trigger button value mapped to servo range
        pulse.setServoPosition(4, Servo4);
      
      }
      else{                                         // If PS4 is not connected, set Servo's to center position (90)
          pulse.setServoPosition(1,90);
          pulse.setServoPosition(2,90);
          pulse.setServoPosition(3,90);
          pulse.setServoPosition(4,90);
      }   
  
}
