#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

class Motor
{
public:

    Motor(int dir1, int dir2, int Enable);      //  Defining pin for the motror

    void motor(int dir, int pwm);
    
private:

    int _dir1;
    int _dir2;
    int _enable;

};

#endif