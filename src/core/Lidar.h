#pragma once
#include <ld06.h>

class Lidar{
public:

    Lidar();

    void init();
    void update();
    bool check();

    void setFOV(float angleRange);
    void lookAt(float angle, float dist);

    void debug();

private:
    LD06 sensor;
};