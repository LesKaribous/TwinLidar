//
//   _______       _       _      _     _            
//  |__   __|     (_)     | |    (_)   | |           
//     | |_      ___ _ __ | |     _  __| | __ _ _ __ 
//     | \ \ /\ / / | '_ \| |    | |/ _` |/ _` | '__|
//     | |\ V  V /| | | | | |____| | (_| | (_| | |   
//     |_| \_/\_/ |_|_| |_|______|_|\__,_|\__,_|_|                                                                            
//
//     Author  : Nadarbreicq, JulesTopart
//     Version : 0.0.1
//     Last update : 24 / 04 / 2022
                                    
#include "TwinLidar.h"

void setup(){
    Intercom::init();
    Lidar::init();
    Led::init();

    Debugger::init(VERBOSE);
    Debugger::log("Init OK.", INFO);

    while (!Intercom::connected){
        Intercom::checkSerial();
        Debugger::checkSerial();
        Led::update();
    }
}

void loop(){
    Led::update();
    Lidar::update();
    Intercom::checkSerial();
    Debugger::checkSerial();
    //delayMicroseconds(10);
}