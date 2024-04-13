#pragma once
#include "geom.h"
#include <vector>

class AbstractFilter{
public:
    enum FilterType{
        POLAR,
        CARTESIAN,
    };

    AbstractFilter(FilterType type) : m_filterType(type){};
    virtual bool pass(DataPoint) = 0;
    inline FilterType type() const { return m_filterType; }
private:
    FilterType m_filterType;
};


class PolarFilter : public AbstractFilter{
public:
    PolarFilter();
    bool pass(DataPoint) override;

    void setDistanceRange(int minDist, int maxDist);
    void setAngleRange(int minAngle, int maxAngle);

private:
    //Polar filter
    int _minDist;   // Minimum Distance mm
    int _maxDist;   // Maximum Distance mm
    int _minAngle;  // Minimum angle °
    int _maxAngle;  // Maximum angle °
    int _threshold; // Minimum point intensity
};


class CartesianFilter : public AbstractFilter{
public:
    CartesianFilter();
    bool pass(DataPoint) override;
    void setRange(float w, float h, float margin);
private:
    //Cartesian filter
    float _cart_max_x;  //abs rectangle filter
    float _cart_max_y;  //abs rectangle filter
    float _cart_margin;  //abs filter margin
};

