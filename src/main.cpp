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
  if (PS4_Interface::init(PS4_TARGET_MAC))
  {
    Serial.println("Waiting for controller... but im never gonna find it :(");
    while (!PS4_Interface::inputsReady)
    {
      delay(100);
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
    // serialTransfer.sendDatum(inputStruct);
    Serial.println(inputStruct.Circle);
    inputsReady = false;
  }

  delay(10);
}
