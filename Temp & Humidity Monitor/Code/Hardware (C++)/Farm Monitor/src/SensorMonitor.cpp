#include "SensorMonitor.h"
#include <Adafruit_Sensor.h>
#include <SD.h>
#include <ETH.h>
#include <Update.h>
#include <SPIFFS.h>

SensorMonitor::SensorMonitor(const uint8_t &&DHTPIN, const uint8_t &DHTTYPE, const uint8_t &&alarmPin)
{
    _DHTPIN = DHTPIN;
    _DHTTYPE = DHTTYPE;
    _alarmPin = alarmPin;
    _dht = new DHT(_DHTPIN, _DHTTYPE);
    pinMode(_alarmPin, OUTPUT);
}

SensorMonitor::~SensorMonitor()
{
    delete _dht;
}

void SensorMonitor::setup()
{
    _dht->begin();
}

float SensorMonitor::readTemperature()
{
    return _dht->readTemperature();
}

float SensorMonitor::readHumidity()
{
    return _dht->readHumidity();
}

void SensorMonitor::activateAlarm(unsigned long &start)
{

    if (millis() - start > 1000)
    {
        start = millis();
        digitalWrite(_alarmPin, HIGH); // turn buzzer on
    }

    if (millis() - start > 1000)
    {
        start = millis();
        deactivateAlarm();// turn buzzer off
    }
}

void SensorMonitor::deactivateAlarm()
{
    digitalWrite(_alarmPin, LOW);
}