#include "Move.h"
#include "_UDP.h"

/*********DEBUGGER************/
#include "debug.h"
/*****************************/

extern Compass compass;

int trigger = A0;


Move::Move()
{
    _mot1.begin(NORTH_DIR1, NORTH_DIR2, NORTH_ENABLE);
    _mot2.begin(EAST_DIR1, EAST_DIR2, EAST_ENABLE);
    _mot3.begin(SOUTH_DIR1, SOUTH_DIR2, SOUTH_ENABLE);
    _mot4.begin(WEST_DIR1, WEST_DIR2, WEST_ENABLE);
}

Move::~Move() {}

void Move::test()
{
    for (int i = 0; i < 1024; i++)
    {
        _mot2.moving(2, i, 0);
        delay(300);
        deblnM1(i);
    }

    while (true)
    {
        deblnM1("Ended...");
        delay(1000);
    }

    /*_mot1.moving(1, 255, 0);
    delay(2000);
    KILL();
    _mot2.moving(1, 255, 0);
    delay(2000);
    KILL();
    _mot3.moving(1, 255, 0);
    delay(2000);
    KILL();
    _mot4.moving(1, 255, 0);
    delay(2000);
    KILL();
    _mot1.moving(1, 255, 0);
    _mot2.moving(1, 255, 0);
    _mot3.moving(1, 255, 0);
    _mot4.moving(1, 255, 0);
    delay(500);
    KILL();*/
}

void Move::KILL()
{
    _mot1.moving(0, 0, 0);
    _mot2.moving(0, 0, 0);
    _mot3.moving(0, 0, 0);
    _mot4.moving(0, 0, 0);
}

void Move::Brake()
{
    _mot1.moving(3, 255, 0);
    _mot2.moving(3, 255, 0);
    _mot3.moving(3, 255, 0);
    _mot4.moving(3, 255, 0);
    delay(100);
    _mot1.moving(0, 0, 0);
    _mot2.moving(0, 0, 0);
    _mot3.moving(0, 0, 0);
    _mot4.moving(0, 0, 0);
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

    debM("Dir:");
    debM(dir);
    debM(",S:");
    debM(speed / 2);
    // debM(",T:");
    // debM(time);
    debM(",Ang:");
    // debM(compass.GetAllAngleRAW(true, 1));
    debM(",Corr:");
    debM(_correct);
    // debM(" micros: ");
    // debM(now);
    deblnM(" .");

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
        deblnM1(_time.EndMicros);
    */

    switch (_dir)
    {
    case North:
        if (!_time.Running) // If running is true ther's no need to set the motors again
        {
            _mot1.moving(0, speed, _correct);
            _mot2.moving(2, speed, _correct);
            _mot3.moving(0, speed, _correct);
            _mot4.moving(1, speed, _correct);
            _time.EndMicros = now + time;
            _time.Running = true;
            deblnM1("North");
        }
        break;

    case NorthEast:
        if (!_time.Running)
        {
            _mot1.moving(1, speed, _correct);
            _mot2.moving(2, speed, _correct);
            _mot3.moving(2, speed, _correct);
            _mot4.moving(1, speed, _correct);
            _time.EndMicros = now + time;
            _time.Running = true;
            _dir = 0;
            deblnM1("NorthEast");
        }
        break;

    case East:
        if (!_time.Running)
        {
            _mot1.moving(1, speed, _correct);
            _mot2.moving(0, speed, _correct);
            _mot3.moving(2, speed, _correct);
            _mot4.moving(0, speed, _correct);
            _time.EndMicros = now + time;
            _time.Running = true;
            deblnM1("East");
        }
        break;

    case SouthEast:
        if (!_time.Running)
        {
            _mot1.moving(1, speed, _correct);
            _mot2.moving(1, speed, _correct);
            _mot3.moving(2, speed, _correct);
            _mot4.moving(2, speed, _correct);
            _time.EndMicros = now + time;
            _time.Running = true;
            deblnM1("SouthEast");
        }
        break;

    case South:
        if (!_time.Running)
        {
            _mot1.moving(0, speed, _correct);
            _mot2.moving(1, speed, _correct);
            _mot3.moving(0, speed, _correct);
            _mot4.moving(2, speed, _correct);
            _time.EndMicros = now + time;
            _time.Running = true;
            deblnM1("South");
        }
        break;

    case SouthWest:
        if (!_time.Running)
        {
            _mot1.moving(2, speed, _correct);
            _mot2.moving(1, speed, _correct);
            _mot3.moving(1, speed, _correct);
            _mot4.moving(2, speed, _correct);
            _time.EndMicros = now + time;
            _time.Running = true;
            deblnM1("SouthWest");
        }
        break;

    case West:
        if (!_time.Running)
        {
            _mot1.moving(2, speed, _correct);
            _mot2.moving(0, speed, _correct);
            _mot3.moving(1, speed, _correct);
            _mot4.moving(0, speed, _correct);
            _time.EndMicros = now + time;
            _time.Running = true;
            deblnM1("West");
        }
        break;

    case NorthWest:
        if (!_time.Running)
        {
            _mot1.moving(2, speed, _correct);
            _mot2.moving(2, speed, _correct);
            _mot3.moving(1, speed, _correct);
            _mot4.moving(1, speed, _correct);
            _time.EndMicros = now + time;
            _time.Running = true;
            deblnM1("NorthWest");
        }
        break;

    case Freewheel:
        if (!_time.Running)
        {
            deblnM1("stop mot");
            _time.Running = false;
            _mot1.moving(0, 0, 0);
            _mot2.moving(0, 0, 0);
            _mot3.moving(0, 0, 0);
            _mot4.moving(0, 0, 0);
        }
        break;

    case Square:
        if (!_time.Running)
        {
            time = 1000;
            _mot1.moving(1, speed, _correct);
            _mot2.moving(0, speed, _correct);
            _mot3.moving(2, speed, _correct);
            _mot4.moving(0, speed, _correct);
            deblnM1("East");
            delay(time);
            Brake();
            _mot1.moving(0, speed, _correct);
            _mot2.moving(1, speed, _correct);
            _mot3.moving(0, speed, _correct);
            _mot4.moving(2, speed, _correct);
            deblnM1("South");
            delay(time);
            Brake();
            _mot1.moving(2, speed, _correct);
            _mot2.moving(0, speed, _correct);
            _mot3.moving(1, speed, _correct);
            _mot4.moving(0, speed, _correct);
            deblnM1("West");
            delay(time);
            Brake();
            _mot1.moving(0, speed, _correct);
            _mot2.moving(2, speed, _correct);
            _mot3.moving(0, speed, _correct);
            _mot4.moving(1, speed, _correct);
            deblnM1("North");
            delay(time);
            Brake();
        }
        break;

    case Hexagon:
        if (!_time.Running)
        {
            time = 500;
            _mot1.moving(0, speed, _correct);
            _mot2.moving(2, speed, _correct);
            _mot3.moving(0, speed, _correct);
            _mot4.moving(1, speed, _correct);
            deblnM1("North");
            delay(time);
            Brake();
            _mot1.moving(1, speed, _correct);
            _mot2.moving(2, speed, _correct);
            _mot3.moving(2, speed, _correct);
            _mot4.moving(1, speed, _correct);
            deblnM1("NorthEast");
            delay(time);
            Brake();
            _mot1.moving(1, speed, _correct);
            _mot2.moving(0, speed, _correct);
            _mot3.moving(2, speed, _correct);
            _mot4.moving(0, speed, _correct);
            deblnM1("East");
            delay(time);
            Brake();
            _mot1.moving(1, speed, _correct);
            _mot2.moving(1, speed, _correct);
            _mot3.moving(2, speed, _correct);
            _mot4.moving(2, speed, _correct);
            deblnM1("SouthEast");
            delay(time);
            Brake();
            _mot1.moving(0, speed, _correct);
            _mot2.moving(1, speed, _correct);
            _mot3.moving(0, speed, _correct);
            _mot4.moving(2, speed, _correct);
            deblnM1("South");
            delay(time);
            Brake();
            _mot1.moving(2, speed, _correct);
            _mot2.moving(1, speed, _correct);
            _mot3.moving(1, speed, _correct);
            _mot4.moving(2, speed, _correct);
            deblnM1("SouthWest");
            delay(time);
            Brake();
            _mot1.moving(2, speed, _correct);
            _mot2.moving(0, speed, _correct);
            _mot3.moving(1, speed, _correct);
            _mot4.moving(0, speed, _correct);
            deblnM1("West");
            delay(time);
            Brake();
            _mot1.moving(2, speed, _correct);
            _mot2.moving(2, speed, _correct);
            _mot3.moving(1, speed, _correct);
            _mot4.moving(1, speed, _correct);
            deblnM1("NorthWest");
            delay(time);
            Brake();
        }
        break;

    case Cross:
        if (!_time.Running)
        {
            time = 800;
            _mot1.moving(0, speed, _correct);
            _mot2.moving(2, speed, _correct);
            _mot3.moving(0, speed, _correct);
            _mot4.moving(1, speed, _correct);
            deblnM1("North");
            delay(time);
            Brake();
            _mot1.moving(0, speed, _correct);
            _mot2.moving(1, speed, _correct);
            _mot3.moving(0, speed, _correct);
            _mot4.moving(2, speed, _correct);
            deblnM1("South * 2");
            delay(time * 2);
            Brake();
            _mot1.moving(0, speed, _correct);
            _mot2.moving(2, speed, _correct);
            _mot3.moving(0, speed, _correct);
            _mot4.moving(1, speed, _correct);
            deblnM1("North");
            delay(time);
            Brake();

            _mot1.moving(1, speed, _correct);
            _mot2.moving(0, speed, _correct);
            _mot3.moving(2, speed, _correct);
            _mot4.moving(0, speed, _correct);
            deblnM1("East");
            delay(time);
            Brake();
            _mot1.moving(2, speed, _correct);
            _mot2.moving(0, speed, _correct);
            _mot3.moving(1, speed, _correct);
            _mot4.moving(0, speed, _correct);
            deblnM1("West * 2");
            delay(time * 2);
            Brake();
            _mot1.moving(1, speed, _correct);
            _mot2.moving(0, speed, _correct);
            _mot3.moving(2, speed, _correct);
            _mot4.moving(0, speed, _correct);
            deblnM1("East");
            delay(time);
            Brake();
        }
        break;

    case CW:
        if (!_time.Running) // If running is true ther's no need to set the motors again
        {
            _mot1.moving(1, speed, 0);
            _mot2.moving(1, speed, 0);
            _mot3.moving(1, speed, 0);
            _mot4.moving(1, speed, 0);
            _time.EndMicros = now + time;
            _time.Running = true;
            // deblnM1("Rotating CW");
        }
        break;

    case CCW:
        if (!_time.Running) // If running is true ther's no need to set the motors again
        {
            _mot1.moving(1, speed, 0);
            _mot2.moving(1, speed, 0);
            _mot3.moving(1, speed, 0);
            _mot4.moving(1, speed, 0);
            _time.EndMicros = now + time;
            _time.Running = true;
            // deblnM1("Rotating CW");
        }
        break;

    case _Brake:

        _mot1.moving(3, 255, 0);
        _mot2.moving(3, 255, 0);
        _mot3.moving(3, 255, 0);
        _mot4.moving(3, 255, 0);
        delay(speed / 1.5);
        _mot1.moving(0, 0, 0);
        _mot2.moving(0, 0, 0);
        _mot3.moving(0, 0, 0);
        _mot4.moving(0, 0, 0);
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
                // deblnM1("stop mot");
                _time.Running = false;
                _mot1.moving(0, 0, 0);
                _mot2.moving(0, 0, 0);
                _mot3.moving(0, 0, 0);
                _mot4.moving(0, 0, 0);
            }
        }
        else
        {
            Angle_Correction3();
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

    //debM("Dir:");
    //debM(dir);
    debM("S:");
    debM(speed / 2);
    // debM(",T:");
    // debM(time);
    debM(",Ang:");
    debM(compass.GetAllAngleRAW(true, 1));
    debM(",Corr:");
    debM(_correct);
    // debM(" micros: ");
    // debM(now);
    deblnM("");

    _time.time = time;

    if (_time.time > 5000000) // TIME GUARD: Robot cannot (and has no need to) run a command for more than 10sec for safety
    {
        _time.time = 5000000;
    }

    if (_dir != 0)
    {
        _time.Running = false;
    }

    if (dir > 0 && dir <= 360)
    {

        // calc mot1
        motD1.speed = speed * cos(DEG_TO_RAD * (_dir - _3motAng.mot1));
        debM1("mot1:");
        debM1(motD1.speed);
        debM1(";");

        if (motD1.speed != 0)
        {
            if (motD1.speed > 0)
            {
                motD1.dir = 1;
            }
            else
            {
                motD1.dir = 2;
            }
        }
        else
        {
            motD1.dir = 0;
        }

        // calc mot2
        motD2.speed = speed * cos(DEG_TO_RAD * (_dir - _3motAng.mot2));
        debM1("mot2:");
        debM1(motD2.speed);
        debM1(";");

        if (motD2.speed != 0)
        {
            if (motD2.speed > 0)
            {
                motD2.dir = 1;
            }
            else
            {
                motD2.dir = 2;
            }
        }
        else
        {
            motD2.dir = 0;
        }

        // calc mot3
        motD3.speed = speed * cos(DEG_TO_RAD * (_dir - _3motAng.mot3));
        debM1("mot3:");
        deblnM1(motD3.speed);

        if (motD3.speed != 0)
        {
            if (motD3.speed > 0)
            {
                motD3.dir = 1;
            }
            else
            {
                motD3.dir = 2;
            }
        }
        else
        {
            motD3.dir = 0;
        }

        // set all motor all at onece
        if (!_time.Running) // If running is true ther's no need to set the motors again
        {
            _mot1.moving(motD1.dir, abs(motD1.speed), _correct);
            _mot2.moving(motD2.dir, abs(motD2.speed), _correct);
            _mot3.moving(motD3.dir, abs(motD3.speed), _correct);
            _time.EndMicros = now + time;
            _time.Running = true;
            // deblnM1("Moving");
        }
    }
    switch (_dir)
    {
    case 361:               // CW
        if (!_time.Running) // If running is true ther's no need to set the motors again
        {
            _mot1.moving(1, speed, 0);
            _mot2.moving(1, speed, 0);
            _mot3.moving(1, speed, 0);
            _time.EndMicros = now + time;
            _time.Running = true;
            // deblnM1("Rotating CW");
        }
        break;

    case 362:               // CCW
        if (!_time.Running) // If running is true ther's no need to set the motors again
        {
            _mot1.moving(2, speed, 0);
            _mot2.moving(2, speed, 0);
            _mot3.moving(2, speed, 0);
            _time.EndMicros = now + time;
            _time.Running = true;
            // deblnM1("Rotating CW");
        }
        break;

    case 360: //_Brake

        _mot1.moving(3, 255, 0);
        _mot2.moving(3, 255, 0);
        _mot3.moving(3, 255, 0);
        delay(speed / 1.5);
        _mot1.moving(0, 0, 0);
        _mot2.moving(0, 0, 0);
        _mot3.moving(0, 0, 0);
        break;

    case Freewheel:
        if (!_time.Running)
        {
            deblnM1("stop mot");
            _time.Running = false;
            _mot1.moving(0, 0, 0);
            _mot2.moving(0, 0, 0);
            _mot3.moving(0, 0, 0);
        }
        break;

    default:

        if (_time.Running)
        {

            if (now > _time.EndMicros) // checking if the motor need to stop (freeWheel)
            {
                // deblnM1("stop mot");
                _time.Running = false;
                _mot1.moving(0, 0, 0);
                _mot2.moving(0, 0, 0);
                _mot3.moving(0, 0, 0);
                // deblnM1("Move done");
            }
        }
        else
        {
            Angle_Correction3();
        }
        break;
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

    debM("Dir:");
    debM(dir);
    debM(",S:");
    debM(speed / 2);
    // debM(",T:");
    // debM(time);
    debM(",Ang:");
    debM(compass.GetAllAngleRAW(true, 1));
    debM(",Corr:");
    debM(_correct);
    // debM(" micros: ");
    // debM(now);
    deblnM(" .");

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
            _mot1.moving(1, speed, 0);
            _mot2.moving(2, speed, 0);
            _mot3.moving(1, speed, 0);
            _mot4.moving(2, speed, 0);
            _time.EndMicros = now + time;
            _time.Running = true;
            // deblnM1("Rotating CW");
        }
        break;

    case 362:               // CCW
        if (!_time.Running) // If running is true ther's no need to set the motors again
        {
            _mot1.moving(2, speed, 0);
            _mot2.moving(1, speed, 0);
            _mot3.moving(2, speed, 0);
            _mot4.moving(1, speed, 0);
            _time.EndMicros = now + time;
            _time.Running = true;
            // deblnM1("Rotating CW");
        }
        break;

    case 360: //_Brake

        _mot1.moving(3, 255, 0);
        _mot2.moving(3, 255, 0);
        _mot3.moving(3, 255, 0);
        _mot4.moving(3, 255, 0);
        delay(speed / 1.5);
        _mot1.moving(0, 0, 0);
        _mot2.moving(0, 0, 0);
        _mot3.moving(0, 0, 0);
        _mot4.moving(0, 0, 0);
        break;

    case Freewheel:
        if (!_time.Running)
        {
            deblnM1("stop mot");
            _time.Running = false;
            _mot1.moving(0, 0, 0);
            _mot2.moving(0, 0, 0);
            _mot3.moving(0, 0, 0);
            _mot4.moving(0, 0, 0);
        }
        break;

    case 364: // Square
        if (!_time.Running)
        {
            time = 1000;
            _mot1.moving(1, speed, _correct);
            _mot2.moving(0, speed, _correct);
            _mot3.moving(2, speed, _correct);
            _mot4.moving(0, speed, _correct);
            deblnM1("East");
            delay(time);
            Brake();
            _mot1.moving(0, speed, _correct);
            _mot2.moving(1, speed, _correct);
            _mot3.moving(0, speed, _correct);
            _mot4.moving(2, speed, _correct);
            deblnM1("South");
            delay(time);
            Brake();
            _mot1.moving(2, speed, _correct);
            _mot2.moving(0, speed, _correct);
            _mot3.moving(1, speed, _correct);
            _mot4.moving(0, speed, _correct);
            deblnM1("West");
            delay(time);
            Brake();
            _mot1.moving(0, speed, _correct);
            _mot2.moving(2, speed, _correct);
            _mot3.moving(0, speed, _correct);
            _mot4.moving(1, speed, _correct);
            deblnM1("North");
            delay(time);
            Brake();
        }
        break;

    case 365: // Hexagon
        if (!_time.Running)
        {
            time = 500;
            _mot1.moving(0, speed, _correct);
            _mot2.moving(2, speed, _correct);
            _mot3.moving(0, speed, _correct);
            _mot4.moving(1, speed, _correct);
            deblnM1("North");
            delay(time);
            Brake();
            _mot1.moving(1, speed, _correct);
            _mot2.moving(2, speed, _correct);
            _mot3.moving(2, speed, _correct);
            _mot4.moving(1, speed, _correct);
            deblnM1("NorthEast");
            delay(time);
            Brake();
            _mot1.moving(1, speed, _correct);
            _mot2.moving(0, speed, _correct);
            _mot3.moving(2, speed, _correct);
            _mot4.moving(0, speed, _correct);
            deblnM1("East");
            delay(time);
            Brake();
            _mot1.moving(1, speed, _correct);
            _mot2.moving(1, speed, _correct);
            _mot3.moving(2, speed, _correct);
            _mot4.moving(2, speed, _correct);
            deblnM1("SouthEast");
            delay(time);
            Brake();
            _mot1.moving(0, speed, _correct);
            _mot2.moving(1, speed, _correct);
            _mot3.moving(0, speed, _correct);
            _mot4.moving(2, speed, _correct);
            deblnM1("South");
            delay(time);
            Brake();
            _mot1.moving(2, speed, _correct);
            _mot2.moving(1, speed, _correct);
            _mot3.moving(1, speed, _correct);
            _mot4.moving(2, speed, _correct);
            deblnM1("SouthWest");
            delay(time);
            Brake();
            _mot1.moving(2, speed, _correct);
            _mot2.moving(0, speed, _correct);
            _mot3.moving(1, speed, _correct);
            _mot4.moving(0, speed, _correct);
            deblnM1("West");
            delay(time);
            Brake();
            _mot1.moving(2, speed, _correct);
            _mot2.moving(2, speed, _correct);
            _mot3.moving(1, speed, _correct);
            _mot4.moving(1, speed, _correct);
            deblnM1("NorthWest");
            delay(time);
            Brake();
        }
        break;

    case 366: // Cross
        if (!_time.Running)
        {
            time = 800;
            _mot1.moving(0, speed, _correct);
            _mot2.moving(2, speed, _correct);
            _mot3.moving(0, speed, _correct);
            _mot4.moving(1, speed, _correct);
            deblnM1("North");
            delay(time);
            Brake();
            _mot1.moving(0, speed, _correct);
            _mot2.moving(1, speed, _correct);
            _mot3.moving(0, speed, _correct);
            _mot4.moving(2, speed, _correct);
            deblnM1("South * 2");
            delay(time * 2);
            Brake();
            _mot1.moving(0, speed, _correct);
            _mot2.moving(2, speed, _correct);
            _mot3.moving(0, speed, _correct);
            _mot4.moving(1, speed, _correct);
            deblnM1("North");
            delay(time);
            Brake();

            _mot1.moving(1, speed, _correct);
            _mot2.moving(0, speed, _correct);
            _mot3.moving(2, speed, _correct);
            _mot4.moving(0, speed, _correct);
            deblnM1("East");
            delay(time);
            Brake();
            _mot1.moving(2, speed, _correct);
            _mot2.moving(0, speed, _correct);
            _mot3.moving(1, speed, _correct);
            _mot4.moving(0, speed, _correct);
            deblnM1("West * 2");
            delay(time * 2);
            Brake();
            _mot1.moving(1, speed, _correct);
            _mot2.moving(0, speed, _correct);
            _mot3.moving(2, speed, _correct);
            _mot4.moving(0, speed, _correct);
            deblnM1("East");
            delay(time);
            Brake();
        }
        break;

    default:

        // calc mot1
        motD1.speed = speed * cos((_dir - _4motAng.mot1) - 90);

        if (motD1.speed != 0)
        {
            if (motD1.speed > 0)
            {
                motD1.dir = 1;
            }
            else
            {
                motD1.dir = 2;
            }
        }
        else
        {
            motD1.dir = 0;
        }

        // calc mot2
        motD2.speed = speed * cos((_dir - _4motAng.mot2) - 90);

        if (motD2.speed != 0)
        {
            if (motD2.speed > 0)
            {
                motD2.dir = 1;
            }
            else
            {
                motD2.dir = 2;
            }
        }
        else
        {
            motD2.dir = 0;
        }

        // calc mot3
        motD3.speed = speed * cos((_dir - _4motAng.mot3) - 90);

        if (motD3.speed != 0)
        {
            if (motD3.speed > 0)
            {
                motD3.dir = 1;
            }
            else
            {
                motD3.dir = 2;
            }
        }
        else
        {
            motD3.dir = 0;
        }

        // calc mot4
        motD4.speed = speed * cos((_dir - _4motAng.mot4) - 90);

        if (motD4.speed != 0)
        {
            if (motD4.speed > 0)
            {
                motD4.dir = 1;
            }
            else
            {
                motD4.dir = 2;
            }
        }
        else
        {
            motD4.dir = 0;
        }

        // set all motor all at onece
        if (!_time.Running) // If running is true ther's no need to set the motors again
        {
            _mot1.moving(motD1.dir, motD1.speed, _correct);
            _mot2.moving(motD2.dir, motD2.speed, _correct);
            _mot3.moving(motD3.dir, motD3.speed, _correct);
            _time.EndMicros = now + time;
            _time.Running = true;
            deblnM1("Moving");
        }

        if (_time.Running)
        {

            if (now > _time.EndMicros) // checking if the motor need to stop (freeWheel)
            {
                // deblnM1("stop mot");
                _time.Running = false;
                _mot1.moving(0, 0, 0);
                _mot2.moving(0, 0, 0);
                _mot3.moving(0, 0, 0);
                deblnM1("Move done");
            }
        }
        else
        {
            Angle_Correction3();
        }
        break;
    }
}

void Move::Tare(unsigned int duration)
{
    // uint8_t buflog[50];

    Dir3(361, 200, duration + 100, micros());       // rotate CW(361)
    delay(100);
    Dir3(361, 90, duration + 100, micros());
    compass._tare(duration);
    Dir(_Brake, 255, 0, micros());
}

void Move::Angle_Correction3()
{
    int correct = compass.Correct();

    if (abs(correct) > 10)
    {
        if (correct > 0)
        {
            Dir3(361, 160 + (abs(correct)/2), 3 * 1000, micros()); // CW
        }
        else
        {
            Dir3(362, 160 + (abs(correct)/2), 3 * 1000, micros()); // CCW
        }
    }
}

double Move::RAD(int _deg)
{
    return (_deg * (3.14159265359 / 180));
}

int Map(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
