#include "Debugger.h"

namespace Debugger{
    char buffer[1024];
    EasyStringStream log(buffer, 1024);


    void header(){
        Serial.println("   _______       _       _      _     _");
        Serial.println("  |__   __|     (_)     | |    (_)   | |");
        Serial.println("     | |_      ___ _ __ | |     _  __| | __ _ _ __");
        Serial.println("     | \\ \\ /\\ / / | '_ \\| |    | |/ _` |/ _` | '__|");
        Serial.println("     | |\\ V  V /| | | | | |____| | (_| | (_| | |");
        Serial.println("     |_| \\_/\\_/ |_|_| |_|______|_|\\__,_|\\__,_|_|");
        Serial.println();
        Serial.println("Author  : Nadarbreicq, JulesTopart ");
        Serial.println();
        Serial.print("Twinlidar... compiled  ");
        Serial.print(__DATE__);
        Serial.print(" at ");
        Serial.println(__TIME__);

    }

    void init(){
        Serial.begin(115200);

        while (!Serial && millis() < 500) {
            //Waiting for serial
            //21-04-2022 - @Nadar - Diminution de 5000ms à 500ms
        }
        header();
        Serial.print("Preparing system...");
        
        delay(200);
        Serial.println("done.");
    }

    void checkSerial(){
        if(Serial.available()){
            String command = Serial.readStringUntil('(');
            Serial.println("Received :" + command);
        }
    }

    void printBuffer(){
        if(log.getCursor() != 0)
            Serial.println(buffer);
        log.reset();
    }


}