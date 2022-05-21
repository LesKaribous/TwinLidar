#include "Debugger.h"

#include <initializer_list>

namespace Debugger{

    bool enabled = true;

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
        if(enabled){
            Serial.begin(9600);

            if(Serial.available() <= 0) {}

            header();
            Serial.print("Preparing system...");
            
            delay(200);
            Serial.println("done.");
        }
    }

    void checkSerial(){
        if(enabled){
            if(Serial.available() > 0){
                String command = Serial.readStringUntil('(');
                Serial.println("Received :" + command);
            }
        }
    }

    void println(String message){
        Serial.println(message);
    }

    void println(char c){
        Serial.println(c);
    }

    void println(float data){
        Serial.println(data);
    }

    void println(int data){
        Serial.println(data);
    }

    void print(String message){
        Serial.print(message);
    }

    void print(char c){
        Serial.print(c);
    }

    void print(float data){
        Serial.print(data);
    }

    void print(int data){
        Serial.print(data);
    }


    void log(int data){
        println(data);
    }

    void log(char data){
        println(data);
    }

    void log(float data){
        println(data);
    }

    void log(String data){
        println(data);
    }

    void log(String prefix,   int data, String suffix){
        Serial.print(prefix);
        Serial.print(data);
        Serial.println(suffix);
    }

    void log(String prefix, float data, String suffix){
        Serial.print(prefix);
        Serial.print(data);
        Serial.println(suffix);
    }

    void log(String prefix,  bool data, String suffix){
        Serial.print(prefix);
        Serial.print(data);
        Serial.println(suffix);
    }

    void logArray(String prefix, int array[], size_t size, char separator, String suffix = ""){
        if(size > 0){
            print(prefix);
            for (size_t i = 0; i < size-1; i++){
                print(array[i]);
                print(separator);
            }
            print(array[size-1]);
            println(suffix);
        }
    }

    void logArrayN(String prefix, int element, String interFix, int array[], size_t size, char separator = ',', String suffix = ""){
        if(size > 0){
            print(prefix);
            print(element);
            print(interFix);
            for (size_t i = 0; i < size-1; i++){
                print(array[i]);
                print(separator);
            }
            print(array[size-1]);
            println(suffix);
        }else println("Invalid array printed !");
    }

}