#include "Arduino.h"
#include "Compass.h"
#include "_UDP.h"

/*********DEBUGGER************/
#include "debug.h"
/*****************************/

ArduPID Controller;

// Arbitrary setpoint and gains - adjust these as fit for your project:
double setpoint = 180;
double p = 0.375;
double i = 0.2;   //1
double d = 10;   //3

Compass::Compass() {}
Compass::~Compass() {}

void Compass::Begin()
{
    JY901.StartIIC();

    Controller.begin(&input, &output, &setpoint, p, i, d);
    Controller.setOutputLimits(0, 512);
    Controller.setWindUpLimits(-10, 10); // Groth bounds for the integral term to prevent integral wind-up
    Controller.setBias(Bias);
    Controller.start();
}

void Compass::setNord()
{
    int _data = 0;

    for (int i = 0; i < 32; i++)
    {
        JY901.GetMag();

        _data += (int)10000 + JY901.stcMag.h[0];
        delay(6);
    }
    _data = _data / 32;
    Vnord = map(_data, value.min, value.max, 0, 359);

    debU("Vnord= ");
    deblnU(Vnord);
    debU("Min= ");
    deblnU(value.min);
    debU("Max= ");
    deblnU(value.max);

    // UDPlogI("Vnord", Vnord);
}

void Compass::setForcedNord()
{
    Vnord = (value.min + value.max) / 2;
}

void Compass::_tare(unsigned int _duration)
{
    unsigned long _startTime = millis(); // Store the current time as the start time

    value.min = 10000;
    value.max = 0;

    while (millis() - _startTime < _duration)
    {
        int _sensorValue = GetAllAngleRAW(false, 1);

        value.max = max(_sensorValue, value.max);
        value.min = min(_sensorValue, value.min);
        ///*
        debC("min:");
        debC(value.min);
        debC(" MAX:");
        deblnC(value.max);
        //*/

        delay(6);
    }
    setForcedNord();
    Vnord = 180;

    debC("Tare ended, min val: ");
    debC(value.min);
    debC(" MAX: ");
    deblnC(value.max);
    // UDPlogI("min", value.min);
    // UDPlogI("MAX", value.max);
}

int Compass::GetNord(void)
{
    return Vnord;
}

int Compass::GetAngle()
{
    JY901.GetMag();

    int _val = JY901.stcMag.h[1];
    // Roll[0] / 32768.0f * 180.0f;

    return map(_val, value.min, value.max, 1, 360);
}

int Compass::GetAngleRAW(void)
{
    JY901.GetMag();
    int _val = JY901.stcMag.h[0]; // + 10000;

    return _val;
}

int Compass::GetAllAngleRAW(bool _prop, int _axis)
{
    if (_prop)
    {
        JY901.GetMag();

        short _data = map(JY901.stcMag.h[_axis], value.min, value.max, 0, 359);
        return _data;
    }
    else
    {
        JY901.GetMag();

        int _data = JY901.stcMag.h[_axis];
        return _data;
    }
}

double Compass::mapF(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/*int Compass::CorrectDir()
{
    int _dir = 0;

    input = GetAllAngleRAW(true, 1); // Replace with sensor feedback

    Controller.compute();

    output = output - Bias;

    if (output < 0)
    {
        _dir = 13;
    }
    else
    {
        _dir = 14;
    }

    return _dir;
}*/

int Compass::Correct()
{

    input = GetAllAngleRAW(true, 1); // Replace with sensor feedback

    Controller.compute();

    output = output - Bias;

    return output;
}

void Compass::PIDvalue(int _p, int _i, int _d)
{
    p = _p;
    i = _i;
    d = _d;
    
}