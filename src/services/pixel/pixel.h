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
    void drawColor(bool state);
    void drawIntercom(bool state);
    void setFullColor(long unsigned int, bool show=false);

    void setTeamColor(bool color){
        teamColor = color;
    }

    Pixel(): Service(ID_NEOPIXEL){};
    SERVICE(Pixel)

private:
    RingState m_currentMode = INTERCOM;

    Adafruit_NeoPixel pixels = Adafruit_NeoPixel(Settings::NUM_PIXELS, Pin::PIXELS, NEO_GRB + NEO_KHZ800);

    int teamColorA = 0xFFFF00; //true = YELLOW, false = BLUE
    int teamColorB = 0x0000FF; //true = YELLOW, false = BLUE
    bool teamColor = true; //true = YELLOW, false = BLUE

    int ledColor[Settings::NUM_PIXELS];

    const int maxHeat = 3000;
    const int minHeat = 200;

    bool blinkState = false;
    unsigned long  lastblink = 0;
    float light = Settings::MINBRIGHTNESS;

    unsigned long lastDraw = 0;
};
