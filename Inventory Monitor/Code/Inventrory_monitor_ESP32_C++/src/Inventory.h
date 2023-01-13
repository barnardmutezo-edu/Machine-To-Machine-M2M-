#ifndef Inventory_H
#define Inventory_H
#include <Arduino.h>
#include "Beverage.h"
#include "ArrayList.h"
class Inventory
{
public:
    explicit Inventory() = default;
    ~Inventory();
    void addBeverage(Beverage *beverage);
    const ArrayList<Beverage *> *getBeverages() const;
    const ArrayList<Beverage *> *getSoldBeverages() const;
    void checkOut(Beverage *beverage);
    uint16_t &getSize();
    const int & getProfit() ;

private:
    ArrayList<Beverage *> beverages;
    ArrayList<Beverage *> soldBeverages;
    uint16_t size;
    int profit;
};

#endif // Inventory_H
