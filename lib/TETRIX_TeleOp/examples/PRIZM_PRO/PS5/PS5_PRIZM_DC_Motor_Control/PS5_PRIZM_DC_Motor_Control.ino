/* Example Sketch demonstrating how to control TETRIX TorqueNADO DC motors using a SONY PS5 gaming controller.
 * Motor Channel 1 is controlled by PS5 Left Joystick Y axis
 * Motor Channel 2 is controlled by PS5 Left Joystick X axis
 * Motor Channel 3 is controlled by PS5 Right Joystick Y axis
 * Motor Channel 4 is controlled by PS5 Right Joystick X axis
 * Hardware: TETRIX PRIZM, TeleOp module and SONY PS5 gaming controller.
 * Date: 03/17/2025
 * Author: PWU
 *
 * Controller: Prizm Pro
 * Be sure to set "USB CDC on Boot" option under Tools menu to Enabled when using Serial Monitor
 */



#include <TELEOP.h>       // TETRIX TeleOp module Library
#include <PRIZM_PRO.h>    // TETRIX PRIZM PRO Library

PRIZM prizm;          // Create an instance within the PRIZM Library class named prizm
PS5 ps5;              // Create an instance within the PS5 Library class named ps5

int PowerM1;          // Channel 1 Motor Power 
int PowerM2;          // Channel 2 Motor Power
int PowerM3;          // Channel 3 Motor Power 
int PowerM4;          // Channel 4 Motor Power


void setup() {

  prizm.PrizmBegin();            // Intializes the PRIZM controller and waits here for press of green start button
  ps5.setDeadZone (LEFT,10);     // Sets a Left Joystick Dead Zone axis range of +/- 10 about center stick
  ps5.setDeadZone(RIGHT,10);     // Sets a Right Joystick Dead Zone axis range of +/- 10 about center stick

  Serial.begin(115200);
}

void loop() {

  ps5.getPS5();                                 // Get (read) PS5 connections status and all PS5 button and joystick data values

  if(ps5.Connected){                            // If PS5 controller has been succesfully connected, control motors
      PowerM1 = ps5.Motor(LY);                  // Power (speed) and direction of Motor 1 is set by position of Left Y-axis Joystick
      PowerM2 = ps5.Motor(LX);                  // Power (speed) and direction of Motor 2 is set by position of Left X-axis Joystick
      PowerM3 = ps5.Motor(RY);                  // Power (speed) and direction of Motor 3 is set by position of Right Y-axis Joystick
      PowerM4 = ps5.Motor(RX);                  // Power (speed) and direction of Motor 4 is set by position of Right X-axis Joystick
      prizm.setMotorPowers(PowerM1, PowerM2, PowerM3, PowerM4);   // set motor output power levels for PRIZM Pro DC motor channels 

      Serial.println(PowerM1);  // print to serial monitor
      Serial.println(PowerM2);
      Serial.println(PowerM3);
      Serial.println(PowerM4);
  }
  else{                                         // If PS5 is not connected, stop motors
      prizm.setMotorPowers(0,0,0,0);
  }

  
}
