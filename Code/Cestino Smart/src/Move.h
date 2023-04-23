#ifndef Move_h
#define Move_h      //Define guard

#include "Arduino.h"
#include "const.h"
#include "Motor.h"

#define N_MAX_DIR 4
/* #define DIR_NORD 0
#define DIR_SUD 1
#define DIR_EST 2
#define DIR_WEST 3      replaced enum        */

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
    } _Time;

    _Time _time;        // _time constructor

    enum DIR        
    {
        North,
        NorthEast,
        East,
        SouthEast,
        South,
        SouthWest,
        West,
        NorthWest
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
    void Dir(int dir, int speed, int time, unsigned long now);

    /**
     * @brief Stops all motor
     */
    //void Stop();
};

#endif