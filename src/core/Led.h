#pragma once
#include "core/Lidar.h"

namespace Led{
    void init();
    void update();
    void debugLidar(Lidar& lidar);
    void drawAngle(int orientation, int width);

    void setFullColor(long unsigned int);

    void idle();
    void ready();
    void detect();
} // namespace LED
