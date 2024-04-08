#include "lidar.h"
#include "os/console.h"
#include "settings.h"
#include "pin.h"

#include <ld06.h>
#include <algorithm>

INSTANTIATE_SERVICE(Lidar)

Lidar::Lidar() : sensor(Pin::Lidar::speed, Serial1), Service(ServiceID::ID_LIDAR) {}

void Lidar::onAttach()
{
	sensor.begin();

	sensor.enableFiltering();
	sensor.enableSectoring();
	sensor.setSectorsResolution(20);
	// lookAt(180, 770);
	setHeading(0);
	setFOV(360);
	sensor.setIntensityThreshold(200);
	// sensor.disableCRC();
	delay(200);
}

void Lidar::onUpdate(){
    if(enabled()) sensor.readScan(600);
}

bool Lidar::hasPoints(){
	// return sensor.hasPoint();
	return true;
}

int Lidar::getDistance(int angle)
{
	return sensor.getDistanceAtAngle(angle);
}

bool Lidar::checkObstacle(int range_min, int range_max)
{

	if (getDistance(_lookAngle) < range_max && getDistance(_lookAngle) > range_min)
		return true;

	if (getDistance(_lookAngle - 30) < range_max * 3 / 4 &&
		getDistance(_lookAngle - 30) > range_min)
		return true;

	if (getDistance(_lookAngle + 30) < range_max * 3 / 4 && getDistance(_lookAngle + 30) > range_min)
		return true;

	if (getDistance(_minAngle) < range_max * 1 / 3 && getDistance(_minAngle) > range_min)
		return true;

	if (getDistance(_maxAngle) < range_max * 1 / 3 && getDistance(_maxAngle) > range_min)
		return true;

	return false;
}

int Lidar::getMaxAngle()
{
	return _minAngle;
}

int Lidar::getMinAngle()
{
	return _minAngle;
}

void Lidar::setMaxAngle(int angle)
{
	_maxAngle = angle;
	sensor.setMaxAngle(_maxAngle);
}

void Lidar::setMinAngle(int angle)
{
	_minAngle = angle;
	sensor.setMinAngle(_minAngle);
}

int Lidar::getMaxDistance()
{
	return _minAngle;
}

int Lidar::getMinDistance()
{
	return _minAngle;
}

void Lidar::setMaxDistance(int dist)
{
	_maxDistance = dist;
	sensor.setMaxDistance(_maxDistance);
}

void Lidar::setMinDistance(int dist)
{
	_minDistance = dist;
	sensor.setMaxDistance(_minDistance);
}

void Lidar::setFOV(int angleR)
{
	_angleRange = angleR;

	_minAngle = _lookAngle - _angleRange / 2.0;
	_maxAngle = _lookAngle + _angleRange / 2.0;

	sensor.setAngleRange(_minAngle, _maxAngle);
}

void Lidar::setPosition(float x, float y, float theta){
    m_x = x;
    m_y = y;
    m_theta = theta;
}

Vec3 Lidar::getPosition(){
    return Vec3(m_x,m_y, m_theta);
}

void Lidar::setHeading(int heading)
{
	_lookAngle = heading;
	_minAngle = _lookAngle - _angleRange / 2.0;
	_maxAngle = _lookAngle + _angleRange / 2.0;

	sensor.setAngleRange(_minAngle, _maxAngle);
}

void Lidar::lookAt(int lookA, int lookD)
{
	_lookAngle = lookA;
	_angleRange = RAD_TO_DEG * (2 * atan((Settings::robotDiameter) / _lookDistance));
	_minAngle = _lookAngle - _angleRange / 2.0;
	_maxAngle = _lookAngle + _angleRange / 2.0;

	_minDistance = std::max(Settings::minDist, _lookDistance - Settings::robotDiameter);
	_maxDistance = _lookDistance;

	Console::info("LookAt") << "min(" << _minAngle << ") max(" << _maxAngle << ")" << Console::endl;

	sensor.setAngleRange(_minAngle, _maxAngle);
	sensor.setDistanceRange(_minDistance, _maxDistance);
}

void Lidar::debug()
{
	// sensor.printScanTeleplot();
	sensor.printScanLidarView();
	sensor.printFOVLidarView();
	// sensor.printSectorsLidarView();

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