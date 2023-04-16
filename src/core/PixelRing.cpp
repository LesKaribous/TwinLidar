#include "core/PixelRing.h"

#include "Pin.h"
#include "core/Lidar.h"
#include "com/Intercom.h"
#include "debug/Console.h"


void PixelRing::Initialize(){
    pixels.begin();
    pixels.setBrightness(50);
}

void PixelRing::Update(){
    if ( pixelsChrono.hasPassed(REFRESH_DELAY) ) {
            pixelsChrono.restart();
            pixels.show();
    }
}

void PixelRing::SetFullColor(long unsigned int color){
    for (size_t i = 0; i < NUM_PIXELS; i++){
        ledColor[i] = color;
        pixels.setPixelColor(i, ledColor[i]);
    }
}


void PixelRing::DrawIntercom(bool state){
    if(state) SetFullColor(pixels.Color(20, 255, 20));
    else SetFullColor(pixels.Color(255, 20, 20));

    pixels.clear(); 

    if ( pixelsChrono.hasPassed(REFRESH_DELAY) ) {
        if(light > 50 || light < 0) blinkState = !blinkState;
        if(blinkState) light += lightInc;
        else light -= lightInc;

        // Draw pixels :
        pixels.setBrightness(light);
        for (size_t i = 0; i < NUM_PIXELS; i++){
            pixels.setPixelColor(i, ledColor[i]);
        }
    }
}

void PixelRing::DrawLidar(Lidar& lidar){
    pixels.clear(); 
    float angle = 0;
    for(int i = 0; i < NUM_PIXELS; i++){
        angle = i*360.0/float(NUM_PIXELS);
        float dist = lidar.GetDistance(angle);
        if(dist == 0) continue;
        int ledCenter  = map(angle,0,359,0,NUM_PIXELS);
        int ledRed    = map(dist,100,1000,255,0);
        int ledGreen  = map(dist,100,1000,0,255);
        pixels.setPixelColor(ledCenter, pixels.Color(ledRed,   ledGreen,   10));
    }

    int ledMAX = lidar.GetMaxAngle() / 10;
    int ledMIN = lidar.GetMinAngle() / 10;

    pixels.setPixelColor(ledMAX, pixels.Color(0,   0,   255));
    pixels.setPixelColor(ledMIN, pixels.Color(0,   0,   255));

}


