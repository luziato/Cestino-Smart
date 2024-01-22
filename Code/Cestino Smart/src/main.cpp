#include <Arduino.h>

/*********DEBUGGER************/
#include "debug.h"
/*****************************/

// Self-Made
#include "const.h"
#include "Move.h"
#include "_UDP.h"
#include "Compass.h"
#include "SimpleKalmanFilter.h"

Move MoveTo;

Compass compass;

SimpleKalmanFilter simpleKalmanFilter(2, 2, 0.01);

int UDPdir;
int UDPspeed;
int UDPtime;

bool mot_KILL = false;

int bat = 0;

void setup()
{
    delay(2000);
    Serial.begin(9600);
    
    //waitForSerial;        //ON/OFF SERIAL CHECK
    
    Serial.println("ciao");

    UDPsetup();

    debln("udp-setup done");

    // Bussola
    compass.Begin();

    debln("bussola-setup done");

    MoveTo.Tare(40);

    debln("setup completed");

}

void loop()
{
    UDPfunc(&UDPdir, &UDPspeed, &UDPtime);

    // deb("D: ");deb(UDPdir);deb(" S: ");deb(UDPspeed);deb(" T: ");deb(UDPtime);debln(" .");

    if (!mot_KILL)
    {
    
    MoveTo.Dir3(UDPdir, UDPspeed, UDPtime * 1000, micros());
    
    }

    //UDPdir = 0;
    UDPspeed = 0;
    UDPtime = 0;

    
    //bat = simpleKalmanFilter.updateEstimate(analogRead(A6));
    

    if (bat < 310)
    {
        //send low battery allert mesage
        /*
        tone(12, 1000, 500);
        delay(1000);
        tone(12, 1000, 500);
        */
    }
    

     //delay(10);
}
