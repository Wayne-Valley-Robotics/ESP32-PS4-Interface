#pragma once
#include <Arduino.h>

namespace PS4_Interface
{
    extern bool inputsReady;

    // Struct definition (can be in header for single-file projects)
    struct __attribute__((packed)) STRUCT
    {
        bool PSButton;
        bool Share;
        bool Options;
        bool L1;
        bool L2;
        bool L3;
        bool R1;
        bool R2;
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

        uint16_t LStickX;
        uint16_t LStickY;
        uint16_t RStickX;
        uint16_t RStickY;
        uint16_t L2Value;
        uint16_t R2Value;
    };

    extern STRUCT inputStruct;

    bool init(const char *_macAddress);
    bool init();
    void printDeviceAddress();
    void onConnect();
    void onDisconnect();
    void batteryWarnCycleProc();
}
