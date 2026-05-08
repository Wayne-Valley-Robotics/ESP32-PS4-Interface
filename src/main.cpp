#include "Arduino.h"
#include "ps4_interface.h"

void setup()
{
  Serial.begin(115200);
  PS4_Interface::init();
}

void loop()
{
  using namespace PS4_Interface;
  Serial.print("TRIANGLE: ");
  Serial.print(PS4.Square());
}