#pragma once

namespace PS4_Interface
{
#include <PS4Controller.h>

    void init();

    // void notify();
    void onConnect();
    void onDisconnect();
    void removePairedDevices();
}