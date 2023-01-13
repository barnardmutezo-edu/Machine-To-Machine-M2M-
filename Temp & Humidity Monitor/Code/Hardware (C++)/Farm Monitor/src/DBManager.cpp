#include "DBManager.h"
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

void DBManager::setup(const char *API_KEY, const char *USER_EMAIL, const char *USER_PASSWORD, const char *DATABASE_URL)
{
    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
    config.api_key = API_KEY;
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;
    config.database_url = DATABASE_URL;
    config.token_status_callback = tokenStatusCallback;

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
    Firebase.setDoubleDigits(5);
}

void DBManager::update(const char *path, const uint8_t &value)
{
    Firebase.setInt(fbdo, path, value);
}
void DBManager::update(const char *path, const int8_t &value)
{
    Firebase.setInt(fbdo, path, value);
}

void DBManager::update(const char *path, bool value)
{
    Firebase.setBool(fbdo, path, value);
}
bool DBManager::isReady()
{
    return Firebase.ready();
}

void DBManager::updateHistory(const char *path, const Props * props)
{
    Serial.println(*props->timeStamp);
    String pathConcat = path;
    pathConcat.concat("/" + *props->timeStamp);
    Serial.println(pathConcat);
    json.add("temperature", *props->avgTemperature);
    json.add("humidity", *props->avgHumidity);
    Firebase.setJSON(fbdo, pathConcat, json);
}

DynamicJsonDocument DBManager::getStates(const char *path)
{
    DynamicJsonDocument doc(1024);
    Firebase.RTDB.getJSON(&fbdo, path);
    deserializeJson(doc, fbdo.jsonString());
    return doc;
}