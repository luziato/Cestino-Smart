#include "Arduino.h"
#include "Compass.h"
#include "_UDP.h"

/*********DEBUGGER************/
#include "debug.h"
/*****************************/

ArduPID Controller;

Adafruit_BNO055 bno = Adafruit_BNO055(-1, 0x28, &Wire);

// Arbitrary setpoint and gains - adjust these as fit for your project:
double setpoint = 150;
double PID_p = 0.2; // 375;
double PID_i = 0.2; // 1
double PID_d = 10;  // 3

Compass::Compass() {}
Compass::~Compass() {}

void Compass::Begin()
{

    if (!bno.begin())
    {
        /* There was a problem detecting the BNO055 ... check your connections */
        Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        while (1)
            ;
    }

    bno.setExtCrystalUse(true);

    Controller.begin(&input, &output, &setpoint, PID_p, PID_i, PID_d);
    Controller.setOutputLimits(0, 512);
    Controller.setWindUpLimits(-10, 10); // Groth bounds for the integral term to prevent integral wind-up
    Controller.setBias(Bias);
    Controller.start();
}

void Compass::setNord(int _fase)
{
    if (_fase == 0)
    {
        int _data = 0;

        for (int i = 0; i < 15; i++)
        {
            _data += GetAngle();
            delay(12);
        }
        Vnord = _data / 15;
        setpoint = Vnord

        debU("Vnord= ");
        deblnU(Vnord);
    }
    
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
        int _sensorValue = GetAngle();

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

void Compass::setAngle(int _angle)
{
    offset = Vnord + _angle;
}

int Compass::GetAngle()
{
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    return euler.x();
}

double Compass::mapF(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/*int Compass::CorrectDir()
{
    int _dir = 0;

    input = GetAngle(); // Replace with sensor feedback

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

    input = GetAngle(); // Replace with sensor feedback

    

    //input = input - Vnord;

    Controller.compute();

    output = output - Bias;


    // input = map(input, 0, 360, -255, 255);

    /*if (input < 80 && input > -80)
    {
        output = input * -0.3;
    }
    else
    {
        output = input * -0.1;
    }*/

    output *= -1;

    return output;
}

void Compass::PIDvalue(float _p, float _i, float _d)
{

    Controller.setCoefficients(_p, _i, _d);
    PID_p = _p;
    PID_i = _i;
    PID_d = _d;
}

void Compass::test()
{
    while (true)
    {

        // Possible vector values can be:
        // - VECTOR_ACCELEROMETER - m/s^2
        // - VECTOR_MAGNETOMETER  - uT
        // - VECTOR_GYROSCOPE     - rad/s
        // - VECTOR_EULER         - degrees
        // - VECTOR_LINEARACCEL   - m/s^2
        // - VECTOR_GRAVITY       - m/s^2
        imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

        /* Display the floating point data */
        //Serial.print("X: ");
        //Serial.print(euler.x());
        //Serial.print(" Y: ");
        //Serial.print(euler.y());
        //Serial.print(" Z: ");
        //Serial.print(euler.z());
        //Serial.print("\t\t");

        /*
        // Quaternion data
        imu::Quaternion quat = bno.getQuat();
        Serial.print("qW: ");
        Serial.print(quat.w(), 4);
        Serial.print(" qX: ");
        Serial.print(quat.x(), 4);
        Serial.print(" qY: ");
        Serial.print(quat.y(), 4);
        Serial.print(" qZ: ");
        Serial.print(quat.z(), 4);
        Serial.print("\t\t");
        */

        /* Display calibration status for each sensor. */
        uint8_t system, gyro, accel, mag = 0;
        bno.getCalibration(&system, &gyro, &accel, &mag);
        Serial.print(">Sys:");
        Serial.println(system, DEC);
        Serial.print(">Gyro:");
        Serial.println(gyro, DEC);
        Serial.print(">Accel:");
        Serial.println(accel, DEC);
        Serial.print(">Mag:");
        Serial.println(mag, DEC);

        delay(100);
    }
}

short Compass::IMUcalib()
{
  /* Get the four calibration values (0..3) */
  /* Any sensor data reporting 0 should be ignored, */
  /* 3 means 'fully calibrated" */
  /* The data should be ignored until the system calibration is > 0 */
  uint8_t _system, _gyro, _accel, _mag;
  _system = _gyro = _accel = _mag = 0;
  bno.getCalibration(&_system, &_gyro, &_accel, &_mag);

  return _system;
  
  /*
  Serial.print("\t");
  if (!system)
  {
    Serial.print("! ");
  }

  // Display the individual values
  Serial.print("Sys:");
  Serial.print(system, DEC);
  Serial.print(" G:");
  Serial.print(gyro, DEC);
  Serial.print(" A:");
  Serial.print(accel, DEC);
  Serial.print(" M:");
  Serial.print(mag, DEC);
  */
}