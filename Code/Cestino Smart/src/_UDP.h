#ifndef _UDP_h
#define _UDP_h

#include "WiFiNINA.h" // Wifi library
#include "WiFiUdp.h"  // UDP library
//#include "main.h"


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

//int dir, speed, time;

void connectToAP();
void printWiFiData();
void UDP_sendPaket(int sockport, uint8_t Identfier, uint8_t *pak, size_t msize);
void printUDP();
void parseData();
void printData(bool sum);
void UDPsetup();
void UDPfunc();

#endif