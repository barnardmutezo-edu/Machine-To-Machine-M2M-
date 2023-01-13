#include "WifiManager.h"
#include <WiFiClientSecure.h>

void WifiManager::setup(const char * WIFI_SSID, const char * WIFI_PASSWORD)
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();
}