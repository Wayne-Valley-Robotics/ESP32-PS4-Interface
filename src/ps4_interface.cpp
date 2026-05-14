#include "ps4_interface.h"

#include <PS4Controller.h>
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include "esp_err.h"

namespace PS4_Interface
{
    bool inputsReady;
    void updateInputs();
    void removePairedDevices();
    void batteryWarnCycleProc();
    void attachEvents();

    INPUT_STRUCT inputStruct;

    bool init(const char *_macAddress)
    {
        attachEvents();
        bool output = PS4.begin(_macAddress);
        removePairedDevices();
        return output;
    }
    bool init()
    {
        attachEvents();
        bool output = PS4.begin();
        removePairedDevices();
        return output;
    }

    void attachEvents()
    {
        PS4.attach(updateInputs);
        PS4.attachOnConnect(onConnect);
        PS4.attachOnDisconnect(onDisconnect);
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
        setLED();
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

        // Buttons
        inputStruct.Cross = PS4.Cross();
        inputStruct.Circle = PS4.Circle();
        inputStruct.Square = PS4.Square();
        inputStruct.Triangle = PS4.Triangle();

        inputStruct.Up = PS4.Up();
        inputStruct.Down = PS4.Down();
        inputStruct.Left = PS4.Left();
        inputStruct.Right = PS4.Right();

        inputStruct.PSButton = PS4.PSButton();
        inputStruct.Touchpad = PS4.Touchpad();
        inputStruct.Share = PS4.Share();
        inputStruct.Options = PS4.Options();

        inputStruct.L1 = PS4.L1();
        inputStruct.R1 = PS4.R1();

        inputStruct.R3 = PS4.R3();
        inputStruct.L3 = PS4.L3();

        // Analog
        inputStruct.LStickX = PS4.LStickX();
        inputStruct.LStickY = PS4.LStickY();
        inputStruct.RStickX = PS4.RStickX();
        inputStruct.RStickY = PS4.RStickY();

        inputStruct.L2 = PS4.L2();
        inputStruct.R2 = PS4.R2();

        // Status Flags
        inputStruct.battery = PS4.Battery();
        inputStruct.charging = PS4.Charging();
        inputStruct.audio = PS4.Audio();
        inputStruct.mic = PS4.Mic();

        // Sensors
        inputStruct.gyro_x = PS4.GyrX();
        inputStruct.gyro_y = PS4.GyrY();
        inputStruct.gyro_z = PS4.GyrZ();
        inputStruct.accel_x = PS4.AccX();
        inputStruct.accel_y = PS4.AccY();
        inputStruct.accel_z = PS4.AccZ();
    }

    // TODO: make cool pulsing animations 🤑🤑
    void setLED()
    {
        uint8_t batteryLevel = PS4.Battery();
        if (batteryLevel < 60)
            PS4.setLed(255, 0, 0);
        else if (batteryLevel < 30)
            PS4.setLed(255, 255, 0);
        else
            PS4.setLed(CONTROLLER_LED_COLOR);
    }
    // Battery warning cycle process
    // void batteryWarnCycleProc()
    // {
    //     uint8_t batteryLevel = PS4.Battery();
    //     uint8_t currentColor[3] = {0, 255, 0};

    //     PS4.setLed(CONTROLLER_LED_COLOR);
    // }
}
