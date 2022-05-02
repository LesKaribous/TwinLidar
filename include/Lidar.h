#pragma once

#include "Geometry.h"
#include "Parser.h"

namespace Lidar{

    extern int maxCount;

    void init();
    void update();

    void push(Point);
    void pop();

    int count();

} // namespace Lidar