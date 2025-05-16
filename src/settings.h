#pragma once

#define LIDAR_SERIAL Serial1

#ifdef TEENSY40
#define INTERCOM_SERIAL Serial2
#else
#define INTERCOM_SERIAL Serial3
#endif


#define INTERCOM_BAUDRATE 31250

namespace Settings{
    //Lidar settings
    const int 
    maxDist = 3000, //2000
    minDist = 200;

    const int 
    robotDiameter = 400; //mm

    //NeoPixel settings
    const int NUM_PIXELS = 35;

    const float 
    BLINK_DELAY = 1000.0f,
    BRIGHTNESS = 50,
    MINBRIGHTNESS = 5,
    BRIGHTNESS_STEP = 1,
    BRIGHTNESS_DELAY = BLINK_DELAY/(BRIGHTNESS/BRIGHTNESS_STEP),
    REFRESH_DELAY = 10.0f;
}
