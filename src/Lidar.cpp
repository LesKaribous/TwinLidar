#include "Lidar.h"
#include "Parser.h"
#include "Debugger.h"
#include "Pin.h"
#include "Geometry.h"

#include <vector>

namespace Lidar{

	std::vector<Point> Points;
	int maxCount = 500;

	float angleMin = 0;
    float angleMax = 90;

	void init(){
		pinMode(Pin::Lidar::speed, OUTPUT);
		analogWrite(Pin::Lidar::speed, 50);

		Serial3.begin(230400);
	}

	void update(){
		Parser::readSerial();

		for(std::vector<Point>::iterator it = Points.begin() ; it != Points.end(); ++it){
			if(millis() - it->birthday > 800) Points.erase(it);
		}

		while(count() > maxCount) pop();
	}
	
	void push(Point p){
		Points.push_back(p);
	}

	int count(){
		return Points.size();
	}

	void pop(){
		Points.erase(Points.begin());
	}

	bool check(){
		return (count() > 50);
	}

    void setFOV(float angle, float width){
		angleMin = angle - width/2.0;
    	angleMax = angle + width/2.0;
		Points.clear();
	}
}