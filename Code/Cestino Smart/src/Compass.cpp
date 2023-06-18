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

void Compass::Angle_Correction()
{
    JY901.GetMag();

    _Vnord++;
    // JY901.stcMag.h[0];
}

void Compass::setNord()
{
    int _data = 0;

    for (int i = 0; i <= 9; i++)
    {
        JY901.GetMag();
        _data += round(JY901.stcMag.h[0]);
        delay(11);
    }

    _Vnord = round(_data / 10);
}

void Compass::_tare(unsigned int _duration)
{
    unsigned long _startTime = millis(); // Store the current time as the start time


    while (millis() - _startTime < _duration)
    {
        JY901.GetMag();

        int _sensorValue = round(JY901.stcMag.h[0]); // Replace JY901.stcMag.h[0] with your actual sensor reading

        _value.max = max(_sensorValue, _value.max);
        _value.min = min(_sensorValue, _value.min);
        delay(11);
    }
}

int Compass::GetAngle(bool _isTaring)
{
    JY901.GetMag();

    if (_isTaring)
    {
        return(JY901.stcMag.h[0]);
    } else
    {
        return( map(JY901.stcMag.h[0], _value.min, _value.max, -180, 180) );
    }
}
