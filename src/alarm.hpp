#ifndef ALARMS_HPP
#define ALARMS_HPP

#include "Arduino.h"

#ifndef UNITTEST

  #include "ArduinoJson.h"
  //#include "../log/logging.h" // handle it

  //#define DEBUG_ALARM
  //#define HIGH_DEBUG_ALARM

#else

  #include <iostream>
  #include "../libraries/nlohmann/json.hpp"

  #define String std::string

  //#define DEBUG_ALARM

#endif

#ifndef byte_type
#define byte_type                    0  // not known
#endif
#ifndef uint8_type
#define uint8_type                   1
#endif
#ifndef int8_type
#define int8_type                    2
#endif
#ifndef uint16be_type
#define uint16be_type                3
#endif
#ifndef uint16le_type
#define uint16le_type                4
#endif
#ifndef int16be_type
#define int16be_type                 5
#endif
#ifndef int16le_type
#define int16le_type                 6
#endif
#ifndef uint32be_type
#define uint32be_type                9
#endif
#ifndef uint32le_type
#define uint32le_type                10
#endif
#ifndef int32be_type
#define int32be_type                 11
#endif
#ifndef int32le_type
#define int32le_type                 12
#endif
#ifndef floatbe_type
#define floatbe_type                 48
#endif
#ifndef floatle_type
#define floatle_type                 49
#endif
#ifndef hex_arr
#define hex_arr                      64
#endif
#ifndef char_arr
#define char_arr                     65
#endif
#ifndef index_itron
#define index_itron                  80
#endif


#define ALARMS_MAX 50

class ALARM{
  public:
    HardwareSerial* serial = &Serial;
    ALARM(HardwareSerial* serial_port){
      serial = serial_port;
    };
    bool add(JsonObject obj);
    bool add(String ref, long min, long max, int diff = 0);
    bool check(String ref, uint8_t type, JsonObject value);
    bool check(String ref, uint8_t type, JsonObject value, bool(*report)(String));
    void list();
    JsonObject get(String ref);
    #ifdef UNITTEST
    uint32_t check_counter();
    #endif
};

#endif
