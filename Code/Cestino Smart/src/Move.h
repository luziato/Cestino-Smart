#ifndef Move_h
#define Move_h

#include "Arduino.h"

class Move
{
public:

    void move(               //  Defining: direction speed and time
        int DIRECTION,        //  Direction of the robot
        int SPEED,      //  Speed of the robot
        int TIME        //  Timer to execute the command
        );      

    // 90° Directions
    void NORD(int DIR, int SPEED, int TIME);       //Sends robot to NORD for TIME at SPEED
    void EST(int DIR, int SPEED, int TIME);       //Sends robot to EST for TIME at SPEED
    void SUD(int DIR, int SPEED, int TIME);       //Sends robot to SUD for TIME at SPEED
    void WEST(int DIR, int SPEED, int TIME);       //Sends robot to WEST for TIME at SPEED
    //45° Directions
    void NE(int DIR, int SPEED, int TIME);       //Sends robot to NORD-EST for TIME at SPEED
    void SE(int DIR, int SPEED, int TIME);       //Sends robot to SUD-EST for TIME at SPEED
    void SO(int DIR, int SPEED, int TIME);       //Sends robot to SUD-OVEST for TIME at SPEED
    void NO(int DIR, int SPEED, int TIME);       //Sends robot to NORD-OVEST for TIME at SPEED  
    
private:

};

#endif