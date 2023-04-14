#pragma once
#include <ld06.h>

class Lidar{
public:

    Lidar();

    void init();
    void update();
    bool check();

    std::vector<PolarVector> getDistanceField();
    float getDistance(float angle);

    void setFOV(float angleRange);
    void lookAt(float angle, float dist);

    void debug();

private:
    LD06 sensor;
};