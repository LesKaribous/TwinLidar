#include "ld06.h"
#include "Arduino.h"
#include "crc.h"

// Packets size
const uint8_t PACKET_SIZE = 47; // note: 1(Start)+1(Datalen)+2(Speed)+2(SAngle)+36(DataByte)+2(EAngle)+2(TimeStamp)+1(CRC)
// Headers
const uint8_t HEADER = 0x54;
const uint8_t VER_SIZE = 0x2c;

//#define LIDAR_SERIAL Serial1
#define LIDAR_SERIAL (*_lidarSerial)

LD06::LD06(int pin, HardwareSerial& serial) : _pin(pin), _lidarSerial(&serial){}

void LD06::begin(){
    LIDAR_SERIAL.begin(230400, SERIAL_8N1);
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, HIGH);
}

/* Read lidar packet data,
 * return : true if a valid package was received
 */
bool LD06::readData(){
    return _useCRC ? readDataCRC() : readDataNoCRC();
}

/* Read lidar packet data without checking CRC,
 * return : true if a valid package was received
 */
bool LD06::readDataCRC(){
    int result = 0;
    static uint8_t crc = 0;
    static uint8_t n = 0;
    static uint8_t lidarData[PACKET_SIZE];
    while (LIDAR_SERIAL.available())
    {
        uint8_t current = LIDAR_SERIAL.read();
        if (n > 1 || (n == 0 && current == HEADER) || (n == 1 && current == VER_SIZE))
        {
            lidarData[n] = current;
            if (n < PACKET_SIZE - 1)
            {
                crc = CrcTable[crc ^ current];
                n++;
            }
            else
            {
                if (crc == current)
                {
                    computeData(lidarData);
                    result = 1;
                }
                else
                {
                    result = -1;
                }
                n = 0;
                crc = 0;
            }
        }
        else
        {
            n = 0;
            crc = 0;
        }
    }
    return result;
}

/* Read lidar packet data without checking CRC,
 * return : true if a package was received
 */
bool LD06::readDataNoCRC(){
    static uint8_t n = 0;
    static uint8_t lidarData[PACKET_SIZE];
    while (LIDAR_SERIAL.available())
    {
        uint8_t current = LIDAR_SERIAL.read();
        if (n > 1 || (n == 0 && current == HEADER) || (n == 1 && current == VER_SIZE))
        {
            lidarData[n] = current;
            if (n == PACKET_SIZE - 1)
            {
                computeData(lidarData);
                n = 0;
                return true;
            }
        }
        else
            n = 0;
    }
    return false;
}

// Read lidar packets and return true scan as more than count points
void LD06::readScan(){
    DataPoint data;
    data.birth = millis();

    if(readData()){
        for (int i = 0; i < PTS_PER_PACKETS; i++){
            data.angle = angles[i]; //degrees relative to lidar origin
            data.distance = distances[i];//mm

            //absolute
            //data.x = lidarPos_x + data.distance * cos( data.angle * DEG_TO_RAD + lidarPos_theta*DEG_TO_RAD);
            //data.y = lidarPos_y + data.distance * sin( data.angle * DEG_TO_RAD + lidarPos_theta*DEG_TO_RAD);

            data.x = lidarPos_x + data.distance * cosf( (data.angle + lidarPos_theta) * DEG_TO_RAD);
            data.y = lidarPos_y - data.distance * sinf( (data.angle + lidarPos_theta) * DEG_TO_RAD);


            data.intensity = confidences[i];
            
            if(filter(data)){
                store(data);
            }
        }
    }
    
    if(_usePolarGrid) polar_grid.compute();

}

bool LD06::useFiltering() const{
    return _useCartesianFiltering || _usePolarFiltering;
}

bool LD06::useGrid() const{
    return _useCartesianGrid || _usePolarGrid;
}

void LD06::setPosition(float x, float y, float theta){
    lidarPos_x = x;
    lidarPos_y = y;
    lidarPos_theta = theta;
}

void LD06::resetStats(){

    while(scan.size() > 0 && millis() - scan.front().birth > PERSISTENCE){
        scan.pop_front();
    }


    if(_useCartesianGrid)cart_grid.clear();
    if(_usePolarGrid)polar_grid.clear();
}

void LD06::computeData(uint8_t *values){
    _speed = float(values[3] << 8 | values[2]) / 100;
    _FSA = float(values[5] << 8 | values[4]) / 100;
    _LSA = float(values[PACKET_SIZE - 4] << 8 | values[PACKET_SIZE - 5]) / 100;
    _timeStamp = int(values[PACKET_SIZE - 2] << 8 | values[PACKET_SIZE - 3]);

    _angleStep = ((_LSA - _FSA > 0) ? (_LSA - _FSA) / (PTS_PER_PACKETS - 1) : (_LSA + (360 - _FSA)) / (PTS_PER_PACKETS - 1));

    if (_angleStep > 20)
        return;

    for (int i = 0; i < PTS_PER_PACKETS; i++){
        float raw_deg = 360.0 - _FSA + i * _angleStep;
        
        raw_deg = fmodf(raw_deg,360.0); //[0, 360]
        if (raw_deg < 0)
            raw_deg += 360;

        angles[i] = raw_deg;
        confidences[i] = values[8 + i * 3];
        distances[i] = int(values[8 + i * 3 - 1] << 8 | values[8 + i * 3 - 2]);
    }
}

// Return true if point pass the filter
bool LD06::filter(const DataPoint &point){
    if(useFiltering()){
        return (cart_filter.pass(point) || !_useCartesianFiltering) && (polar_filter.pass(point) || !_usePolarFiltering);
    }else return true; //no filter all points pass
}

void LD06::clear(){
    cart_grid.clear();
    polar_grid.clear();
}

void LD06::store(DataPoint point){
    if(scan.size() >= MAX_POINTS-1){
        if(_useCartesianGrid)cart_grid.unstore(scan.front());
        if(_usePolarGrid)polar_grid.unstore(scan.front());
        scan.pop_front();
    }
    
    scan.push_back(point);
    if(_useCartesianGrid)cart_grid.store(point);
    if(_usePolarGrid)polar_grid.store(point);
}

float LD06::getDistanceAtAngle(int angle){ //Faster with sectoring enable
    
    angle -= lidarPos_theta;
    angle = fmodf(angle,360); //[0, 360]
    if (angle < 0)
        angle += 360;

    //Serial.println(angle);
    if(_usePolarGrid){
        return polar_grid.getDistanceAtAngle(angle);
    }
    
    if(scan.size() == 0) return 0;
    float averageDistance = 0;
    int count = 0;
    for(auto& point : scan){
        if(point.angle > angle - 1 && point.angle < angle - 1 ){ //map on 360°
            averageDistance += point.distance;
            count++;
        }
    }
    return count == 0 ? 0 : averageDistance/float(count);
}


// Print full scan using csv format
void LD06::printScanCSV(){
    Serial.println("Angle(°),Distance(mm),x(mm),y(mm)");
    for (uint16_t i = 0; i < scan.size(); i++)
    {
        Serial.println(String() + scan[i].angle + "," + scan[i].distance + "," + scan[i].x + "," + scan[i].y);
    }
    Serial.println("");
}


// Print full scan using teleplot format (check :https://teleplot.fr/)
void LD06::printScanTeleplot(){
    //polar_grid.print();
    
    Serial.print(">lidarXY:");
    for (uint16_t i = 0; i < scan.size(); i++)
    {
        Serial.print(String() + scan[i].x + ":" + scan[i].y + ";");
    }
    Serial.print(String() + "0" + ":" + "0" + ";");
    Serial.print(String() + "3000" + ":" + "0" + ";");
    Serial.print(String() + "3000" + ":" + "2000" + ";");
    Serial.print(String() + "0" + ":" + "2000" + ";");
    Serial.print(String() + (lidarPos_x+20) + ":" + (lidarPos_y) +";");
    Serial.print(String() + (lidarPos_x-20) + ":" + (lidarPos_y) +";");
    Serial.print(String() + (lidarPos_x) + ":" + (lidarPos_y+20) +";");
    Serial.print(String() + (lidarPos_x) + ":" + (lidarPos_y-20) +";");
    Serial.print(String() + (lidarPos_x) + ":" + (lidarPos_y) +";");
    Serial.println("|xy");
    /*
    Serial.print(">lidar:");
    for (uint16_t i = 0; i < scan.size(); i++)
    {
        Serial.print(String() + scan[i].angle + ":" + scan[i].distance + ";");
    }
    Serial.println("|np");
    */
}


// Settings
void LD06::enableCRC(){
    _useCRC = true;
}

void LD06::disableCRC(){
    _useCRC = false;
}

void LD06::setIntensityThreshold(int threshold){
    _threshold = threshold;
}

void LD06::setPolarResolution(float res){
    polar_grid.setSectorsResolution(res);
}

void LD06::setCartesianRange(float w, float h, float margin){
    cart_filter.setRange(w, h, margin);
    cart_grid.setGridSize(w, h);
}

void LD06::setPolarRange(float minDist, float maxDist, float minangle, float maxangle){
    polar_filter.setAngleRange(minangle, maxangle);
    polar_filter.setDistanceRange(minDist,maxDist);
}
