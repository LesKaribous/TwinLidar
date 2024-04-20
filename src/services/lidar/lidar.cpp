#include "lidar.h"
#include "os/console.h"
#include "settings.h"
#include "utils/timer/timer.h"
#include "pin.h"
//#include <U8g2lib.h>

#include "ld06.h"
#include <algorithm>

//U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R2,Pin::ScreenSCL,Pin::ScreenSDA);

INSTANTIATE_SERVICE(Lidar)

Lidar::Lidar() : sensor(Pin::Lidar::speed, Serial1), Service(ServiceID::ID_LIDAR) {}

void Lidar::onAttach()
{
	sensor.begin();
	//u8g2.begin();

	sensor.enablePolarFiltering();
	sensor.enableCartesianFiltering();

	//sensor.disablePolarFiltering();
	//sensor.disableCartesianFiltering();
	sensor.disableCartesianGrid();
	sensor.enablePolarGrid();
	
	sensor.setPolarResolution(10);
	sensor.setCartesianRange(3000, 2000, 70);
	sensor.setPolarRange(200, 2500, 0, 360);
	sensor.setIntensityThreshold(250);
	// sensor.disableCRC();
	delay(200);
}

void Lidar::onUpdate(){
    if(enabled()){
		sensor.readScan();

		RUN_EVERY(
			sensor.resetStats();
		,500);
		/*
		RUN_EVERY(
			sensor.printScanTeleplot();
		,200);*/

		//sensor.printScanTeleplot();
	}


	//u8g2.drawPixel(x,y);
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

