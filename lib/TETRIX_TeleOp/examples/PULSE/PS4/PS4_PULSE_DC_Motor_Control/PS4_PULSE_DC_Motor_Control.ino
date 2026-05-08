/* Example Sketch demonstrating how to control two TETRIX PRIME DC motors using a SONY PS4 gaming controller.
 * Motor Channel 1 is controlled by PS4 Left Joystick Y axis
 * Motor Channel 2 is controlled by PS4 Right Joystick Y axis
 * Hardware: TETRIX PULSE, TeleOp module and SONY PS4 gaming controller.
 * Date: 09/26/2018
 * Author: PWU
 */



#include <TELEOP.h>   // TETRIX TeleOp module Library
#include <PULSE.h>    // TETRIX PULSE Library

PULSE pulse;          // Create an instance within the PULSE Library class named pulse
PS4 ps4;              // Create an instance within the PS4 Library class named ps4

int PowerM1;          // Channel 1 Motor Power 
int PowerM2;          // Channel 2 Motor Power


void setup() {

  pulse.PulseBegin();            // Intializes the PULSE controller and waits here for press of green start button
  ps4.setDeadZone (LEFT,10);     // Sets a Left Joystick Dead Zone axis range of +/- 10 about center stick
  ps4.setDeadZone(RIGHT,10);     // Sets a Right Joystick Dead Zone axis range of +/- 10 about center stick

  Serial.begin(115200);
}

void loop() {

  ps4.getPS4();                                 // Get (read) PS4 connections status and all PS4 button and joystick data values

  if(ps4.Connected){                            // If PS4 controller has been succesfully connected, control motors
      PowerM1 = ps4.Motor(LY);                  // Power (speed) and direction of Motor 1 is set by position of Left Y-axis Joystick
      PowerM2 = ps4.Motor(RY);                  // Power (speed) and direction of Motor 2 is set by position of Right Y-axis Joystick
      pulse.setMotorPowers(PowerM1, PowerM2);   // set motor output power levels for PULSE DC motor channels 1 and 2

      Serial.println(PowerM1);
  }
  else{                                         // If PS4 is not connected, stop motors
      pulse.setMotorPowers(0,0);
  }

  
}
