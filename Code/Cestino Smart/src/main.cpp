#include <Arduino.h>

/*********DEBUGGER************/
#include "debug.h"
/*****************************/

// Self-Made
#include "const.h"
#include "Move.h"
#include "_UDP.h"

Move MoveTo;

int UDPdir;
int UDPspeed;
int UDPtime;

void setup()
{
    Serial.begin(115200);

    UDPsetup();

    debln("setup completed");

    // debln("TESTING...");
}

void loop()
{
    UDPfunc(&UDPdir, &UDPspeed, &UDPtime);

    // deb("D: ");deb(UDPdir);deb(" S: ");deb(UDPspeed);deb(" T: ");deb(UDPtime);debln(" .");

    MoveTo.Dir(UDPdir + 1, UDPspeed, UDPtime * 1000, micros());

    //delay(10);
}
