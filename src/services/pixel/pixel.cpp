#include "pixel.h"
#include "services/intercom/intercom.h"
#include "os/console.h"

INSTANTIATE_SERVICE(Pixel)

void Pixel::onAttach(){
    pixels.begin();
    pixels.setBrightness(50);
}

void Pixel::onUpdate(){
    if ( millis() - lastDraw > Settings::REFRESH_DELAY) {
            lastDraw = millis();

            if (m_currentMode == INTERCOM)
                drawIntercom(Intercom::instance().isConnected());
            else if (m_currentMode == LIDAR)
                drawLidar(Lidar::instance());

            pixels.show();
    }
}

void Pixel::setMode(RingState mode){
    m_currentMode = mode;
}

void Pixel::setFullColor(long unsigned int color){
    for (size_t i = 0; i < Settings::NUM_PIXELS; i++){
        ledColor[i] = color;
        pixels.setPixelColor(i, ledColor[i]);
    }
}

void Pixel::drawIntercom(bool state){
    if (millis() - lastblink > (state ? Settings::BRIGHTNESS_DELAY : Settings::BRIGHTNESS_DELAY /2)) {
        
        lastblink = millis();

        if(state) setFullColor(pixels.Color(20, 255, 20));
        else setFullColor(pixels.Color(255, 20, 20));


        if(light > Settings::BRIGHTNESS || light <= Settings::MINBRIGHTNESS) blinkState = !blinkState;
        if(blinkState) light += Settings::BRIGHTNESS_STEP;
        else light -= Settings::BRIGHTNESS_STEP;

        pixels.clear(); 
        // Draw pixels :
        pixels.setBrightness(light);
        for (size_t i = 0; i < Settings::NUM_PIXELS; i++){
            pixels.setPixelColor(i, ledColor[i]);
        }
    }
}

void Pixel::drawLidar(Lidar& lidar){
    pixels.clear(); 
    float angle = 0;
    for(int i = 0; i < Settings::NUM_PIXELS; i++){
        angle = i*360.0/float(Settings::NUM_PIXELS);
        float dist = lidar.getDistance(angle);
        if(dist == 0) continue;
        int ledCenter = map(angle,0,359,0,Settings::NUM_PIXELS);
        int ledRed    = std::min(std::max(map(dist,300,1000,255,0),0.0f), 255.0f);
        int ledGreen  = std::min(std::max(map(dist,300,1000,0,255), 0.0f), 255.0f);
        pixels.setPixelColor(ledCenter, pixels.Color(ledRed,   ledGreen,   10));
    }
}


