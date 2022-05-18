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
    //--- INIT ---
    Intercom::init();
    Debugger::init();
    Lidar::init();
    Debugger::log << "Init OK.";
}

void loop(){
    Lidar::update();
    Intercom::checkSerial();
    Debugger::printBuffer();
}