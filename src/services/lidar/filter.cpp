#include "filter.h"

PolarFilter::PolarFilter() : AbstractFilter(POLAR){
    _minDist = 200;     // Minimum Distance mm
    _maxDist = 1000;  // Maximum Distance mm
    _minAngle = 0;    // Minimum angle °
    _maxAngle = 360;  // Maximum angle °
    _threshold = 100; // Minimum point intensity
}

bool PolarFilter::pass(DataPoint point){
    if ((point.angle >= _minAngle && point.angle <= _maxAngle) || 
        (point.angle + 360 >= _minAngle && point.angle + 360 <= _maxAngle) ||
        (point.angle - 360 >= _minAngle && point.angle - 360 <= _maxAngle)) {
        
        if(point.distance > _maxDist) return false;
        if(point.distance < _minDist) return false;
        if(point.intensity < _threshold) return false;
        return true;
    } else {
        return false;
    }
}

void PolarFilter::setDistanceRange(int minDist, int maxDist){
    _minDist = minDist;
    _maxDist = maxDist;
}

void PolarFilter::setAngleRange(int minAngle, int maxAngle){
    if(minAngle < 0){
        minAngle + 360;
        maxAngle + 360;
    }
    _minAngle = minAngle;
    _maxAngle = maxAngle;
}









CartesianFilter::CartesianFilter() : AbstractFilter(CARTESIAN){
    _cart_max_x = 3000;  //abs rectangle filter
    _cart_max_y = 2000;  //abs rectangle filter
}

bool CartesianFilter::pass(DataPoint point) {
    return point.x > _cart_margin && point.y > _cart_margin && point.x < _cart_max_x-_cart_margin && point.y < _cart_max_y-_cart_margin;
}

void CartesianFilter::setRange(float w, float h, float margin){
    _cart_max_x = w; _cart_max_y = h; _cart_margin = margin;
}