#pragma once
#include "core/Lidar.h"

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

const int NUM_PIXELS = 35;

const float BLINK_DELAY = 1000.0f;
const float BRIGHTNESS = 40;
const float MINBRIGHTNESS = 5;
const float BRIGHTNESS_STEP = 1;
const float BRIGHTNESS_DELAY = BLINK_DELAY/(BRIGHTNESS/BRIGHTNESS_STEP);

const float REFRESH_DELAY = 100.0f;

class PixelRing{
public:
    void Initialize();
    void Update();
    void DrawLidar(Lidar& lidar);
    void DrawIntercom(bool state);

    void SetFullColor(long unsigned int);

private:
    Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, Pin::PIXELS, NEO_GRB + NEO_KHZ800);

    int ledColor[NUM_PIXELS];

    const int maxHeat = 3000;
    const int minHeat = 200;

    bool blinkState = false;
    unsigned long  lastblink = 0;
    float light = MINBRIGHTNESS;

    unsigned long lastDraw = 0;

}; // namespace LED
