#ifndef CharToInt_h
#define CharToInt_h

#include "Arduino.h"

class UDPtoINT
{
private:
    const static byte CHARS_NUM = 32;
    char recChars[CHARS_NUM];
    char tempChars[CHARS_NUM]; // temporary array for use when parsing

    // variables to hold the parsed data
    char _messageFromPC[CHARS_NUM] = {0};
    int _int1 = 0; // First set of data: Direction
    int _int2 = 0; // Second set of data: Speed
    int _int3 = 0; // Third set of data: Time

    bool _newData = false;

public:

    int dir = _int1;
    int speed = _int2;
    int time = _int3;

    UDPtoINT(/* args */);
    ~UDPtoINT();


    void recvData();
    void parseData();
    void showData();
};



#endif