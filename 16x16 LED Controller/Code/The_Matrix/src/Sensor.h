#ifndef Sensor_H
#define Sensor_H
#include "Arduino.h"

// Base class for the sensors
class Sensor
{
public:
    explicit Sensor(const uint8_t &pinNumber);
    virtual uint8_t reading() const = 0;

protected:
    uint8_t m_pinNumber;
};

class LDRSensor : public Sensor
{
public:
    explicit LDRSensor(const uint8_t &pinNumber);
    uint8_t reading() const override;
};

class SonicSensor : public Sensor
{
public:
    explicit SonicSensor(const uint8_t &&trigPin, const uint8_t &&echoPin);
    uint8_t reading() const;

private:
    uint8_t m_trigPin;
};
#endif // Sensor_H
