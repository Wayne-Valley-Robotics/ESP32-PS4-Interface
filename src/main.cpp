#include "Arduino.h"
#include "ps4_interface.h"

void setup()
{
  Serial.begin(115200);
  PS4_Interface::init();
  
  // Setup digital output pins for boolean button states
  // Using ESP32 GPIO pins 2-17 for digital buttons
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  
  // Setup analog output pins for analog sticks and triggers
  // Using ESP32 GPIO pins 32-37 for ADC/PWM capabilities
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(35, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(37, OUTPUT);
}

void loop()
{
  using namespace PS4_Interface;
  
  // Digital outputs for boolean button states
  digitalWrite(2, PS4.PSButton());
  digitalWrite(3, PS4.Share());
  digitalWrite(4, PS4.Options());
  digitalWrite(5, PS4.L3());
  digitalWrite(6, PS4.R3());
  digitalWrite(7, PS4.Touchpad());
  digitalWrite(8, PS4.Up());
  digitalWrite(9, PS4.Down());
  digitalWrite(10, PS4.Left());
  digitalWrite(11, PS4.Right());
  digitalWrite(12, PS4.Cross());
  digitalWrite(13, PS4.Circle());
  digitalWrite(14, PS4.Square());
  digitalWrite(15, PS4.Triangle());
  digitalWrite(16, PS4.L1());
  digitalWrite(17, PS4.R1());
  
  // Analog outputs for analog sticks and triggers
  analogWrite(32, PS4.LStickX());
  analogWrite(33, PS4.LStickY());
  analogWrite(34, PS4.RStickX());
  analogWrite(35, PS4.RStickY());
  analogWrite(36, PS4.L2Value());
  analogWrite(37, PS4.R2Value());
  
  delay(10);
}
