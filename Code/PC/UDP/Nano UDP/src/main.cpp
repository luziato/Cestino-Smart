#include <Arduino.h>

#include <WiFiNINA.h> // Wifi library
#include <WiFiUdp.h>  // UDP library

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

unsigned char udpTXBuffer[255];
unsigned char udpRXBuffer[255];

#define UDP_MESSAGE 1
#define UDP_LOGIN 2
#define UDP_LOGOUT 3
#define UDP_NULL 4
#define UDP_HEADE_LEN 16

int dir, speed, time;

void connectToAP();
void printWiFiData();
void UDP_sendPaket(int sockport, uint8_t Identfier, uint8_t *pak, size_t msize);
void printUDP();
void parseData();
void printData(bool sum);

//
// ***********************************************************
//
#define btn 2

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

  Udp.write(udpTXBuffer, UDP_HEADE_LEN + msize);
  Udp.endPacket();
}

void loop()
{
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // read the packet into packetBufffer
    // int len = Udp.read(udpRXBuffer, 255);
    Udp.read(udpRXBuffer, 255);
    UDP_getData(udpRXBuffer);

    Serial.print("-> ");
    Serial.println((char *)UDP_getData(udpRXBuffer));

    parseData();

    printData(true);

    memset(udpRXBuffer, 0, sizeof(udpRXBuffer)); // cleaning buffer
  }
}

//
//  Functions ************************************************
//

// UDP to Int
void parseData()
{ // split the data into its parts

  char *strtokIndx; // this is used by strtok() as an index

  // Converts direction
  strtokIndx = strtok((char *)UDP_getData(udpRXBuffer), ";"); // get the first part - the string
  dir = atoi(strtokIndx); // convert this part to an integer

  // Converts speed
  strtokIndx = strtok(NULL, ";"); // this continues where the previous call left off
  speed = atoi(strtokIndx);       // convert this part to an integer

  // Converts time
  strtokIndx = strtok(NULL, ";"); // this continues where the previous call left off
  time = atoi(strtokIndx);        // convert this part to an integer
}

// Print UDP paket
void printUDP()
{
  int packetSize = Udp.parsePacket();
  Serial.println("Contents:");
  for (int i = 0; i < packetSize; i++)
  {

    char buffFeed[10];
    sprintf(buffFeed, "%02x - %c ", udpRXBuffer[i], udpRXBuffer[i]);
    Serial.println(buffFeed);
  }
  Serial.println("");
}

// Print extracted data, take bool: TRUE: extracted data +1; FALSE: just estracted data
void printData(bool sum)
{
  if (sum == true)
  {
    Serial.print(dir + 1);
    Serial.print(" ; ");
    Serial.print(speed + 1);
    Serial.print(" ; ");
    Serial.print(time + 1);
    Serial.println(" .");
  }
  else
  {
    Serial.print(dir);
    Serial.print(" ; ");
    Serial.print(speed);
    Serial.print(" ; ");
    Serial.print(time);
    Serial.println(" .");
  }
}

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
