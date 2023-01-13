#ifndef Props_H
#define Props_H
struct Props
{
   explicit Props();
   ~Props();
    float *avgTemperature;
    float *avgHumidity;
    char *timeStamp;
};
#endif // Props_H