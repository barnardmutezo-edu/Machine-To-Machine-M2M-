#include "Arduino.h"
#ifndef ConfManager_H
#define ConfManager_H
// No need for so many files..

struct WiFiConfig
{
    explicit WiFiConfig() = default;
    WiFiConfig(char const *SSID, char const *SSID_PASS);
    char const *m_SSID_PASS;
    char const *m_SSID;
};

struct MQTTConfig
{
    explicit MQTTConfig() = default;
    explicit MQTTConfig(char const *BROKER, char const *BROKER_USER, char const *BROKER_PASS, char const *CLIENT_NAME, char const *SUB_TOPIC, uint16_t &PORT);
    char const *m_BROKER;
    char const *m_BROKER_USER;
    char const *m_BROKER_PASS;
    char const *m_CLIENT_NAME;
    char const *m_SUB_TOPIC;
    uint16_t m_PORT;
};
struct FBConfig
{
    explicit FBConfig() = default;
    explicit FBConfig(const char *API_KEY, const char *USER_EMAIL, const char *USER_PASSWORD, const char *DATABASE_URL);
    char const *m_API_KEY;
    char const *m_USER_EMAIL;
    char const *m_USER_PASSWORD;
    char const *m_DATABASE_URL;
};

#endif // ConfManager_H
