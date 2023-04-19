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

Intercom intercom;
PixelRing pixel;
Lidar lidar;

enum class RingMode{
    LIDAR,
    INTERCOM
} currentMode;

void parseRequest(Request req){
    String command = req.content.c_str();

    if(command.startsWith("displayIntercom")){
        currentMode = RingMode::INTERCOM;
    }else if(command.startsWith("displayLidar")){
        currentMode = RingMode::LIDAR;
    }else if(command.startsWith("lookAt")){

            String argString = command.substring(command.indexOf("(") +1, command.indexOf(")"));
            String angleStr = argString.substring(0, argString.indexOf(','));
            String distStr  = argString.substring(argString.indexOf(',')+1, argString.length());

            float angle = float(angleStr.toInt());
            float dist = float(distStr.toInt());

            Console::info() << "Angle :" << angle << Console::endl;
            Console::info() << "Dist :" << dist << Console::endl;

            lidar.LookAt(angle, dist);
    }else if(command.startsWith("checkLidar")){
            Console::info() << "Command parsed :" << command.c_str() << Console::endl;
            String argString = command.substring(command.indexOf("(") +1, command.indexOf(")"));

            int angle = argString.toInt();

            Console::info() << "Angle :" << angle << Console::endl;

            lidar.SetFOV(50);
            lidar.SetHeading(angle);
            lidar.Update();

            if(lidar.GetDistance(angle) < 500 && lidar.GetDistance(angle) > 80) intercom.Reply(req, "obstacle");
            else intercom.Reply(req, "RAS");

    }else if(command.startsWith("dummyRequest")){
        String answer = String(req.id);
        intercom.Reply(req, "dummyRequest received !");
        
    }
}

void setup(){
    Console::Initialize();
    Console::SetLevel(ConsoleLevel::_TRACE);

    currentMode = RingMode::INTERCOM;

    pixel.Initialize();
    intercom.Initialize();
    lidar.Initialize();
}


void loop(){
    lidar.Update();
    intercom.Update();
    
    while(intercom.HasPendingRequest()){
        parseRequest(intercom.UnstackRequest());
    }

    if(currentMode == RingMode::INTERCOM){
        pixel.DrawIntercom(intercom.IsConnected());
    }else if(currentMode == RingMode::LIDAR){
        pixel.DrawLidar(lidar);
    }

    pixel.Update();
    //delayMicroseconds(10);
}