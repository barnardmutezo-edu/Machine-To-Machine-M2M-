
#include <Arduino.h>
#ifndef Helpers_H
#define Helpers_H
const unsigned long secondsToMillis(const uint8_t &seconds)
{
    return seconds * 1000;
}
const unsigned long minutesToMillis(const uint8_t &minutes)
{
    return minutes * secondsToMillis(60);
}
const unsigned long hoursToMillis(const uint8_t &hours)
{
    return hours * minutesToMillis(60);
}
#endif // Helpers_H