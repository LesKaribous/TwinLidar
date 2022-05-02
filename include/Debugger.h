#pragma once
#include <Arduino.h>
#include <EasyStringStream.h>

namespace Debugger{

    void header();
    void init();
    void checkSerial();
    void printBuffer();

    extern EasyStringStream log;

}; // namespace Debugger




