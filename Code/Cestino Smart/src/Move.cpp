#include "Arduino.h"
#include "define.h"
#include "Move.h"
#include "Motor.h"

//  Motor definitions
Motor::Motor motor motN(dir1N, dir2N, enableN);    //NORD motor
Motor motE(dir1E, dir2E, enableE);    //EST motor
Motor motS(dir1S, dir2S, enableS);    //SUD motor
Motor motW(dir1W, dir2W, enableW);    //WEST motor

//90° Directions______________________________________________________

void Move::N(int DIRECTION, int SPEED, int TIME)      //Sends robot to NORD for TIME at SPEED
    {

        Motor.motN(1,SPEED);
        Motor.motE(1,SPEED);
        Motor.motS(1,SPEED);
        Motor.motW(1,SPEED);

        
        




    }











void Move::E(int DIR, int SPEED, int TIME)      //Sends robot to EST for TIME at SPEED
    {

    }

void Move::S(int DIR, int SPEED, int TIME)      //Sends robot to SUD for TIME at SPEED
    {

    }

void Move::W(int DIR, int SPEED, int TIME)      //Sends robot to WEST for TIME at SPEED
    {

    }

//45° Directions______________________________________________________

void Move::NE(int DIR, int SPEED, int TIME)      //Sends robot to NORD-EST for TIME at SPEED
    {

    }
    
void Move::SE(int DIR, int SPEED, int TIME)      //Sends robot to SUD-EST for TIME at SPEED
    {

    }

void Move::SO(int DIR, int SPEED, int TIME)      //Sends robot to SUD-OVEST for TIME at SPEED
    {

    }

void Move::NO(int DIR, int SPEED, int TIME)      //Sends robot to NORD-OVEST for TIME at SPEED  
    {

    }

