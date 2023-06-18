#include "Arduino.h"
#include "_UDP.h"
//********************************************
#include "WiFiNINA.h" // Wifi library
#include "WiFiUdp.h"  // UDP library
#include "credentials.h" // The log-in credential for wifi connection

/*********DEBUGGER************/
#include "debug.h"
/*****************************/

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID; // your network SSID (name)
char pass[] = SECRET_PASS; // your network password (use for WPA, or use as key for WEP)

int status = WL_IDLE_STATUS; // Status of WiFi connection

WiFiSSLClient client; // Instantiate the Wifi client

// UDP Variables
unsigned int localPort = 30000;          // local port to listen on
const char *computerIP = "192.168.1.50"; // ENTER YOUR COMPUTER'S IP BETWEEN QUOTES

WiFiUDP Udp; // Instantiate UDP class

unsigned char udpTXBuffer[255];
unsigned char udpRXBuffer[255];

unsigned long udpReconnectionTimer = 0;
int reconnectingTimer = 4000;


//********************************************


void UDPsetup()
{
  if (WiFi.status() == WL_NO_MODULE) // Check for Wifi Module. If no module, don't continue
  {
    deblnU("No WIFI card found.");
    while (true)
      ;
  }

  // Connect to Wifi Access Point
  connectToAP();

  // UDP Connect
  Udp.begin(localPort);
  
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

void UDPfunc(int *_dir, int *_speed, int *_time)
{
  int packetSize = Udp.parsePacket();

  reconnect(reconnectingTimer);
  
  if (packetSize)
  {
    // read the packet into packetBufffer
    // int len = Udp.read(udpRXBuffer, 255);
    Udp.read(udpRXBuffer, 255);
    UDP_getData(udpRXBuffer);

    UDP_getData(udpRXBuffer);
    parseData(udpRXBuffer, _dir, _speed, _time);
    
    //printData(true);

  }
  else
  {
    memset(udpRXBuffer, 0, sizeof(udpRXBuffer)); // cleaning buffer
    *_dir = 0;
    *_speed = 0;
    *_time = 0;
  }

}

//
//  Functions ************************************************
//

// UDP to Int
void parseData(unsigned char* rxbf, int *_dir, int *_speed, int *_time)
{ // split the data into its parts

  char *strtokIndx; // this is used by strtok() as an index

    switch(rxbf[0])
    {
      case UDP_MESSAGE:
          // Converts direction
          strtokIndx = strtok((char *)UDP_getData(rxbf), ";"); // get the first part - the string
          *(_dir) = atoi(strtokIndx); // convert this part to an integer

          // Converts speed
          strtokIndx = strtok(NULL, ";"); // this continues where the previous call left off
          *(_speed) = atoi(strtokIndx);       // convert this part to an integer

          // Converts time
          strtokIndx = strtok(NULL, ";"); // this continues where the previous call left off
          *(_time) = atoi(strtokIndx);        // convert this part to an integer

          udpReconnectionTimer = millis();

          debU(" dir: ");debU(*_dir);debU("; speed: ");debU(*_speed);debU("; time: ");debU(*_time);deblnU("; end message");
        break;

      case UDP_POOLING:
          udpReconnectionTimer = millis();
          deblnU("UDP_POOLING");
        break;
    }
 
}

// Print UDP paket
void printUDP()
{
  int packetSize = Udp.parsePacket();
  deblnU("Contents:");
  for (int i = 0; i < packetSize; i++)
  {

    char buffFeed[10];
    sprintf(buffFeed, "%02x - %c ", udpRXBuffer[i], udpRXBuffer[i]);
    deblnU(buffFeed);
  }
  deblnU("");
}

// Print extracted data, take bool: TRUE: extracted data +1; FALSE: just estracted data
void printData(bool sum)
{
 /* if (sum == true)
  {
    debU(dir + 1);
    debU(" ; ");
    debU(speed + 1);
    debU(" ; ");
    debU(time + 1);
    deblnU(" .");
  }
  else
  {
    debU(dir);
    debU(" ; ");
    debU(speed);
    debU(" ; ");
    debU(time);
    deblnU(" .");
  }*/
}

// Connect to wifi network
void connectToAP()
{
  // Try to connect to Wifi network
  while (status != WL_CONNECTED)
  {
    status = WiFi.begin(ssid, pass);
    deblnU("Connecting WiFi...");

    // wait 1 second for connection:
    delay(1000);
  }

  printWiFiData();
}

// Print WiFi data
void printWiFiData()
{
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  debU("IP address : ");
  deblnU(ip);

  debU("Subnet mask: ");
  deblnU((IPAddress)WiFi.subnetMask());

  debU("Gateway IP : ");
  deblnU((IPAddress)WiFi.gatewayIP());
}

void reconnect(int period)
{
  if ((udpReconnectionTimer + period) < millis() )
  {
    UDP_sendPaket(localPort, UDP_LOGIN, 0, 0);
    debU(udpReconnectionTimer);debU(" ; ");debU(period);debU(" ; ");debU(millis());debU(" ; ");debU(udpReconnectionTimer+period);debU(" ; ");
    deblnU("Inviato Login");
    udpReconnectionTimer = millis();
  }
}
