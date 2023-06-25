#include "Move.h"
#include "_UDP.h"

/*********DEBUGGER************/
#include "debug.h"
/*****************************/

extern Compass compass;

int trigger = A0;

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
    _mNorth.moving(0, 0, 0);
    _mEast.moving(0, 0, 0);
    _mSouth.moving(0, 0, 0);
    _mWest.moving(0, 0, 0);
}

void Move::Brake()
{
    _mNorth.moving(3, 255, 0);
    _mEast.moving(3, 255, 0);
    _mSouth.moving(3, 255, 0);
    _mWest.moving(3, 255, 0);
    delay(100);
    _mNorth.moving(0, 0, 0);
    _mEast.moving(0, 0, 0);
    _mSouth.moving(0, 0, 0);
    _mWest.moving(0, 0, 0);
}

void Move::Dir(int dir, int speed, unsigned long time, unsigned long now)
{

    // analogWrite(trigger, 255);
    //  uint8_t buflog[30];

    _dir = dir;

    int _correct = compass.Correct();

    if (dir != 0)
    {
        // sprintf((char *)buflog, "%d,%d\n", dir, _dir);
        // UDP_sendPaket(30000, UDP_MESSAGE, buflog, strlen((char *)buflog));
    }

    debM1("Dir:");
    debM1(dir);
    debM1(",S:");
    debM1(speed / 2);
    // debM1(",T:");
    // debM1(time);
    debM1(",Ang:");
    // debM1(compass.GetAllAngleRAW(true, 1));
    debM1(",Corr:");
    debM1(_correct);
    // debM1(" micros: ");
    // debM1(now);
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
            _mNorth.moving(0, speed, _correct);
            _mEast.moving(2, speed, _correct);
            _mSouth.moving(0, speed, _correct);
            _mWest.moving(1, speed, _correct);
            _time.EndMicros = now + time;
            _time.Running = true;
            deblnM("North");
        }
        break;

    case NorthEast:
        if (!_time.Running)
        {
            _mNorth.moving(1, speed, _correct);
            _mEast.moving(2, speed, _correct);
            _mSouth.moving(2, speed, _correct);
            _mWest.moving(1, speed, _correct);
            _time.EndMicros = now + time;
            _time.Running = true;
            _dir = 0;
            deblnM("NorthEast");
        }
        break;

    case East:
        if (!_time.Running)
        {
            _mNorth.moving(1, speed, _correct);
            _mEast.moving(0, speed, _correct);
            _mSouth.moving(2, speed, _correct);
            _mWest.moving(0, speed, _correct);
            _time.EndMicros = now + time;
            _time.Running = true;
            deblnM("East");
        }
        break;

    case SouthEast:
        if (!_time.Running)
        {
            _mNorth.moving(1, speed, _correct);
            _mEast.moving(1, speed, _correct);
            _mSouth.moving(2, speed, _correct);
            _mWest.moving(2, speed, _correct);
            _time.EndMicros = now + time;
            _time.Running = true;
            deblnM("SouthEast");
        }
        break;

    case South:
        if (!_time.Running)
        {
            _mNorth.moving(0, speed, _correct);
            _mEast.moving(1, speed, _correct);
            _mSouth.moving(0, speed, _correct);
            _mWest.moving(2, speed, _correct);
            _time.EndMicros = now + time;
            _time.Running = true;
            deblnM("South");
        }
        break;

    case SouthWest:
        if (!_time.Running)
        {
            _mNorth.moving(2, speed, _correct);
            _mEast.moving(1, speed, _correct);
            _mSouth.moving(1, speed, _correct);
            _mWest.moving(2, speed, _correct);
            _time.EndMicros = now + time;
            _time.Running = true;
            deblnM("SouthWest");
        }
        break;

    case West:
        if (!_time.Running)
        {
            _mNorth.moving(2, speed, _correct);
            _mEast.moving(0, speed, _correct);
            _mSouth.moving(1, speed, _correct);
            _mWest.moving(0, speed, _correct);
            _time.EndMicros = now + time;
            _time.Running = true;
            deblnM("West");
        }
        break;

    case NorthWest:
        if (!_time.Running)
        {
            _mNorth.moving(2, speed, _correct);
            _mEast.moving(2, speed, _correct);
            _mSouth.moving(1, speed, _correct);
            _mWest.moving(1, speed, _correct);
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
            _mNorth.moving(0, 0, 0);
            _mEast.moving(0, 0, 0);
            _mSouth.moving(0, 0, 0);
            _mWest.moving(0, 0, 0);
        }
        break;

    case Square:
        if (!_time.Running)
        {
            time = 1000;
            _mNorth.moving(1, speed, _correct);
            _mEast.moving(0, speed, _correct);
            _mSouth.moving(2, speed, _correct);
            _mWest.moving(0, speed, _correct);
            deblnM("East");
            delay(time);
            Brake();
            _mNorth.moving(0, speed, _correct);
            _mEast.moving(1, speed, _correct);
            _mSouth.moving(0, speed, _correct);
            _mWest.moving(2, speed, _correct);
            deblnM("South");
            delay(time);
            Brake();
            _mNorth.moving(2, speed, _correct);
            _mEast.moving(0, speed, _correct);
            _mSouth.moving(1, speed, _correct);
            _mWest.moving(0, speed, _correct);
            deblnM("West");
            delay(time);
            Brake();
            _mNorth.moving(0, speed, _correct);
            _mEast.moving(2, speed, _correct);
            _mSouth.moving(0, speed, _correct);
            _mWest.moving(1, speed, _correct);
            deblnM("North");
            delay(time);
            Brake();
        }
        break;

    case Hexagon:
        if (!_time.Running)
        {
            time = 500;
            _mNorth.moving(0, speed, _correct);
            _mEast.moving(2, speed, _correct);
            _mSouth.moving(0, speed, _correct);
            _mWest.moving(1, speed, _correct);
            deblnM("North");
            delay(time);
            Brake();
            _mNorth.moving(1, speed, _correct);
            _mEast.moving(2, speed, _correct);
            _mSouth.moving(2, speed, _correct);
            _mWest.moving(1, speed, _correct);
            deblnM("NorthEast");
            delay(time);
            Brake();
            _mNorth.moving(1, speed, _correct);
            _mEast.moving(0, speed, _correct);
            _mSouth.moving(2, speed, _correct);
            _mWest.moving(0, speed, _correct);
            deblnM("East");
            delay(time);
            Brake();
            _mNorth.moving(1, speed, _correct);
            _mEast.moving(1, speed, _correct);
            _mSouth.moving(2, speed, _correct);
            _mWest.moving(2, speed, _correct);
            deblnM("SouthEast");
            delay(time);
            Brake();
            _mNorth.moving(0, speed, _correct);
            _mEast.moving(1, speed, _correct);
            _mSouth.moving(0, speed, _correct);
            _mWest.moving(2, speed, _correct);
            deblnM("South");
            delay(time);
            Brake();
            _mNorth.moving(2, speed, _correct);
            _mEast.moving(1, speed, _correct);
            _mSouth.moving(1, speed, _correct);
            _mWest.moving(2, speed, _correct);
            deblnM("SouthWest");
            delay(time);
            Brake();
            _mNorth.moving(2, speed, _correct);
            _mEast.moving(0, speed, _correct);
            _mSouth.moving(1, speed, _correct);
            _mWest.moving(0, speed, _correct);
            deblnM("West");
            delay(time);
            Brake();
            _mNorth.moving(2, speed, _correct);
            _mEast.moving(2, speed, _correct);
            _mSouth.moving(1, speed, _correct);
            _mWest.moving(1, speed, _correct);
            deblnM("NorthWest");
            delay(time);
            Brake();
        }
        break;

    case Cross:
        if (!_time.Running)
        {
            time = 800;
            _mNorth.moving(0, speed, _correct);
            _mEast.moving(2, speed, _correct);
            _mSouth.moving(0, speed, _correct);
            _mWest.moving(1, speed, _correct);
            deblnM("North");
            delay(time);
            Brake();
            _mNorth.moving(0, speed, _correct);
            _mEast.moving(1, speed, _correct);
            _mSouth.moving(0, speed, _correct);
            _mWest.moving(2, speed, _correct);
            deblnM("South * 2");
            delay(time * 2);
            Brake();
            _mNorth.moving(0, speed, _correct);
            _mEast.moving(2, speed, _correct);
            _mSouth.moving(0, speed, _correct);
            _mWest.moving(1, speed, _correct);
            deblnM("North");
            delay(time);
            Brake();

            _mNorth.moving(1, speed, _correct);
            _mEast.moving(0, speed, _correct);
            _mSouth.moving(2, speed, _correct);
            _mWest.moving(0, speed, _correct);
            deblnM("East");
            delay(time);
            Brake();
            _mNorth.moving(2, speed, _correct);
            _mEast.moving(0, speed, _correct);
            _mSouth.moving(1, speed, _correct);
            _mWest.moving(0, speed, _correct);
            deblnM("West * 2");
            delay(time * 2);
            Brake();
            _mNorth.moving(1, speed, _correct);
            _mEast.moving(0, speed, _correct);
            _mSouth.moving(2, speed, _correct);
            _mWest.moving(0, speed, _correct);
            deblnM("East");
            delay(time);
            Brake();
        }
        break;

    case CW:
        if (!_time.Running) // If running is true ther's no need to set the motors again
        {
            _mNorth.moving(1, speed, 0);
            _mEast.moving(2, speed, 0);
            _mSouth.moving(1, speed, 0);
            _mWest.moving(2, speed, 0);
            _time.EndMicros = now + time;
            _time.Running = true;
            // deblnM("Rotating CW");
        }
        break;

    case CCW:
        if (!_time.Running) // If running is true ther's no need to set the motors again
        {
            _mNorth.moving(2, speed, 0);
            _mEast.moving(1, speed, 0);
            _mSouth.moving(2, speed, 0);
            _mWest.moving(1, speed, 0);
            _time.EndMicros = now + time;
            _time.Running = true;
            // deblnM("Rotating CW");
        }
        break;

    case _Brake:

        _mNorth.moving(3, 255, 0);
        _mEast.moving(3, 255, 0);
        _mSouth.moving(3, 255, 0);
        _mWest.moving(3, 255, 0);
        delay(speed / 1.5);
        _mNorth.moving(0, 0, 0);
        _mEast.moving(0, 0, 0);
        _mSouth.moving(0, 0, 0);
        _mWest.moving(0, 0, 0);
        break;

    default:
        // debM(now);
        // debM(" ; end micros");
        // debM(_time.EndMicros);
        // debM(" ; ");
        // deblnM(_time.Running);
        if (_time.Running)
        {

            if (now > _time.EndMicros) // checking if the motor need to stop (freeWheel)
            {
                // deblnM("stop mot");
                _time.Running = false;
                _mNorth.moving(0, 0, 0);
                _mEast.moving(0, 0, 0);
                _mSouth.moving(0, 0, 0);
                _mWest.moving(0, 0, 0);
            }
        }
        else
        {
            Angle_Correction();
        }

        break;
    }
}

void Move::Dir3(int dir, int speed, unsigned long time, unsigned long now)
{
    // uint8_t buflog[30];

    _dir = dir;

    int _correct = compass.Correct();

    /*if (dir != 0)
    {
        // sprintf((char *)buflog, "%d,%d\n", dir, _dir);
        // UDP_sendPaket(30000, UDP_MESSAGE, buflog, strlen((char *)buflog));
    }*/

    debM1("Dir:");
    debM1(dir);
    debM1(",S:");
    debM1(speed / 2);
    // debM1(",T:");
    // debM1(time);
    debM1(",Ang:");
    debM1(compass.GetAllAngleRAW(true, 1));
    debM1(",Corr:");
    debM1(_correct);
    // debM1(" micros: ");
    // debM1(now);
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

    _dir = RAD(_dir);

    // calc mot1
    mot1.speed = speed * cos((_dir - _3motAng.mot1) - 90);

    if (mot1.speed != 0)
    {
        if (mot1.speed > 0)
        {
            mot1.dir = 1;
        }
        else
        {
            mot1.dir = 2;
        }
    }
    else
    {
        mot1.dir = 0;
    }

    // calc mot2
    mot2.speed = speed * cos((_dir - _3motAng.mot2) - 90);

    if (mot2.speed != 0)
    {
        if (mot2.speed > 0)
        {
            mot2.dir = 1;
        }
        else
        {
            mot2.dir = 2;
        }
    }
    else
    {
        mot2.dir = 0;
    }

    // calc mot3
    mot3.speed = speed * cos((_dir - _3motAng.mot3) - 90);

    if (mot3.speed != 0)
    {
        if (mot3.speed > 0)
        {
            mot3.dir = 1;
        }
        else
        {
            mot3.dir = 2;
        }
    }
    else
    {
        mot3.dir = 0;
    }

    // set all motor all at onece
    if (!_time.Running) // If running is true ther's no need to set the motors again
    {
        _mNorth.moving(mot1.dir, mot1.speed, _correct);
        _mEast.moving(mot2.dir, mot2.speed, _correct);
        _mSouth.moving(mot3.dir, mot3.speed, _correct);
        _time.EndMicros = now + time;
        _time.Running = true;
        deblnM("Moving");
    }

    if (_time.Running)
    {

        if (now > _time.EndMicros) // checking if the motor need to stop (freeWheel)
        {
            // deblnM("stop mot");
            _time.Running = false;
            _mNorth.moving(0, 0, 0);
            _mEast.moving(0, 0, 0);
            _mSouth.moving(0, 0, 0);
            deblnM("Move done");
        }
    }
    else
    {
        Angle_Correction();
    }
}

void Move::Dir4(int dir, int speed, unsigned long time, unsigned long now)
{
    // uint8_t buflog[30];

    _dir = dir;

    int _correct = compass.Correct();

    /*if (dir != 0)
    {
        // sprintf((char *)buflog, "%d,%d\n", dir, _dir);
        // UDP_sendPaket(30000, UDP_MESSAGE, buflog, strlen((char *)buflog));
    }*/

    debM1("Dir:");
    debM1(dir);
    debM1(",S:");
    debM1(speed / 2);
    // debM1(",T:");
    // debM1(time);
    debM1(",Ang:");
    debM1(compass.GetAllAngleRAW(true, 1));
    debM1(",Corr:");
    debM1(_correct);
    // debM1(" micros: ");
    // debM1(now);
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

    if (_dir < 0) // dir command guard
    {
        _dir = 0;
    }
    else if (_dir > 359)
    {
        _dir = 366;
    }

    switch (_dir)
    {
    case 361:               // CW
        if (!_time.Running) // If running is true ther's no need to set the motors again
        {
            _mNorth.moving(1, speed, 0);
            _mEast.moving(2, speed, 0);
            _mSouth.moving(1, speed, 0);
            _mWest.moving(2, speed, 0);
            _time.EndMicros = now + time;
            _time.Running = true;
            // deblnM("Rotating CW");
        }
        break;

    case 362:               // CCW
        if (!_time.Running) // If running is true ther's no need to set the motors again
        {
            _mNorth.moving(2, speed, 0);
            _mEast.moving(1, speed, 0);
            _mSouth.moving(2, speed, 0);
            _mWest.moving(1, speed, 0);
            _time.EndMicros = now + time;
            _time.Running = true;
            // deblnM("Rotating CW");
        }
        break;

    case 360: //_Brake

        _mNorth.moving(3, 255, 0);
        _mEast.moving(3, 255, 0);
        _mSouth.moving(3, 255, 0);
        _mWest.moving(3, 255, 0);
        delay(speed / 1.5);
        _mNorth.moving(0, 0, 0);
        _mEast.moving(0, 0, 0);
        _mSouth.moving(0, 0, 0);
        _mWest.moving(0, 0, 0);
        break;

    case Freewheel:
        if (!_time.Running)
        {
            deblnM("stop mot");
            _time.Running = false;
            _mNorth.moving(0, 0, 0);
            _mEast.moving(0, 0, 0);
            _mSouth.moving(0, 0, 0);
            _mWest.moving(0, 0, 0);
        }
        break;

    case 364: // Square
        if (!_time.Running)
        {
            time = 1000;
            _mNorth.moving(1, speed, _correct);
            _mEast.moving(0, speed, _correct);
            _mSouth.moving(2, speed, _correct);
            _mWest.moving(0, speed, _correct);
            deblnM("East");
            delay(time);
            Brake();
            _mNorth.moving(0, speed, _correct);
            _mEast.moving(1, speed, _correct);
            _mSouth.moving(0, speed, _correct);
            _mWest.moving(2, speed, _correct);
            deblnM("South");
            delay(time);
            Brake();
            _mNorth.moving(2, speed, _correct);
            _mEast.moving(0, speed, _correct);
            _mSouth.moving(1, speed, _correct);
            _mWest.moving(0, speed, _correct);
            deblnM("West");
            delay(time);
            Brake();
            _mNorth.moving(0, speed, _correct);
            _mEast.moving(2, speed, _correct);
            _mSouth.moving(0, speed, _correct);
            _mWest.moving(1, speed, _correct);
            deblnM("North");
            delay(time);
            Brake();
        }
        break;

    case 365: // Hexagon
        if (!_time.Running)
        {
            time = 500;
            _mNorth.moving(0, speed, _correct);
            _mEast.moving(2, speed, _correct);
            _mSouth.moving(0, speed, _correct);
            _mWest.moving(1, speed, _correct);
            deblnM("North");
            delay(time);
            Brake();
            _mNorth.moving(1, speed, _correct);
            _mEast.moving(2, speed, _correct);
            _mSouth.moving(2, speed, _correct);
            _mWest.moving(1, speed, _correct);
            deblnM("NorthEast");
            delay(time);
            Brake();
            _mNorth.moving(1, speed, _correct);
            _mEast.moving(0, speed, _correct);
            _mSouth.moving(2, speed, _correct);
            _mWest.moving(0, speed, _correct);
            deblnM("East");
            delay(time);
            Brake();
            _mNorth.moving(1, speed, _correct);
            _mEast.moving(1, speed, _correct);
            _mSouth.moving(2, speed, _correct);
            _mWest.moving(2, speed, _correct);
            deblnM("SouthEast");
            delay(time);
            Brake();
            _mNorth.moving(0, speed, _correct);
            _mEast.moving(1, speed, _correct);
            _mSouth.moving(0, speed, _correct);
            _mWest.moving(2, speed, _correct);
            deblnM("South");
            delay(time);
            Brake();
            _mNorth.moving(2, speed, _correct);
            _mEast.moving(1, speed, _correct);
            _mSouth.moving(1, speed, _correct);
            _mWest.moving(2, speed, _correct);
            deblnM("SouthWest");
            delay(time);
            Brake();
            _mNorth.moving(2, speed, _correct);
            _mEast.moving(0, speed, _correct);
            _mSouth.moving(1, speed, _correct);
            _mWest.moving(0, speed, _correct);
            deblnM("West");
            delay(time);
            Brake();
            _mNorth.moving(2, speed, _correct);
            _mEast.moving(2, speed, _correct);
            _mSouth.moving(1, speed, _correct);
            _mWest.moving(1, speed, _correct);
            deblnM("NorthWest");
            delay(time);
            Brake();
        }
        break;

    case 366: // Cross
        if (!_time.Running)
        {
            time = 800;
            _mNorth.moving(0, speed, _correct);
            _mEast.moving(2, speed, _correct);
            _mSouth.moving(0, speed, _correct);
            _mWest.moving(1, speed, _correct);
            deblnM("North");
            delay(time);
            Brake();
            _mNorth.moving(0, speed, _correct);
            _mEast.moving(1, speed, _correct);
            _mSouth.moving(0, speed, _correct);
            _mWest.moving(2, speed, _correct);
            deblnM("South * 2");
            delay(time * 2);
            Brake();
            _mNorth.moving(0, speed, _correct);
            _mEast.moving(2, speed, _correct);
            _mSouth.moving(0, speed, _correct);
            _mWest.moving(1, speed, _correct);
            deblnM("North");
            delay(time);
            Brake();

            _mNorth.moving(1, speed, _correct);
            _mEast.moving(0, speed, _correct);
            _mSouth.moving(2, speed, _correct);
            _mWest.moving(0, speed, _correct);
            deblnM("East");
            delay(time);
            Brake();
            _mNorth.moving(2, speed, _correct);
            _mEast.moving(0, speed, _correct);
            _mSouth.moving(1, speed, _correct);
            _mWest.moving(0, speed, _correct);
            deblnM("West * 2");
            delay(time * 2);
            Brake();
            _mNorth.moving(1, speed, _correct);
            _mEast.moving(0, speed, _correct);
            _mSouth.moving(2, speed, _correct);
            _mWest.moving(0, speed, _correct);
            deblnM("East");
            delay(time);
            Brake();
        }
        break;

    default:
        _dir = RAD(_dir);

        // calc mot1
        mot1.speed = speed * cos((_dir - _4motAng.mot1) - 90);

        if (mot1.speed != 0)
        {
            if (mot1.speed > 0)
            {
                mot1.dir = 1;
            }
            else
            {
                mot1.dir = 2;
            }
        }
        else
        {
            mot1.dir = 0;
        }

        // calc mot2
        mot2.speed = speed * cos((_dir - _4motAng.mot2) - 90);

        if (mot2.speed != 0)
        {
            if (mot2.speed > 0)
            {
                mot2.dir = 1;
            }
            else
            {
                mot2.dir = 2;
            }
        }
        else
        {
            mot2.dir = 0;
        }

        // calc mot3
        mot3.speed = speed * cos((_dir - _4motAng.mot3) - 90);

        if (mot3.speed != 0)
        {
            if (mot3.speed > 0)
            {
                mot3.dir = 1;
            }
            else
            {
                mot3.dir = 2;
            }
        }
        else
        {
            mot3.dir = 0;
        }

        // calc mot4
        mot4.speed = speed * cos((_dir - _4motAng.mot4) - 90);

        if (mot4.speed != 0)
        {
            if (mot4.speed > 0)
            {
                mot4.dir = 1;
            }
            else
            {
                mot4.dir = 2;
            }
        }
        else
        {
            mot4.dir = 0;
        }

        // set all motor all at onece
        if (!_time.Running) // If running is true ther's no need to set the motors again
        {
            _mNorth.moving(mot1.dir, mot1.speed, _correct);
            _mEast.moving(mot2.dir, mot2.speed, _correct);
            _mSouth.moving(mot3.dir, mot3.speed, _correct);
            _time.EndMicros = now + time;
            _time.Running = true;
            deblnM("Moving");
        }

        if (_time.Running)
        {

            if (now > _time.EndMicros) // checking if the motor need to stop (freeWheel)
            {
                // deblnM("stop mot");
                _time.Running = false;
                _mNorth.moving(0, 0, 0);
                _mEast.moving(0, 0, 0);
                _mSouth.moving(0, 0, 0);
                deblnM("Move done");
            }
        }
        else
        {
            Angle_Correction();
        }
        break;
    }
}

void Move::Tare(unsigned int duration)
{
    // uint8_t buflog[50];

    Dir(CW, 80, duration + 100, millis());
    compass._tare(duration);
    Dir(_Brake, 255, 0, millis());
}

void Move::Angle_Correction()
{
    int correct = compass.Correct();

    if (abs(correct) > 10)
    {
        if (correct > 0)
        {
            Dir(CW, 130 + abs(correct), 1 * 1000, micros());
        }
        else
        {
            Dir(CCW, 130 + abs(correct), 1 * 1000, micros());
        }
    }
}

double Move::RAD(int _deg)
{
    return (_deg * (3.14159265359 / 180));
}
