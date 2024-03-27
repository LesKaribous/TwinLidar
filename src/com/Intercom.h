#pragma once
#include <Arduino.h>
#include <deque>
//Slave class
//TODO Unify the Intercom library

struct Request{
    u_int32_t id;
    String content;
    String payload;
};


class Intercom {
public:
    Intercom();
    
    void Initialize();
    void Update();
    void SendMessage(String string);

    void Reply(Request& req, String answer);

    void OnPingReceived();
    void OnConnectionSuccess();
    void OnConnectionLost();

    bool HasPendingRequest();
    Request UnstackRequest();
    void OnRequest(const String& payload);

    inline bool IsConnected(){return _connected;}

private:
    Stream& _stream;

    std::deque<Request> _pendingRequest;

    long _lastStream = 0;
    long _lastPing = 0;
    bool _connected = false;

    void ProcessIncomingData();
};

