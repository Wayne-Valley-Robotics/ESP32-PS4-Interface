/*  TETRIX TELE-OP MODULE ARDUINO LIBRARY
   	Written by: Paul W. Uttley
	10/02/2018
	Version 1.0

*/

// Added support for PS5 - 03.17.25

#include <Arduino.h>
//#include <avr/wdt.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <Wire.h>
#include "TELEOP.h"

//================================================================================= PS4 CONTROLLER ======================================================================================

void PS4::getPS4(){
  Wire.begin();
  Wire.beginTransmission(8);      //transmit to I2C address
  Wire.write(0x1E);               //send register
  Wire.endTransmission();         //end transmission
  delay(10);
  Wire.requestFrom(8, 32);        //request 32 bytes from Tele-Op Module at I2Caddress
  buttons_1   = Wire.read();
  buttons_2   = Wire.read();
  Touchb 	  = Wire.read();
  PBb		  = Wire.read();
  LxStick	  = Wire.read();
  LyStick     = Wire.read();
  RxStick     = Wire.read();
  RyStick     = Wire.read();
  L2Trigger   = Wire.read();
  R2Trigger   = Wire.read();
  LxMotor	  = Wire.read();
  LyMotor	  = Wire.read();
  RxMotor	  = Wire.read();
  RyMotor	  = Wire.read();
  LxServo	  = Wire.read();
  LyServo	  = Wire.read();
  RxServo	  = Wire.read();
  RyServo	  = Wire.read();
  LtMotor	  = Wire.read();
  RtMotor	  = Wire.read();
  LtServo	  = Wire.read();
  RtServo	  = Wire.read();
  Pitch_LO    = Wire.read();
  Pitch_HI    = Wire.read();
  Roll_LO     = Wire.read();
  Roll_HI     = Wire.read();
  TouchX_LO   = Wire.read();
  TouchX_HI	  = Wire.read();
  TouchY_LO   = Wire.read();
  TouchY_HI   = Wire.read();
  Status      = Wire.read();
  inRange	  = Wire.read();

  delay(10);

  Pitchb = (Pitch_HI * 256) + Pitch_LO;			// 0 - 360
  Rollb = (Roll_HI *256) + Roll_LO;				// 0 - 360

  TouchXb = (TouchX_HI * 256) + TouchX_LO;
  TouchYb = (TouchY_HI * 256) + TouchY_LO;

  L2b 		= 0;
  L1b 		= 0;
  R2b 		= 0;
  R1b 		= 0;
  Crossb 	= 0;
  Circleb 	= 0;
  Squareb 	= 0;
  Triangleb = 0;
  Upb 		= 0;
  Downb 	= 0;
  Rightb 	= 0;
  Leftb 	= 0;
  R3b 		= 0;
  L3b 		= 0;
  Shareb 	= 0;
  Optionsb	= 0;

  Connected 	= 0;
  if(Status == 1) {Connected = 1;}


  if(buttons_1 & B00000001){L2b = 1;} 	// set booleans for button group 1
  if(buttons_1 & B00000010){L1b = 1;}
  if(buttons_1 & B00000100){R2b = 1;}
  if(buttons_1 & B00001000){R1b = 1;}
  if(buttons_1 & B00010000){Crossb = 1;}
  if(buttons_1 & B00100000){Circleb = 1;}
  if(buttons_1 & B01000000){Squareb = 1;}
  if(buttons_1 & B10000000){Triangleb = 1;}

  if(buttons_2 & B00000001){Upb = 1;} 	// set booleans for button group 2
  if(buttons_2 & B00000010){Downb = 1;}
  if(buttons_2 & B00000100){Rightb = 1;}
  if(buttons_2 & B00001000){Leftb = 1;}
  if(buttons_2 & B00010000){R3b = 1;}
  if(buttons_2 & B00100000){L3b = 1;}
  if(buttons_2 & B01000000){Shareb = 1;}
  if(buttons_2 & B10000000){Optionsb = 1;}
 }



 int PS4::Touchpad(int PS4touch){
 	int TouchCoordinate;
	switch (PS4touch){
		case 33:
			TouchCoordinate = TouchXb;
			break;
		case 34:
			TouchCoordinate = TouchYb;
			break;
	}

	return TouchCoordinate;
 }


 int PS4::Angle(int PS4gyro){
 	int Gyro;
	switch (PS4gyro){
		case 31:
			Gyro = Pitchb;
			break;
		case 32:
			Gyro = Rollb;
			break;
	}

	return Gyro;
 }


 int PS4::Stick(int PS4stick){

	int Stick;
	switch (PS4stick){
		case 8:
			Stick = LxStick;
			break;
		case 9:
			Stick = LyStick;
			break;
		case 10:
			Stick = RxStick;
			break;
		case 11:
			Stick = RyStick;
			break;
	}

 		return Stick;
 }


 int PS4::Button(int PS4button){
 	int Button;
	switch (PS4button){
		case 12:
			Button = L2Trigger;
			break;
		case 13:
			Button = R2Trigger;
			break;
		case 14:
			Button = L1b;
			break;
		case 15:
			Button = L2b;
			break;
		case 16:
			Button = L3b;
			break;
		case 17:
			Button = R1b;
			break;
		case 18:
			Button = R2b;
			break;
		case 19:
			Button = R3b;
			break;
		case 20:
			Button = Upb;
			break;
		case 21:
			Button = Downb;
			break;
		case 22:
			Button = Rightb;
			break;
		case 23:
			Button = Leftb;
			break;
		case 24:
			Button = Crossb;
			break;
		case 25:
			Button = Circleb;
			break;
		case 26:
			Button = Squareb;
			break;
		case 27:
			Button = Triangleb;
			break;
		case 28:
			Button = Shareb;
			break;
		case 29:
			Button = Optionsb;
			break;
		case 30:
			Button = Touchb;
			break;
		case 35:
			Button = PBb;
			break;

	}

	return Button;

 }

 void PS4::setDeadZone(int Stick, int Amount){
 	Amount = constrain(Amount,0,100); //constrain to 0 - 100
 	if(Stick == 23) {
	  Wire.beginTransmission(8);      //transmit to I2C address
	  Wire.write(0x22);               //send register
	  Wire.write(Amount);			  //Send dead zone set for left stick
	  Wire.endTransmission();         //end transmission
	  delay(10);
	}
	if(Stick == 22) {
	  Wire.beginTransmission(8);      //transmit to I2C address
	  Wire.write(0x23);               //send register
	  Wire.write(Amount);			  //Send dead zone set for right stick
	  Wire.endTransmission();         //end transmission
	  delay(10);
	}

 }


 int PS4::Servo(int PS4servo){
 	int ServoMap = 90;
	// ==================== Analog Trigger Buttons (no dead zone applied) ===============================
	if(PS4servo == 12){ServoMap = map(L2Trigger, 0, 255, 0, 180);}
  	if(PS4servo == 13){ServoMap = map(R2Trigger, 0, 255, 0, 180);}
	if(PS4servo == 31){ServoMap = map(Pitchb, 0, 360,  0, 180);}
	if(PS4servo == 32){ServoMap = map(Rollb, 0, 360,  0, 180);}

	// ==================== TeleOp joysticks mapped to 0 - 180 servo range with dead zone =====

	if(PS4servo == 8){ServoMap = LxServo;}

	if(PS4servo == 9){ServoMap = LyServo;}

	if(PS4servo == 10){ServoMap = RxServo;}

	if(PS4servo == 11){ServoMap = RyServo;}

	return ServoMap;
 }

 int PS4::Motor(int PS4motor){
 	int MotorMap = 0;
	// ==================== Analog Trigger Buttons (no dead band applied) ===============================
	if(PS4motor == 12){MotorMap = map(L2Trigger, 0, 255,  0, 100);}
	if(PS4motor == 13){MotorMap = map(R2Trigger, 0, 255,  0, 100);}
	if(PS4motor == 31){MotorMap = map(Pitchb, 0, 360,  -100, 100);}
	if(PS4motor == 32){MotorMap = map(Rollb, 0, 360,  -100, 100);}

	// ==================== TeleOp joysticks mapped to -100 to 100 power range with dead zone =====

	if(PS4motor == 8){MotorMap = LxMotor;}

	if(PS4motor == 9){MotorMap = LyMotor;}

	if(PS4motor == 10){MotorMap = RxMotor;}

	if(PS4motor == 11){MotorMap = RyMotor;}

  return MotorMap;
 }


 void PS4::setRumble(int level){
 	int rumble = 0;
	if(level == 5){rumble = 0;}
	if(level == 6){rumble = 1;}
	if(level == 7){rumble = 2;}
  Wire.beginTransmission(8);      //transmit to I2C address
  Wire.write(0x1F);               //send register
  Wire.write(rumble);			  //rumble set to off = 0, rumble set to low = 1, rumble set to high = 2
  Wire.endTransmission();         //end transmission
  delay(10);
}


void PS4::setLED(int LED){
  Wire.beginTransmission(8);    //transmit to I2C address
  Wire.write(0x20);             //send register
  Wire.write(LED);		      	//send LED color
  Wire.endTransmission();       //end transmission
  delay(10);
}

void PS4:: resetTeleOp(){
  Wire.beginTransmission(8);    //transmit to I2C address
  Wire.write(0x21);             //send register to do a dog reset of TeleOp module
  Wire.endTransmission();       //end transmission
  delay(10);
}

//============================================================= PS5 CONTROLLER ======================================================================================

void PS5::getPS5(){
  Wire.begin();
  Wire.beginTransmission(8);      //transmit to I2C address
  Wire.write(0x1E);               //send register
  Wire.endTransmission();         //end transmission
  delay(10);
  Wire.requestFrom(8, 32);        //request 32 bytes from Tele-Op Module at I2Caddress
  buttons_1   = Wire.read();
  buttons_2   = Wire.read();
  Touchb 	  = Wire.read();
  PBb		  = Wire.read();
  LxStick	  = Wire.read();
  LyStick     = Wire.read();
  RxStick     = Wire.read();
  RyStick     = Wire.read();
  L2Trigger   = Wire.read();
  R2Trigger   = Wire.read();
  LxMotor	  = Wire.read();
  LyMotor	  = Wire.read();
  RxMotor	  = Wire.read();
  RyMotor	  = Wire.read();
  LxServo	  = Wire.read();
  LyServo	  = Wire.read();
  RxServo	  = Wire.read();
  RyServo	  = Wire.read();
  LtMotor	  = Wire.read();
  RtMotor	  = Wire.read();
  LtServo	  = Wire.read();
  RtServo	  = Wire.read();
  Pitch_LO    = Wire.read();
  Pitch_HI    = Wire.read();
  Roll_LO     = Wire.read();
  Roll_HI     = Wire.read();
  TouchX_LO   = Wire.read();
  TouchX_HI	  = Wire.read();
  TouchY_LO   = Wire.read();
  TouchY_HI   = Wire.read();
  Status      = Wire.read();
  inRange	  = Wire.read();

  delay(10);

  Pitchb = (Pitch_HI * 256) + Pitch_LO;			// 0 - 360
  Rollb = (Roll_HI *256) + Roll_LO;				// 0 - 360

  TouchXb = (TouchX_HI * 256) + TouchX_LO;
  TouchYb = (TouchY_HI * 256) + TouchY_LO;

  L2b 		= 0;
  L1b 		= 0;
  R2b 		= 0;
  R1b 		= 0;
  Crossb 	= 0;
  Circleb 	= 0;
  Squareb 	= 0;
  Triangleb = 0;
  Upb 		= 0;
  Downb 	= 0;
  Rightb 	= 0;
  Leftb 	= 0;
  R3b 		= 0;
  L3b 		= 0;
  Shareb 	= 0;
  Optionsb	= 0;

  Connected 	= 0;
  if(Status == 1) {Connected = 1;}


  if(buttons_1 & B00000001){L2b = 1;} 	// set booleans for button group 1
  if(buttons_1 & B00000010){L1b = 1;}
  if(buttons_1 & B00000100){R2b = 1;}
  if(buttons_1 & B00001000){R1b = 1;}
  if(buttons_1 & B00010000){Crossb = 1;}
  if(buttons_1 & B00100000){Circleb = 1;}
  if(buttons_1 & B01000000){Squareb = 1;}
  if(buttons_1 & B10000000){Triangleb = 1;}

  if(buttons_2 & B00000001){Upb = 1;} 	// set booleans for button group 2
  if(buttons_2 & B00000010){Downb = 1;}
  if(buttons_2 & B00000100){Rightb = 1;}
  if(buttons_2 & B00001000){Leftb = 1;}
  if(buttons_2 & B00010000){R3b = 1;}
  if(buttons_2 & B00100000){L3b = 1;}
  if(buttons_2 & B01000000){Shareb = 1;}
  if(buttons_2 & B10000000){Optionsb = 1;}
 }



 int PS5::Touchpad(int PS5touch){
 	int TouchCoordinate;
	switch (PS5touch){
		case 33:
			TouchCoordinate = TouchXb;
			break;
		case 34:
			TouchCoordinate = TouchYb;
			break;
	}

	return TouchCoordinate;
 }


 int PS5::Angle(int PS5gyro){
 	int Gyro;
	switch (PS5gyro){
		case 31:
			Gyro = Pitchb;
			break;
		case 32:
			Gyro = Rollb;
			break;
	}

	return Gyro;
 }


 int PS5::Stick(int PS5stick){

	int Stick;
	switch (PS5stick){
		case 8:
			Stick = LxStick;
			break;
		case 9:
			Stick = LyStick;
			break;
		case 10:
			Stick = RxStick;
			break;
		case 11:
			Stick = RyStick;
			break;
	}

 		return Stick;
 }


 int PS5::Button(int PS5button){
 	int Button;
	switch (PS5button){
		case 12:
			Button = L2Trigger;
			break;
		case 13:
			Button = R2Trigger;
			break;
		case 14:
			Button = L1b;
			break;
		case 15:
			Button = L2b;
			break;
		case 16:
			Button = L3b;
			break;
		case 17:
			Button = R1b;
			break;
		case 18:
			Button = R2b;
			break;
		case 19:
			Button = R3b;
			break;
		case 20:
			Button = Upb;
			break;
		case 21:
			Button = Downb;
			break;
		case 22:
			Button = Rightb;
			break;
		case 23:
			Button = Leftb;
			break;
		case 24:
			Button = Crossb;
			break;
		case 25:
			Button = Circleb;
			break;
		case 26:
			Button = Squareb;
			break;
		case 27:
			Button = Triangleb;
			break;
		case 28:
			Button = Shareb;
			break;
		case 29:
			Button = Optionsb;
			break;
		case 30:
			Button = Touchb;
			break;
		case 35:
			Button = PBb;
			break;

	}

	return Button;

 }

 void PS5::setDeadZone(int Stick, int Amount){
 	Amount = constrain(Amount,0,100); //constrain to 0 - 100
 	if(Stick == 23) {
	  Wire.beginTransmission(8);      //transmit to I2C address
	  Wire.write(0x22);               //send register
	  Wire.write(Amount);			  //Send dead zone set for left stick
	  Wire.endTransmission();         //end transmission
	  delay(10);
	}
	if(Stick == 22) {
	  Wire.beginTransmission(8);      //transmit to I2C address
	  Wire.write(0x23);               //send register
	  Wire.write(Amount);			  //Send dead zone set for right stick
	  Wire.endTransmission();         //end transmission
	  delay(10);
	}

 }


 int PS5::Servo(int PS5servo){
 	int ServoMap = 90;
	// ==================== Analog Trigger Buttons (no dead zone applied) ===============================
	if(PS5servo == 12){ServoMap = map(L2Trigger, 0, 255, 0, 180);}
  	if(PS5servo == 13){ServoMap = map(R2Trigger, 0, 255, 0, 180);}
	if(PS5servo == 31){ServoMap = map(Pitchb, 0, 360,  0, 180);}
	if(PS5servo == 32){ServoMap = map(Rollb, 0, 360,  0, 180);}

	// ==================== TeleOp joysticks mapped to 0 - 180 servo range with dead zone =====

	if(PS5servo == 8){ServoMap = LxServo;}

	if(PS5servo == 9){ServoMap = LyServo;}

	if(PS5servo == 10){ServoMap = RxServo;}

	if(PS5servo == 11){ServoMap = RyServo;}

	return ServoMap;
 }

 int PS5::Motor(int PS5motor){
 	int MotorMap = 0;
	// ==================== Analog Trigger Buttons (no dead band applied) ===============================
	if(PS5motor == 12){MotorMap = map(L2Trigger, 0, 255,  0, 100);}
	if(PS5motor == 13){MotorMap = map(R2Trigger, 0, 255,  0, 100);}
	if(PS5motor == 31){MotorMap = map(Pitchb, 0, 360,  -100, 100);}
	if(PS5motor == 32){MotorMap = map(Rollb, 0, 360,  -100, 100);}

	// ==================== TeleOp joysticks mapped to -100 to 100 power range with dead zone =====

	if(PS5motor == 8){MotorMap = LxMotor;}

	if(PS5motor == 9){MotorMap = LyMotor;}

	if(PS5motor == 10){MotorMap = RxMotor;}

	if(PS5motor == 11){MotorMap = RyMotor;}

  return MotorMap;
 }


 void PS5::setRumble(int level){
 	int rumble = 0;
	if(level == 5){rumble = 0;}
	if(level == 6){rumble = 1;}
	if(level == 7){rumble = 2;}
  Wire.beginTransmission(8);      //transmit to I2C address
  Wire.write(0x1F);               //send register
  Wire.write(rumble);			  //rumble set to off = 0, rumble set to low = 1, rumble set to high = 2
  Wire.endTransmission();         //end transmission
  delay(10);
}


void PS5::setLED(int LED){
  Wire.beginTransmission(8);    //transmit to I2C address
  Wire.write(0x20);             //send register
  Wire.write(LED);		      	//send LED color
  Wire.endTransmission();       //end transmission
  delay(10);
}

void PS5:: resetTeleOp(){
  Wire.beginTransmission(8);    //transmit to I2C address
  Wire.write(0x21);             //send register to do a dog reset of TeleOp module
  Wire.endTransmission();       //end transmission
  delay(10);
}
