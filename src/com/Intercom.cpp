#include "com/Intercom.h"
#include "debug/Console.h"

#define LIDAR_SERIAL Serial3

Intercom::Intercom() : _Stream(LIDAR_SERIAL) {}

void Intercom::Initialize(){
    LIDAR_SERIAL.begin(115200);
}

void Intercom::SendMessage(const char* message) {
    _Stream.print(message);
    _Stream.write('\n');
    Console::trace("Intercom") << ">" << std::string(message) << Console::endl;
}

bool hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

void Intercom::Update() {
    while(_Stream.available()) {
        _lastStream = millis();
        char message[256];
        int messageSize = _Stream.readBytesUntil('\n', message, sizeof(message) - 1);
        message[messageSize] = '\0';

        Console::trace("Intercom") << "<" << message << Console::endl;
        if (strcmp(message, "ping") == 0) {
            OnPingReceived();
        }else if (strcmp(message, "pong") == 0) {
            OnPongReceived();
        }else if ( hasEnding(std::string(message), ";")) {
            OnCommand(message);
        }
    }

    if(millis() - _lastPing > 500 && (!_connected || (_connected && millis() - _lastStream > 2000))){
        SendMessage("ping");
        _lastPing = millis();
    }
    if(_connected && millis() - _lastStream > 4000){
        OnConnectionLost();
    }
}

void Intercom::OnPingReceived() {
    SendMessage("pong");
}

void Intercom::OnPongReceived() {
    if(!_connected) _connected = true;
}

void Intercom::OnConnectionLost() {
    Console::trace("Intercom") << "Connection lost." << Console::endl;
    _connected = false;
}

void Intercom::OnConnectionSuccess(){
    Console::trace("Intercom") << "Connection successful." << Console::endl;
    _connected = true;
}

void Intercom::OnCommand(std::string command){
    Console::trace("Intercom") << "Command received " << command << Console::endl;
    _pendingCommand.push(command.substr(0, command.find_last_of(";")));
}

bool Intercom::HasPendingCommand(){
    return _pendingCommand.size() != 0;
}

std::string Intercom::UnstackCommand(){
    if(HasPendingCommand()){
        std::string command = _pendingCommand.top();
        _pendingCommand.pop();
        return command;
    }else return "";
}