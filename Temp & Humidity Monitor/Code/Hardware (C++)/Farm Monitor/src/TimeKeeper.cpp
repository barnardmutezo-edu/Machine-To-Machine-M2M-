#include "TimeKeeper.h"
#include "time.h"

TimeKeeper::TimeKeeper(char *ntpServer, long &&gmtOffsetSec, int &&daylightOffsetSec)
{
    _ntpServer = ntpServer;
    _gmtOffset_sec = gmtOffsetSec;
    _daylightOffset_sec = daylightOffsetSec;
}

void TimeKeeper::setup()
{
    configTime(_gmtOffset_sec, _daylightOffset_sec, _ntpServer);
}

char * TimeKeeper::getTimeStamp()
{
    time_t rawtime;
    struct tm timeinfo;
    while (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
    }
    char timeStringBuff[50]; 
    strftime(timeStringBuff, sizeof(timeStringBuff), "%d %B %Y %H:%M", &timeinfo);
    return timeStringBuff;
}
