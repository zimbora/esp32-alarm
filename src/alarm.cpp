
#include "alarm.hpp"

#ifndef UNITTEST
//DynamicJsonDocument doc_alarm(512);
StaticJsonDocument<1024> doc_alarm; // json doc to store alarms 100B for each alarm, approximately
#else
	nlohmann::json doc_alarm;

	uint32_t test_check_counter = 0;
	uint32_t ALARM::check_counter(){
		return test_check_counter;
	}

	#define JsonObject nlohmann::json
#endif

bool ALARM::timedOut(String ref){

	if(!doc_alarm.containsKey(ref)){
		#ifdef DEBUG_ALARM
		 serial->println(ref +"doesn't exists");
		#endif
		return false;
	}

	uint32_t timeout = doc_alarm[ref]["to"];
  int16_t period = doc_alarm[ref]["p"];
	#ifdef DEBUG_ALARM
  log(String(ref)+": "+String(timeout)+"("+String(period)+")");
  #endif

	uint32_t now_ = now();
	if(timeout <= now_ || (timeout - period > now_) ){
    uint32_t timeout = get_aligned_hour(period);
    timeout += period;
    doc_alarm[ref]["to"] = timeout;

    #ifdef DEBUG_AUTOREQUEST
    log("period: "+String(period));
    log("timestamp: "+String(now_) );
    log("new timeout: "+String(timeout));
    #endif
		return true;
  }

	return false;
}

// return true if is in alarm
bool ALARM::check(String ref, uint8_t type, JsonObject table){

	#ifdef UNITTEST
	test_check_counter++;
	#endif

	bool check_action = false;

	if(!doc_alarm.containsKey(ref)){
		#ifdef HIGH_DEBUG_ALARM
		serial->println("doc_alarm doesn't contains key: "+ref);
		#endif
		return false;
	}
	if(!table.containsKey(ref)){
		#ifdef HIGH_DEBUG_ALARM
		serial->println("table doesn't contains key: "+ref);
		#endif
		return false;
	}

	#ifdef DEBUG_ALARM
	serial->println("alarm found");
	#endif

	if(!doc_alarm[ref].containsKey("min")){
		#ifdef HIGH_DEBUG_ALARM
		serial->println("doc_alarm doesn't contains key min");
		#endif
		return false;
	}
	if(!doc_alarm[ref].containsKey("max")){
		#ifdef HIGH_DEBUG_ALARM
		serial->println("doc_alarm doesn't contains key min");
		#endif
		return false;
	}
	if(!doc_alarm[ref].containsKey("d")){
		#ifdef HIGH_DEBUG_ALARM
		serial->println("doc_alarm doesn't contains key min");
		#endif
		return false;
	}
	if(!doc_alarm[ref].containsKey("o")){
		#ifdef HIGH_DEBUG_ALARM
		serial->println("doc_alarm doesn't contains key o");
		#endif
		return false;
	}

	if(type == int16be_type){
		uint16_t ref_min = doc_alarm[ref]["min"];
		uint16_t ref_max = doc_alarm[ref]["max"];
		uint16_t value = table[ref];

		#ifdef HIGH_DEBUG_ALARM
		serial->printf("value: %d \n",value);
		#endif

		if(doc_alarm[ref]["d"] == 1){
			#ifdef HIGH_DEBUG_ALARM
			serial->printf("diff: %d \n",doc_alarm[ref]["d"]);
			#endif
			int16_t last_value = doc_alarm[ref]["o"];
			value -= last_value;
		}

		if(ref_min > value || ref_max < value){
			check_action = true;
			if(doc_alarm[ref]["t"] == 0){
				doc_alarm[ref]["t"] = 1;
			}else{
				#ifdef DEBUG_ALARM
				serial->println("alarm already sent");
				#endif
			}
		}else if(ref_min < value & ref_max > value){
			if(doc_alarm[ref]["t"] == 1){
				doc_alarm[ref]["t"] = 0;
			}else{
				#ifdef DEBUG_ALARM
				serial->println("value is ok");
				#endif
			}
		}
	}else if(type == uint16be_type){
		uint16_t ref_min = doc_alarm[ref]["min"];
		uint16_t ref_max = doc_alarm[ref]["max"];
		uint16_t value = table[ref];

		#ifdef HIGH_DEBUG_ALARM
		serial->printf("value: %d \n",value);
		#endif

		if(doc_alarm[ref]["d"] == 1){
			#ifdef HIGH_DEBUG_ALARM
			serial->printf("diff: %d \n",doc_alarm[ref]["d"]);
			#endif
			uint16_t last_value = doc_alarm[ref]["o"];
			value -= last_value;
		}

		if(ref_min > value || ref_max < value){
			check_action = true;
			if(doc_alarm[ref]["t"] == 0){
				doc_alarm[ref]["t"] = 1;
			}else{
				#ifdef DEBUG_ALARM
				serial->println("alarm already sent");
				#endif
			}
		}else if(ref_min < value & ref_max > value){
			if(doc_alarm[ref]["t"] == 1){
				doc_alarm[ref]["t"] = 0;
			}else{
				#ifdef DEBUG_ALARM
				serial->println("value is ok");
				#endif
			}
		}
	}else if(type == int32be_type){
		int32_t ref_min = doc_alarm[ref]["min"];
		int32_t ref_max = doc_alarm[ref]["max"];
		int32_t value = table[ref];

		#ifdef HIGH_DEBUG_ALARM
		serial->printf("value: %d \n",value);
		#endif

		if(doc_alarm[ref]["d"] == 1){
			#ifdef HIGH_DEBUG_ALARM
			serial->printf("diff: %d \n",doc_alarm[ref]["d"]);
			#endif
			int32_t last_value = doc_alarm[ref]["o"];
			value -= last_value;
		}

		if(ref_min > value || ref_max < value){
			check_action = true;
			if(doc_alarm[ref]["t"] == 0){
				doc_alarm[ref]["t"] = 1;
			}else{
				#ifdef DEBUG_ALARM
				serial->println("alarm already sent");
				#endif
			}
		}else if(ref_min < value & ref_max > value){
			if(doc_alarm[ref]["t"] == 1){
				doc_alarm[ref]["t"] = 0;
			}else{
				#ifdef DEBUG_ALARM
				serial->println("value is ok");
				#endif
			}
		}
	}else if(type == uint32be_type){
		uint32_t ref_min = doc_alarm[ref]["min"];
		uint32_t ref_max = doc_alarm[ref]["max"];
		uint32_t value = table[ref];

		#ifdef HIGH_DEBUG_ALARM
		serial->printf("value: %d \n",value);
		#endif

		if(doc_alarm[ref]["d"] == 1){
			#ifdef HIGH_DEBUG_ALARM
			serial->printf("diff: %d \n",doc_alarm[ref]["d"]);
			#endif
			uint32_t last_value = doc_alarm[ref]["o"];
			value -= last_value;
		}

		if(ref_min > value || ref_max < value){
			check_action = true;
			if(doc_alarm[ref]["t"] == 0){
				doc_alarm[ref]["t"] = 1;
			}else{
				#ifdef DEBUG_ALARM
				serial->println("alarm already sent");
				#endif
			}
		}else if(ref_min < value & ref_max > value){
			if(doc_alarm[ref]["t"] == 1){
				doc_alarm[ref]["t"] = 0;
			}else{
				#ifdef DEBUG_ALARM
				serial->println("value is ok");
				#endif
			}
		}
	}else if(type == floatbe_type){
		float ref_min = doc_alarm[ref]["min"];
		float ref_max = doc_alarm[ref]["max"];
		float value = table[ref];

		#ifdef HIGH_DEBUG_ALARM
		serial->printf("value: %d \n",value);
		#endif

		if(doc_alarm[ref]["d"] == 1){
			#ifdef HIGH_DEBUG_ALARM
			serial->printf("diff: %d \n",doc_alarm[ref]["d"]);
			#endif
			float last_value = doc_alarm[ref]["o"];
			value -= last_value;
		}

		if(ref_min > value || ref_max < value){
			check_action = true;
			if(doc_alarm[ref]["t"] == 0){
				doc_alarm[ref]["t"] = 1;
			}else{
				#ifdef DEBUG_ALARM
				serial->println("alarm already sent");
				#endif
			}
		}else if(ref_min < value & ref_max > value){
			if(doc_alarm[ref]["t"] == 1){
				doc_alarm[ref]["t"] = 0;
			}else{
				#ifdef DEBUG_ALARM
				serial->println("value is ok");
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

// return true if is in alarm, calls report if alarm state was changed
bool ALARM::check(String ref, uint8_t type, JsonObject table, bool(*report)(String)){

	#ifdef UNITTEST
	test_check_counter++;
	#endif

	bool check_action = false;

	if(!doc_alarm.containsKey(ref)){
		#ifdef DEBUG_ALARM
		 serial->println(ref +"doesn't exists");
		#endif
		return false;
	}
	if(!table.containsKey(ref)){
		#ifdef DEBUG_ALARM
		 serial->println("value not found for: "+ref);
		#endif
		return false;
	}

	if(!doc_alarm[ref].containsKey("min"))
		return false;
	if(!doc_alarm[ref].containsKey("max"))
		return false;
	if(!doc_alarm[ref].containsKey("d")) // diff
		return false;
	if(!doc_alarm[ref].containsKey("o")) // old value
		return false;

	if(type == int16be_type){
    uint16_t ref_min = doc_alarm[ref]["min"];
    uint16_t ref_max = doc_alarm[ref]["max"];
    uint16_t value = table[ref];

		#ifdef HIGH_DEBUG_ALARM
    serial->printf("value: %d \n",value);
		#endif

    if(doc_alarm[ref]["d"] == 1){
			#ifdef HIGH_DEBUG_ALARM
			serial->printf("diff: %d \n",doc_alarm[ref]["d"]);
			#endif
      int16_t last_value = doc_alarm[ref]["o"];
      value -= last_value;
    }

    if(ref_min > value || ref_max < value){
			check_action = true;
      if(doc_alarm[ref]["t"] == 0){
				if(report(ref)){
        	doc_alarm[ref]["t"] = 1;
				}
      }else{
				#ifdef DEBUG_ALARM
				serial->println("alarm already sent");
				#endif
			}
    }else if(ref_min < value & ref_max > value){
      if(doc_alarm[ref]["t"] == 1){
				if(report(ref))
        	doc_alarm[ref]["t"] = 0;
      }else{
				#ifdef DEBUG_ALARM
				serial->println("value is ok");
				#endif
			}
    }
  }else if(type == uint16be_type){
		uint16_t ref_min = doc_alarm[ref]["min"];
    uint16_t ref_max = doc_alarm[ref]["max"];
    uint16_t value = table[ref];

		#ifdef HIGH_DEBUG_ALARM
    serial->printf("value: %d \n",value);
		#endif

    if(doc_alarm[ref]["d"] == 1){
			#ifdef HIGH_DEBUG_ALARM
			serial->printf("diff: %d \n",doc_alarm[ref]["d"]);
			#endif
      uint16_t last_value = doc_alarm[ref]["o"];
      value -= last_value;
    }

    if(ref_min > value || ref_max < value){
			check_action = true;
      if(doc_alarm[ref]["t"] == 0){
				if(report(ref)){
        	doc_alarm[ref]["t"] = 1;
				}
      }else{
				#ifdef DEBUG_ALARM
				 serial->println("alarm already sent");
				#endif
			 }
    }else if(ref_min < value & ref_max > value){
      if(doc_alarm[ref]["t"] == 1){
				if(report(ref))
        	doc_alarm[ref]["t"] = 0;
      }else{
				#ifdef DEBUG_ALARM
				 serial->println("value is ok");
				#endif
			 }
    }
  }else if(type == int32be_type){
		int32_t ref_min = doc_alarm[ref]["min"];
    int32_t ref_max = doc_alarm[ref]["max"];
    int32_t value = table[ref];

		#ifdef HIGH_DEBUG_ALARM
    serial->printf("value: %d \n",value);
		#endif

    if(doc_alarm[ref]["d"] == 1){
			#ifdef HIGH_DEBUG_ALARM
			serial->printf("diff: %d \n",doc_alarm[ref]["d"]);
			#endif
      int32_t last_value = doc_alarm[ref]["o"];
      value -= last_value;
    }

    if(ref_min > value || ref_max < value){
			check_action = true;
      if(doc_alarm[ref]["t"] == 0){
				if(report(ref)){
        	doc_alarm[ref]["t"] = 1;
				}
      }else{
				#ifdef DEBUG_ALARM
				 serial->println("alarm already sent");
				#endif
			 }
    }else if(ref_min < value & ref_max > value){
      if(doc_alarm[ref]["t"] == 1){
				if(report(ref))
        	doc_alarm[ref]["t"] = 0;
      }else{
				#ifdef DEBUG_ALARM
				 serial->println("value is ok");
				#endif
			 }
    }
  }else if(type == uint32be_type){
		uint32_t ref_min = doc_alarm[ref]["min"];
    uint32_t ref_max = doc_alarm[ref]["max"];
    uint32_t value = table[ref];

		#ifdef HIGH_DEBUG_ALARM
    serial->printf("value: %d \n",value);
		#endif

    if(doc_alarm[ref]["d"] == 1){
			#ifdef HIGH_DEBUG_ALARM
			serial->printf("diff: %d \n",doc_alarm[ref]["d"]);
			#endif
      uint32_t last_value = doc_alarm[ref]["o"];
      value -= last_value;
    }

    if(ref_min > value || ref_max < value){
			check_action = true;
      if(doc_alarm[ref]["t"] == 0){
				if(report(ref)){
        	doc_alarm[ref]["t"] = 1;
				}
      }else{
				#ifdef DEBUG_ALARM
				 serial->println("alarm already sent");
				#endif
			 }
    }else if(ref_min < value & ref_max > value){
      if(doc_alarm[ref]["t"] == 1){
				if(report(ref))
        	doc_alarm[ref]["t"] = 0;
      }else{
				#ifdef DEBUG_ALARM
				 serial->println("value is ok");
				#endif
			 }
    }
  }else if(type == floatbe_type){
		float ref_min = doc_alarm[ref]["min"];
    float ref_max = doc_alarm[ref]["max"];
    float value = table[ref];

		#ifdef HIGH_DEBUG_ALARM
    serial->printf("value: %d \n",value);
		#endif

    if(doc_alarm[ref]["d"] == 1){
			#ifdef HIGH_DEBUG_ALARM
			serial->printf("diff: %d \n",doc_alarm[ref]["d"]);
			#endif
      float last_value = doc_alarm[ref]["o"];
      value -= last_value;
    }

    if(ref_min > value || ref_max < value){
			check_action = true;
      if(doc_alarm[ref]["t"] == 0){
				if(report(ref)){
        	doc_alarm[ref]["t"] = 1;
				}
      }else{
				#ifdef DEBUG_ALARM
				 serial->println("alarm already sent");
				#endif
			 }
    }else if(ref_min < value & ref_max > value){
      if(doc_alarm[ref]["t"] == 1){
				if(report(ref))
        	doc_alarm[ref]["t"] = 0;
      }else{
				#ifdef DEBUG_ALARM
				 serial->println("value is ok");
				#endif
			 }
    }
  }

	return check_action;
}

bool ALARM::add(JsonObject obj){

	if(!obj.containsKey("ref"))
		return false;

	String ref = obj["ref"];

	if(obj.containsKey("min_value"))
		doc_alarm[ref]["min"] = obj["min_value"];
	else return false;

	if(obj.containsKey("max_value"))
		doc_alarm[ref]["max"] = obj["max_value"];
	else return false;

	if(obj.containsKey("diff"))
		doc_alarm[ref]["d"] = obj["diff"];
	else
		doc_alarm[ref]["d"] = 0;

	if(obj.containsKey("action"))
		doc_alarm[ref]["a"] = obj["action"]; // action
	else doc_alarm[ref]["a"] = NULL;

	if(obj.containsKey("period"))
		doc_alarm[ref]["p"] = obj["period"]; // action
	else
		doc_alarm[ref]["p"] = 60; // action

	uint32_t period = doc_alarm[ref]["p"];
	uint32_t timeout = get_aligned_hour(period)+period;
	doc_alarm[ref]["to"] = timeout; // timeout

	doc_alarm[ref]["t"] = 0; // triggered
	doc_alarm[ref]["o"] = 0; // last value

	bool res = doc_alarm.containsKey(ref);
	if(!res){
		#ifdef ERROR_ALARM
		serial->println("JsonDocument overflow !!");
		#endif
	}
	return res;
}

bool ALARM::add(String ref, uint32_t period, long min, long max, int diff){

	if(ref == "")
		return false;

	doc_alarm[ref]["min"] = min;
	doc_alarm[ref]["max"] = max;
	doc_alarm[ref]["d"] = diff;
	doc_alarm[ref]["p"] = period;

	uint32_t timeout = get_aligned_hour(period)+period;
	doc_alarm[ref]["to"] = timeout; // timeout

	doc_alarm[ref]["t"] = 0; // triggered
	doc_alarm[ref]["o"] = 0; // last value

	return true;
}

void ALARM::list(){
	#ifndef UNITTEST
	serializeJson(doc_alarm,*serial);
	#endif
}

JsonObject ALARM::get(String ref){
	JsonObject object;
	if(doc_alarm.containsKey(ref)){
		#ifndef UNITTEST
		object = doc_alarm[ref].as<JsonObject>();
		#else
		object = doc_alarm[ref];
		#endif
	}
	return object;
}

uint32_t ALARM::get_aligned_hour(uint32_t period){

  time_t unix_time = now();

  if(use_local_time){
		unix_time += time_offset;
	}

  unix_time -= (unix_time % period);    // minute align
  return unix_time;
}
