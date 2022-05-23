#include "Parser.h"
#include "Debugger.h"
#include "Pin.h"
#include "Lidar.h"
#include "Settings.h"

#include <OneWire.h>

#define LIDAR_SERIAL Serial3

namespace Parser{


    // CalCRC8 function declaration (See bottom)
    uint8_t CalCRC8(uint8_t *p, uint8_t len);

    bool filter = true;
    int badCrC = 0;

    void init(){
        LIDAR_SERIAL.begin(230400);
    }

    void readData(){
        if(LIDAR_SERIAL.available() >= 47){     //Check if a complete packet is possibly available
            byte packet[47];                    //Create a buffer for 46 bytes + 1 byte CrC
            byte header = LIDAR_SERIAL.peek();  //Check if the first byte is the 0x54 header

            if (header != 0x54){                //If not, throw the first byte and start again
                LIDAR_SERIAL.read();
                return;
            }

            //Header correct.

            LIDAR_SERIAL.readBytes(packet, 47); //Read the next 47 bytes and store them from element 1 in packet byte array

            u_int8_t crc = CalCRC8(packet, 46); //Calculate the checksum
            if (crc != packet[46]){
                badCrC++;
                Debugger::log("Bad CrC", int(badCrC), WARN);
                return;
            }

            //Parse data according to this datasheet : https://www.ldrobot.com/editor/file/20210422/1619071627351038.pdf
            LD06_DATA data;
            data.header = packet[0];
            data.ver_len = packet[1];
            data.speed = packet[3] << 8 | packet[2];        //Useless, speed isn't used yet
            data.start_angle = packet[5] << 8 | packet[4];  //Gather the angle at which Lidar start to measure

            // data.ver_len is supposed to be equal to PACKSIZE
            for (size_t i = 0; i < PACKSIZE; i++){  //Parse 12 points 3 bytes each
                uint16_t distance = packet[7 + i * 3] << 8 | packet[6 + i * 3];
                uint8_t intensity = packet[8 + i * 3]; 
                data.point[i] = Point(distance, 0, intensity); // Create a Point object without angle
            }

            data.end_angle = packet[43] << 8 | packet[42];
            data.timestamp = packet[45] << 8 | packet[44];
            data.crc8 = packet[46]; //Gather the CrC

            float packetAngle = data.end_angle - data.start_angle;
            float angleStep = (packetAngle / float(PACKSIZE-1)); // Calculate the angle step
            for (size_t i = 0; i < PACKSIZE /*data.ver_len*/; i++){
                data.point[i].angle = float(data.start_angle) + angleStep*i;
                data.point[i].angle /= -100.0f; //Raw angle are inverted and multiplieds by 10² convert them to degrees

                if(data.point[i].angle < -180) data.point[i].angle += 360;
                data.point[i].angle += 60.0f; //Add 180°

                //Filter data according to the FOV
                if(data.point[i].distance < Lidar::distMax && data.point[i].distance > Lidar::distMin || !filter){
                    if(data.point[i].angle < Lidar::angleMax && data.point[i].angle > Lidar::angleMin || !filter){
                        Lidar::push(data.point[i]);
                    }
                }
            }      
        }
    }


    //CRC Lookup table
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


}

Point::Point(uint16_t _distance, uint16_t _angle, uint8_t _intensity)
{
    distance = _distance;
    angle = _angle;
    intensity = _intensity;
    birthday = millis();
}

Point::Point()
{
    distance = 0;
    angle = 0;
    intensity = 0;
    birthday = millis();
}


