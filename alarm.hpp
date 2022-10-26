#ifndef ALARMS_HPP
#define ALARMS_HPP

#include "Arduino.hpp"

#ifndef UNITTEST

  #include "ArduinoJson.h"
  #include "../log/logging.h"
  //#include "../settings/settings.h"

#else

  #include <iostream>
  #include "../libraries/nlohmann/json.hpp"

  #define String std::string

  //#define DEBUG_ALARM

#endif

#define ALARMS_MAX 50

class ALARM {

  public:
    ALARM(){};
    bool check(String ref, uint8_t type);
    bool check(String ref, uint8_t type,bool(*report)(String));
    bool add(JsonObject obj);
    #ifdef UNITTEST
    uint32_t check_counter();
    #endif
};

extern ALARM Alarm;
#endif
