#include "grid.h"
#include <Arduino.h>

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
    if(sectors[index].avgDistance < 5) return 0;
    return sectors[index].avgDistance;
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




CartesianGrid::CartesianGrid() : AbstractGrid(CARTESIAN){
    _gridResolution = 100;   //mm
    _gridWidth = 3000;
    _gridHeight = 2000;
    _gridCol = _gridWidth / _gridResolution;      //mm
    _gridRow = _gridHeight / _gridResolution;     //mm
}


bool CartesianGrid::isOccupied(int x, int y) {
    int index1D = y * _gridCol + x;
    return cells.find(index1D) != cells.end();
}


//traverse occupancy map from x, y in the theta direction
float CartesianGrid::getDistance(float x, float y, float theta) {
// Direction vector
    float dx = cos(theta);
    float dy = sin(theta);

    // Current position
    float cx = x;
    float cy = y;

    while (cx >= 0 && cx < _gridCol && cy >= 0 && cy < _gridRow) {
        int ix = static_cast<int>(round(cx));
        int iy = static_cast<int>(round(cy));

        // Check the current cell and its immediate neighbors
        for (int nx = ix - 1; nx <= ix + 1; ++nx) {
            for (int ny = iy - 1; ny <= iy + 1; ++ny) {
                if (nx >= 0 && nx < _gridCol && ny >= 0 && ny < _gridRow && isOccupied(nx, ny)) {
                    // Calculate and return the distance
                    float distance = sqrt(pow(x - nx, 2) + pow(y - ny, 2));
                    return distance;
                }
            }
        }

        // Move to the next cell in the direction of the ray
        cx += dx;
        cy += dy;
    }

    // Return -1 if no occupied cells were found
    return -1;
}

void CartesianGrid::store(DataPoint p){

    int index_x = std::min(std::max( static_cast<int>(round(p.x/_gridResolution)),0), _gridCol);
    int index_y = std::min(std::max( static_cast<int>(round(p.y/_gridResolution)),0), _gridRow);

    int index1D = (index_y * _gridCol) + index_x;

    cells[index1D] = true;
}

void CartesianGrid::unstore(DataPoint p){

    int index_x = std::min(std::max( static_cast<int>(round(p.x/_gridResolution)),0), _gridCol);
    int index_y = std::min(std::max( static_cast<int>(round(p.y/_gridResolution)),0), _gridRow);

    int index1D = (index_y * _gridCol) + index_x;

    cells[index1D] = false;
    cells.extract(index1D);
}

void CartesianGrid::compute(){
    //nothing to do here
}

void CartesianGrid::clear(){
    cells.clear();
}

void CartesianGrid::setResolution(float cellSize){
    _gridResolution = cellSize;
    _gridCol = _gridWidth / _gridResolution;      //mm
    _gridRow = _gridHeight / _gridResolution;     //mm
}

void CartesianGrid::setGridSize(float w, float h){
    _gridHeight = w;
    _gridWidth = h;
    _gridCol = _gridWidth / _gridResolution;      //mm
    _gridRow = _gridHeight / _gridResolution;     //mm
}

void CartesianGrid::setMode(GridMode mode){
    _mode = mode;
}