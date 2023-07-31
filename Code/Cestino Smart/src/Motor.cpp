#include "Arduino.h"
#include "Motor.h"

Motor::Motor() {}

Motor::~Motor() {}

void Motor::begin(int dir1, int dir2, int Enable)
{

    pinMode(dir1, OUTPUT);
    pinMode(dir2, OUTPUT);
    pinMode(Enable, OUTPUT);

    _dir1 = dir1;
    _dir2 = dir2;
    _enable = Enable;
}

void Motor::moving(int dir, int pwm, int correction)
{
    int pwmCorrect;
    int _correction = correction;

    /*      Motor Truth Table
    ╒════════════════════════════╤═══════════════════════════╕
    │ Inputs                     │ Function                  │
    ├────────────┬───────────────┼───────────────────────────┤
    │ Ven = High │ C = H ; D = L │ Forward                   │
    │            ├───────────────┼───────────────────────────┤
    │            │ C = L ; D = H │ Reverse                   │
    │            ├───────────────┼───────────────────────────┤
    │            │ C = D         │ Fast Motor Stop           │
    ├────────────┼───────────────┼───────────────────────────┤
    │ Ven = Low  │ C = X ; D = X │ Free Running / Motor Stop │
    ├────────────┴───────────────┴───────────────────────────┤
    │ L = Low     H = High     X = Don’t care                │
    ╘════════════════════════════════════════════════════════╛
    */

    switch (dir)
    {
    case 0:
        /* FREEWHEEL */
        digitalWrite(_enable, LOW); //  Low ENABLE state means motor free running
        break;

    case 1:
        /* CW */

        if (pwm + _correction > 255)
        {
            pwmCorrect = 255;
        }
        else if (pwm + _correction < 0)
        {
            pwmCorrect = 0;
        }
        else
        {
            pwmCorrect = pwm + (_correction*2);
        }

        /*if (pwmCorrect<_pwmCut)
        {
            pwmCorrect = 0;
        }*/

        digitalWrite(_enable, HIGH); //  Setting speed

        analogWrite(_dir1, pwmCorrect); //  Setting direction
        analogWrite(_dir2, 0);
        break;

    case 2:
        /* CCW */

        _correction *= -1;

        if (pwm + _correction > 255)
        {
            pwmCorrect = 255;
        }
        else if (pwm + _correction < 0)
        {
            pwmCorrect = 0;
        }
        else
        {
            pwmCorrect = pwm + (_correction*2);
        }

        /*if (pwmCorrect<_pwmCut)
        {
            pwmCorrect = 0;
        }*/

        digitalWrite(_enable, HIGH); //  Setting speed

        analogWrite(_dir1, 0); //  Setting direction
        analogWrite(_dir2, pwmCorrect);
        break;

    case 3:
        /* HARD BREAK */
        digitalWrite(_enable, HIGH); //  Setting breaking speed

        analogWrite(_dir1, pwm); //  Setting break
        analogWrite(_dir2, pwm);
        break;

    default:

        analogWrite(_enable, LOW); //  Low ENABLE state means motor free running

        break;
    }
}
