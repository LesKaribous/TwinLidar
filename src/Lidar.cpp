#include "Lidar.h"
#include "Parser.h"
#include "Debugger.h"
#include "Pin.h"
#include "Settings.h"

#include <algorithm>
#include <list>

#define PERSISTENCE 400
#define DEBUG_REFRESS 200
namespace Lidar{

	std::list<Point> Points;
	int maxCount = 500;

	float angleMin;
    float angleMax;
	float distMin;
	float distMax;

	float angleRange;

	float lookAngle;
	float lookDistance;

	bool threshold = 8;

	void debug();

	void init(){
		pinMode(Pin::Lidar::speed, OUTPUT);
		analogWrite(Pin::Lidar::speed, 50);

		setFOV(30);
		lookAt(0, 500);
		Parser::init();
	}

	void update(){
		Parser::readData();
		
		filter();
		
		if(Debugger::level() <= VERBOSE) debug();
		
	}
	
	void filter(){
		std::list<std::list<Point>::iterator> trash;

		for(std::list<Point>::iterator it = Points.begin(); it != Points.end() ; it++){
			if(millis() - it->birthday > PERSISTENCE){
				trash.push_back(it);
			}
		}

		for (std::list<Point>::iterator it : trash){
			Points.erase(it);
		}
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

    void setFOV(float angleR){
		angleRange = angleR;

		angleMin = lookAngle - angleRange/2.0;
		angleMax = lookAngle + angleRange/2.0;

		distMin = Settings::minDist ;
		//Points.clear();
	}

	void setThreshold(int value){
		threshold = value;
	}

	void lookAt(float lookA, float lookD){
		lookAngle = lookA;
	 	lookDistance = lookD;

		angleMin = lookAngle - angleRange/2.0;
		angleMax = lookAngle + angleRange/2.0;

		distMin = Settings::minDist ;
		distMax = lookDistance;

		//Points.clear();
	}


	long unsigned int lastSent = 0;

	void debug(){

		if(millis() - lastSent > DEBUG_REFRESS){
			lastSent = millis();
			int array[] = { angleMin*100.0f, angleMax*100.0f, distMin, distMax };
			Debugger::logArray("fov(", array, 4);

			Debugger::log("count(", count(), ")");

			int inc = (distMax - distMin)/10.0f;
			for (size_t j = 0; j < 10; j++){
				int samplingArray[] = {(j*inc) + distMin, angleMin *100, 254,0};
				Debugger::logArrayN("Data.point[", 0, "]:{", samplingArray, 4, ',', "}");
			}
			for (size_t j = 0; j < 10; j++){
				int samplingArray[] = {(j*inc) + distMin,angleMax*100, 254,0};
				Debugger::logArrayN("Data.point[", 0, "]:{", samplingArray, 4, ',', "}");
			}
            
			for(Point p : Points){
				
				int inFOV = 0;
				if(p.distance < Lidar::distMax && p.distance > Lidar::distMin){
                    if(p.angle < Lidar::angleMax && p.angle > Lidar::angleMin){
                        inFOV = 1;
                    }
                }

				int dataArray[] = {p.distance,p.angle*100, p.intensity, inFOV};
            	Debugger::logArrayN("Data.point[", 0, "]:{", dataArray, 4, ',', "}");
			}
		}
	}
}