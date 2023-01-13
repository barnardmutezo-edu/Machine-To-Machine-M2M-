#include <Arduino.h>
#include "credentials.h"
#include "Sensor.h"
#include "Matrix.h"
#include "MQTTManager.h"
#include "ConfManager.h"
#include "MyWiFI.h"
#include "FBManager.h"
#include "Helpers.h"

const uint8_t scrollSpeed = 80;
const uint8_t displayTimeSec = 10;

unsigned long duration;
auto countdown = false;

uint8_t distanceCm;
bool watched = false;
bool enableMatrix = false;
bool alreadyShowing = false;
unsigned long currentTime;
unsigned long lastTime;
unsigned long prevWatchTime;
const uint8_t motionPin = 39;
WiFiConfig wifiConfig(SSID, SSID_PASS);
MQTTConfig mqttConfig(BROKER, BROKER_USER, BROKER_PASS, CLIENT_NAME, SUB_TOPIC, PORT);
FBConfig fbConfig(API_KEY, USER_EMAIL, USER_PASSWORD, DATABASE_URL);

MyWiFi myWiFi(wifiConfig);
MQTTManager mqttManager(mqttConfig);
FBManager database(fbConfig);

String data = "Default";
LDRSensor ldrSensor(36); // Monitors the lumiosity and sets the matrix brightness accordingly
SonicSensor sonicSensor(5, 19);

Matrix matrix(16, 16, 18, &ldrSensor);

void retrieveData(); // Run only once per boot, re-treave any previous states, usefull incase of power shortage
void monitorMQTT();
void monitorMatrix();
void activateMatrix();
void monitorWatchTime();
void updateStats();
void setup()
{
    Serial.begin(115200);
    while (!Serial)
        ;
    myWiFi.setup();
    mqttManager.setup(myWiFi.espClient);
    database.setup();
    retrieveData();

    // Tried to refactor this but it become messy
    pinMode(motionPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(motionPin), activateMatrix, RISING);
}

void loop()
{
    currentTime = millis();
    monitorMQTT();
    monitorMatrix();
}

void monitorMQTT()
{
    mqttManager.loop();
    if (mqttManager.hasData() && mqttManager.getData() != data)
    {
        data = mqttManager.getData();
        Serial.println("new data");
        Serial.println(data);
    }
}

void monitorMatrix()
{
    if (enableMatrix)
    {
        alreadyShowing = true;
        monitorWatchTime();
        matrix.scroll(data, scrollSpeed);
    }

    if (enableMatrix && (currentTime - lastTime > secondsToMillis(15)))
    {
        enableMatrix = false;
        alreadyShowing = false;
        matrix.turnoff();
        updateStats();
    }
}

void activateMatrix()
{
    if (enableMatrix && alreadyShowing)
        return; // Avoiding lags
    lastTime = millis();
    enableMatrix = true;
}

void retrieveData()
{
    if (database.isReady())
    {
        Serial.println("Ready!!");
        auto json = database.getStates("latestData");
        data = json["data"].as<String>();
    }
}

void monitorWatchTime()
{
    distanceCm = sonicSensor.reading();
    if (distanceCm <= 100)
    {
        if (!countdown) // Lock the time
        {
            prevWatchTime = currentTime;
            countdown = true;
        }
    }
    else
    {
        countdown = false;
    }

    if (countdown && (currentTime - prevWatchTime >= secondsToMillis(10)))
    {
        watched = true;
        countdown = false;
        prevWatchTime = currentTime;
    }

    Serial.println(distanceCm);
}

void updateStats()
{
    Serial.println("updating state!");
    DynamicJsonDocument doc(256);
    if (watched)
    {
        watched = false;
        doc["watched"] = true;
    }
    else
    {
        doc["watched"] = false;
    }

    doc["passedBy"] = true;
    mqttManager.sendData(doc);
}