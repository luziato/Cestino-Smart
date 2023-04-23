#include "UDPtoINT.h"

UDPtoINT::UDPtoINT(){}
UDPtoINT::~UDPtoINT(){}

void recvWithStartEndMarkers();
void parseData();
void showData();

/* void loop() {
    recvData();
    if (_newData == true) {
        strcpy(tempChars, recChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0
        parseData();
        showData();
        newData = false;
    }
} */

//============

void UDPtoINT::recvData() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && _newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                recChars[ndx] = rc;
                ndx++;
                if (ndx >= CHARS_NUM) {
                    ndx = CHARS_NUM - 1;
                }
            }
            else {
                recChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                _newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

//============

void UDPtoINT::parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index

    //Converts direction
    strtokIndx = strtok(tempChars,";");      // get the first part - the string
    _int1 = atoi(strtokIndx);     // convert this part to an integer

    //Converts speed
    strtokIndx = strtok(NULL, ";"); // this continues where the previous call left off
    _int2 = atoi(strtokIndx);     // convert this part to an integer

    //Converts time
    strtokIndx = strtok(NULL, ";"); // this continues where the previous call left off
    _int3 = atoi(strtokIndx);     // convert this part to an integer

}

//============

void UDPtoINT::showData() {

    Serial.print("Message: ");
    Serial.print("Direction: ");
    Serial.print(_int1);
    Serial.print(", Speed: ");
    Serial.print(_int2);
    Serial.print(", Time: ");
    Serial.println(_int2);

}