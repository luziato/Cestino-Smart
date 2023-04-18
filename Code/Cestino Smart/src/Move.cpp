#include "Arduino.h"
#include "define.h"
#include "Move.h"
#include "Motor.h"
#include "Motor.cpp"

/* 

//  Motor definitions
Motor::Motor motor motN(dir1N, dir2N, enableN);    //NORD motor
Motor motE(dir1E, dir2E, enableE);    //EST motor
Motor motS(dir1S, dir2S, enableS);    //SUD motor
Motor motW(dir1W, dir2W, enableW);    //WEST motor 

*/


Motor motN;
Motor motE;
Motor motS;
Motor motW;




//90° Directions______________________________________________________

void Move::NORD(int DIRECTION, int SPEED, int TIME)      //Sends robot to NORD for TIME at SPEED
    {

        Motor::motor.motN(1,SPEED);
        //motE.motor(1,SPEED);
        //motS.motor(1,SPEED);
        // motor(1,SPEED);

        
        


        //return(0);

    }

void Move::EST(int DIR, int SPEED, int TIME)      //Sends robot to EST for TIME at SPEED
    {

    }

void Move::SUD(int DIR, int SPEED, int TIME)      //Sends robot to SUD for TIME at SPEED
    {

    }

void Move::WEST(int DIR, int SPEED, int TIME)      //Sends robot to WEST for TIME at SPEED
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

