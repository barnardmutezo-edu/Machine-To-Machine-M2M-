#ifndef FBManager_H
#define FBManager_H
#include <Arduino.h>
#include <FirebaseESP32.h>
#include <ArduinoJson.h>
#include "ConfManager.h"
class FBManager
{
private:
    FirebaseData fbdo;
    FirebaseAuth auth;
    FirebaseConfig config;
    FirebaseJson json;
    FBConfig m_fbConfig;

public:
    explicit FBManager(FBConfig const & fbConfig);
    void setup();
    DynamicJsonDocument getStates(const char *path);
    bool isReady();
};
#endif // FBManager_H
