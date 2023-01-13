#ifndef MyWiFi_H
#define MyWiFi_H
#include "Arduino.h"
#include "WiFiManager.h"
#include "WiFiClient.h"
#include <ArduinoOTA.h>
#include "ConfManager.h"

class MyWiFi
{
public:
    explicit MyWiFi(WiFiConfig const &wifiConfig);
    void setup();
    WiFiClient espClient;
private:
    WiFiConfig m_wifiConfig;
};
#endif // MyWiFi_H
