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
double i = 0.2; // 1
double d = 10;  // 3

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
    //setForcedNord();
    Vnord = 135;

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

void Compass::setAngle(int _angle)
{
    offset = Vnord + _angle;

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

        short _data = map(JY901.stcMag.h[_axis], value.min, value.max, 1, 360);
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

    // Controller.compute();

    // output = output - Bias;

    input = input - offset;

    input = map(input, 0, 360, -255, 255);

    if (input < 80 && input > -80)
    {
        output = input * -0.2;
    }
    else
    {
        output = input * -0.1;
    }

    // output *= -1;

    return output;
}

void Compass::PIDvalue(int _p, int _i, int _d)
{
    p = _p;
    i = _i;
    d = _d;
}

void Compass::test()
{
  
Adafruit_BNO055 bno = Adafruit_BNO055(55);
  Serial.println("Orientation Sensor Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  delay(1000);
    
  bno.setExtCrystalUse(true);


while(true) 
{
  /* Get a new sensor event */ 
  sensors_event_t event; 
  bno.getEvent(&event);
  
  /* Display the floating point data */
  Serial.print("X: ");
  Serial.print(event.orientation.x, 4);
  Serial.print("\tY: ");
  Serial.print(event.orientation.y, 4);
  Serial.print("\tZ: ");
  Serial.print(event.orientation.z, 4);
  Serial.println("");
  
  delay(100);
}
}