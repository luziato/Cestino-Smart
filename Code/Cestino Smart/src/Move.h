#ifndef Move_h
#define Move_h // Define guard

#include "Arduino.h"
#include "const.h"
#include "Motor.h"
#include "Compass.h"

#define N_MAX_DIR 4

class Move
{

private:
    Motor _mot1;
    Motor _mot2;
    Motor _mot3;
    Motor _mot4;

    typedef struct
    {
        int mot1 = 0;
        int mot2 = 120;
        int mot3 = -120;

    } _3MotAng;

    _3MotAng _3motAng;

    typedef struct
    {
        int mot1 = 0;
        int mot2 = 90;
        int mot3 = 180;
        int mot4 = -90;

    } _4MotAng;

    _4MotAng _4motAng;

    typedef struct // mot1 data
    {
        int dir;
        int speed;
    } MotD1;

    typedef struct // mot1 data
    {
        int dir;
        int speed;
    } MotD2;

    typedef struct // mot1 data
    {
        int dir;
        int speed;
    } MotD3;

    typedef struct // mot1 data
    {
        int dir;
        int speed;
    } MotD4;

    MotD1 motD1;
    MotD2 motD2;
    MotD3 motD3;
    MotD4 motD4;

    //******* FOR FUTURE USE*********

    short motQt = 3;          // define motor quantity to calulate each position in degrees
    short motOfset = 120 / 2; // define the ofset in degrees of the motor, not realy necessary

    //*******************************

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

    //************UTILS**********
    /**
     * @brief Map the Data value window to another window
     *
     * @param x New data to map
     * @param in_min Initial data minimum
     * @param in_max Initial data maximum
     * @param out_min New data minimum
     * @param out_max New data maximum
     */
    int Map(double x, double in_min, double in_max, double out_min, double out_max);
    double RAD(int _deg); // convert Degrees to Radiants

public:
    Move();
    ~Move();

    /**
     * @brief Sends robot to North for TIME at SPEED (4 motor config 8 direction)
     *
     * @param dir Direction of the robot in 45° increment form 0
     * @param speed Speed of the robot
     * @param time Timer to execute the command
     * @param now Time in witch the method is called (micros())
     */
    void Dir(int dir, int speed, unsigned long time, unsigned long now);

    /**
     * @brief Sends robot to North for TIME at SPEED (3 motor config)
     *
     * @param dir Direction of the robot in degrees 0-360
     * @param speed Speed of the robot 0/255
     * @param time Timer to execute the command
     * @param now Time in witch the method is called (micros())
     */
    void Dir3(int dir, int speed, unsigned long time, unsigned long now);

    /**
     * @brief Sends robot to North for TIME at SPEED (4 motor congif)
     *
     * @param dir Direction of the robot in degrees 0-360
     * @param speed Speed of the robot 0/255
     * @param time Timer to execute the command
     * @param now Time in witch the method is called (micros())
     */
    void Dir4(int dir, int speed, unsigned long time, unsigned long now);

    void KILL();
    void Brake();
    void Tare(unsigned int duration);
    void Angle_Correction();
    void test();

};

#endif