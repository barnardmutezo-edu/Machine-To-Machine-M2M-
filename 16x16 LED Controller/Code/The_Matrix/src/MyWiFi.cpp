#include "MyWiFi.h"
MyWiFi::MyWiFi(WiFiConfig const &wifiConfig)
{
    m_wifiConfig = wifiConfig;
}
void MyWiFi::setup()
{
    Serial.println("Setting up wifi");
    WiFiManager wm;
    bool res;
    res = wm.autoConnect(m_wifiConfig.m_SSID, m_wifiConfig.m_SSID_PASS);
    if (!res)
    {
        Serial.println("Failed to connect");
    }
    else
    {
        Serial.println("connected...yeey :)");
    }
}