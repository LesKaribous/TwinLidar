#pragma once
#include <Arduino.h>

namespace Debugger{

    void header();
    void init();
    void checkSerial();

    void println(String = "");
    void println(char);
    void println(int);
    void println(float);

    void print(String);
    void print(float);
    void print(char);
    void print(int);

    void log(char);
    void log(int);
    void log(float);
    void log(String);

    void log(String prefix,   int data, String suffix = "");
    void log(String prefix, float data, String suffix = "");
    void log(String prefix,  bool data, String suffix = "");

    void logArray(String prefix, int array[], size_t size, char separator = ',', String suffix = "");
    void logArrayN(String prefix, int element, String interFix, int array[], size_t size, char separator = ',', String suffix = "");


}; // namespace Debugger




