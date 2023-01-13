#include "Inventory.h"
void Inventory::addBeverage(Beverage *beverage)
{
    beverages.add(beverage);
}
const ArrayList<Beverage *> *Inventory::getBeverages() const
{
    return &beverages;
}
const ArrayList<Beverage *> *Inventory::getSoldBeverages() const
{
    return &soldBeverages;
}

void Inventory::checkOut(Beverage *beverage)
{
    soldBeverages.add(beverage);
    beverages.remove(beverage);
}

uint16_t &Inventory::getSize()
{
    size = beverages.size();
    return size;
}

const int &Inventory::getProfit()
{
    for (auto it = soldBeverages.begin(); it != soldBeverages.end(); ++it)
    {
        profit += it.operator*()->getPrice();
    }
    return profit;
}

Inventory::~Inventory()
{
    for (uint16_t i = 0; i < beverages.size(); i++)
    {
        delete beverages[i];
    }

    for (uint16_t i = 0; i < soldBeverages.size(); i++)
    {
        delete beverages[i];
    }
}
