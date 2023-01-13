#include "Matrix.h"
Matrix::Matrix(const int &&W, const int &&H, const uint8_t &&pinNumber, LDRSensor *ldr)
{
    matrix = new Adafruit_NeoMatrix(W, H, pinNumber,
                                    NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
                                        NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                                    NEO_GRB + NEO_KHZ800);
    colors = {
        matrix->Color(204, 0, 204), matrix->Color(204, 204, 0), matrix->Color(0, 255, 255),
        matrix->Color(255, 10, 127), matrix->Color(127, 0, 255), matrix->Color(0, 255, 0),
        matrix->Color(255, 99, 255)};

    matrix->begin();
    matrix->setTextWrap(false);
    matrix->setTextColor(colors[0]);
    x = matrix->width();
    pass = 0;
    m_ldr = ldr;
}

void Matrix::scroll(const String &text, const int &&scrollSpeed)
{
    auto brightness = getBrightness(m_ldr->reading());
    int scrollWidth = text.length() * 7;
    matrix->fillScreen(0);
    matrix->setCursor(x, 4);
    matrix->setBrightness(brightness);
    matrix->print(text);
    if (--x < -scrollWidth)
    {
        x = matrix->width();
        if (++pass >= 7)
            pass = 0;
        matrix->setTextColor(colors[pass]);
    }
    matrix->show();
    delay(scrollSpeed);
}
const uint8_t Matrix::getBrightness(uint8_t &&value)
{
    const uint8_t LOW_BRIGHTNESS = 1;
    const uint8_t MID_BRIGHTNESS = 25;
    const uint8_t HIGH_BRIGHTNESS = 50;

    if (value >= 0 && value < 100)
    {
        return LOW_BRIGHTNESS;
    }
    else if (value >= 100 && value < 200)
    {
        return MID_BRIGHTNESS;
    }
    return HIGH_BRIGHTNESS;
}

void Matrix::turnoff()
{
    matrix->fillScreen(0);
    matrix->setCursor(x, 4);
    matrix->setBrightness(0);
    matrix->show();
    Serial.println("Screen off!");
}

Matrix::~Matrix()
{
    delete matrix;
}
