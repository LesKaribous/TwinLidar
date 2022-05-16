#pragma once

#include "Geometry.h"
#include "Parser.h"

namespace Lidar{

    extern int maxCount;

    extern float angleMin;
    extern float angleMax;

    void init();
    void update();

    void push(Point);
    void pop();

    bool check();
    void setFOV(float angle, float width);

    int count();

} // namespace Lidar