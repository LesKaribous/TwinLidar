#pragma once
#include <ld06.h>

#include "Pin.h"

class Lidar
{
public:
    Lidar();

    void Initialize();
    void Update();

    bool HasPoints();
    int GetDistance(int angle);

    void SetPosition(float x, float y, float z);
    void SetHeading(int heading);

    int GetMaxAngle();
    int GetMinAngle();
    void SetMaxAngle(int);
    void SetMinAngle(int);

    int GetMaxDistance();
    int GetMinDistance();
    void SetMaxDistance(int);
    void SetMinDistance(int);

    bool CheckObstacle(int, int);

    void SetFOV(int angleRange);
    void LookAt(int angle, int dist);

    void Debug();

public:
    LD06 sensor;

    float x, y, z;

    int _lookAngle;
    int _lookDistance;
    int _minAngle;
    int _maxAngle;
    int _minDistance;
    int _maxDistance;
    int _angleRange;
};