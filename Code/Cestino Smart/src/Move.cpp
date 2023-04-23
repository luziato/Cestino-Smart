// #include "Arduino.h"  //RDA: Non ricordo se è necessario inserirlo tutte le volte
#include "Move.h"

Move::Move()
{
    _mNorth.begin(NORTH_DIR1, NORTH_DIR2, NORTH_ENABLE);
    _mEast.begin(EAST_DIR1, EAST_DIR2, EAST_ENABLE);
    _mSouth.begin(SOUTH_DIR1, SOUTH_DIR2, SOUTH_ENABLE);
    _mWest.begin(WEST_DIR1, WEST_DIR2, WEST_ENABLE);
}

Move::~Move() {}

void Move::Dir(int dir, int speed, int time, unsigned long now)
{

    if (time > 10000000) // TIME GUARD: Robot cannot (and has no need to) run a command for more than 10sec for safety
    {
        time = 10000000;
    }

    /*Setting time variable*/
    _time.EndMicros = now + time;

    switch (dir)
    {
    case North:
        if (!_time.Running) // If running is true ther's no need to set the motors again
        {
            _mNorth.moving(0, speed);
            _mEast.moving(2, speed);
            _mSouth.moving(0, speed);
            _mWest.moving(1, speed);
            _time.Running = true;
        }
        break;

    case NorthEast:
        if (!_time.Running)
        {
            _mNorth.moving(1, speed);
            _mEast.moving(2, speed);
            _mSouth.moving(2, speed);
            _mWest.moving(1, speed);
            _time.Running = true;
        }
        break;

    case East:
        if (!_time.Running)
        {
            _mNorth.moving(1, speed);
            _mEast.moving(0, speed);
            _mSouth.moving(2, speed);
            _mWest.moving(0, speed);
            _time.Running = true;
        }
        break;

    case SouthEast:
        if (!_time.Running)
        {
            _mNorth.moving(1, speed);
            _mEast.moving(1, speed);
            _mSouth.moving(2, speed);
            _mWest.moving(2, speed);
            _time.Running = true;
        }
        break;

    case South:
        if (!_time.Running)
        {
            _mNorth.moving(0, speed);
            _mEast.moving(1, speed);
            _mSouth.moving(0, speed);
            _mWest.moving(2, speed);
            _time.Running = true;
        }
        break;

    case SouthWest:
        if (!_time.Running)
        {
            _mNorth.moving(2, speed);
            _mEast.moving(1, speed);
            _mSouth.moving(1, speed);
            _mWest.moving(2, speed);
            _time.Running = true;
        }
        break;

    case West:
        if (!_time.Running)
        {
            _mNorth.moving(2, speed);
            _mEast.moving(0, speed);
            _mSouth.moving(1, speed);
            _mWest.moving(0, speed);
            _time.Running = true;
        }
        break;

    case NorthWest:
        if (!_time.Running)
        {
            _mNorth.moving(2, speed);
            _mEast.moving(2, speed);
            _mSouth.moving(1, speed);
            _mWest.moving(1, speed);
            _time.Running = true;
        }
        break;

    default:
        _mNorth.moving(0, speed);
        _mEast.moving(0, speed);
        _mSouth.moving(0, speed);
        _mWest.moving(0, speed);
        _time.Running = false;

        break;
    }

    if (_time.EndMicros >= micros()) // checking if the motor need to stop (freeWheel)
    {
        _time.Running = false;

        _mNorth.moving(0, speed);
        _mEast.moving(0, speed);
        _mSouth.moving(0, speed);
        _mWest.moving(0, speed);
    }
}
