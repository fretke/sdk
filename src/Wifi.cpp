#include <ESP8266WiFi.h>

void Wifi::searchWifi()
{
    numberOfNetworks = 0;
    Serial.println("----");

    while (numberOfNetworks == 0)
    {
        numberOfNetworks = WiFi.scanNetworks();
        Serial.println("scanning for network...");
        delay(1000);
    }

    for (int i = 0; i < numberOfNetworks; i++)
    {
        Serial.print("Network name: ");
        Serial.println(WiFi.SSID(i));
        Serial.print("Signal strength: ");
        Serial.println(WiFi.RSSI(i));
        Serial.println("--------------");
    }
}

Wifi::Wifi(char *ssid, char *pass)
{
    _ssid = ssid;
    _pass = pass;
}

void Wifi::connect()
{
    searchWifi();
    uint32_t notConnectedCounter = 0;
    WiFi.begin(_ssid, _pass);
    delay(1000);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(1000);
        notConnectedCounter++;
        if (notConnectedCounter > 30)
        {
            Serial.println("Resetting due to Wifi not connecting...");
            ESP.restart();
        }
    }
    _ip = WiFi.localIP();
    Serial.print("");
    Serial.println("WiFi connected");
    Serial.print("IP Address : ");
    Serial.println(_ip);
}