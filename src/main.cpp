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
  Serial2.begin(115200);
  serialTransfer.begin(Serial2);
  bool isInit_BT;
#if EMULATE_MAC_ADDRESS
  isInit_BT = PS4_Interface::init(EMULATED_MAC_ADDRESS);
#else
  isInit_BT = PS4_Interface::init();
#endif
  if (!isInit_BT)
  {
    bool ledState = true;
    while (1)
    {
      Serial.println("FATAL: Bluetooth init failed.");
      digitalWrite(2, ledState);
      ledState = !ledState;
      delay(1000);
    }
  }

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

void loop()
{
  using namespace PS4_Interface;

  // hold on. if we get notified on every update, why dont we just immediately send the data from there?
  // needs a simple refactor but come on seriously??? why didnt i think of that
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
