#include <Arduino.h>
#include <SerialTransfer.h>
#include <ArduinoOTA.h>
#include <EEPROM.h>
#include "ps4_interface.h"

SerialTransfer serialTransfer;

void ConnectivityTestState(bool testInput);
void loadConfigFromEEPROM();

void setup()
{
  pinMode(2, OUTPUT); // builtin led

  Serial.begin(115200);
  Serial.println("boot");

  // Initialize OTA
  ArduinoOTA.begin();
  ArduinoOTA.setHostname("ESP32-PS4-Interface");
  ArduinoOTA.setPassword("secure_password_here");  // Change this

  // EEPROM for persistent config
  EEPROM.begin(512);
  
  // Load config from EEPROM
  loadConfigFromEEPROM();

  delay(1000);
  Serial1.begin(115200);
  serialTransfer.begin(Serial1);
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
    ConnectivityTestState(PS4_Interface::inputStruct.PSButton);
  }

  // Check heap fragmentation
  if (esp_get_free_heap_size() < 10000) {
    Serial.println("WARNING: Low heap memory!");
  }
  
  // OTA updates
  ArduinoOTA.handle();
  
  serialTransfer.tick(); // redundant?
  delay(10);
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

void loadConfigFromEEPROM() {
  // Load MAC address from EEPROM if not set
  if (!PS4_TARGET_MAC) {
    // EEPROM.get(0, PS4_TARGET_MAC);
  }
}
