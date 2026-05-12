#include "ps4_interface.h"

#include <PS4Controller.h>
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include "esp_err.h"

namespace PS4_Interface
{
    void updateInputs();
    void removePairedDevices();
    void ps4SetLed(uint8_t r, uint8_t g, uint8_t b);
    void batteryWarnCycleProc();

    STRUCT inputStruct;

    bool init(const char *_macAddress)
    {
        PS4.attach(updateInputs);
        PS4.attachOnConnect(onConnect);
        PS4.attachOnDisconnect(onDisconnect);
        bool output = PS4.begin(_macAddress);
        removePairedDevices();
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
        Serial.println("Connected!");
    }

    void onDisconnect()
    {
        Serial.println("Disconnected!");
    }

    void updateInputs()
    {
        if (!ps4IsConnected)
        {
            inputsReady = false;
            return;
        }

        inputsReady = true;

        // Digital values for boolean button states
        inputStruct.PSButton = PS4.PSButton();
        inputStruct.Share = PS4.Share();
        inputStruct.Options = PS4.Options();
        inputStruct.L1 = PS4.L1();
        inputStruct.L2 = PS4.L2();
        inputStruct.L3 = PS4.L3();
        inputStruct.R1 = PS4.R1();
        inputStruct.R2 = PS4.R2();
        inputStruct.R3 = PS4.R3();
        inputStruct.Touchpad = PS4.Touchpad();
        
        inputStruct.Up = PS4.Up();
        inputStruct.Down = PS4.Down();
        inputStruct.Left = PS4.Left();
        inputStruct.Right = PS4.Right();

        inputStruct.Cross = PS4.Cross();
        inputStruct.Circle = PS4.Circle();
        inputStruct.Square = PS4.Square();
        inputStruct.Triangle = PS4.Triangle();
        
        inputStruct.LStickX = PS4.LStickX();
        inputStruct.LStickY = PS4.LStickY();
        inputStruct.RStickX = PS4.RStickX();
        inputStruct.RStickY = PS4.RStickY();
        inputStruct.L2Value = PS4.L2Value();
        inputStruct.R2Value = PS4.R2Value();
    }

    void ps4SetLed(uint8_t r, uint8_t g, uint8_t b)
    {
        PS4.setLed(r, g, b);
    }

    // Battery warning cycle process
    void batteryWarnCycleProc()
    {
        uint8_t currentColor[3] = {0, 255, 0};
        uint8_t maxColor = 255;
        uint8_t fadeStep = maxColor / (fadeSpeedMillis / 10);
        uint8_t currentFade = 0;

        // Fade to 0
        for (uint8_t i = 0; i < maxColor; i++)
        {
            currentColor[1] = maxColor - i;
            currentColor[2] = maxColor - i;
            PS4.setLed(0, currentColor[1], currentColor[2]);
            delay(10);
        }

        // Keep red at max
        PS4.setLed(maxColor, 0, 0);

        // Fade back to original color
        for (uint8_t i = 0; i < maxColor; i++)
        {
            currentColor[1] = i;
            currentColor[2] = i;
            PS4.setLed(maxColor, currentColor[1], currentColor[2]);
            delay(10);
        }
    }
}
