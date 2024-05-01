#pragma once
#include "services/service.h"
#include "utils/geometry.h"
#include "services/lidar/ld06.h"

class Lidar : public Service{
public:
    Lidar();

    void onAttach() override;
    void onUpdate() override;

    int getCount(int angle, bool absolute=true);
    int getDistance(int angle, bool absolute=true);

    void setPosition(float x, float y, float theta);
    Vec3 getPosition();

private:
    LD06 sensor;

    float m_x, m_y, m_theta;

private:
    SERVICE(Lidar)
};

