#ifndef WIFI
#define WIFI

#include <ESP8266WiFi.h>
#include <ArduinoJson.h

class Wifi
{

private:
    char *_ssid;
    char *_pass;
    int numberOfNetworks = 0;
    IPAddress _ip;

    void searchWifi();

public:
    Wifi(char *ssid, char *pass);

    void connect();
};

#endif