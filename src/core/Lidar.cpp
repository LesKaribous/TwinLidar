#include "core/Lidar.h"
#include "debug/Console.h"
#include "Pin.h"
#include "Settings.h"

#include <ld06.h>
#include <algorithm>

#define PERSISTENCE 2000 // 400ms
#define DEBUG_REFRESS 200

float lookAngle;
float lookDistance;

void debug();

Lidar::Lidar() : sensor(Pin::Lidar::speed, Serial1){
}

void Lidar::init(){
	sensor.begin();
	//setFOV(30);
	sensor.enableFiltering();
	sensor.enableSectoring();
	//lookAt(180, 770);
	lookAt(0, 500);
	//sensor.disableCRC();
	delay(200);
}

void Lidar::update(){
	if(sensor.readScan(500)){
		debug();
	}
}

void Lidar::setFOV(float angleR)
{
	float angleRange = angleR;

	float angleMin = lookAngle - angleRange / 2.0;
	float angleMax = lookAngle + angleRange / 2.0;

	sensor.setAngleRange(angleMin, angleMax);
}

void Lidar::lookAt(float lookA, float lookD)
{
	lookAngle = lookA;
	lookDistance = lookD + Settings::robotDiameter;
	float angleRange = RAD_TO_DEG * (2* atan((Settings::robotDiameter)/lookDistance));
	float angleMin = lookAngle - angleRange / 2.0;
	float angleMax = lookAngle + angleRange / 2.0;

	float distMin = Settings::minDist;
	float distMax = lookDistance;

	sensor.setAngleRange(angleMin, angleMax);
	sensor.setDistanceRange(distMin, distMax);
	// Points.clear();
}

long unsigned int lastSent = 0;

void Lidar::debug()
{
	//sensor.printScanTeleplot();
	//sensor.printScanLidarView();
	sensor.printFOVLidarView();
	sensor.printSectorsLidarView();

	/*
	if (millis() - lastSent > DEBUG_REFRESS)
	{
		lastSent = millis();
		int array[] = {angleMin * 100.0f, angleMax * 100.0f, distMin, distMax};
		Debugger::logArray("fov(", array, 4);

		Debugger::log("count(", count(), ")");

		int inc = (distMax - distMin) / 10.0f;
		for (size_t j = 0; j < 10; j++)
		{
			int samplingArray[] = {(j * inc) + distMin, angleMin * 100, 254, 0};
			Debugger::logArrayN("Data.point[", 0, "]:{", samplingArray, 4, ',', "}");
		}
		for (size_t j = 0; j < 10; j++)
		{
			int samplingArray[] = {(j * inc) + distMin, angleMax * 100, 254, 0};
			Debugger::logArrayN("Data.point[", 0, "]:{", samplingArray, 4, ',', "}");
		}

		for (Point p : Points)
		{

			int inFOV = 0;
			if (p.distance < Lidar::distMax && p.distance > Lidar::distMin)
			{
				if (p.angle < Lidar::angleMax && p.angle > Lidar::angleMin)
				{
					inFOV = 1;
				}
			}

			int dataArray[] = {p.distance, p.angle * 100, p.intensity, inFOV};
			Debugger::logArrayN("Data.point[", 0, "]:{", dataArray, 4, ',', "}");
		}
	}
	*/
}
