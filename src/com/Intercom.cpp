#include "com/Intercom.h"
#include "debug/Console.h"
#include "core/Lidar.h"
#include "core/Led.h"

#define TWINSYSTEM Serial2

namespace Intercom{
    bool connected = false;
    uint32_t timeout = 0;
    uint32_t ping = 0;
    uint32_t lastCountSent = 0;

    void init(){
        TWINSYSTEM.begin(9600);
    }

    void reboot(){
        _reboot_Teensyduino_();
    }

    void sendCount(){
        TWINSYSTEM.print("count(");
        //TWINSYSTEM.print(lidar.check());
        TWINSYSTEM.println(")");
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
                Console::warn("Main board connection timed out");
            }

            TWINSYSTEM.println("ping");
            ping = millis();

            
        }

        if(millis() - lastCountSent > 200){
            sendCount();
            lastCountSent = millis();
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
            String angleStr = argString.substring(0, argString.length());

            float angle = float(angleStr.toInt()) / 100.0f;

            Console::info() << "Angle :" << angle << Console::endl;
            //Lidar::setFOV(angle);

        }else if( command.startsWith("lookAt") ){

            String argString = command.substring(command.indexOf("(") +1, command.indexOf(")"));
            String angleStr = argString.substring(0, argString.indexOf(','));
            String distStr  = argString.substring(argString.indexOf(',')+1, argString.length());

            float angle = float(angleStr.toInt()) / 100.0f;
            float dist = float(distStr.toInt()) / 100.0f;

            Console::info() << "Angle :" << angle << Console::endl;
            Console::info() << "Dist :" << dist << Console::endl;
            //Lidar::lookAt(angle, dist);

        }else if( command.startsWith("getPointCount") ){
            TWINSYSTEM.print("count(");
            //TWINSYSTEM.print(Lidar::count());
            TWINSYSTEM.println(")");
            //Debugger::log("count(", Lidar::count(), ")", INFO);
        }else if( command.startsWith("check") ){
            TWINSYSTEM.print("checked(");
            //TWINSYSTEM.print(Lidar::check());
            TWINSYSTEM.println(")");
        }
    }



} // namespace Intercom
