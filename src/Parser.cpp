#include "Parser.h"
#include "Debugger.h"
#include "Pin.h"
#include "Lidar.h"

#include <OneWire.h>

namespace Parser{

    static const uint8_t CrcTable[256] = {
        0x00, 0x4d, 0x9a, 0xd7, 0x79, 0x34, 0xe3,
        0xae, 0xf2, 0xbf, 0x68, 0x25, 0x8b, 0xc6, 0x11, 0x5c, 0xa9, 0xe4, 0x33,
        0x7e, 0xd0, 0x9d, 0x4a, 0x07, 0x5b, 0x16, 0xc1, 0x8c, 0x22, 0x6f, 0xb8,
        0xf5, 0x1f, 0x52, 0x85, 0xc8, 0x66, 0x2b, 0xfc, 0xb1, 0xed, 0xa0, 0x77,
        0x3a, 0x94, 0xd9, 0x0e, 0x43, 0xb6, 0xfb, 0x2c, 0x61, 0xcf, 0x82, 0x55,
        0x18, 0x44, 0x09, 0xde, 0x93, 0x3d, 0x70, 0xa7, 0xea, 0x3e, 0x73, 0xa4,
        0xe9, 0x47, 0x0a, 0xdd, 0x90, 0xcc, 0x81, 0x56, 0x1b, 0xb5, 0xf8, 0x2f,
        0x62, 0x97, 0xda, 0x0d, 0x40, 0xee, 0xa3, 0x74, 0x39, 0x65, 0x28, 0xff,
        0xb2, 0x1c, 0x51, 0x86, 0xcb, 0x21, 0x6c, 0xbb, 0xf6, 0x58, 0x15, 0xc2,
        0x8f, 0xd3, 0x9e, 0x49, 0x04, 0xaa, 0xe7, 0x30, 0x7d, 0x88, 0xc5, 0x12,
        0x5f, 0xf1, 0xbc, 0x6b, 0x26, 0x7a, 0x37, 0xe0, 0xad, 0x03, 0x4e, 0x99,
        0xd4, 0x7c, 0x31, 0xe6, 0xab, 0x05, 0x48, 0x9f, 0xd2, 0x8e, 0xc3, 0x14,
        0x59, 0xf7, 0xba, 0x6d, 0x20, 0xd5, 0x98, 0x4f, 0x02, 0xac, 0xe1, 0x36,
        0x7b, 0x27, 0x6a, 0xbd, 0xf0, 0x5e, 0x13, 0xc4, 0x89, 0x63, 0x2e, 0xf9,
        0xb4, 0x1a, 0x57, 0x80, 0xcd, 0x91, 0xdc, 0x0b, 0x46, 0xe8, 0xa5, 0x72,
        0x3f, 0xca, 0x87, 0x50, 0x1d, 0xb3, 0xfe, 0x29, 0x64, 0x38, 0x75, 0xa2,
        0xef, 0x41, 0x0c, 0xdb, 0x96, 0x42, 0x0f, 0xd8, 0x95, 0x3b, 0x76, 0xa1,
        0xec, 0xb0, 0xfd, 0x2a, 0x67, 0xc9, 0x84, 0x53, 0x1e, 0xeb, 0xa6, 0x71,
        0x3c, 0x92, 0xdf, 0x08, 0x45, 0x19, 0x54, 0x83, 0xce, 0x60, 0x2d, 0xfa,
        0xb7, 0x5d, 0x10, 0xc7, 0x8a, 0x24, 0x69, 0xbe, 0xf3, 0xaf, 0xe2, 0x35,
        0x78, 0xd6, 0x9b, 0x4c, 0x01, 0xf4, 0xb9, 0x6e, 0x23, 0x8d, 0xc0, 0x17,
        0x5a, 0x06, 0x4b, 0x9c, 0xd1, 0x7f, 0x32, 0xe5, 0xa8
    };

    uint8_t CalCRC8(uint8_t *p, uint8_t len){
        uint8_t crc = 0;
        uint16_t i;
        for (i = 0; i < len; i++){
        crc = CrcTable[(crc ^ *p++) & 0xff];
        }
        return crc;
    }




    void readSerial(){
        //Debugger::log << "[Parser] : Parsing Lidar data :" << '\n';

        //Debugger::log << "[Parser] :    Looking for packet..." << '\n';
        while (Serial2.available() > 46){
            if (Serial2.read() == 0x54){

                //Create a new buffer with 0 value
                byte buffer[46];
                
                for (size_t i = 0; i < 46; i++)
                    buffer[i] = 0;

                //Read the next 46 bytes
                Serial2.readBytes(buffer, 46);

                //Print bytes for debug
                /*
                for (size_t i = 0; i < 46; i++){
                    Serial.print(buffer[i], HEX);
                    Serial.print(" ");
                }
                Serial.println();
                */

                //Calculate the checksum
                //u_int8_t crc = CalCRC8(buffer, 46);
                u_int8_t crc = buffer[45]; //disable CRC
                if (crc != buffer[45]){
                    Serial.print("[Parser] Error : Checksum Failed : ") ;
                    Serial.print(crc);
                    Serial.print(" != ");
                    Serial.println(buffer[45]);
                    return;
                }

                //Debugger::log << "-------------- Packet Start --------------" << '\n';

                LD06_DATA data;
                data.header = 0x54;
                data.ver_len = buffer[0];
                data.speed = buffer[2] << 8 | buffer[1]; // Un pêtit doute
                data.start_angle = buffer[4] << 8 | buffer[3];

                // data.ver_len is supposed to be equal to PACKSIZE
                for (size_t i = 0; i < PACKSIZE /*data.ver_len*/; i++)
                {

                    uint16_t distance = buffer[6 + i * 3] << 8 | buffer[5 + i * 3];
                    uint8_t intensity = buffer[7 + i * 3];

                    data.point[i] = Point(distance, 0, intensity);
                }

                data.end_angle = buffer[42] << 8 | buffer[41];
                data.timestamp = buffer[44] << 8 | buffer[43];
                data.crc8 = buffer[45];

                float packetAngle = data.end_angle - data.start_angle;
                for (size_t i = 0; i < PACKSIZE /*data.ver_len*/; i++)
                {
                    data.point[i].angle = data.start_angle + (packetAngle / PACKSIZE-1)*i;

                    Debugger::log << "Data.point[" << i << "] : {" << int(data.point[i].distance) << "," << int(data.point[i].angle) << "," << int(data.point[i].intensity) << "}\n";
                }



                /*
                Debugger::log << "Data.ver_len : " << (int)data.ver_len << '\n';
                Debugger::log << "Data.speed : " << data.speed << '\n';
                Debugger::log << "Data.start_angle : " << data.start_angle << '\n';
                Debugger::log << "Data.end_angle : " << data.end_angle << '\n';
                Debugger::log << "Data.timestamp : " << data.timestamp << '\n';
                Debugger::log << "Data.crc8 : " << (int)data.crc8 << '\n';
                */

                //Debugger::log << "-------------- Packet End --------------" << '\n';
            }
        }
    }

}

Point::Point(uint16_t _distance, uint16_t _angle, uint8_t _intensity)
{
    distance = _distance;
    angle = _angle;
    intensity = _intensity;
}

Point::Point()
{
    distance = 0;
    angle = 0;
    intensity = 0;
}

Vec2 Point::toVec2()
{
    Vec2 buf(0, 0);
    buf.setMag(distance);
    buf.setHeading(angle);
    return buf;
}
