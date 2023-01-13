#include <Arduino.h>
#include "Props.h"

Props::Props(){
avgTemperature = new float;
avgHumidity = new float;
timeStamp = new char;
}

Props::~Props(){
    delete avgTemperature;
    delete avgHumidity; 
    delete timeStamp; 
}
