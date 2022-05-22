#pragma once
#include <Arduino.h>

#define VERBOSE Debugger::Level::LVERBOSE
#define INFO Debugger::Level::LINFO
#define WARN Debugger::Level::LWARN
#define ERROR Debugger::Level::LERROR

namespace Debugger{

    enum class Level{
        LVERBOSE = 0,
        LINFO = 1,
        LWARN = 2,
        LERROR = 3
    };

    void header();
    void init(Level = INFO);
    void checkSerial();

    Level level();

    void println(String = "");
    void println(char);
    void println(int);
    void println(float);

    void print(String);
    void print(float);
    void print(char);
    void print(int);

    void log(char, Level level = Level::LVERBOSE);
    void log(int, Level level = Level::LVERBOSE);
    void log(float, Level level = Level::LVERBOSE);
    void log(String, Level level = Level::LVERBOSE);

    void log(String prefix,   int data, Level level = Level::LVERBOSE);
    void log(String prefix,  char data, Level level = Level::LVERBOSE);
    void log(String prefix, float data, Level level = Level::LVERBOSE);

    void log(String prefix,   int data, String suffix, Level level = Level::LVERBOSE);
    void log(String prefix,  char data, String suffix, Level level = Level::LVERBOSE);
    void log(String prefix, float data, String suffix, Level level = Level::LVERBOSE);

    void logArray(String prefix, int array[], size_t size, char separator = ',', String suffix = ")", Level level = Level::LVERBOSE);
    void logArrayN(String prefix, int element, String interFix, int array[], size_t size, char separator = ',', String suffix = ")", Level level = Level::LVERBOSE);


}; // namespace Debugger




