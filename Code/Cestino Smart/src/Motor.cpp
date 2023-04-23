#include "Arduino.h"
#include "Motor.h"

Motor::Motor(){}

Motor::~Motor()
{}

void Motor::begin(int dir1, int dir2, int Enable)
{

    pinMode(dir1, OUTPUT);
    pinMode(dir2, OUTPUT);
    pinMode(Enable, OUTPUT);

	_dir1 = dir1;
    _dir2 = dir2;
    _enable = Enable;

}

void Motor::moving(int dir, int pwm)
    {
        

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
            digitalWrite(_enable, LOW);     //  Low ENABLE state means motor free running
            break;

        case 1:
            /* CW */
            digitalWrite(_enable, pwm);      //  Setting speed

            digitalWrite(_dir1, HIGH);       //  Setting direction
            digitalWrite(_dir2, LOW);
            break;
        
        case 2:
            /* CCW */
            digitalWrite(_enable, pwm);      //  Setting speed

            digitalWrite(_dir1, LOW);       //  Setting direction
            digitalWrite(_dir2, HIGH);
            break;

        case 3:
            /* HARD BREAK */
            digitalWrite(_enable, pwm);      //  Setting breaking speed

            digitalWrite(_dir1, HIGH);       //  Setting break
            digitalWrite(_dir2, HIGH);
            break;
        
        
        default:

            digitalWrite(_enable, LOW);     //  Low ENABLE state means motor free running

            break;
        }
    }

