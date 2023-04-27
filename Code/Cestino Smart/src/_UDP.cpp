#include "_UDP.h"


void UDPsetup()
{
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

void UDPfunc()
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

// Print WiFi data
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
