#ifndef debug_h
#define debug_h


/*****************_SET_*****************/
    #define DEBUG 1
        #define DEBUG_COMPASS 1
        #define DEBUG_UDP 1
        #define DEBUG_MOVE 1
            #define DEBUG_MOVE1 0
            #define DEBUG_MOVEA 0
/***************************************/




    #if DEBUG
     #define waitForSerial while(!Serial){} //wait for Serial port to open
     // General debugging
     #define deb(x) Serial.print(x)
     #define debln(x) Serial.println(x)

        //Debbugger for Compass
        #if DEBUG_COMPASS == 1
            #define debC(x) Serial.print(x)
            #define deblnC(x) Serial.print(x)
        #else
            #define debC(x)
            #define deblnC(x)
        #endif

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
            // Debugger for MOVE ANGLE
            #if DEBUG_MOVEA == 1
             #define debMA(x) Serial.print(x)
             #define deblnMA(x) Serial.println(x)
            #else
             #define debMA(x)
             #define deblnMA(x)
            #endif
        #else
         #define debM(x)
         #define deblnM(x)
         #define debMA(x)
         #define deblnMA(x)
         #define debM1(x)
         #define deblnM1(x)
        #endif

    #else
     #define deb(x)
     #define debln(x)
     
     #define debC(x)
     #define deblnC(x)
     #define debU(x)
     #define deblnU(x)
     #define debM(x)
     #define deblnM(x)
     #define debM1(x)
     #define deblnM1(x)

    #endif

#endif