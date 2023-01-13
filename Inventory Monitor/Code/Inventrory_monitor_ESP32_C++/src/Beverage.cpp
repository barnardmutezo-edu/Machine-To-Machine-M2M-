#include "Beverage.h"
Beverage::Beverage(String &&name, u_int8_t &&price)
{
    m_name = name;
    m_price = price;
}

String Beverage::getName()
{
    return m_name;
}

u_int8_t Beverage::getPrice()
{
    return m_price;
}