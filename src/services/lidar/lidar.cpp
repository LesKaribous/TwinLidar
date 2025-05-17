#include "lidar.h"
#include "os/console.h"
#include "settings.h"
#include "utils/timer/timer.h"
#include "pin.h"
//#include <U8g2lib.h>

#include "ld06.h"
#include <algorithm>

//Yellow
constexpr uint8_t m_static_map_A[GRID_WIDTH][GRID_HEIGHT] = {
  {1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
  {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
  {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
  {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
  {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

//Blue
constexpr uint8_t m_static_map_B[GRID_WIDTH][GRID_HEIGHT] = {
  {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
  {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
  {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
  {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
  {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1},
  {1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1}
};


//U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R2,Pin::ScreenSCL,Pin::ScreenSDA);

INSTANTIATE_SERVICE(Lidar)

Lidar::Lidar() : sensor(Pin::Lidar::speed, Serial1), Service(ServiceID::ID_LIDAR),  u8g2(U8G2_R2, Pin::ScreenSCL, Pin::ScreenSDA)  {}

void Lidar::onAttach()
{
	sensor.begin();
	//u8g2.begin();

	sensor.enablePolarFiltering();
	sensor.enableCartesianFiltering();

	//sensor.disablePolarFiltering();
	//sensor.disableCartesianFiltering();
	//sensor.disableCartesianGrid();
	sensor.enablePolarGrid();
	sensor.enableCartesianGrid();
	
	sensor.setPolarResolution(10);
	sensor.setCartesianRange(3000, 2000, 70);
	sensor.setPolarRange(200, 2500, 0, 360);
	sensor.setIntensityThreshold(250);

	u8g2.begin();
    u8g2.clear();

	//set font size
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.firstPage();

	// sensor.disableCRC();
	delay(200);
}

void Lidar::onUpdate(){
    if(enabled()){
		sensor.readScan();


		RUN_EVERY(
			sensor.resetStats();
			return;
		,1000);
		
		RUN_EVERY(
			drawOccupancyGrid();
		,500);
		
		/*
		RUN_EVERY(
			sensor.printScanTeleplot();
		,500);
		/**/

		//sensor.printScanTeleplot();
	}


	//u8g2.drawPixel(x,y);
}

int Lidar::getDistance(int angle, bool absolute){
	if(absolute) return sensor.getDistanceAtAngle(angle);
	else return sensor.getDistanceAtAngle(angle+m_theta);
}

void Lidar::setStaticMap(bool staticMap){
	this->staticMap = staticMap;
}

bool Lidar::isStaticOccupied(int x, int y){
	if(staticMap){
   		return (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT && m_static_map_A[x][y] > 0);
	}else{

		return (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT && m_static_map_B[x][y] > 0);
	}

}

int Lidar::getCount(int angle, bool absolute){
	if(absolute) return sensor.getCountAtAngle(angle);
	else return sensor.getCountAtAngle(angle+m_theta);
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

BinaryPayload Lidar::getOccupancyMap() {
    CartesianGrid* grid = sensor.getCartesianGrid();
    if (grid == nullptr) return {nullptr, 0};

    static uint8_t packed[33] = {0}; // 260 bits = 33 bytes
    memset(packed, 0, sizeof(packed));

    int bitIndex = 0;
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            if (grid->isOccupied(x, y) || isStaticOccupied(x, y)) {
                int byteIndex = bitIndex / 8;
                int bitInByte = bitIndex % 8;
                packed[byteIndex] |= (1 << bitInByte);
            }
            ++bitIndex;
        }
    }

    return {packed, sizeof(packed)};
}


void Lidar::drawOccupancyGrid(){
	CartesianGrid* grid = sensor.getCartesianGrid();
	if(grid == nullptr) return;
	u8g2.clear();

	/*
	u8g2.setCursor(0, 10);
	u8g2.print("x: ");
	u8g2.print(m_x);

	u8g2.setCursor(0, 40);
	u8g2.print("y: ");
	u8g2.print(m_y);
	
	u8g2.setCursor(0, 60);
	u8g2.print("t: ");
	u8g2.print(m_theta);
	/**/
	
	float coordsX = (m_x * SCREEN_WIDTH/3000.0);
	float coordsY = (m_y * SCREEN_HEIGHT/2000.0);

	u8g2.drawFrame(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	u8g2.drawPixel(coordsX, coordsY);
	u8g2.drawPixel(coordsX-1, coordsY);
	u8g2.drawPixel(coordsX+1, coordsY);
	u8g2.drawPixel(coordsX, coordsY-1);
	u8g2.drawPixel(coordsX, coordsY+1);

	//Draw line to show the direction usin theta
	//u8g2.drawLine(coordsX, coordsY, (coordsX + 10.0*cos(m_theta*DEG_TO_RAD)), (coordsY + 10.0*sin(m_theta*DEG_TO_RAD)));

	/**/
	for (int x = 0; x < GRID_WIDTH; ++x) {
        for (int y = 0; y < GRID_HEIGHT; ++y) {
			if(grid->isOccupied(x,y) || isStaticOccupied(x,y)){
				//u8g2.drawPixel(x,y);
				u8g2.drawBox(x * SCREEN_WIDTH/GRID_WIDTH, y*SCREEN_HEIGHT/GRID_HEIGHT, SCREEN_WIDTH/GRID_WIDTH, SCREEN_HEIGHT/GRID_HEIGHT);
			}
        }
    }
	/**/

    u8g2.sendBuffer();
}
