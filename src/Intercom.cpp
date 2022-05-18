#include "Intercom.h"
#include "Debugger.h"
#include "Lidar.h"

//TwinLidar use Serial2 to communicate with motherboard

namespace Intercom{
    bool connected = false;
    unsigned long timeout = 0;
    unsigned long ping = 0;

    void init(){
        Serial2.begin(9600);
    }

    void checkSerial(){
        if(Serial2.available() > 0){
            String command = Serial2.readStringUntil('\n');
            parseRequest(command);
        }
        
        if(millis() - ping > 1000){
            Serial2.println("ping");
            ping = millis();
        }else if(connected && millis() - timeout > 5000){
            connected = false;
            Debugger::log << "Main board connection timed out";
        }
    }
    
    void parseRequest(String command){
        if(command.startsWith("ping")){

            Serial2.println("pong");

        }else if(command.startsWith("pong")){

            connected = true;
            timeout = millis();

        }else if( command.startsWith("setFov") ){

            String argString = command.substring(command.indexOf("(") +1, command.indexOf(")"));
            String angleStr = argString.substring(0, argString.indexOf(','));
            String widthStr = argString.substring(argString.indexOf(',')+1, argString.lastIndexOf(',')-1);
            String distStr  = argString.substring(argString.lastIndexOf(',')+1, argString.length());

            float angle = float(angleStr.toInt()) / 100.0f;
            float width = float(widthStr.toInt()) / 100.0f;
            float dist = float(widthStr.toInt()) / 100.0f;

            Debugger::log << angle << " : " << width << ":" << dist;
            Lidar::setFOV(angle, width);

        }else if( command.startsWith("getPointCount") ){
            Serial2.print("count(");
            Serial2.print(Lidar::count());
            Serial2.println(")");
        }
    }



} // namespace Intercom
