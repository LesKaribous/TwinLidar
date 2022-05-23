#pragma once

#include "Parser.h"

namespace Lidar{

    extern int maxCount;

    extern float angleMin;
    extern float angleMax;
    extern float distMin;
	extern float distMax;

    void init();
    void update();
    
    void setThreshold(int);
    void filter();
    void push(Point);
    void pop();

    bool check();
    void setFOV(float angleRange);
    void lookAt(float angle, float dist);

    bool isLastDifferent(Point);
    int count();

} // namespace Lidar