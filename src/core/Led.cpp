#include "core/Led.h"
#include "Pin.h"
#include "core/Lidar.h"
#include "com/Intercom.h"

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Chrono.h>

#define NUM_PIXELS 35
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
        pixels.setBrightness(150);
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

    void debugLidar(Lidar& lidar){
        pixels.clear(); 
        float angle = 0;
        for(int i = 0; i < NUM_PIXELS; i++){
            angle = i*360.0/float(NUM_PIXELS);
            float dist = lidar.getDistance(angle);
            if(dist == 0) continue;
            int ledCenter  = map(angle,0,359,0,NUM_PIXELS);
            int ledRed    = map(dist,200,800,255,0);
            int ledGreen  = map(dist,200,800,0,255);
            pixels.setPixelColor(ledCenter, pixels.Color(ledRed,   ledGreen,   10));
        }
        pixels.show();
    }

    void drawAngle(int orientation, int width){
        //  Orientation doit être inférieure à 360°
        byte ledCenter  = map(orientation,0,359,NUM_PIXELS,0);
        byte ledWidth   = map(width,0,1000,5,0);

        byte widthColor = map(width,0,1000,255,0);
        uint32_t color = pixels.Color(widthColor,255-widthColor,0); // Modifie la couleur en fonction de la distance

        // Affiche la led de centre
        pixels.setPixelColor(ledCenter, pixels.Color(0,   0,   255));

        if (ledWidth != 0)
        {
            for(int i=1; i<=ledWidth; i++)
            {
            // Traite le décalage des leds par rapport au centre
            int ledPos = ledCenter + i;
            int ledNeg = ledCenter - i;

            // Gestion des valeurs en dehors des limites du ring de leds
            if ( ledPos > (NUM_PIXELS-1)) ledPos = ledPos - NUM_PIXELS ;
            if ( ledNeg < 0 ) ledNeg = ledNeg + NUM_PIXELS ;

            // Allume les leds 
            pixels.setPixelColor(ledPos, color);
            pixels.setPixelColor(ledNeg, color);
            }
        }
        pixels.show();
    }

} // namespace LED
