#pragma once
#include <Arduino.h>

#define LIDAR_SERIAL Serial1

namespace Pin{
    const int PIXELS = 4;

    const int ScreenSDA = 18;
    const int ScreenSCL = 19;

    namespace Lidar{
        const int
            Rx = 7,
            speed =  6;
    }
}   

