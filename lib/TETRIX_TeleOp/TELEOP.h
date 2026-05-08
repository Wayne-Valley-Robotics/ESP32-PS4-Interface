/* 	Header file for TETRIX TELE-OP MODULE for Arduino
   	Written by: Paul W. Uttley
	10/02/2018
	Version 1.0

*/

// Added support for PS5 - 03.17.25

#include <Arduino.h>

#ifndef TELEOP_H
#define TELEOP_H

class PS4
{
	public:

// =========================== LITERALS =================================

	#define	RED		1				// PS4 LED Colors
	#define	BLUE	2
	#define	YELLOW	3
	#define	GREEN	4

	#define STOP    5				// PS4 rumble motor
	#define SLOW	6
	#define FAST	7

	#define LX		8				// PS4 button map
	#define LY		9
	#define RX		10
	#define RY		11

	#define L2T		12
	#define R2T		13

	#define L1		14
	#define L2		15
	#define L3		16
	#define R1		17
	#define R2		18
	#define R3		19

	#define UP		20
	#define DOWN	21
	#define	RIGHT	22
	#define LEFT	23

	#define CROSS	24
	#define CIRCLE	25
	#define	SQUARE	26
	#define TRIANGLE 27

	#define	SHARE	28
	#define OPTIONS	29

	#define TOUCH   30

	#define PITCH	31
	#define ROLL	32

	#define TOUCHX	33
	#define TOUCHY	34

	#define PB		35

	byte Status = 0;				// PS4 connection status; 1 = connected, 0 = disconnected

	int LxServo = 0;				// Left and Right XY joysticks mapped to 0 -180 for servos
	int LyServo = 0;
	int RxServo = 0;
	int RyServo = 0;

	int8_t LxMotor = 0;				// Left and Right XY joysticks mapped to - 100 to 100 for DC motors (signed byte)
	int8_t LyMotor = 0;
	int8_t RxMotor = 0;
	int8_t RyMotor = 0;

	int LtMotor = 0;				// Analog toggle buttons mapped to DC motor range (-100 to 100)
	int RtMotor = 0;

	int LtServo = 0;				// Analog buttons mapped to SERVO range (0 to 180)
	int RtServo = 0;

	unsigned int Pitchb = 0;			// Pitch angle assembled byte of controller 0 - 360
	unsigned int Rollb  = 0;			// Roll angle assembled byte of controller  0 - 360

	byte Pitch_LO;					// received high and low Pitch I2C bytes
	byte Pitch_HI;

	byte Roll_LO;					// received high and low Roll I2C bytes
	byte Roll_HI;

	unsigned int TouchXb = 0;		// X coordinate of finger on Touchpad
	unsigned int TouchYb = 0;		// Y coordinate of finger on Touchpad

	byte TouchX_LO;					// Low Byte
	byte TouchX_HI;					// Hi Byte
	byte TouchY_LO;
	byte TouchY_HI;

	byte buttons_1 = 0;				// bits that represent status of button group 1
	byte buttons_2 = 0;				// bits that represent status of button group 2

	unsigned int LxStick = 0;			// left joystick raw x  0 - 255
	unsigned int LyStick = 0;			// left joystick raw y  0 - 255
	unsigned int RxStick = 0;			// right joystick raw x 0 - 255
	unsigned int RyStick = 0;			// right joystick raw y 0 - 255
	unsigned int L2Trigger = 0;			// left analog trigger button  0 - 255
	unsigned int R2Trigger = 0;			// right analog trigger button  0 - 255

	int LeftDead  = 0;					// Left Joystick Dead Band
	int RightDead = 0;					// Right Joystick Dead Band

	unsigned int Touchb; 				// Touchpad button press
	unsigned int PBb;					// PS4 Power button (PS)

	boolean Upb;						// Button group 1
	boolean Downb;
	boolean Rightb;
	boolean Leftb;
	boolean R3b;
	boolean L3b;
	boolean Shareb;
	boolean Optionsb;

	boolean L2b;						// Button group 2
	boolean L1b;
	boolean R2b;
	boolean R1b;
	boolean Crossb;
	boolean Circleb;
	boolean Squareb;
	boolean Triangleb;

	boolean Connected;				// True if connected
	boolean Disconnected;			// True if disconnected
	boolean inRange;				// PS4 in range = 1; out of range = 0;




		void getPS4(void);					// read PS4 buttons and Joysticks sticks (must be called frequently in the main loop - reads all registers)

		void setRumble(int level);			// Rumble can be set to HIGH or LOW

		void setLED(int LED);	   			// LED color control

		void resetTeleOp(void);				// Force a dog reset of the teleop module

		int Servo(int PS4servo);			// returns from firmware a value mapped to servo range

		int Motor(int PS4motor);			// returns from firmware a value mapped to DC motor range

		int Button(int PS4button);			// returns last read button state

		int Stick(int PS4stick);			// returns last read stick state

		int Angle(int PS4gyro);				// returns last read gyro position

		int Touchpad(int PS4touch);			// returns last read touchpad finger coordinate

		void setDeadZone(int Stick, int Amount);	// sets a dead zone or "neutral band" about the center joystick position


	private:


};

class PS5
{
	public:

// =========================== LITERALS =================================

	#define	RED		1				// PS5 LED Colors
	#define	BLUE	2
	#define	YELLOW	3
	#define	GREEN	4

	#define STOP    5			// PS5 rumble motor
	#define SLOW	6
	#define FAST	7

	#define LX		8				// PS5 button map
	#define LY		9
	#define RX		10
	#define RY		11

	#define L2T		12
	#define R2T		13

	#define L1		14
	#define L2		15
	#define L3		16
	#define R1		17
	#define R2		18
	#define R3		19

	#define UP		20
	#define DOWN	21
	#define	RIGHT	22
	#define LEFT	23

	#define CROSS	24
	#define CIRCLE	25
	#define	SQUARE	26
	#define TRIANGLE 27

	#define	SHARE	28
	#define OPTIONS	29

	#define TOUCH   30

	#define PITCH	31
	#define ROLL	32

	#define TOUCHX	33
	#define TOUCHY	34

	#define PB		35

	byte Status = 0;				// PS5 connection status; 1 = connected, 0 = disconnected

	int LxServo = 0;				// Left and Right XY joysticks mapped to 0 -180 for servos
	int LyServo = 0;
	int RxServo = 0;
	int RyServo = 0;

	int8_t LxMotor = 0;				// Left and Right XY joysticks mapped to - 100 to 100 for DC motors (signed byte)
	int8_t LyMotor = 0;
	int8_t RxMotor = 0;
	int8_t RyMotor = 0;

	int LtMotor = 0;				// Analog toggle buttons mapped to DC motor range (-100 to 100)
	int RtMotor = 0;

	int LtServo = 0;				// Analog buttons mapped to SERVO range (0 to 180)
	int RtServo = 0;

	unsigned int Pitchb = 0;			// Pitch angle assembled byte of controller 0 - 360
	unsigned int Rollb  = 0;			// Roll angle assembled byte of controller  0 - 360

	byte Pitch_LO;					// received high and low Pitch I2C bytes
	byte Pitch_HI;

	byte Roll_LO;					// received high and low Roll I2C bytes
	byte Roll_HI;

	unsigned int TouchXb = 0;		// X coordinate of finger on Touchpad
	unsigned int TouchYb = 0;		// Y coordinate of finger on Touchpad

	byte TouchX_LO;					// Low Byte
	byte TouchX_HI;					// Hi Byte
	byte TouchY_LO;
	byte TouchY_HI;

	byte buttons_1 = 0;				// bits that represent status of button group 1
	byte buttons_2 = 0;				// bits that represent status of button group 2

	unsigned int LxStick = 0;			// left joystick raw x  0 - 255
	unsigned int LyStick = 0;			// left joystick raw y  0 - 255
	unsigned int RxStick = 0;			// right joystick raw x 0 - 255
	unsigned int RyStick = 0;			// right joystick raw y 0 - 255
	unsigned int L2Trigger = 0;			// left analog trigger button  0 - 255
	unsigned int R2Trigger = 0;			// right analog trigger button  0 - 255

	int LeftDead  = 0;					// Left Joystick Dead Band
	int RightDead = 0;					// Right Joystick Dead Band

	unsigned int Touchb; 				// Touchpad button press
	unsigned int PBb;					// PS5 Power button (PS)

	boolean Upb;						// Button group 1
	boolean Downb;
	boolean Rightb;
	boolean Leftb;
	boolean R3b;
	boolean L3b;
	boolean Shareb;
	boolean Optionsb;

	boolean L2b;						// Button group 2
	boolean L1b;
	boolean R2b;
	boolean R1b;
	boolean Crossb;
	boolean Circleb;
	boolean Squareb;
	boolean Triangleb;

	boolean Connected;				// True if connected
	boolean Disconnected;			// True if disconnected
	boolean inRange;				  // PS5 in range = 1; out of range = 0;




		void getPS5(void);					// read PS5 buttons and Joysticks sticks (must be called frequently in the main loop - reads all registers)

		void setRumble(int level);			// Rumble can be set to HIGH or LOW

		void setLED(int LED);	   			// LED color control

		void resetTeleOp(void);				// Force a dog reset of the teleop module

		int Servo(int PS5servo);			// returns from firmware a value mapped to servo range

		int Motor(int PS5motor);			// returns from firmware a value mapped to DC motor range

		int Button(int PS5button);			// returns last read button state

		int Stick(int PS5stick);			// returns last read stick state

		int Angle(int PS5gyro);				// returns last read gyro position

		int Touchpad(int PS5touch);			// returns last read touchpad finger coordinate

		void setDeadZone(int Stick, int Amount);	// sets a dead zone or "neutral band" about the center joystick position


	private:


};

#endif
