#pragma once
#include "services/service.h"
#include "utils/geometry.h"
#include "services/lidar/ld06.h"
#include "services/intercom/comUtilities.h"
#include <U8g2lib.h>

class Lidar : public Service{
public:
    Lidar();

    void onAttach() override;
    void onUpdate() override;

    int getCount(int angle, bool absolute=true);
    int getDistance(int angle, bool absolute=true);

    bool isStaticOccupied(int x, int y);
    void setStaticMap(bool staticMap); //true = YELLOW, false = BLUE

    void setPosition(float x, float y, float theta);
    Vec3 getPosition();

    BinaryPayload getOccupancyMap();
    void drawOccupancyGrid();

private:
    LD06 sensor;
    U8G2_SH1106_128X64_NONAME_F_HW_I2C  u8g2;
    float m_x, m_y, m_theta;
    bool staticMap = true; ///true = YELLOW, false = BLUE 

private:
    SERVICE(Lidar)
};

