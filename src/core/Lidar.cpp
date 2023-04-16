#include "core/Lidar.h"
#include "debug/Console.h"

#include "Settings.h"
#include "PixelRing.h"

#include <ld06.h>
#include <algorithm>


Lidar::Lidar() : sensor(Pin::Lidar::speed, Serial1){}

void Lidar::Initialize(){
	sensor.begin();
	
	sensor.enableFiltering();
	sensor.enableSectoring();
	sensor.setSectorsResolution(10);
	//lookAt(180, 770);
	LookAt(0, 400);
	SetFOV(90);
	//sensor.disableCRC();
	delay(200);
}

void Lidar::Update(){
	if(sensor.readScan(500)){
		//Debug();
	}
}

float Lidar::GetDistance(float angle){
	return sensor.getDistanceAtAngle(angle);
}

float Lidar::GetMaxAngle(){
	float angleRange = RAD_TO_DEG * (2* atan((Settings::robotDiameter)/lookDistance));
	return lookAngle + angleRange / 2.0;
}
float Lidar::GetMinAngle(){
	float angleRange = RAD_TO_DEG * (2* atan((Settings::robotDiameter)/lookDistance));
	return lookAngle - angleRange / 2.0;
}

void Lidar::SetFOV(float angleR)
{
	float angleRange = angleR;

	float angleMin = lookAngle - angleRange / 2.0;
	float angleMax = lookAngle + angleRange / 2.0;

	sensor.setAngleRange(angleMin, angleMax);
}

void Lidar::LookAt(float lookA, float lookD)
{
	lookAngle = lookA;
	lookDistance = lookD + Settings::robotDiameter;
	//float angleRange = RAD_TO_DEG * (2* atan((Settings::robotDiameter)/lookDistance));
	float angleRange = 50;
	float angleMin = lookAngle - angleRange / 2.0;
	float angleMax = lookAngle + angleRange / 2.0;

	float distMin = Settings::minDist;
	float distMax = lookDistance;

	Console::info("LookAt") << "min(" << angleMin << ") max(" << angleMax << ")" << Console::endl;

	sensor.setAngleRange(angleMin, angleMax);
	sensor.setDistanceRange(distMin, distMax);
	// Points.clear();
}

void Lidar::Debug(){
	//sensor.printScanTeleplot();
	sensor.printScanLidarView();
	sensor.printFOVLidarView();
	//sensor.printSectorsLidarView();

	/*
	Serial.print(">sectors:");
    float angle = 0;
    for(int i = 0; i < 36; i++){
		angle = i*360.0/float(36);
		float dist = getDistance(angle);
		if(dist == 0) Serial.print(String() + i + ":" + 0 + ":" + 0 + ":" + 0 + ":" + 0 +  ";");
        Serial.print(String() + i + ":" + 1 + ":" + dist + ":" + (dist-200.0) + ":" + dist+200 +  ";");
	}
	Serial.println("|np"); //don't plot
	*/
}