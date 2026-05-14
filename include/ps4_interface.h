#pragma once
#include <Arduino.h>

namespace PS4_Interface
{
    constexpr uint16_t fadeSpeedMillis = 4000;

    static bool inputsReady = false;

    // Struct definition (can be in header for single-file projects)
    struct __attribute__((packed)) STRUCT
    {
        bool PSButton;
        bool Share;
        bool Options;
        bool L3;
        bool R3;
        bool Touchpad;
        bool Up;
        bool Down;
        bool Left;
        bool Right;
        bool Cross;
        bool Circle;
        bool Square;
        bool Triangle;
        bool L1;
        bool R1;
        uint16_t GyrX;
        uint16_t GyrY;
        uint16_t GyrZ;
        uint16_t AccX;
        uint16_t AccY;
        uint16_t AccZ;
    };

    extern STRUCT inputStruct;

    bool init(const char *_macAddress);
    void printDeviceAddress();
    void onConnect();
    void onDisconnect();
    void ps4SetLed(uint8_t r, uint8_t g, uint8_t b);
    void batteryWarnCycleProc();
}
