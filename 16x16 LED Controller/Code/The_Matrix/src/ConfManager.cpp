#include "ConfManager.h"
WiFiConfig::WiFiConfig(char const *SSID, char const *SSID_PASS)
{
    m_SSID = SSID;
    m_SSID_PASS = SSID_PASS;
}

MQTTConfig::MQTTConfig(char const *BROKER, char const *BROKER_USER, char const *BROKER_PASS, char const *CLIENT_NAME, char const *SUB_TOPIC, uint16_t &PORT)
{
    m_BROKER = BROKER;
    m_BROKER_USER = BROKER_USER;
    m_BROKER_PASS = BROKER_PASS;
    m_CLIENT_NAME = CLIENT_NAME;
    m_SUB_TOPIC = SUB_TOPIC;
    m_PORT = PORT;
}
FBConfig::FBConfig(const char *API_KEY, const char *USER_EMAIL, const char *USER_PASSWORD, const char *DATABASE_URL)
{
    m_API_KEY = API_KEY;
    m_USER_EMAIL = USER_EMAIL;
    m_USER_PASSWORD = USER_PASSWORD;
    m_DATABASE_URL = DATABASE_URL;
}