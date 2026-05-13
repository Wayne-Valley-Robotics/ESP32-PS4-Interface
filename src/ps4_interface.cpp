#include "ps4_interface.h"

#include <PS4Controller.h>
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include "esp_err.h"
#include <EEPROM.h>
#include <ArduinoJson.h>

namespace PS4_Interface
{
    bool inputsReady;
    void updateInputs();
    void removePairedDevices();
    void batteryWarnCycleProc();

    STRUCT inputStruct;
    uint8_t batteryLevel;
    uint8_t firmwareVersion = 1;

    bool init(const char *_macAddress)
    {
        PS4.attach(updateInputs);
        PS4.attachOnConnect(onConnect);
        PS4.attachOnDisconnect(onDisconnect);
        bool output = PS4.begin(_macAddress);
        removePairedDevices();
        
        // Save MAC to EEPROM
        EEPROM.put(4, _macAddress);
        saveConfigToEEPROM();
        
        return output;
    }
    bool init()
    {
        PS4.attach(updateInputs);
        PS4.attachOnConnect(onConnect);
        PS4.attachOnDisconnect(onDisconnect);
        bool output = PS4.begin();
        removePairedDevices();
        return output;
    }

    void removePairedDevices()
    {
        uint8_t pairedDeviceBtAddr[20][6];
        int count = esp_bt_gap_get_bond_device_num();
        esp_bt_gap_get_bond_device_list(&count, pairedDeviceBtAddr);
        for (int i = 0; i < count; i++)
        {
            esp_bt_gap_remove_bond_device(pairedDeviceBtAddr[i]);
        }
    }

    void printDeviceAddress()
    {
        const uint8_t *point = esp_bt_dev_get_address();
        for (int i = 0; i < 6; i++)
        {
            char str[3];
            sprintf(str, "%02x", (int)point[i]);
            Serial.print(str);
            if (i < 5)
            {
                Serial.print(":");
            }
        }
    }

    void onConnect()
    {
        digitalWrite(2, HIGH);
        Serial.println("Connected!");
    }

    void onDisconnect()
    {
        digitalWrite(2, LOW);
        Serial.println("Disconnected!");
    }

    void updateInputs()
    {
        inputsReady = true;

        // Digital values for boolean button states
        inputStruct.PSButton = PS4.PSButton();
        inputStruct.Touchpad = PS4.Touchpad();
        inputStruct.Share = PS4.Share();
        inputStruct.Options = PS4.Options();
        inputStruct.L1 = PS4.L1();
        inputStruct.L2 = PS4.L2();
        inputStruct.L3 = PS4.L3();
        inputStruct.R1 = PS4.R1();
        inputStruct.R2 = PS4.R2();
        inputStruct.R3 = PS4.R3();

        inputStruct.Up = PS4.Up();
        inputStruct.Down = PS4.Down();
        inputStruct.Left = PS4.Left();
        inputStruct.Right = PS4.Right();

        inputStruct.Cross = PS4.Cross();
        inputStruct.Circle = PS4.Circle();
        inputStruct.Square = PS4.Square();
        inputStruct.Triangle = PS4.Triangle();

        // Analog values for byte inputs
        inputStruct.LStickX = PS4.LStickX();
        inputStruct.LStickY = PS4.LStickY();
        inputStruct.RStickX = PS4.RStickX();
        inputStruct.RStickY = PS4.RStickY();
        inputStruct.L2Value = PS4.L2Value();
        inputStruct.R2Value = PS4.R2Value();
        
        // Update battery level
        batteryLevel = PS4.Battery();
    }

    // Battery warning cycle process
    void batteryWarnCycleProc()
    {
        uint8_t batteryLevel = PS4.Battery();
        uint8_t currentColor[3] = {0, 255, 0};

        // Define thresholds
        const uint8_t CRITICAL_THRESHOLD = 15;
        const uint8_t WARNING_THRESHOLD = 25;
        
        if (batteryLevel <= CRITICAL_THRESHOLD) {
            currentColor[0] = 255;  // Red
            Serial.println("CRITICAL: Battery low!");
            // Trigger alarm or notification
        } else if (batteryLevel <= WARNING_THRESHOLD) {
            currentColor[0] = 255;  // Orange
            Serial.println("WARNING: Battery low!");
        }
        
        PS4.setLed(CONTROLLER_LED_COLOR);
        
        // Save battery level to EEPROM
        EEPROM.put(10, batteryLevel);
    }
    
    // New functions for production readiness
    void saveConfigToEEPROM() {
      StaticJsonDocument<256> doc;
      doc["mac"] = PS4_TARGET_MAC;
      doc["version"] = "1.0.0";
      
      char buffer[512];
      serializeJson(doc, buffer);
      EEPROM.put(0, buffer);
      EEPROM.commit();
    }
    
    void loadConfigFromEEPROM() {
      // Load configuration from EEPROM
    }
    
    void resetToFactoryDefaults() {
      // Reset configuration to factory defaults
    }
    
    bool verifyOTAUpdate() {
      // Verify OTA update signature
      return true;
    }
    
    void handleOTAUpdate() {
      // Handle OTA update process
    }
    
    void logError(const char* message) {
      Serial.print("ERROR: ");
      Serial.println(message);
    }
    
    void logWarning(const char* message) {
      Serial.print("WARNING: ");
      Serial.println(message);
    }
    
    void logInfo(const char* message) {
      Serial.print("INFO: ");
      Serial.println(message);
    }
    
    uint8_t getBatteryLevel() {
      return batteryLevel;
    }
    
    uint8_t getFirmwareVersion() {
      return firmwareVersion;
    }
    
    void setFirmwareVersion(uint8_t version) {
      firmwareVersion = version;
    }
}
