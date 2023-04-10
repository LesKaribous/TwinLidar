#include "core/Led.h"
#include "Pin.h"
#include "core/Lidar.h"
#include "com/Intercom.h"

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Chrono.h>

#define NUM_PIXELS 7
#define REFRESH_DELAY 80.0f
#define BLINK_DELAY 800.0f

namespace Led{

    Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, Pin::PIXELS, NEO_GRB + NEO_KHZ800);
    Chrono pixelsChrono;

    int ledColor[NUM_PIXELS];

    const int maxHeat = 3000;
    const int minHeat = 200;

    bool blinkState = false;
    float light = 0;
    const float lightInc = ((BLINK_DELAY/REFRESH_DELAY)/REFRESH_DELAY)*255.0f;

    void init(){
        pixels.begin();
        idle();
        pixels.setBrightness(255);
    }
    
    void update(){
        if ( pixelsChrono.hasPassed(REFRESH_DELAY) ) {
                pixelsChrono.restart();
                pixels.clear(); 
                
                //if(Lidar::count() > 8 && Intercom::connected) detect();

                if(light > 254 || light < 0) blinkState = !blinkState;
                if(blinkState) light += lightInc;
                else light -= lightInc;

                // Draw pixels :
                //setFullColor(pixels.Color(light*1.0f, light*0.196f, light*0.196f));
                pixels.setBrightness(light);
                for (size_t i = 0; i < NUM_PIXELS; i++){
                    pixels.setPixelColor(i, ledColor[i]);
                }

                pixels.show();
        }
    }



    int heatToColor(int heat){
        int blue = map(heat,minHeat, maxHeat,  255, 0);
        int color = pixels.Color(255, 255, 255);

    }

    void setFullColor(long unsigned int color){
        for (size_t i = 0; i < NUM_PIXELS; i++){
            ledColor[i] = color;
            pixels.setPixelColor(i, ledColor[i]);
        }
    }

    void idle(){
        setFullColor(pixels.Color(255, 20, 20));
    }

    void ready(){
        setFullColor(pixels.Color(20, 255, 20));
    }

    void detect(){
        setFullColor(pixels.Color(255, 120, 0));
    }

} // namespace LED
