#pragma once

#include <Arduino.h>

#define PACKSIZE 12

struct Point{
    float distance, angle;
    int intensity;

    unsigned long birthday;

    Point();
    Point(u_int16_t _distance, uint16_t _angle, uint8_t _intensity);
};


namespace Parser{

    struct LD06_DATA{
        uint8_t header;
        uint8_t ver_len;
        uint16_t speed;
        uint16_t start_angle;
        Point point[PACKSIZE];
        uint16_t end_angle;
        uint16_t timestamp;
        uint8_t crc8;
    };

    void init();
    void readData();
}