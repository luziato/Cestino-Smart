#ifndef Motor_h
#define Motor_h

//#include "Arduino.h"

class Motor
{
private:

    int _dir1;
    int _dir2;
    int _enable;

public:

    Motor();
    ~Motor();

    void begin(int dir1, int dir2, int Enable);


    /**
     * @brief Move motor
     * 
     * @param dir 0: Freewheel 1: CW 2: CCW 3: Hard brake
     * @param pwm From 0 to 255
    */
    void moving(int dir, int pwm, int correction);
};

#endif