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

Lidar lidar;

void setup(){
    //Intercom::init();
    //Led::init();
    Console::Initialize();
    Console::SetLevel(ConsoleLevel::_INFO); 
    Console::info("Init OK");
    
    // while (!Intercom::connected){
    //     //Intercom::checkSerial();
    //     Debugger::checkSerial();
    //     Led::update();
    // }
}

void loop(){
    //Led::update();
    lidar.update();
    //Intercom::checkSerial();
    //delayMicroseconds(10);
}