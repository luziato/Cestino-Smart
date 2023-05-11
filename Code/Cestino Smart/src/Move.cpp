#include "Move.h"

/*********DEBUGGER************/
#include "debug.h"
/*****************************/

Move::Move()
{
    _mNorth.begin(NORTH_DIR1, NORTH_DIR2, NORTH_ENABLE);
    _mEast.begin(EAST_DIR1, EAST_DIR2, EAST_ENABLE);
    _mSouth.begin(SOUTH_DIR1, SOUTH_DIR2, SOUTH_ENABLE);
    _mWest.begin(WEST_DIR1, WEST_DIR2, WEST_ENABLE);
}

Move::~Move() {}

void Move::KILL()
{
    _mNorth.moving(0, 0);
    _mEast.moving(0, 0);
    _mSouth.moving(0, 0);
    _mWest.moving(0, 0);
}

void Move::Brake()
{
    _mNorth.moving(3, 255);
    _mEast.moving(3, 255);
    _mSouth.moving(3, 255);
    _mWest.moving(3, 255);
    delay(100);
    _mNorth.moving(0, 0);
    _mEast.moving(0, 0);
    _mSouth.moving(0, 0);
    _mWest.moving(0, 0);
}

void Move::Dir(int dir, int speed, unsigned long time, unsigned long now)
{

    debM1("Dir: ");
    debM1(dir);
    debM1(" S: ");
    debM1(speed);
    debM1(" T: ");
    debM1(time);
    debM1(" micros: ");
    debM1(now);
    deblnM1(" .");

    if (time > 10000000) // TIME GUARD: Robot cannot (and has no need to) run a command for more than 10sec for safety
    {
        time = 10000000;
    }

    if (dir != 0)
    {
        _time.Running = false;
    }

    switch (dir)
    {
    case North:
        if (!_time.Running) // If running is true ther's no need to set the motors again
        {
            _mNorth.moving(0, speed);
            _mEast.moving(2, speed);
            _mSouth.moving(0, speed);
            _mWest.moving(1, speed);
            _time.EndMicros = now + time;
            _time.Running = true;
            deblnM("North");
        }
        break;

    case NorthEast:
        if (!_time.Running)
        {
            _mNorth.moving(1, speed);
            _mEast.moving(2, speed);
            _mSouth.moving(2, speed);
            _mWest.moving(1, speed);
            _time.EndMicros = now + time;
            _time.Running = true;
            deblnM("NorthEast");
        }
        break;

    case East:
        if (!_time.Running)
        {
            _mNorth.moving(1, speed);
            _mEast.moving(0, speed);
            _mSouth.moving(2, speed);
            _mWest.moving(0, speed);
            _time.EndMicros = now + time;
            _time.Running = true;
            deblnM("East");
        }
        break;

    case SouthEast:
        if (!_time.Running)
        {
            _mNorth.moving(1, speed);
            _mEast.moving(1, speed);
            _mSouth.moving(2, speed);
            _mWest.moving(2, speed);
            _time.EndMicros = now + time;
            _time.Running = true;
            deblnM("SouthEast");
        }
        break;

    case South:
        if (!_time.Running)
        {
            _mNorth.moving(0, speed);
            _mEast.moving(1, speed);
            _mSouth.moving(0, speed);
            _mWest.moving(2, speed);
            _time.EndMicros = now + time;
            _time.Running = true;
            deblnM("South");
        }
        break;

    case SouthWest:
        if (!_time.Running)
        {
            _mNorth.moving(2, speed);
            _mEast.moving(1, speed);
            _mSouth.moving(1, speed);
            _mWest.moving(2, speed);
            _time.EndMicros = now + time;
            _time.Running = true;
            deblnM("SouthWest");
        }
        break;

    case West:
        if (!_time.Running)
        {
            _mNorth.moving(2, speed);
            _mEast.moving(0, speed);
            _mSouth.moving(1, speed);
            _mWest.moving(0, speed);
            _time.EndMicros = now + time;
            _time.Running = true;
            deblnM("West");
        }
        break;

    case NorthWest:
        if (!_time.Running)
        {
            _mNorth.moving(2, speed);
            _mEast.moving(2, speed);
            _mSouth.moving(1, speed);
            _mWest.moving(1, speed);
            _time.EndMicros = now + time;
            _time.Running = true;
            deblnM("NorthWest");
        }
        break;

        case STOP:
        if (!_time.Running)
        {
            deblnM("stop mot");
            _time.Running = false;
            _mNorth.moving(0, 0);
            _mEast.moving(0, 0);
            _mSouth.moving(0, 0);
            _mWest.moving(0, 0);
        }
        break;

    case Square:
        if (!_time.Running)
        {
            time = 1000;
            _mNorth.moving(1, speed);
            _mEast.moving(0, speed);
            _mSouth.moving(2, speed);
            _mWest.moving(0, speed);
            deblnM("East");
            delay(time);
            Brake();
            _mNorth.moving(0, speed);
            _mEast.moving(1, speed);
            _mSouth.moving(0, speed);
            _mWest.moving(2, speed);
            deblnM("South");
            delay(time);
            Brake();
            _mNorth.moving(2, speed);
            _mEast.moving(0, speed);
            _mSouth.moving(1, speed);
            _mWest.moving(0, speed);
            deblnM("West");
            delay(time);
            Brake();
            _mNorth.moving(0, speed);
            _mEast.moving(2, speed);
            _mSouth.moving(0, speed);
            _mWest.moving(1, speed);
            deblnM("North");
            delay(time);
            Brake();
        }
        break;

    case Hexagon:
        if (!_time.Running)
        {
            time = 500;
            _mNorth.moving(0, speed);
            _mEast.moving(2, speed);
            _mSouth.moving(0, speed);
            _mWest.moving(1, speed);
            deblnM("North");
            delay(time);
            Brake();
            _mNorth.moving(1, speed);
            _mEast.moving(2, speed);
            _mSouth.moving(2, speed);
            _mWest.moving(1, speed);
            deblnM("NorthEast");
            delay(time);
            Brake();
            _mNorth.moving(1, speed);
            _mEast.moving(0, speed);
            _mSouth.moving(2, speed);
            _mWest.moving(0, speed);
            deblnM("East");
            delay(time);
            Brake();
            _mNorth.moving(1, speed);
            _mEast.moving(1, speed);
            _mSouth.moving(2, speed);
            _mWest.moving(2, speed);
            deblnM("SouthEast");
            delay(time);
            Brake();
            _mNorth.moving(0, speed);
            _mEast.moving(1, speed);
            _mSouth.moving(0, speed);
            _mWest.moving(2, speed);
            deblnM("South");
            delay(time);
            Brake();
            _mNorth.moving(2, speed);
            _mEast.moving(1, speed);
            _mSouth.moving(1, speed);
            _mWest.moving(2, speed);
            deblnM("SouthWest");
            delay(time);
            Brake();
            _mNorth.moving(2, speed);
            _mEast.moving(0, speed);
            _mSouth.moving(1, speed);
            _mWest.moving(0, speed);
            deblnM("West");
            delay(time);
            Brake();
            _mNorth.moving(2, speed);
            _mEast.moving(2, speed);
            _mSouth.moving(1, speed);
            _mWest.moving(1, speed);
            deblnM("NorthWest");
            delay(time);
            Brake();
        }
        break;

    case Cross:
        if (!_time.Running)
        {
            time = 800;
            _mNorth.moving(0, speed);
            _mEast.moving(2, speed);
            _mSouth.moving(0, speed);
            _mWest.moving(1, speed);
            deblnM("North");
            delay(time);
            Brake();
            _mNorth.moving(0, speed);
            _mEast.moving(1, speed);
            _mSouth.moving(0, speed);
            _mWest.moving(2, speed);
            deblnM("South * 2");
            delay(time * 2);
            Brake();
            _mNorth.moving(0, speed);
            _mEast.moving(2, speed);
            _mSouth.moving(0, speed);
            _mWest.moving(1, speed);
            deblnM("North");
            delay(time);
            Brake();

            _mNorth.moving(1, speed);
            _mEast.moving(0, speed);
            _mSouth.moving(2, speed);
            _mWest.moving(0, speed);
            deblnM("East");
            delay(time);
            Brake();
            _mNorth.moving(2, speed);
            _mEast.moving(0, speed);
            _mSouth.moving(1, speed);
            _mWest.moving(0, speed);
            deblnM("West * 2");
            delay(time * 2);
            Brake();
            _mNorth.moving(1, speed);
            _mEast.moving(0, speed);
            _mSouth.moving(2, speed);
            _mWest.moving(0, speed);
            deblnM("East");
            delay(time);
            Brake();
        }
        break;

    default:
        // deblnM(_time[nmot].Running); deblnM( _time[nmot].EndMicros < micros());
        if (_time.Running && _time.EndMicros < micros()) // checking if the motor need to stop (freeWheel)
        {
            deblnM("stop mot");
            _time.Running = false;
            _mNorth.moving(0, 0);
            _mEast.moving(0, 0);
            _mSouth.moving(0, 0);
            _mWest.moving(0, 0);
        }
        break;
    }
}
