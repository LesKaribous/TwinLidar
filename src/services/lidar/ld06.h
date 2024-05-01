#pragma once

#include "grid.h"
#include "filter.h"
#include <Arduino.h>
#include <deque>

#define MAX_POINTS 512
#define PERSISTENCE 500//ms

const uint8_t PTS_PER_PACKETS = 12;


class LD06{
public:
    LD06(int pin, HardwareSerial& serial = Serial1);

    void begin();

    // Read data from lidar
    bool readData();
    void readScan();

    // Print Data over Serial
    void printScanCSV();      // Print full scan using csv format
    void printScanTeleplot(); // Print full scan using teleplot format (check :https://teleplot.fr/)

    // Settings
    void enableCRC();  // Enable CRC checking
    void disableCRC(); // Disable CRC checking

    inline void enablePolarFiltering(){ _usePolarFiltering = true; }
    inline void enableCartesianFiltering(){ _useCartesianFiltering = true; }
    inline void disablePolarFiltering(){ _usePolarFiltering = false; }
    inline void disableCartesianFiltering(){ _useCartesianFiltering = false; }
    bool useFiltering() const;

    inline void enablePolarGrid(){ _usePolarGrid = true; }
    inline void enableCartesianGrid(){ _useCartesianGrid = true; }
    inline void disablePolarGrid(){ _usePolarGrid = false; }
    inline void disableCartesianGrid(){ _useCartesianGrid = false; }
    bool useGrid()const;

    inline void disableGrid(){ _useCartesianGrid = _usePolarGrid = false; }
    inline void disableFiltering(){ _useCartesianFiltering = _usePolarFiltering = false; }

    void setPolarResolution(float);
    void setCartesianRange(float w, float h, float margin);
    void setPolarRange(float minDist, float maxDist, float minangle, float maxangle);

    void setPosition(float x, float y, float theta); // Set Abs position

    void resetStats();

    //Filtering
    void setIntensityThreshold(int threshold);
    float getCountAtAngle(int angle); //Faster with sectoring enable
    float getDistanceAtAngle(int angle); //Faster with sectoring enable

    // Getters
    inline float getSpeed() const { return _speed; }
    inline float getAngleStep() const { return _angleStep; }
    inline float getTimeStamp() const { return _timeStamp; }

private:
    bool readDataCRC();
    bool readDataNoCRC();
    void computeData(uint8_t *values);
    bool filter(const DataPoint &point);
    void clear();
    void store(DataPoint);

    //Attributes
    const int _pin;
    PolarFilter polar_filter;
    PolarGrid polar_grid;
    CartesianFilter cart_filter;
    CartesianGrid cart_grid;

    // Settings
    bool _useCRC = true;
    bool _useCartesianFiltering = true;
    bool _usePolarFiltering = true;
    bool _useCartesianGrid = true;
    bool _usePolarGrid = true;
    int _threshold = 100; // Minimum point intensity

    // Data
    std::deque<DataPoint> scan;

    float lidarPos_x = 0; //mm
    float lidarPos_y = 0; //mm
    float lidarPos_theta = 0; //rad

    // Temporary variables
    float _speed;
    float _FSA;
    float _LSA;
    float _angleStep;
    int _timeStamp;

    //Serial
    HardwareSerial* _lidarSerial;

    // Reading buffers
    float angles[PTS_PER_PACKETS];
    uint16_t distances[PTS_PER_PACKETS];
    uint8_t confidences[PTS_PER_PACKETS];
};