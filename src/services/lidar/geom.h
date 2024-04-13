#pragma once
#include <cstdint>
#include "geom.h"

struct DataPoint{
    long birth;
    uint16_t distance;  // mm
    float angle;        // degrees
    float x, y;         // mm
    uint8_t intensity; // 0-255
};

struct PolarVector{
    float angle, distance;
};