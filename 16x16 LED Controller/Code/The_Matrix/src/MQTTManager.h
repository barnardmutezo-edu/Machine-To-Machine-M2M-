#ifndef MQTTManager_H
#define MQTTManager_H
#include "Arduino.h"
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <ArduinoOTA.h>
#include "ConfManager.h"
class MQTTManager
{
public:
    MQTTManager(MQTTConfig const &m_mqttConfig);
    ~MQTTManager();
    void setup(WiFiClient &espClient);
    const bool hasData() const;
    const String &getData() const;
    void sendData(const DynamicJsonDocument & doc);
    void loop();

private:
    PubSubClient *client;
    void reconnect();
    static void callback(char *topic, byte *payload, unsigned int length);
    inline static String data;
    MQTTConfig m_mqttConfig;
    void setupWiFi();
};
#endif // MQTTManager_H
