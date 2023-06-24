#ifndef Compass_h
#define Compass_h

// #include "Arduino.h"

#include <JY901.h>
#include "ArduPID.h"

class Compass
{
private:
    double mapF(long x, long in_min, long in_max, long out_min, long out_max);

    double input;
    double output;
    double Bias = 255;

public:
    typedef struct
    {
        short min; // Initialize the minimum value with a large number
        short max; // Initialize the maximum value with zero
    } Value;

    Value value; // value consructor

    Compass();
    ~Compass();

    int Vnord = 0;

    void Begin();
    int GetNord(void);
    void _tare(unsigned int _duration);
    void setNord();
    void setForcedNord();
    int GetAngle();
    int GetAngleRAW(void);
    int GetAllAngleRAW(bool _prop, int _axis);
    //int CorrectDir();
    int Correct();
};

#endif