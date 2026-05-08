/* Example Sketch demonstrating how to control two TETRIX PRIME DC motors using a SONY PS5 gaming controller.
 * Motor Channel 1 is controlled by PS5 Left Joystick Y axis
 * Motor Channel 2 is controlled by PS5 Right Joystick Y axis
 * Hardware: TETRIX PULSE, TeleOp module and SONY PS5 gaming controller.
 * Date: 03/17/2025
 * Author: PWU
 */



#include <TELEOP.h>   // TETRIX TeleOp module Library
#include <PULSE.h>    // TETRIX PULSE Library

PULSE pulse;          // Create an instance within the PULSE Library class named pulse
PS5 ps5;              // Create an instance within the PS5 Library class named ps5

int PowerM1;          // Channel 1 Motor Power 
int PowerM2;          // Channel 2 Motor Power


void setup() {

  pulse.PulseBegin();            // Intializes the PULSE controller and waits here for press of green start button
  ps5.setDeadZone (LEFT,10);     // Sets a Left Joystick Dead Zone axis range of +/- 10 about center stick
  ps5.setDeadZone(RIGHT,10);     // Sets a Right Joystick Dead Zone axis range of +/- 10 about center stick

  Serial.begin(115200);
}

void loop() {

  ps5.getPS5();                                 // Get (read) PS5 connections status and all PS5 button and joystick data values

  if(ps5.Connected){                            // If PS5 controller has been succesfully connected, control motors
      PowerM1 = ps5.Motor(LY);                  // Power (speed) and direction of Motor 1 is set by position of Left Y-axis Joystick
      PowerM2 = ps5.Motor(RY);                  // Power (speed) and direction of Motor 2 is set by position of Right Y-axis Joystick
      pulse.setMotorPowers(PowerM1, PowerM2);   // set motor output power levels for PULSE DC motor channels 1 and 2

      Serial.println(PowerM1);
  }
  else{                                         // If PS5 is not connected, stop motors
      pulse.setMotorPowers(0,0);
  }

  
}
