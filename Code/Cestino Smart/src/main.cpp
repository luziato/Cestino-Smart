#include <Arduino.h>

//Self-Made
#include <define.h>
#include <Move.h>
#include <Motor.h>

Motor::Motor motor;


void setup() {

  Motor.begin(dir1N, dir2N, enableN);    //NORD motor
  Motor.begin(dir1E, dir2E, enableE);    //EST motor
  Motor.begin(dir1S, dir2S, enableS);    //SUD motor
  Motor.begin(dir1W, dir2W, enableW);    //WEST motor 

  
}

void loop() {
  // put your main code here, to run repeatedly:
}