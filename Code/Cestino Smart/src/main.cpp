#include <Arduino.h>

/*********DEBUGGER************/
#include "debug.h"
/*****************************/

// Self-Made
#include "const.h"
#include "Move.h"
#include "_UDP.h"

Move MoveTo;

Compass compass;

int UDPdir;
int UDPspeed;
int UDPtime;

void setup()
{
    Serial.begin(115200);

    UDPsetup();

    //Bussola
    compass.Begin();

    MoveTo.Tare(6000);

    debln("setup completed");

    // debln("TESTING...");


}

void loop()
{
    UDPfunc(&UDPdir, &UDPspeed, &UDPtime);

    // deb("D: ");deb(UDPdir);deb(" S: ");deb(UDPspeed);deb(" T: ");deb(UDPtime);debln(" .");

    MoveTo.Dir4(UDPdir, UDPspeed, UDPtime * 1000, micros());

    UDPdir = 0;
    UDPspeed = 0;
    UDPtime = 0;
    
    //delay(1);
}

