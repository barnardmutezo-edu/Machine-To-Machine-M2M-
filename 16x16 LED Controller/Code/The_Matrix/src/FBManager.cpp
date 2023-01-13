#include "FBManager.h"
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

FBManager::FBManager(FBConfig const &  fbConfig){
    m_fbConfig = fbConfig;
}

void FBManager::setup()
{
    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
    config.api_key = m_fbConfig.m_API_KEY;
    auth.user.email = m_fbConfig.m_USER_EMAIL;
    auth.user.password =m_fbConfig.m_USER_PASSWORD;
    config.database_url = m_fbConfig.m_DATABASE_URL;
    config.token_status_callback = tokenStatusCallback;
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(false);
    Firebase.setDoubleDigits(5);
}

bool FBManager::isReady()
{
    return Firebase.ready();
}

DynamicJsonDocument FBManager::getStates(const char *path)
{
    DynamicJsonDocument doc(1024);
    Firebase.RTDB.getJSON(&fbdo, path);
    deserializeJson(doc, fbdo.jsonString());
    return doc;
}