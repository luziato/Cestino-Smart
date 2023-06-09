#ifndef Move_h
#define Move_h // Define guard

#include "Arduino.h"
#include "const.h"
#include "Motor.h"

#define N_MAX_DIR 4

class Move
{

private:
    Motor _mNorth;
    Motor _mEast;
    Motor _mSouth;
    Motor _mWest;

    // Timer variables
    typedef struct
    {
        unsigned long EndMicros; // The calculated time at witch the motor should stop ( time + now[micros] )
        bool Running = false;    // Do I need to run the code?
        unsigned long time;      // Needed to hold time form dir func 
        unsigned long oldTime;
    } _Time;

    _Time _time; // _time constructor

    int _dir;

    enum DIR
    {
        North = 1,
        NorthEast,
        East,
        SouthEast,
        South,
        SouthWest,
        West,
        NorthWest,
        Freewheel,
        Square,
        Hexagon,
        Cross,
        CW,
        CCW,
        _Brake
    };

public:
    Move();
    ~Move();

    /**
     * @brief Sends robot to North for TIME at SPEED
     *
     * @param dir Direction of the robot in 45° increment form 0
     * @param speed Speed of the robot
     * @param time Timer to execute the command
     * @param now Time in witch the method is called
     */
    void Dir(int dir, int speed, unsigned long time, unsigned long now);

    void KILL();
    void Brake();
};

#endif