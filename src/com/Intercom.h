#pragma once
#include <Arduino.h>
#include <string>
#include <stack>

class Intercom {
public:
    Intercom();
    
    void Initialize();
    void Update();
    void SendMessage(const char* message);

    void OnPingReceived();
    void OnPongReceived();
    void OnConnectionSuccess();
    void OnConnectionLost();

    bool HasPendingCommand();
    std::string UnstackCommand();
    void OnCommand(std::string command);

    inline bool IsConnected(){return _connected;}

private:
    Stream& _Stream;

    std::stack<std::string> _pendingCommand;

    long _lastStream = 0;
    long _lastPing = 0;
    bool _connected = false;
};

