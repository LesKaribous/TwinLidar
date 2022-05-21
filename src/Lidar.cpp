#include "Lidar.h"
#include "Parser.h"
#include "Debugger.h"
#include "Pin.h"
#include "Geometry.h"

#include <list>

#define PERSISTENCE 5000

namespace Lidar{

	std::list<Point> Points;
	int maxCount = 500;

	float angleMin = 0;
    float angleMax = 90;
	float distMin = 200;
	float distMax = 1500;

	float angleRange = 30;
	float distRange = 300;

	float lookAngle = 0;
	float lookDistance = 500;

	void debug();

	void init(){
		pinMode(Pin::Lidar::speed, OUTPUT);
		analogWrite(Pin::Lidar::speed, 50);

		setFOV(90, 2000);
		lookAt(0, 500);
		Parser::init();
	}

	void update(){
		
		Parser::readData();


		
		//debug();
		
	}
	
	void push(Point p){
		if(count() >= maxCount) pop();
		Points.push_back(p);
	}

	int count(){
		return Points.size();
	}

	void pop(){
		Points.pop_front();
	}

	bool isLastDifferent(Point p){
		return !(p.distance == Points.back().distance && p.angle == Points.back().angle);
	}

	bool check(){
		return (count() > 50);
	}

    void setFOV(float angleR, float distR){
		angleRange = angleR;
    	distRange = distR;

		angleMin = lookAngle - angleRange/2.0;
		angleMax = lookAngle + angleRange/2.0;

		distMin = lookDistance - distRange/2.0;
		distMax = lookDistance + distRange/2.0;

		Points.clear();
	}

	void lookAt(float lookA, float lookD){
		lookAngle = lookA;
	 	lookDistance = lookD;

		angleMin = lookAngle - angleRange/2.0;
		angleMax = lookAngle + angleRange/2.0;

		distMin = lookDistance - distRange/2.0;
		distMax = lookDistance + distRange/2.0;

		Points.clear();
	}

	void debug(){
		std::list<Point>::iterator it = Points.begin();
		int i = 0;
		while (it != Points.end())
		{
			/*
			bool isTooOld = false;//(millis() - it->birthday < PERSISTENCE);
			if (isTooOld){
				Points.erase(it++);
			}else{
				int dataArray[] = {it->distance,it->angle*100, it->intensity};
				Debugger::logArrayN("Data.point[", i, "]:{", dataArray, 3, ',', "}");
				
				
				i++;
			}
			*/

			int dataArray[] = {it->distance,it->angle*100, it->intensity};
			Debugger::logArrayN("Data.point[", i, "]:{", dataArray, 3, ',', "}");
			++it;
			i++;
			
		}
	}
}