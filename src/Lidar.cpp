#include "Lidar.h"
#include "Parser.h"
#include "Debugger.h"
#include "Pin.h"
#include "Geometry.h"

#include <vector>

namespace Lidar{

	std::vector<Point> Points;
	int maxCount = 500;

	void init(){
		pinMode(Pin::Lidar::speed, OUTPUT);
		analogWrite(Pin::Lidar::speed, 120);

		Serial3.begin(230400);
	}

	void update(){
		Parser::readSerial();
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
		float angleStep = 10;
		float minAngle = 0;
		float maxAngle = 20;

		float minDist = 200;
		float maxDist = 500;

		int steps = 360/angleStep;

		for(int n = 0; n < steps; n++ ){
			int count = 0;
			for (size_t i = 0; i < Points.size(); i++){
				if(Points[i].distance > minDist && Points[i].distance < maxDist)
					if(Points[i].angle > minAngle && Points[i].angle > minAngle) count++;
			}
			if(count > 10) return true;
			else{
				count = 0;
				minAngle += angleStep;
				maxAngle += angleStep;
			}
		}
		return false;
	}
}