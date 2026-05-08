#include "ps4_interface.h"

namespace PS4_Interface
{
#include <PS4Controller.h>
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include "esp_err.h"
    void init()
    {
        // PS4.attach(notify);
        PS4.attachOnConnect(onConnect);
        PS4.attachOnDisconnect(onDisconnect);
        PS4.begin();
        removePairedDevices(); // This helps to solve connection issues
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

    void onConnect()
    {
        Serial.println("Connected!");
    }

    void onDisconnect()
    {
        Serial.println("Disconnected!");
    }
}