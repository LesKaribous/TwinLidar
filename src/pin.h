#pragma once
#include <Arduino.h>

#define LIDAR_SERIAL Serial1
#define GRID_WIDTH 20
#define GRID_HEIGHT 13
#define SCREEN_WIDTH 96
#define SCREEN_HEIGHT 64

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

