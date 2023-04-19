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
	sensor.setSectorsResolution(20);
	//lookAt(180, 770);
	SetHeading(0);
	SetFOV(90);
	//sensor.disableCRC();
	delay(200);
}

void Lidar::Update(){
	if(sensor.readScan(500)){}
}

bool Lidar::HasPoints(){
	//return sensor.hasPoint();
	return true;
}

int Lidar::GetDistance(int angle){
	return sensor.getDistanceAtAngle(angle);
}

int Lidar::GetMaxAngle(){
	return _minAngle;
}

int Lidar::GetMinAngle(){
	return _minAngle;
}

void Lidar::SetMaxAngle(int angle){
	_maxAngle = angle;
	sensor.setMaxAngle(_maxAngle);
}

void Lidar::SetMinAngle(int angle){
	_minAngle = angle;
	sensor.setMinAngle(_minAngle);
}

int Lidar::GetMaxDistance(){
	return _minAngle;
}

int Lidar::GetMinDistance(){
	return _minAngle;
}

void Lidar::SetMaxDistance(int dist){
	_maxDistance = dist;
	sensor.setMaxDistance(_maxDistance);
}

void Lidar::SetMinDistance(int dist){
	_minDistance = dist;
	sensor.setMaxDistance(_minDistance);
}

void Lidar::SetFOV(int angleR){
	_angleRange = angleR;

	_minAngle = _lookAngle - _angleRange / 2.0;
	_maxAngle = _lookAngle + _angleRange / 2.0;

	sensor.setAngleRange(_minAngle, _maxAngle);
}

void Lidar::SetHeading(int heading){
	_lookAngle = heading;
	_minAngle = _lookAngle - _angleRange / 2.0;
	_maxAngle = _lookAngle + _angleRange / 2.0;

	sensor.setAngleRange(_minAngle, _maxAngle);
}


void Lidar::LookAt(int lookA, int lookD)
{
	_lookAngle = lookA;
	_angleRange = RAD_TO_DEG * (2* atan((Settings::robotDiameter)/_lookDistance));
	_minAngle = _lookAngle - _angleRange / 2.0;
	_maxAngle = _lookAngle + _angleRange / 2.0;

	_minDistance = max(Settings::minDist, _lookDistance - Settings::robotDiameter);
	_maxDistance = _lookDistance;

	Console::info("LookAt") << "min(" << _minAngle << ") max(" << _maxAngle << ")" << Console::endl;

	sensor.setAngleRange(_minAngle, _maxAngle);
	sensor.setDistanceRange(_minDistance, _maxDistance);
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