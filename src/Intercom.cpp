#include "Intercom.h"
#include "Debugger.h"
#include "Lidar.h"
#include "Led.h"

#define TWINSYSTEM Serial2

namespace Intercom{
    bool connected = false;
    unsigned long timeout = 0;
    unsigned long ping = 0;

    void init(){
        TWINSYSTEM.begin(9600);
    }

    void reboot(){
        TWINSYSTEM.end();
        _reboot_Teensyduino_();
    }

    void checkSerial(){
        
        if(TWINSYSTEM.available() > 0){
            String command = TWINSYSTEM.readStringUntil('\n');
            parseRequest(command);
        }
        
        if(millis() - ping > 2000){
            if(connected && millis() - timeout > 5000){
                connected = false;
                Led::idle();
                Debugger::log("Main board connection timed out");
            }

            TWINSYSTEM.println("ping");
            ping = millis();
        }
    }
    
    void parseRequest(String command){
        if(command.startsWith("ping")){

            TWINSYSTEM.println("pong");

        }else if(command.startsWith("reboot")){

            reboot();

        }else if(command.startsWith("pong")){

            connected = true;
            Led::ready();
            timeout = millis();

        }else if( command.startsWith("setFov") ){

            String argString = command.substring(command.indexOf("(") +1, command.indexOf(")"));
            String angleStr = argString.substring(0, argString.indexOf(','));
            String distStr  = argString.substring(argString.indexOf(',')+1, argString.length());

            float angle = float(angleStr.toInt()) / 100.0f;
            float dist = float(distStr.toInt()) / 100.0f;

            Debugger::log("Angle :", angle);
            Debugger::log("Dist :" , dist);
            Lidar::setFOV(angle, dist);

        }else if( command.startsWith("lookAt") ){

            String argString = command.substring(command.indexOf("(") +1, command.indexOf(")"));
            String angleStr = argString.substring(0, argString.indexOf(','));
            String distStr  = argString.substring(argString.indexOf(',')+1, argString.length());

            float angle = float(angleStr.toInt()) / 100.0f;
            float dist = float(distStr.toInt()) / 100.0f;

            Debugger::log("Angle :", angle);
            Debugger::log("Dist :" , dist);
            Lidar::lookAt(angle, dist);

        }else if( command.startsWith("getPointCount") ){
            TWINSYSTEM.print("count(");
            TWINSYSTEM.print(Lidar::count());
            TWINSYSTEM.println(")");
        }
    }



} // namespace Intercom
