#include <Arduino.h>
#include <SerialTransfer.h>
#include "ps4_interface.h"

SerialTransfer serialTransfer;

void setup()
{
  Serial.begin(115200);
  Serial.println("boot");

  // Choose your mode:
  // arduino_OTA::initWiFiOnly();     // WiFi only, no OTA
  // arduino_OTA::initOTAOnly();     // OTA only (firmware updates)
  // arduino_OTA::init();            // Auto: try WiFi, fall back to OTA

  delay(1000);
  // Serial1.begin(115200);
  // serialTransfer.begin(Serial1);
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
      delay(100);
    }
    delay(100);
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
  }

  delay(10);
}
