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
    delay(5);
    compass.setNord();

    debln("setup completed");

    // debln("TESTING...");
/*
    JY901.StartIIC();
    JY901.GetMag();
    magX = JY901.stcMag.h[0];
    magY = JY901.stcMag.h[1];
    magZ = JY901.stcMag.h[2];

    / PSEUDO-CODE START

    loop 3 secondi // taro il massimo
    {
        JY901.GetMag();
        if JY901.stcMag.h[0] > maxVAL
        {
            maxVAL = JY901.stcMag.h[0];
        }
    }

        minVAL = maxVAL
    loop 3 secondi //taro il minimo partendo dal massimo
    {
        JY901.GetMag();
        if JY901.stcMag.h[0] < minVAL
        {
            minVAL = JY901.stcMag.h[0]
        }
    }

    //ho finito di tarare min e max ora uso "map" per portarlo in gradi da 0 a 359

    map(JY901.stcMag.h[0],);
    map(JY901.stcMag[0], minVAL, maxVAL, 0, 359)


    // PSEUDO-CODE STOP */


}

void loop()
{
    UDPfunc(&UDPdir, &UDPspeed, &UDPtime);

    // deb("D: ");deb(UDPdir);deb(" S: ");deb(UDPspeed);deb(" T: ");deb(UDPtime);debln(" .");

    MoveTo.Dir(UDPdir, UDPspeed, UDPtime * 1000, micros());

    UDPdir = 0;
    UDPspeed = 0;
    UDPtime = 0;
    
    delay(100);
}
