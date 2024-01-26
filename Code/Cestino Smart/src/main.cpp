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

int UDPdir;
int UDPspeed;
int UDPtime;

bool mot_KILL = false;

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



     //delay(10);
}
