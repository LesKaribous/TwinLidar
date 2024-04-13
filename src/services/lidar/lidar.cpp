#include "lidar.h"
#include "os/console.h"
#include "settings.h"
#include "utils/timer/timer.h"
#include "pin.h"

#include <ld06.h>
#include <algorithm>

INSTANTIATE_SERVICE(Lidar)

Lidar::Lidar() : sensor(Pin::Lidar::speed, Serial1), Service(ServiceID::ID_LIDAR) {}

void Lidar::onAttach()
{
	sensor.begin();

	sensor.enablePolarFiltering();
	sensor.enableCartesianFiltering();
	sensor.disableCartesianGrid();
	sensor.enablePolarGrid();
	
	sensor.setPolarResolution(10);
	sensor.setCartesianRange(1500, 2000, 100);
	sensor.setPolarRange(200, 1000, 0, 360);
	sensor.setIntensityThreshold(240);
	// sensor.disableCRC();
	delay(200);
}

void Lidar::onUpdate(){
    if(enabled()){
		sensor.readScan();

		RUN_EVERY(
			sensor.resetStats();
		
		,1500);

		//sensor.printScanTeleplot();
	}
}

int Lidar::getDistance(int angle, bool absolute){
	if(absolute) return sensor.getDistanceAtAngle(angle);
	else return sensor.getDistanceAtAngle(angle+m_theta);
}

void Lidar::setPosition(float x, float y, float theta){
    m_x = x;
    m_y = y;
    m_theta = theta;
	sensor.setPosition(m_x, m_y, m_theta);
}

Vec3 Lidar::getPosition(){
    return Vec3(m_x,m_y, m_theta);
}

