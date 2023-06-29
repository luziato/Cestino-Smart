#define wifi_net 0      //network selector: 0 smartbin 1 netmaker

#if wifi_net == 0
    #define SECRET_SSID "smartbin"
    #define SECRET_PASS "SmartB!n"
#endif

#if wifi_net == 1
#define SECRET_SSID "NETMAKER"
#define SECRET_PASS "C4s4luz14t3ll!"
#endif