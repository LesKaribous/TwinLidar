#include "com/Intercom.h"
#include "debug/Console.h"

#define LIDAR_SERIAL Serial3

Intercom::Intercom() : _stream(LIDAR_SERIAL) {}

void Intercom::Initialize(){
    LIDAR_SERIAL.begin(115200);
}

void Intercom::SendMessage(String string) {
    _stream.print(string);
    _stream.write('\n');
    Console::trace("Intercom") << ">" << string << Console::endl;
}

void Intercom::Update() {
    if(_stream.available()) {
        _lastStream = millis();
        ProcessIncomingData();
    }

    if(millis() - _lastPing > 500 && (!_connected || (_connected && millis() - _lastStream > 2000))){
        SendMessage("ping");
        _lastPing = millis();
    }
    if(_connected && millis() - _lastStream > 4000){
        OnConnectionLost();
    }
}


void Intercom::Reply(Request& req, String answer){
    String ss = "";
    ss += req.id;
    ss += ":";
    ss += answer;
    SendMessage(ss);
}


void Intercom::OnPingReceived() {
    SendMessage("pong");
}

void Intercom::OnConnectionLost() {
    Console::trace("Intercom") << "Connection lost." << Console::endl;
    _connected = false;
}

void Intercom::OnConnectionSuccess(){
    Console::trace("Intercom") << "Connection successful." << Console::endl;
    _connected = true;
}

void Intercom::OnRequest(const String& payload){
    int separatorIndex = payload.indexOf(':');
    if (separatorIndex > 0) {
        uint32_t requestId = payload.substring(0, separatorIndex).toInt();
        String request = payload.substring(separatorIndex + 1);
        Console::trace("Intercom") << "Request[" << String(requestId).c_str() << "] received : " << payload.c_str() << Console::endl;

        Request req = {requestId, request.c_str(), payload.c_str()};
        _pendingRequest.push(req);
    }
}

void Intercom::ProcessIncomingData() {
    while (_stream.available()) {
        String incomingMessage = _stream.readStringUntil('\n');
        incomingMessage.trim(); // Remove any leading/trailing whitespace or newline characters

        if (incomingMessage.startsWith("ping")) {
            OnPingReceived();
        } else if (incomingMessage.startsWith("pong")) {
            OnConnectionSuccess();
        } else {
            int separatorIndex = incomingMessage.indexOf(':');
            if (separatorIndex > 0) {
                OnRequest(incomingMessage);
            }
        }
    }
}

bool Intercom::HasPendingRequest(){
    return _pendingRequest.size() != 0;
}

Request Intercom::UnstackRequest(){
    if(HasPendingRequest()){
       Request command = _pendingRequest.top();
        _pendingRequest.pop();
        return command;
    }
    Request bad = {0, "bad payload", "bad payload"};
    return bad;
}