#include "Arduino.h"
#include "Compass.h"

/*********DEBUGGER************/
#include "debug.h"
/*****************************/

Compass::Compass() {}
Compass::~Compass() {}

void Compass::Begin()
{
    JY901.StartIIC();
}

void Compass::setNord()
{
    int _data = 0;

    for (int i = 0; i <= 9; i++)
    {
        JY901.GetAngle();
        _data += (int)JY901.stcAngle.Angle[2]/32768*180;
        delay(6);
    }

    Vnord = round(_data / 10);
    debU("Vnord= ");deblnU(Vnord);
}

void Compass::_tare(unsigned int _duration)
{
    unsigned long _startTime = millis(); // Store the current time as the start time


    while (millis() - _startTime < _duration)
    {
        JY901.GetAngle();

        int _sensorValue = round(JY901.stcAngle.Angle[2]/32768*180); // Replace JY901.stcAngle.Angle[2]/32768*180 with your actual sensor reading

        value.max = max(_sensorValue, value.max);
        value.min = min(_sensorValue, value.min);
        delay(6);
    }
}

int Compass::GetAngleNord(void)
{
    return Vnord;    
}

int Compass::GetAngle(void)
{
    JY901.GetAngle();
    return JY901.stcAngle.Angle[2]/32768*180;    
}
