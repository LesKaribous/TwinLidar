#pragma once
#include "core/Lidar.h"

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Chrono.h>

const int NUM_PIXELS = 35;
const float REFRESH_DELAY = 120.0f;
const float BLINK_DELAY = 800.0f;

class PixelRing{
public:
    void Initialize();
    void Update();
    void DrawLidar(Lidar& lidar);
    void DrawIntercom(bool state);

    void SetFullColor(long unsigned int);

private:
    Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, Pin::PIXELS, NEO_GRB + NEO_KHZ800);
    Chrono pixelsChrono;

    int ledColor[NUM_PIXELS];

    const int maxHeat = 3000;
    const int minHeat = 200;

    bool blinkState = false;
    float light = 0;
    const float lightInc = ((BLINK_DELAY/REFRESH_DELAY)/REFRESH_DELAY)*255.0f;

}; // namespace LED
