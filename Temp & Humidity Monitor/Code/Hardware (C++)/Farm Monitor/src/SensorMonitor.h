#ifndef SensorMonitor_H
#define SensorMonitor_H
#include <Arduino.h>
#include "DHT.h"

class SensorMonitor
{

private:
    uint8_t _DHTPIN;
    uint8_t _DHTTYPE;
    uint8_t _alarmPin;
    DHT *_dht;

public:
    explicit SensorMonitor(const uint8_t &&DHTPIN, const uint8_t &DHTTYPE, const uint8_t &&alarmPin);
    ~SensorMonitor();
    void setup();
    float readTemperature();
    float readHumidity();
    void activateAlarm(unsigned long &start);
    void deactivateAlarm();
};
#endif // SensorMonitor_H
