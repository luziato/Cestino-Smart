#ifndef MyClass_h
#define MyClass_h

#include "Arduino.h" 

class MyClass 
{
public:

	MyClass(int pin);
    
	void myFunction(int blinkRate);

private:

	int _pin;
};

#endif