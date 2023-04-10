#pragma once

#include <Arduino.h>

namespace Intercom{
    extern bool connected;

    void init();
    void reboot();
    void checkSerial();
    void parseRequest(String);
    
} // namespace Intercom
