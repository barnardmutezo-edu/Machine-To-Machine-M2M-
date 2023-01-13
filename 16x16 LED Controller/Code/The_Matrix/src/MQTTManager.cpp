#include "MQTTManager.h"
MQTTManager::MQTTManager(MQTTConfig const &mqttConfig)
{
    m_mqttConfig = mqttConfig;
}

void MQTTManager::setup(WiFiClient &espClient)
{
    client = new PubSubClient(espClient);
    client->setServer(m_mqttConfig.m_BROKER, m_mqttConfig.m_PORT);
    client->setCallback(callback);
}
void MQTTManager::reconnect()
{
    Serial.println("In reconnect");
    while (!client->connected())
    {
        if (client->connect(m_mqttConfig.m_BROKER, m_mqttConfig.m_BROKER_USER, m_mqttConfig.m_BROKER_PASS))
        {
            Serial.println("Connected");
            client->subscribe(m_mqttConfig.m_SUB_TOPIC);
        }
        else
        {
            Serial.println("reconnecting");
            delay(5000);
        }
    }
}

void MQTTManager::loop()
{
    if (!client->connected())
    {
        reconnect();
    }

    client->loop();
}

void MQTTManager::callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message receaved: ");
    Serial.println(topic);
    DynamicJsonDocument doc(250);
    deserializeJson(doc, payload, length);
    data = doc["msg"].as<String>();
}

const bool MQTTManager::hasData() const
{
    return !data.isEmpty();
}

const String &MQTTManager::getData() const
{
    return data;
}
void MQTTManager::sendData(const DynamicJsonDocument &doc)
{

    char output[250];
    serializeJson(doc, output);
    client->publish("matrix/sub", output);
    Serial.println("Send data! ");
}

MQTTManager::~MQTTManager()
{
    client->disconnect();
    delete client;
}
