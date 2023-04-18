#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

class Motor
{
public:

    Motor();      //  Defining pin for the motror

    void begin(int dir1, int dir2, int Enable);

    void motor(int dir, int pwm);
    
private:

    int _dir1;
    int _dir2;
    int _enable;

};

#endif