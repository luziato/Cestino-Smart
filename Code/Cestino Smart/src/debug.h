#ifndef debug_h
#define debug_h

/*****************_SET_*****************/
    #define DEBUG 1
        #define DEBUG_UDP 1
        #define DEBUG_MOVE 1
            #define DEBUG_MOVE1 0
/***************************************/




    #if DEBUG
     // General debugging
     #define deb(x) Serial.print(x)
     #define debln(x) Serial.println(x)

        // Debugger for UDP
        #if DEBUG_UDP == 1
         #define debU(x) Serial.print(x)
         #define deblnU(x) Serial.println(x)
        #else
         #define debU(x)
         #define deblnU(x)
        #endif

        // Debugger for MOVE
        #if DEBUG_MOVE == 1
         #define debM(x) Serial.print(x)
         #define deblnM(x) Serial.println(x)
            // Debugger for MOVE level 1
            #if DEBUG_MOVE1 == 1
             #define debM1(x) Serial.print(x)
             #define deblnM1(x) Serial.println(x)
            #else
             #define debM1(x)
             #define deblnM1(x)
            #endif
        #else
         #define debM(x)
         #define deblnM(x)
        #endif

    #else
     #define deb(x)
     #define debln(x)
     
     #define debU(x)
     #define deblnU(x)
     #define debM(x)
     #define deblnM(x)
     #define debM1(x)
     #define deblnM1(x)

    #endif

#endif