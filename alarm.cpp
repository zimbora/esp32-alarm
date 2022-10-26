
#include "alarm.hpp"

ALARM Alarm;

#ifndef UNITTEST
//DynamicJsonDocument doc_alarm(512);
extern StaticJsonDocument<512> doc_alarm;
extern DynamicJsonDocument table;
#else
	extern nlohmann::json doc_alarm;
	extern nlohmann::json table;

	uint32_t test_check_counter = 0;
	uint32_t ALARM::check_counter(){
		return test_check_counter;
	}
#endif

uint8_t alarm_counter = 0;

// return true if alarm is activated
bool ALARM::check(String ref, uint8_t type){

	#ifdef UNITTEST
	test_check_counter++;
	#endif

	bool check_action = false;

	if(!doc_alarm.containsKey(ref))
		return false;
	if(!table.containsKey(ref))
		return false;

	#ifdef DEBUG_ALARM
	log("alarm found");
	#endif

	if(!doc_alarm[ref].containsKey("min"))
		return false;
	if(!doc_alarm[ref].containsKey("max"))
		return false;
	if(!doc_alarm[ref].containsKey("d"))
		return false;
	if(!doc_alarm[ref].containsKey("o"))
		return false;

	if(type == int16be_type){
    uint16_t ref_min = doc_alarm[ref]["min"];
    uint16_t ref_max = doc_alarm[ref]["max"];
    uint16_t value = table[ref];

		#ifdef HIGH_DEBUG_ALARM
    Serial.printf("value: %d \n",value);
		#endif

    if(doc_alarm[ref]["d"] == 1){
			#ifdef HIGH_DEBUG_ALARM
			Serial.printf("diff: %d \n",doc_alarm[ref]["d"]);
			#endif
      int16_t last_value = doc_alarm[ref]["o"];
      value -= last_value;
    }

    if(ref_min > value || ref_max < value){
      if(doc_alarm[ref]["t"] == 0){
        	doc_alarm[ref]["t"] = 1;
					check_action = true;
      }else{
				#ifdef DEBUG_ALARM
				 log("alarm already sent");
				#endif
			 }
    }else if(ref_min < value & ref_max > value){
      if(doc_alarm[ref]["t"] == 1){
      	doc_alarm[ref]["t"] = 0;
      }else{
				#ifdef DEBUG_ALARM
				 log("value is ok");
				 #endif
			 }
    }
  }else if(type == uint16be_type){
		uint16_t ref_min = doc_alarm[ref]["min"];
    uint16_t ref_max = doc_alarm[ref]["max"];
    uint16_t value = table[ref];

		#ifdef HIGH_DEBUG_ALARM
    Serial.printf("value: %d \n",value);
		#endif

    if(doc_alarm[ref]["d"] == 1){
			#ifdef HIGH_DEBUG_ALARM
			Serial.printf("diff: %d \n",doc_alarm[ref]["d"]);
			#endif
      uint16_t last_value = doc_alarm[ref]["o"];
      value -= last_value;
    }

    if(ref_min > value || ref_max < value){
      if(doc_alarm[ref]["t"] == 0){
        	doc_alarm[ref]["t"] = 1;
					check_action = true;
      }else{
				#ifdef DEBUG_ALARM
				 log("alarm already sent");
				#endif
			 }
    }else if(ref_min < value & ref_max > value){
      if(doc_alarm[ref]["t"] == 1){
      	doc_alarm[ref]["t"] = 0;
      }else{
				#ifdef DEBUG_ALARM
				 log("value is ok");
				 #endif
			 }
    }
  }else if(type == int32be_type){
		int32_t ref_min = doc_alarm[ref]["min"];
    int32_t ref_max = doc_alarm[ref]["max"];
    int32_t value = table[ref];

		#ifdef HIGH_DEBUG_ALARM
    Serial.printf("value: %d \n",value);
		#endif

    if(doc_alarm[ref]["d"] == 1){
			#ifdef HIGH_DEBUG_ALARM
			Serial.printf("diff: %d \n",doc_alarm[ref]["d"]);
			#endif
      int32_t last_value = doc_alarm[ref]["o"];
      value -= last_value;
    }

    if(ref_min > value || ref_max < value){
      if(doc_alarm[ref]["t"] == 0){
        	doc_alarm[ref]["t"] = 1;
					check_action = true;
      }else{
				#ifdef DEBUG_ALARM
				 log("alarm already sent");
				#endif
			 }
    }else if(ref_min < value & ref_max > value){
      if(doc_alarm[ref]["t"] == 1){
      	doc_alarm[ref]["t"] = 0;
      }else{
				#ifdef DEBUG_ALARM
				 log("value is ok");
				 #endif
			 }
    }
  }else if(type == uint32be_type){
		uint32_t ref_min = doc_alarm[ref]["min"];
    uint32_t ref_max = doc_alarm[ref]["max"];
    uint32_t value = table[ref];

		#ifdef HIGH_DEBUG_ALARM
    Serial.printf("value: %d \n",value);
		#endif

    if(doc_alarm[ref]["d"] == 1){
			#ifdef HIGH_DEBUG_ALARM
			Serial.printf("diff: %d \n",doc_alarm[ref]["d"]);
			#endif
      uint32_t last_value = doc_alarm[ref]["o"];
      value -= last_value;
    }

    if(ref_min > value || ref_max < value){
      if(doc_alarm[ref]["t"] == 0){
        	doc_alarm[ref]["t"] = 1;
					check_action = true;
      }else{
				#ifdef DEBUG_ALARM
				 log("alarm already sent");
				#endif
			 }
    }else if(ref_min < value & ref_max > value){
      if(doc_alarm[ref]["t"] == 1){
      	doc_alarm[ref]["t"] = 0;
      }else{
				#ifdef DEBUG_ALARM
				 log("value is ok");
				 #endif
			 }
    }
  }else if(type == floatbe_type){
		float ref_min = doc_alarm[ref]["min"];
    float ref_max = doc_alarm[ref]["max"];
    float value = table[ref];

		#ifdef HIGH_DEBUG_ALARM
    Serial.printf("value: %d \n",value);
		#endif

    if(doc_alarm[ref]["d"] == 1){
			#ifdef HIGH_DEBUG_ALARM
			Serial.printf("diff: %d \n",doc_alarm[ref]["d"]);
			#endif
      float last_value = doc_alarm[ref]["o"];
      value -= last_value;
    }

    if(ref_min > value || ref_max < value){
      if(doc_alarm[ref]["t"] == 0){
        	doc_alarm[ref]["t"] = 1;
					check_action = true;
      }else{
				#ifdef DEBUG_ALARM
				 log("alarm already sent");
				#endif
			 }
    }else if(ref_min < value & ref_max > value){
      if(doc_alarm[ref]["t"] == 1){
      	doc_alarm[ref]["t"] = 0;
      }else{
				#ifdef DEBUG_ALARM
				 log("value is ok");
				 #endif
			 }
    }
  }
	else{
		#if defined UNITTEST and defined DEBUG
			printf("type: %d not supported \n",type);
		#endif
		return false;
	}

	return check_action;
}

bool ALARM::check(String ref, uint8_t type,bool(*report)(String)){

	#ifdef UNITTEST
	test_check_counter++;
	#endif

	bool check_action = false;

	if(!doc_alarm.containsKey(ref))
		return false;
	if(!table.containsKey(ref))
		return false;

	#ifdef DEBUG_ALARM
	log("alarm found");
	#endif

	if(!doc_alarm[ref].containsKey("min"))
		return false;
	if(!doc_alarm[ref].containsKey("max"))
		return false;
	if(!doc_alarm[ref].containsKey("d"))
		return false;
	if(!doc_alarm[ref].containsKey("o"))
		return false;

	if(type == int16be_type){
    uint16_t ref_min = doc_alarm[ref]["min"];
    uint16_t ref_max = doc_alarm[ref]["max"];
    uint16_t value = table[ref];

		#ifdef HIGH_DEBUG_ALARM
    Serial.printf("value: %d \n",value);
		#endif

    if(doc_alarm[ref]["d"] == 1){
			#ifdef HIGH_DEBUG_ALARM
			Serial.printf("diff: %d \n",doc_alarm[ref]["d"]);
			#endif
      int16_t last_value = doc_alarm[ref]["o"];
      value -= last_value;
    }

    if(ref_min > value || ref_max < value){
      if(doc_alarm[ref]["t"] == 0){
				if(report(ref)){
        	doc_alarm[ref]["t"] = 1;
					check_action = true;
				}
      }else log("alarm already sent");
    }else if(ref_min < value & ref_max > value){
      if(doc_alarm[ref]["t"] == 1){
				if(report(ref))
        	doc_alarm[ref]["t"] = 0;
      }else log("value is ok");
    }
  }else if(type == uint16be_type){
		uint16_t ref_min = doc_alarm[ref]["min"];
    uint16_t ref_max = doc_alarm[ref]["max"];
    uint16_t value = table[ref];

		#ifdef HIGH_DEBUG_ALARM
    Serial.printf("value: %d \n",value);
		#endif

    if(doc_alarm[ref]["d"] == 1){
			#ifdef HIGH_DEBUG_ALARM
			Serial.printf("diff: %d \n",doc_alarm[ref]["d"]);
			#endif
      uint16_t last_value = doc_alarm[ref]["o"];
      value -= last_value;
    }

    if(ref_min > value || ref_max < value){
      if(doc_alarm[ref]["t"] == 0){
				if(report(ref)){
        	doc_alarm[ref]["t"] = 1;
					check_action = true;
				}
      }else log("alarm already sent");
    }else if(ref_min < value & ref_max > value){
      if(doc_alarm[ref]["t"] == 1){
				if(report(ref))
        	doc_alarm[ref]["t"] = 0;
      }else log("value is ok");
    }
  }else if(type == int32be_type){
		int32_t ref_min = doc_alarm[ref]["min"];
    int32_t ref_max = doc_alarm[ref]["max"];
    int32_t value = table[ref];

		#ifdef HIGH_DEBUG_ALARM
    Serial.printf("value: %d \n",value);
		#endif

    if(doc_alarm[ref]["d"] == 1){
			#ifdef HIGH_DEBUG_ALARM
			Serial.printf("diff: %d \n",doc_alarm[ref]["d"]);
			#endif
      int32_t last_value = doc_alarm[ref]["o"];
      value -= last_value;
    }

    if(ref_min > value || ref_max < value){
      if(doc_alarm[ref]["t"] == 0){
				if(report(ref)){
        	doc_alarm[ref]["t"] = 1;
					check_action = true;
				}
      }else log("alarm already sent");
    }else if(ref_min < value & ref_max > value){
      if(doc_alarm[ref]["t"] == 1){
				if(report(ref))
        	doc_alarm[ref]["t"] = 0;
      }else log("value is ok");
    }
  }else if(type == uint32be_type){
		uint32_t ref_min = doc_alarm[ref]["min"];
    uint32_t ref_max = doc_alarm[ref]["max"];
    uint32_t value = table[ref];

		#ifdef HIGH_DEBUG_ALARM
    Serial.printf("value: %d \n",value);
		#endif

    if(doc_alarm[ref]["d"] == 1){
			#ifdef HIGH_DEBUG_ALARM
			Serial.printf("diff: %d \n",doc_alarm[ref]["d"]);
			#endif
      uint32_t last_value = doc_alarm[ref]["o"];
      value -= last_value;
    }

    if(ref_min > value || ref_max < value){
      if(doc_alarm[ref]["t"] == 0){
				if(report(ref)){
        	doc_alarm[ref]["t"] = 1;
					check_action = true;
				}
      }else log("alarm already sent");
    }else if(ref_min < value & ref_max > value){
      if(doc_alarm[ref]["t"] == 1){
				if(report(ref))
        	doc_alarm[ref]["t"] = 0;
      }else log("value is ok");
    }
  }else if(type == floatbe_type){
		float ref_min = doc_alarm[ref]["min"];
    float ref_max = doc_alarm[ref]["max"];
    float value = table[ref];

		#ifdef HIGH_DEBUG_ALARM
    Serial.printf("value: %d \n",value);
		#endif

    if(doc_alarm[ref]["d"] == 1){
			#ifdef HIGH_DEBUG_ALARM
			Serial.printf("diff: %d \n",doc_alarm[ref]["d"]);
			#endif
      float last_value = doc_alarm[ref]["o"];
      value -= last_value;
    }

    if(ref_min > value || ref_max < value){
      if(doc_alarm[ref]["t"] == 0){
				if(report(ref)){
        	doc_alarm[ref]["t"] = 1;
					check_action = true;
				}
      }else log("alarm already sent");
    }else if(ref_min < value & ref_max > value){
      if(doc_alarm[ref]["t"] == 1){
				if(report(ref))
        	doc_alarm[ref]["t"] = 0;
      }else log("value is ok");
    }
  }

	return check_action;
}

bool ALARM::add(JsonObject obj){

	String ref = obj["ref"];
	if(obj.containsKey("min_value"))
		doc_alarm[ref]["min"] = obj["min_value"];
	if(obj.containsKey("max_value"))
		doc_alarm[ref]["max"] = obj["max_value"];
	if(obj.containsKey("diff"))
		doc_alarm[ref]["d"] = obj["diff"];
	if(obj.containsKey("action"))
		doc_alarm[ref]["a"] = obj["action"]; // action


	doc_alarm[ref]["t"] = 0; // triggered
	doc_alarm[ref]["o"] = 0; // last value

	//log("alarm ref: "+ref);

	return true;
}
/*
bool ALARM::report(String ref){

	#ifdef DEBUG_ALARM
	log("report alarm");
	#endif

	if(!table.containsKey(ref))
		return false;

	#ifndef UNITTEST
		String value = table[ref];
		return mqtt_pushMessage("/"+ref,value,0,0);
	#else
		#ifdef DEBUG_ALARM
		std::cout << ref << ": " << table[ref] << "\n";
		#endif
		return true;
	#endif
}
*/
