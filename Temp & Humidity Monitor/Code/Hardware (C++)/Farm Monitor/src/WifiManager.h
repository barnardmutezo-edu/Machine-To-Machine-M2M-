#ifndef WifiManager_H
#define WifiManager_H
#include <Arduino.h>
class WifiManager
{
public:
    explicit WifiManager() = default;
    void setup(const char * WIFI_SSID, const char * WIFI_PASSWORD);
    bool isReady();
};
#endif // WifiManager_H
