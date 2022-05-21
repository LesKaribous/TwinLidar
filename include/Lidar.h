#pragma once

#include "Geometry.h"
#include "Parser.h"

namespace Lidar{

    extern int maxCount;

    extern float angleMin;
    extern float angleMax;
    extern float distMin;
	extern float distMax;

    void init();
    void update();

    void push(Point);
    void pop();

    bool check();
    void setFOV(float angleRange, float distRange);
    void lookAt(float angle, float dist);

    bool isLastDifferent(Point p);
    int count();

} // namespace Lidar