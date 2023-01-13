#include "Sensor.h"
Sensor::Sensor(const uint8_t &pinNumber)
{
    m_pinNumber = pinNumber;
}

LDRSensor::LDRSensor(const uint8_t &pinNumber) : Sensor(pinNumber)
{
    pinMode(this->m_pinNumber, INPUT);
}
uint8_t LDRSensor::reading() const
{
    return (uint8_t)map(analogRead(m_pinNumber), 0, 4095, 0, 255);
}

SonicSensor::SonicSensor(const uint8_t &&trigPin, const uint8_t &&echoPin) : Sensor(echoPin)
{
    m_trigPin = trigPin;
    pinMode(m_trigPin, OUTPUT);
    pinMode(this->m_pinNumber, INPUT);
}
uint8_t SonicSensor::reading() const
{
    const float SOUND_SPEED = 0.034;
    const float CM_TO_INCH = 0.393701;
    unsigned long duration;
    uint8_t distanceCm;

    digitalWrite(m_trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(m_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(m_trigPin, LOW);

    duration = pulseIn(this->m_pinNumber, HIGH);
    distanceCm = duration * SOUND_SPEED / 2;

    return distanceCm;
}
