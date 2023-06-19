#include "Arduino.h"

#define Rangle analogRead(A1)

int tare = 20;
int zone = 5;

int min = 0;
int max = 1024;

int newData = 0;

void setup()
{
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    Serial.begin(9600);
    tarAngle();
}

void loop()
{

    newData = map(getAngle(), min, max, -180, 180);
     
    Correct();

    Serial.print("Read -> ");
    Serial.print(getAngle());
    Serial.print(" ; ");
    Serial.print("newData -> ");
    Serial.print(newData);
    Serial.print(" ; ");

}

int getAngle()
{
    int data = analogRead(A0);

    return (data);
}

void Correct()
{
    int ang = newData;
    if (abs(ang + zone) || abs(ang - zone) < zone)
    {
        if (ang > tare)
        {
            Serial.print("CCW by ");
            Serial.println(ang - tare);
        }
        else
        {
            Serial.print("CW by ");
            Serial.println(ang + tare);
        }
    } else {Serial.println("STOP");}
}

int tarAngle ()
{
    newData = map(getAngle(), min, max, -180, 180);
    return (newData + tare);
}

//NOT WPRKIN DEAD-ZONE THE REST IS WORKING