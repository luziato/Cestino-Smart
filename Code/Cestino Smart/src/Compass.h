#ifndef Compass_h
#define Compass_h

// #include "Arduino.h"

#include <JY901.h>

class Compass
{
private:
    int _Vnord = 0;

    typedef struct
    {
        int min; // Initialize the minimum value with a large number
        int max; // Initialize the maximum value with zero
    } _Value;

    _Value _value; // _value consructor

public:
    Compass();
    ~Compass();

    void Begin();
    int GetAngle(bool isTaring);
    void _tare(unsigned int _duration);
    void setNord();
    void Angle_Correction();
};

#endif