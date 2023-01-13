#include <Arduino.h>
#include <Wifi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "AWS_CREDENTIALS.h"
#include "credentials.h"

const char *topicRecieve = "esp32/data";
const char *topicSend = "LORA/pub";

String data; // stores payload from ESP32
bool processData = false;

// todo REFACTOR TO ONE CLASS!!
WiFiClientSecure net = WiFiClientSecure();
PubSubClient awsClient(net); // Sends payload from esp32
WiFiClient espClient;
PubSubClient esp32Client(espClient); // recieves paylaod from esp32

void connectAWS();  // connects to my AWS acounts todo NEEDS REFACTORING!!
void forwardData(); // forwards the data from ESP32 to AWS
void connectAWS()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);
  awsClient.setServer(AWS_IOT_ENDPOINT, 8883);
  Serial.println("Connecting to AWS IOT");
  while (!awsClient.connect(THINGNAME))
  {
    Serial.print(".");
    delay(100);
  }

  if (!awsClient.connected())
  {
    Serial.println("AWS IoT Timeout!");
    return;
  }
  Serial.println("AWS IoT Connected!");
}

void reconnect()
{
  while (!esp32Client.connected())
  {
    Serial.print("\nConncting to ");
    Serial.println(BROKER);
    if (esp32Client.connect(BROKER_ID, BROKER_USER, BROKER_PASSWORD))
    {
      Serial.print("\nConnected to ");
      Serial.println(BROKER);
      esp32Client.subscribe(topicRecieve);
    }
    else
    {
      Serial.println("\n Trying to reconnect");
      delay(5000);
    }
  }
}

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message receaved: ");
  Serial.println(topic);

  for (uint8_t i = 0; i < length; i++)
  {
    data += (char)payload[i];
  }
  processData = true;
}

void setup()
{
  Serial.begin(9600);
  connectAWS();
  esp32Client.setServer(BROKER, 1883);
  esp32Client.setCallback(callback);
}

void loop()
{
  if (!esp32Client.connected())
  {
    reconnect();
  }

  if (processData)
  {
    forwardData();
    processData = false;
  }
  esp32Client.loop();
  awsClient.loop();
}

void forwardData()
{
  Serial.println("Forwarding to AWS");
  Serial.println(data);
  awsClient.publish(topicSend, data.c_str());
  data = ""; // cleanup
}
