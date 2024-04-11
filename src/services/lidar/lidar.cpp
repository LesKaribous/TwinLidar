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

	sensor.enablePolarFiltering();
	sensor.enableCartesianFiltering();
	sensor.enableCartesianGrid();
	sensor.enablePolarGrid();
	
	sensor.setPolarResolution(10);
	sensor.setCartesianSize(3000,2000);
	sensor.setPolarRange(200, 3000, -180, 180);
	sensor.setIntensityThreshold(200);
	// sensor.disableCRC();
	delay(200);
}

void Lidar::onUpdate(){
    if(enabled()) sensor.readScan();

	static long lastPrint = 0;

	if(millis() - lastPrint > 500){
		lastPrint = millis();
		sensor.printScanTeleplot();
	}
}

int Lidar::getDistance(int angle){
	return sensor.getDistanceAtAngle(angle);
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

