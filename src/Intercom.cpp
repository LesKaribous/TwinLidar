#include "Intercom.h"
#include "Debugger.h"

namespace Intercom{
    bool sync = false;

    void init(){
        Serial3.begin(9600);
    }

    void checkSerial(){
        if(!sync)
            Serial3.println("TwinLidar");
        else Serial3.println("OK");

        if(Serial3.available() > 0){
            String command = Serial.readStringUntil('\n');
            parseRequest(command);
        }

        Debugger::log << sync;
    }
    
    void parseRequest(String command){
        if(command.startsWith("Vec3{")){
            int startIndex = command.indexOf("{") + 1;
            int stopIndex = command.indexOf("}");

            String Angle = command.substring(startIndex, command.indexOf(","));
            String Dist = command.substring(command.indexOf(","), stopIndex);

            Debugger::log << "Angle : " << Angle << ", Distance: " << Dist << "\n";
            Serial3.println("OK");
        }else if(command.startsWith("Twinsystem")) sync = true;
    }



} // namespace Intercom
