#include <Arduino.h>
// Example 5 - Receive with start- and end-markers combined with parsing

const byte CHARS_NUM = 32;
char recChars[CHARS_NUM];
char tempChars[CHARS_NUM];        // temporary array for use when parsing

      // variables to hold the parsed data
char messageFromPC[CHARS_NUM] = {0};
int int1 = 0;
float floatFromPC = 0.0;

boolean newData = false;

//============

void setup() {
    Serial.begin(9600);
    Serial.println("This demo expects 3 pieces of data - text, an integer and a floating point value");
    Serial.println("Enter data in this style <HelloWorld, 12, 24.7>  ");
    Serial.println();
}

//============

void loop() {
    recvWithStartEndMarkers();
    if (newData == true) {
        strcpy(tempChars, recChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0
        parseData();
        showData();
        newData = false;
    }
}

//============

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
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
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

//============

void parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index

    strtokIndx = strtok(tempChars,",");      // get the first part - the string
    strcpy(messageFromPC, strtokIndx); // copy it to messageFromPC
 
    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    int1 = atoi(strtokIndx);     // convert this part to an integer

    strtokIndx = strtok(NULL, ",");
    floatFromPC = atof(strtokIndx);     // convert this part to a float

}

//============

void showData() {
    Serial.print("Message ");
    Serial.println(messageFromPC);
    Serial.print("Integer ");
    Serial.println(int1);
    Serial.print("Float ");
    Serial.println(floatFromPC);
}