#pragma once

#include <Arduino.h>

namespace Intercom{

    void init();
    
    void checkSerial();
    void parseRequest(String);
    
} // namespace Intercom
