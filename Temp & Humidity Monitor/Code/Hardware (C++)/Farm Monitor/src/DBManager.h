#ifndef DBManager_H
#define DBManager_H
#include <Arduino.h>
#include <FirebaseESP32.h>
#include <ArduinoJson.h>
#include "Props.h"

class DBManager
{
private:
    FirebaseData fbdo;
    FirebaseAuth auth;
    FirebaseConfig config;
    FirebaseJson json;
public:
    explicit DBManager() = default;
    void setup(const char *API_KEY, const char *USER_EMAIL, const char *USER_PASSWORD, const char *DATABASE_URL);
    void update(const char *path, const uint8_t &value); // Updates the humidity
    void update(const char *path, const int8_t &value); // Updates the temperature
    void update(const char *path, bool value); // updates whether or not the alarm is active
    DynamicJsonDocument getStates(const char *path);// returns the current state if user interact with the database
    void updateHistory(const char *path, const Props * props);
    bool isReady();
};
#endif // DBManager_H
