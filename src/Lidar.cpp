#include "Lidar.h"
#include "Parser.h"
#include "Debugger.h"
#include "Pin.h"
#include "Geometry.h"

#include <queue>

namespace Lidar{

	std::queue<Point> Points;
	int maxCount = 500;

	void init(){
		pinMode(Pin::Lidar::speed, OUTPUT);
		analogWrite(Pin::Lidar::speed, 0);

		Serial3.begin(230400);
	}

	void update(){
		Parser::readSerial();
		if(Points.size() > maxCount) Points.pop();
	}
	
	void add(Point p){
		Points.push(p);
	}

	int count(){
		return Points.size();
	}

	void remove(){
		Points.pop();
	}

}