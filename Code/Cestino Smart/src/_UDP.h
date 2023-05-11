/* #include "WiFiNINA.h" // Wifi library
#include "WiFiUdp.h"  // UDP library
#include "credentials.h" // The log-in credential for wifi connection
 */

#ifndef _UDP_h
#define _UDP_h

#endif

#define UDP_MESSAGE 1
#define UDP_LOGIN 2
#define UDP_LOGOUT 3
#define UDP_NULL 4
#define UDP_HEADE_LEN 16

//int dir, speed, time;

extern void connectToAP();
extern void printWiFiData();
extern void UDP_sendPaket(int sockport, uint8_t Identfier, uint8_t *pak, size_t msize);
extern void printUDP();
extern void parseData(int *_dir, int *_speed, int *_time);
extern void printData(bool sum);
extern void UDPsetup();
extern void UDPfunc(int *_dir, int *_speed, int *_time);

