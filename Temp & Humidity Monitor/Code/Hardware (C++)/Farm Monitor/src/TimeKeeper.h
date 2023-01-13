#ifndef TimeKeeper_H
#define TimeKeeper_H
#include <Arduino.h>

class TimeKeeper
{
private:
    char *_ntpServer;
    long _gmtOffset_sec;
    int _daylightOffset_sec;
public:
    explicit TimeKeeper(char *ntpServer, long &&gmtOffsetSec, int &&daylightOffsetSec);
    char * getTimeStamp();
    void setup();
};

#endif // TimeKeeper_H
