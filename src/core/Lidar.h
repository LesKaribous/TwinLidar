#pragma once
#include <ld06.h>

#include "Pin.h"

class Lidar{
public:

    Lidar();

    void Initialize();
    void Update();
    bool HasPoints();

    float GetDistance(float angle);

    float GetMaxAngle();
    float GetMinAngle();

    void SetFOV(float angleRange);
    void LookAt(float angle, float dist);

    void Debug();

private : 
	LD06 sensor; 
	int lookAngle;
	int lookDistance;
};