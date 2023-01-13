#ifndef Beverage_H
#define Beverage_H
#include <Arduino.h>

class Beverage
{
public:
    explicit Beverage(String &&name, u_int8_t &&price);
    String getName();
    u_int8_t getPrice();
private:
    String m_name;
    u_int8_t m_price;
};

#endif // Beverage_H
