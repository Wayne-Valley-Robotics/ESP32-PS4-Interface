#include <Arduino.h>
#include <SerialTransfer.h>
#include "ps4_interface.h"

SerialTransfer serialTransfer;

void ConnectivityTestState(bool testInput);

void setup()
{
  pinMode(2, OUTPUT); // builtin led

  Serial.begin(115200);
  Serial.println("boot");
  delay(500);
  Serial2.begin(115200);
  serialTransfer.begin(Serial2);
  bool isInit_BT;
  if (PS4_TARGET_MAC) // if has any value
    isInit_BT = PS4_Interface::init(PS4_TARGET_MAC);
  else
    isInit_BT = PS4_Interface::init();

  if (isInit_BT)
  {
    Serial.print("Device address: ");
    PS4_Interface::printDeviceAddress();
    Serial.println();
    Serial.println("Waiting for controller...");
    while (!PS4_Interface::inputsReady)
    {
      delay(20);
    }
    Serial.println("Reached target: Bluetooth");
  }
  else
  {
    while (1)
    {
      Serial.println("FATAL: Bluetooth init failed.");
      delay(5000);
    }
  }
}

void loop()
{
  using namespace PS4_Interface;

  if (inputsReady)
  {
    inputsReady = false;
    serialTransfer.sendDatum(inputStruct);
    ConnectivityTestState(inputStruct.PSButton);
  }
}

void ConnectivityTestState(bool testInput)
{
  static bool cachedState;

  if (cachedState != testInput)
  {
    digitalWrite(2, !testInput);
    cachedState = testInput;
  }
}
