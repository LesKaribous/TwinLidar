#include "grid.h"
#include "pin.h"
#include <Arduino.h>
#include <math.h>
#include "utils/timer/timer.h"
#include "os/console.h"

PolarGrid::PolarGrid() : AbstractGrid(POLAR){
    setSectorsResolution(_sectorResolution);
}

void PolarGrid::store(DataPoint point){
    int index = floor(point.angle / _sectorResolution);
    sectors[index].add(point);
}

void PolarGrid::unstore(DataPoint point){
    int index = floor(point.angle / _sectorResolution);
    sectors[index].remove(point);
}

void PolarGrid::compute(){
    for(Sector& sector : sectors ){
        sector.compute();
    }
}

// Print sectors using teleplot format (check :https://teleplot.fr/)
void PolarGrid::printSectors(){
    Serial.print(">sectors:");
    for (uint16_t i = 0; i < sectors.size(); i++)
    { //Print > point count : average distance : min dist : max dist
        Serial.print(String() + i + ":" + sectors[i].avgDistance + ";");
    }
    Serial.println();

}

void PolarGrid::clear(){
    sectors.clear();
    sectors.resize(360.0/_sectorResolution);
    for(int i = 0; i < sectors.size() ; i++){
        sectors[i].points.reserve(MAX_POINTS);
        sectors[i].averageAngle = (float(i)+0.5) * _sectorResolution;
    }
}

void PolarGrid::print(){
    Serial.print(">sectors:");
    for (uint16_t i = 0; i < sectors.size(); i++)
    { //Print > point count : average distance : min dist : max dist
        Serial.print(String() + i + ":" + sectors[i].points.size() + ":" + sectors[i].avgDistance + ";");
    }
    Serial.println("|np"); //don't plot
}

void PolarGrid::setSectorsResolution(float angle){
    _sectorResolution = angle;
    sectors.clear();
    sectors.resize(360/angle); //Reserve sector count
    for(int i = 0; i < sectors.size() ; i++){
        sectors[i].points.reserve(MAX_POINTS);
        sectors[i].averageAngle = (float(i)+0.5) * _sectorResolution;
    }
}

float PolarGrid::getDistanceAtAngle(float angle){
    int index = floor(angle / _sectorResolution);
    if(sectors[index].avgDistance < 5) return infinityf();
    return sectors[index].avgDistance;
}

float PolarGrid::getCountAtAngle(float angle){
    int index = floor(angle / _sectorResolution);
    if(sectors[index].avgDistance < 5) return 0;
    return sectors[index].points.size();
}

//Sectors
void PolarGrid::Sector::compute(){
    avgDistance = 0;
    for(auto d : points){
        avgDistance += d;
    }
    if(points.size() > 0) avgDistance /= points.size();
}

void PolarGrid::Sector::clear(){
    avgDistance = 0;
    points.clear();
    points.reserve(MAX_POINTS);
}

void PolarGrid::Sector::add(const DataPoint& p){
    if(points.size()-1 == MAX_POINTS)clear();
    points.push_back(p.distance);
}

void PolarGrid::Sector::remove(const DataPoint& p){
    for(auto i = points.begin(); i < points.end(); i++){
        if(int(p.distance) == *i) points.erase(i);
        return;
    }
     if(points.size()>0)points.erase(points.begin());
}






/**************************************
        Cartesian   Grid
***************************************/

CartesianGrid::CartesianGrid() : AbstractGrid(CARTESIAN){
    clear();
}

void CartesianGrid::setGridSize(float w, float h) {
    _gridWidth = w;
    _gridHeight = h;
}

void CartesianGrid::setMode(GridMode mode) {
    _mode = mode;
}

void CartesianGrid::clear() {
    for (int x = 0; x < GRID_WIDTH; ++x)
        for (int y = 0; y < GRID_HEIGHT; ++y) {
            occupancy[x][y] = 0;
            lastUpdate[x][y] = 0;
        }
}

int CartesianGrid::worldToGridX(float x) {
    return int((x * GRID_WIDTH) / _gridWidth);
}

int CartesianGrid::worldToGridY(float y) {
    return int((y * GRID_HEIGHT) / _gridHeight );
}

void CartesianGrid::store(DataPoint point) {
    int xi = worldToGridX(point.x);
    int yi = worldToGridY(point.y);

    if (xi >= 0 && xi < GRID_WIDTH && yi >= 0 && yi < GRID_HEIGHT) {
        occupancy[xi][yi] = 255;
        lastUpdate[xi][yi] = millis();
        //Console::info() << "store: " << xi << "," << yi << " : " << occupancy[xi][yi] << "\n";
    }
}

void CartesianGrid::compute() {
    uint32_t now = millis();
    for (int x = 0; x < GRID_WIDTH; ++x) {
        for (int y = 0; y < GRID_HEIGHT; ++y) {
            uint32_t age = now - lastUpdate[x][y];
            if (age > 0 && occupancy[x][y] > 0) {
                int decay = age / 1000; // Decay 1 per 100ms
                occupancy[x][y] = (occupancy[x][y] > decay) ? occupancy[x][y] - decay : 0;
            }
        }
    }
}


bool CartesianGrid::isOccupied(int x, int y) {
    return (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT && occupancy[x][y] > 25);
    //return (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT && occupancy_map[x][y] > 0);
}
