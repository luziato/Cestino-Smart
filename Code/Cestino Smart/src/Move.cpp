#include "Move.h"
#include "_UDP.h"

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
    //uint8_t buflog[30];

   // _dir = Angle_Correction(dir);

    if (dir != 0)
    {
        //sprintf((char *)buflog, "%d,%d\n", dir, _dir);
        //UDP_sendPaket(30000, UDP_MESSAGE, buflog, strlen((char *)buflog));
    }

    debM1("Dir: ");
    debM1(dir);
    debM1(" S: ");
    debM1(speed);
    debM1(" T: ");
    debM1(time);
    debM1(" micros: ");
    debM1(now);
    deblnM1(" .");

    _time.time = time;

    if (_time.time > 5000000) // TIME GUARD: Robot cannot (and has no need to) run a command for more than 10sec for safety
    {
        _time.time = 5000000;
    }

    if (_dir != 0)
    {
        _time.Running = false;
    }

    /*    _time.oldTime = _time.time;

        _time.EndMicros = micros() + _time.time;
        _time.time = 0;
        deblnM(_time.EndMicros);
    */

    switch (_dir)
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
            _dir = 0;
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

    case Freewheel:
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

    case CW:
        if (!_time.Running) // If running is true ther's no need to set the motors again
        {
            _mNorth.moving(2, speed);
            _mEast.moving(1, speed);
            _mSouth.moving(2, speed);
            _mWest.moving(1, speed);
            _time.EndMicros = now + time;
            _time.Running = true;
            deblnM("Rotating CW");
        }
        break;

    case CCW:
        if (!_time.Running) // If running is true ther's no need to set the motors again
        {
            _mNorth.moving(2, speed);
            _mEast.moving(2, speed);
            _mSouth.moving(2, speed);
            _mWest.moving(2, speed);
            _time.EndMicros = now + time;
            _time.Running = true;
            deblnM("Rotating CcW");
        }

    case _Brake:

        _mNorth.moving(3, 255);
        _mEast.moving(3, 255);
        _mSouth.moving(3, 255);
        _mWest.moving(3, 255);
        delay(speed / 1.5);
        _mNorth.moving(0, 0);
        _mEast.moving(0, 0);
        _mSouth.moving(0, 0);
        _mWest.moving(0, 0);
        break;

    default:
        //debM(now);
        //debM(" ; end micros");
        //debM(_time.EndMicros);
        //debM(" ; ");
        //deblnM(_time.Running);
        if (_time.Running)
        {
            if (now > _time.EndMicros) // checking if the motor need to stop (freeWheel)
            {
                deblnM("stop mot");
                _time.Running = false;
                _mNorth.moving(0, 0);
                _mEast.moving(0, 0);
                _mSouth.moving(0, 0);
                _mWest.moving(0, 0);
            }
        }
        break;
    }
}

void Move::Tare(unsigned int duration)
{
    uint8_t buflog[30];

    int _nord = _bussola.GetAngleNord();
    int curangle, nloop = 0;
    Dir(CW, 180, duration + 100, millis());
    _bussola._tare(duration);
    Dir(_Brake, 255, 0, millis());

    do
    {
        Dir(CW, 180, 30, millis());

        delay(30);
        Dir(_Brake, 255, 0, millis());
        delay(100);

        curangle = _bussola.GetAngle();

        sprintf((char *)buflog, "%d,%d,%d", curangle, _nord, nloop);
        UDP_sendPaket(30000, UDP_MESSAGE, buflog, strlen((char *)buflog));
        

        if ((curangle - 4 >= _nord && curangle + 4 <= _nord) || nloop++ > 20)
            break;
    } while (1);
}

int Move::Angle_Correction(int _dir)
{
    JY901.GetAngle();

    int correctDirection = _dir + ((JY901.stcAngle.Angle[2] / 32768 * 180) / 45);
    // map(JY901.stcAngle.Angle[2]/32768*180, value.min, value.max, 1, 8);

    return correctDirection;
}
