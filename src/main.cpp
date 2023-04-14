//
//   _______       _       _      _     _            
//  |__   __|     (_)     | |    (_)   | |           
//     | |_      ___ _ __ | |     _  __| | __ _ _ __ 
//     | \ \ /\ / / | '_ \| |    | |/ _` |/ _` | '__|
//     | |\ V  V /| | | | | |____| | (_| | (_| | |   
//     |_| \_/\_/ |_|_| |_|______|_|\__,_|\__,_|_|                                                                            
//
//     Author  : Nadarbreicq, JulesTopart
//     Version : 0.1.0
//     Last update : 10 / 04 / 2023
                                    
#include "TwinLidar.h"

Lidar lidar;

void setup(){
    //Intercom::init();
    Led::init();
    Console::Initialize();
    Console::SetLevel(ConsoleLevel::_INFO); 
    Console::info("Init OK") << Console::endl;
    
    lidar.init();

    while (!Intercom::connected){
        //Intercom::checkSerial();
        //Debugger::checkSerial();
        Led::update();
        if(millis() > 3000){
            Intercom::connected = true;
            Led::ready();
        }
    }
    while(millis() < 8000) Led::update();
}


void loop(){
    
    lidar.update();
    //Intercom::checkSerial();
    //delayMicroseconds(10);
}