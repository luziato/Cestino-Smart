#ifndef Compass_h
#define Compass_h

// #include "Arduino.h"

#include <JY901.h>




class Compass
{
public:
    typedef struct
    {
        int min; // Initialize the minimum value with a large number
        int max; // Initialize the maximum value with zero
    } Value;

    
    Value value; // value consructor

    Compass();
    ~Compass();

    int Vnord = 0;

    void Begin();
    int GetAngleNord(void);
    void _tare(unsigned int _duration);
    void setNord();
    int GetAngle(void);
};

#endif