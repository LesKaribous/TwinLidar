#include "services/service.h"
#include "settings.h"
#include "pin.h"
#include "services/lidar/lidar.h"
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class Pixel : public Service{
public:

    enum RingState{
        LIDAR,
        INTERCOM
    };
    
    void onAttach()override;
    void onUpdate()override;

    void setMode(RingState state);
    void drawLidar(Lidar& lidar);
    void drawIntercom(bool state);
    void setFullColor(long unsigned int);

    Pixel(): Service(ID_NEOPIXEL){};
    SERVICE(Pixel)

private:
    RingState m_currentMode = INTERCOM;

    Adafruit_NeoPixel pixels = Adafruit_NeoPixel(Settings::NUM_PIXELS, Pin::PIXELS, NEO_GRB + NEO_KHZ800);

    int ledColor[Settings::NUM_PIXELS];

    const int maxHeat = 3000;
    const int minHeat = 200;

    bool blinkState = false;
    unsigned long  lastblink = 0;
    float light = Settings::MINBRIGHTNESS;

    unsigned long lastDraw = 0;
};
