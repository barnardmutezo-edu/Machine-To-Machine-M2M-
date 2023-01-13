#include "credentials.h"
#include "DBManager.h"
#include "WifiManager.h"
#include "SensorMonitor.h"
#include "TimeKeeper.h"
#include "Props.h"
#include <ArduinoJson.h>

// Paths to the different properties
const char *root = "/monitors/Stovner";
const char *allSensorPath = strcat(root,"/sensors");
const char *temperaturePath = strcat(root, "/sensors/temperature");
const char *humidityPath = strcat(root,"/sensors/humidity");
const char *alarmPath = strcat(root,"/sensors/alarm/alarmIsActive");
const char *historyPath = "/monitors/Stovner/history";
bool alreadySet = false;
int8_t temperature;
uint8_t humidity;
int32_t allTemperatures;
uint32_t allHumidities;
unsigned long prevCalculatedAVG = 0;
WifiManager wifiManager;
unsigned long prevSensorUpdateMillis = 0;
DBManager database;
float avgTempPerHour = 0;
float avgHumidityPerHour = 0;
bool alarmIsActive = false;
SensorMonitor sensorManager(5, DHT11, 18);
char ntpServer[] = "pool.ntp.org";
TimeKeeper timekeeper(ntpServer, 3600, 3600);
bool tempporalyDisable = false;
unsigned long prevTempDissablemillis = 0;
unsigned long secondsToMillis(const uint8_t &&seconds);
unsigned long minutesToMillis(const uint8_t &&minutes);
unsigned long hoursToMillis(const uint8_t &&hours);
void readSensors();
Props *props;
Props *initProps( Props*props );

void reset();
void setup()
{
  Serial.begin(115200);
  wifiManager.setup(WIFI_SSID, WIFI_PASSWORD);
  database.setup(API_KEY, USER_EMAIL, USER_PASSWORD, DATABASE_URL);
  sensorManager.setup();
  timekeeper.setup();
}

void loop()
{
  readSensors();
}

void readSensors()
{

  if (millis() - prevSensorUpdateMillis > secondsToMillis(1) || prevSensorUpdateMillis == 0) // Update after boot
  {
    prevSensorUpdateMillis = millis();
    int8_t currentTemp = sensorManager.readTemperature();
    uint8_t currentHumidity = sensorManager.readHumidity();

    if (isnan(humidity) || isnan(temperature))
    {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    // Only update the database when the values are unique
    if (currentTemp != temperature)
    {
      temperature = currentTemp;
      database.update(temperaturePath, temperature);
    }
    if (currentHumidity != humidity)
    {
      humidity = currentHumidity;
      database.update(humidityPath, humidity);
    }

    // temperature = -1;

    if (temperature < 0)
    {

      // Default when the alarm is triggered
      if (!tempporalyDisable)
      {
        prevTempDissablemillis = millis();
        database.update(alarmPath, true);
        Serial.println("Activating alarm");
        sensorManager.activateAlarm(prevTempDissablemillis);
        auto json = database.getStates(allSensorPath); // Get the state needed to evaulate if user wants to disable the alarm or not
        alarmIsActive = json["alarm"]["isActive"].as<bool>();
      }

      if (!alarmIsActive) // if the user presses the button to disable the alarm, temporaly switch it off for 10 min
      {
        tempporalyDisable = true;
        sensorManager.deactivateAlarm();
        Serial.println("temporaly dissabling the alarm");
      }

      if (millis() - prevTempDissablemillis > minutesToMillis(10) && tempporalyDisable)
      {
        prevTempDissablemillis = millis();
        tempporalyDisable = false;
      }
    }

    allTemperatures += temperature;
    allHumidities += humidity;

    /* Serial.print("Humidity: ");
     Serial.print(humidity);
     Serial.print(" %\t");
     Serial.print("Temperature: ");
     Serial.print(temperature);
     Serial.println(" *C ");*/
  }

  if (millis() - prevCalculatedAVG > hoursToMillis(1))
  {

    prevCalculatedAVG = millis();
    Serial.println("updatting the avg!");

    Serial.print("allTemperatures: ");
    Serial.println(allTemperatures);

    Serial.print("allHumidities: ");
    Serial.println(allHumidities);

    // calculating the avg per hour
     avgTempPerHour = allTemperatures / 3600;
     avgHumidityPerHour = allHumidities / 3600;

    Serial.print("Average temp last hour: ");
    Serial.println(avgTempPerHour);
    Serial.print("Average humidity last hour: ");
    Serial.println(avgHumidityPerHour);

    // Sets the avarage temp/humidty from the past hour to the database.
    props = initProps(props); 
    database.updateHistory(historyPath, props);
    // Reset for next calulation
    reset();
  }
}

Props * initProps(Props*props){
  props = new Props();
  props->avgTemperature = &avgTempPerHour;
  props->avgHumidity = &avgHumidityPerHour;
  props->timeStamp = timekeeper.getTimeStamp();
  return props;
}

void reset(){
  allTemperatures = 0;
  allHumidities = 0;
  delete props;
}

// Simple helper functions.
unsigned long secondsToMillis(const uint8_t &&seconds)
{
  return seconds * 1000;
}
unsigned long minutesToMillis(const uint8_t &&minutes)
{
  return minutes * secondsToMillis(60);
}
unsigned long hoursToMillis(const uint8_t &&hours)
{
  return hours * minutesToMillis(60);
}