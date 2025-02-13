#pragma once

#ifdef ESP32
#include <WiFi.h>
#elif defined ESP8266
#include <ESP8266WiFi.h>
#endif

DeclareComponentSingleton(Wifi, "wifi",)

    enum ConnectionState { Off, Connecting, Connected, ConnectionError, Disabled, Hotspot, PingAlive, PingDead, CONNECTION_STATES_MAX };
    const String connectionStateNames[CONNECTION_STATES_MAX] {"Off", "Connecting", "Connected", "ConnectionError", "Disabled", "Hotspot", "PingAlive","PingDead" };

    const long timeBetweenTries = 500; //ms
    const long connectionTimeout = 10000; //ms
    long timeAtConnect;
    long lastConnectTime;

    ConnectionState state;

    String ssid;
    String pass;

    bool initInternal() override;
    void updateInternal() override;
    void clearInternal() override;

    void connect();
    void disconnect();
    void setState(ConnectionState s);

    String getIP() const;

    DeclareEventTypes(ConnectionStateChanged);
    DeclareEventNames("ConnectionStateChanged");

EndDeclareComponent