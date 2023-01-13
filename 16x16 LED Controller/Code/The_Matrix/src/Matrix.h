#ifndef Matrix_H
#define Matrix_H
#include "Arduino.h"
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include "Sensor.h"
#include <vector>

class Matrix
{
public:
    explicit Matrix(const int &&W, const int &&H, const uint8_t &&pinNumber, LDRSensor *ldr);
    void scroll(const String &text, const int &&scrollSpeed);
    void turnoff();
    ~Matrix();

private:
    std::vector<uint16_t> colors;
    Adafruit_NeoMatrix *matrix;
    int x;
    uint8_t pass;
    LDRSensor *m_ldr;
    const uint8_t getBrightness(uint8_t &&value);
};
#endif // Matrix_H
