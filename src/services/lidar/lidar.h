#pragma once
#include "services/service.h"
#include <ld06.h>

class Lidar : public Service{
public:
    Lidar();

    void onAttach() override;
    void onUpdate() override;

    bool hasPoints();
    int getDistance(int angle);

    void setPosition(float x, float y, float theta);
    void setHeading(int heading);

    int getMaxAngle();
    int getMinAngle();
    void setMaxAngle(int);
    void setMinAngle(int);

    int getMaxDistance();
    int getMinDistance();
    void setMaxDistance(int);
    void setMinDistance(int);

    bool checkObstacle(int, int);

    void setFOV(int angleRange);
    void lookAt(int angle, int dist);

    void debug();


private:
    LD06 sensor;

    float m_x, m_y, m_theta;

    int _lookAngle;
    int _lookDistance;
    int _minAngle;
    int _maxAngle;
    int _minDistance;
    int _maxDistance;
    int _angleRange;

private:
    SERVICE(Lidar)
};

