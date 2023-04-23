

/**
 * Sketch for Arduino Nano 33 IoT
 *
 * Connects to WiFi network and uses UDP to send
 * onboard sensor data.
 *
 * Sensors: 3D Gyro and 3D accelerometer (6 values)
 * Sensor values are Floats cast to a byte array.
 * They must be recast to Float on the remote device
 * receiving the UDP data.
 *
 * This is to connect with a JUCE application running on my laptop:
 * https://github.com/RFullum/MastersProject1
 */

#include <Arduino.h>

#include <WiFiNINA.h>        // Wifi library
#include <WiFiUdp.h>         // UDP library
#include <Arduino_LSM6DS3.h> // IMU accelerometer library

#include "credentials.h" // The log-in credential for wifi connection

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID; // your network SSID (name)
char pass[] = SECRET_PASS; // your network password (use for WPA, or use as key for WEP)

int status = WL_IDLE_STATUS; // Status of WiFi connection

WiFiSSLClient client; // Instantiate the Wifi client

// UDP Variables
unsigned int localPort = 30000;          // local port to listen on
const char *computerIP = "192.168.1.50"; // ENTER YOUR COMPUTER'S IP BETWEEN QUOTES
const unsigned int gyroXPort = 30000;    // Destination Ports

WiFiUDP Udp; // Instantiate UDP class

// Byte Arrays to send to JUCE
byte gyroXBuff[4];

unsigned char udpTXBuffer[255];
unsigned char udpRXBuffer[255];

#define UDP_MESSAGE 1
#define UDP_LOGIN 2
#define UDP_LOGOUT 3
#define UDP_NULL 4
#define UDP_HEADE_LEN 16

void connectToAP();
void printWiFiData();
void UDP_sendPaket(int sockport, uint8_t Identfier, uint8_t *pak, size_t msize);
void blink();

//
// ***********************************************************
//
#define btn 2

int count = 0;

void blink(int count) // Blink the led "count" times
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);

  for (int i = 0; i < count; i++)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }

  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
}

void setup()
{
  Serial.begin(115200); // starting serial

  pinMode(btn, INPUT_PULLUP); // button
  pinMode(LED_BUILTIN, OUTPUT);

  while (!Serial)
  {
  } // wait for serial port to connect. Needed for native USB

  if (WiFi.status() == WL_NO_MODULE) // Check for Wifi Module. If no module, don't continue
  {
    Serial.println("No WIFI card found.");
    while (true)
      ;
  }

  // Connect to Wifi Access Point
  connectToAP();

  // UDP Connect with report via serial
  Udp.begin(localPort);

  delay(1000 * 3);
  UDP_sendPaket(localPort, UDP_LOGIN, 0, 0);
  Serial.println("Inviato Login");
}

char *UDP_getData(uint8_t *pak)
{
  return ((char *)&pak[UDP_HEADE_LEN - 4]);

}

void UDP_sendPaket(int sockport, uint8_t Identfier, uint8_t *pak, size_t msize)
{

  char bf[20];
  Udp.beginPacket(computerIP, sockport);

  udpTXBuffer[0] = (uint8_t)Identfier; // ID
  udpTXBuffer[1] = 0;
  udpTXBuffer[2] = 0;
  udpTXBuffer[3] = 0;
  udpTXBuffer[4] = 4; // Name Len
  udpTXBuffer[5] = 0;
  udpTXBuffer[6] = 0;
  udpTXBuffer[7] = 0;
  udpTXBuffer[8] = (uint8_t)msize; // Msg Len (max len 255)
  udpTXBuffer[9] = 0;
  udpTXBuffer[10] = 0;
  udpTXBuffer[11] = 0;

  udpTXBuffer[12] = 'C';
  udpTXBuffer[13] = 'E';
  udpTXBuffer[14] = 'S';
  udpTXBuffer[15] = 'T';

  for (int im = 0; im < (int)msize; im++)
    udpTXBuffer[UDP_HEADE_LEN + im] = pak[im];

/*    for (int itx = 0; itx < (int)(UDP_HEADE_LEN + msize); itx++)
  {
    sprintf(bf, "%02x - %c ", udpTXBuffer[itx], udpTXBuffer[itx]);
    Serial.println(bf);
  }  */

  Udp.write(udpTXBuffer, UDP_HEADE_LEN + msize);
  Udp.endPacket();
}

int iloop = 0;
uint8_t buff[50];

void loop()
{
  // delay(1000);
  // int Val = digitalRead(btn);
  /* if(Val == LOW)
   {
     sprintf((char*)buff, "%03d", iloop++);
     UDP_sendPaket(localPort, UDP_MESSAGE, buff, strlen((char*)buff));
     Serial.println("Inviato DATI");
   }
 */
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    /*
      Serial.print("Received packet of size ");
      Serial.println(packetSize);
      Serial.print("From ");
      IPAddress remoteIp = Udp.remoteIP();
      Serial.print(remoteIp);
      Serial.print(", port ");
      Serial.println(Udp.remotePort());
  */
    // read the packet into packetBufffer
    // int len = Udp.read(udpRXBuffer, 255);
    Udp.read(udpRXBuffer, 255);
    UDP_getData(udpRXBuffer);

        Serial.println("Contents:");
        for(int i = 0; i < packetSize; i++)
        { 

          char buffFeed [10];
          sprintf(buffFeed, "%02x - %c ", udpRXBuffer[i], udpRXBuffer[i]);
          Serial.println(buffFeed);
        }
        Serial.println("");

    Serial.println(UDP_getData(udpRXBuffer));

    

    //Serial.println(udpRXBuffer);
    //count = udpRXBuffer* ;

    //blink(5);
  }

  /*
  Udp.beginPacket(computerIP, accelZPort);
  Udp.write(accelZBuff, 4);
  Udp.endPacket();
  */
}

//
//  Functions ************************************************
//
/*
void floatToBuff(byte udpBuffer[4], float sensorVal)
{
  byte *sensorValByte = reinterpret_cast<byte*>(&sensorVal);
  memcpy(udpBuffer, sensorValByte, sizeof(sensorValByte));
}
*/

// Connect to wifi network
void connectToAP()
{
  // Try to connect to Wifi network
  while (status != WL_CONNECTED)
  {
    status = WiFi.begin(ssid, pass);
    Serial.println("Connecting WiFi...");

    // wait 1 second for connection:
    delay(1000);
  }

  printWiFiData();
}

void printWiFiData()
{
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP address : ");
  Serial.println(ip);

  Serial.print("Subnet mask: ");
  Serial.println((IPAddress)WiFi.subnetMask());

  Serial.print("Gateway IP : ");
  Serial.println((IPAddress)WiFi.gatewayIP());
}
