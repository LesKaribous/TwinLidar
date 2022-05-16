#include "Intercom.h"
#include "Debugger.h"

namespace Intercom{
    bool connected = false;
    unsigned long timeout = 0;

    void init(){
        Serial2.begin(9600);
    }

    void checkSerial(){
        if(Serial2.available() > 0){
            String command = Serial.readStringUntil('\n');
            parseRequest(command);
            timeout = millis();
            connected = true;
        }
        if( (connected && millis() - timeout > 5000) || (!connected && millis() - timeout > 1000)){
            connected = false;
            Serial2.println("ping");
            Debugger::log << "ping";
            timeout = millis();
        }
    }
    
    void parseRequest(String command){
        Debugger::log << command;
        if(command == "ping"){
            Serial2.println("pong");
        }
    }



} // namespace Intercom
