// Your First C++ Program

#include <stdint.h>
#include <stdio.h>
#include <iostream>

#include "./tmp/alarm.hpp"
#include "./libraries/output.h"

// Editable by tester
uint8_t test[] = {
  true, // test1 - testing null structs
  true, // test2 - testing incomplete and null structs
  true, // test3 - testing incomplete structs
  true, // test4 - Testing difference between values, no alarm, last value 0.
  true, // test5 - Testing values in alarm
  true, // test6 - Testing floating values in alarm
  true, // test7 - Testing difference between values, no alarm, last value != 0.
  true, // test8 - Testing difference between floating values, no alarm, last value != 0.
  true, // test9 - Testing difference between values, in alarm, last value != 0.
  true,  // test10 - Testing difference between floating values, in alarm, last value != 0.
  true,  // test11 callback
};

#define String std::string
using json = nlohmann::json;

// Editable by tester
// available types for test
uint8_t type_arr[] = {
  //byte_type,
  //uint8_type,
  //int8_type ,
  uint16be_type,
  //uint16le_type,
  int16be_type,
  //int16le_type,
  uint32be_type,
  //uint32le_type,
  int32be_type,
  //int32le_type,
  floatbe_type,
  //floatle_type,
  //hex_arr,
  //char_arr,
  //index_itron
};

json doc_alarm = {};
json table = {};

extern ALARM Alarm;

// testing null structs
bool alarm_test1(){
  // Null json
  bool res = true;
  print_colour_text("Test1 - testing null structs!","white");
  if(Alarm.check("p1",-1)){
    res = false;
  }

  return res;
}

// testing incomplete and null structs
bool alarm_test2(){

  bool res = true;
  doc_alarm = {
    {"p1",
      {"min",10}
    }
  };

  print_colour_text("Test2 - testing incomplete and null structs!","white");
  if(Alarm.check("p1",-1)){
    res = false;
  }

  if(Alarm.check("p2",-1)){
    res = false;
  }

  if(Alarm.check("p1",uint8_type)){
    res = false;
  }

  if(Alarm.check("p2",uint8_type)){
    res = false;
  }

  return res;
}

// testing incomplete structs
bool alarm_test3(){

  bool res = true;
  // Null json
  doc_alarm = {
    {"p1",
      {"min",10}
    }
  };

  table = {
    {"p1",15}
  };

  print_colour_text("Test3 - testing incomplete structs!","white");

  uint8_t i = 0;
  std::string ref = "";
  while(i<sizeof(type_arr)){
    ref = "p1";

    if(Alarm.check(ref,type_arr[i])){
      res = false;
      #ifdef DEBUG
      printf("failed >> ref: %s type: %d \n",ref.c_str(),type_arr[i]);
      #endif
    }

    ref = "p2";

    if(Alarm.check(ref,type_arr[i])){
      res = false;
      #ifdef DEBUG
      printf("ref: %s type: %d \n",ref.c_str(),type_arr[i]);
      #endif
    }

    i++;
  }

  return res;
}

// Testing difference between values, no alarm, last value 0.
// Negative and positive values
bool alarm_test4(){

  bool res = true;
  print_colour_text("Test4 - Testing difference between values, no alarm, last value 0.!","white");

  uint8_t i = 0;
  std::string ref = "";

  doc_alarm = {
    {"p1",
      {
        {"min",10},
        {"max",20},
        {"d",1}, // calculate difference between actual value and last value
        {"o",0} // alarm last value
      }
    }
  };

  table = {
    {"p1",15} // value to be evaluated
  };
  i = 0;
  while(i<sizeof(type_arr)){
    ref = "p1";

    if(Alarm.check(ref,type_arr[i])){
      res = false;
      #ifdef DEBUG
      printf("failed >> ref: %s type: %d \n",ref.c_str(),type_arr[i]);
      #endif
    }

    i++;
  }

  doc_alarm = {
    {"p1",
      {
        {"min",-10},
        {"max",-20},
        {"d",1}, // calculate difference between actual value and last value
        {"o",0} // alarm last value
      }
    }
  };

  table = {
    {"p1",-15} // value to be evaluated
  };
  i = 0;
  while(i<sizeof(type_arr)){
    ref = "p1";

    if(Alarm.check(ref,type_arr[i])){
      res = false;
      #ifdef DEBUG
      printf("failed >> ref: %s type: %d \n",ref.c_str(),type_arr[i]);
      #endif
    }

    i++;
  }

  return res;
}

// Testing values in alarm
// Negative and positive values
bool alarm_test5(){

  uint8_t i = 0;
  std::string ref = "p1";

  doc_alarm = {
    {"p1",
      {
        {"min",10},
        {"max",20},
        {"d",0}, // calculate difference between actual value and last value
        {"o",0}, // alarm last value
        {"t",0} // alarm triggered
      }
    }
  };

  table = {
    {"p1",25} // value to be evaluated
  };

  print_colour_text("Test5 - alarm set by excess !","white");

  i = 0;
  bool res = true;
  while(i<sizeof(type_arr) && type_arr[i] < hex_arr){

    doc_alarm["p1"]["t"] = 0;
    if(!Alarm.check(ref,type_arr[i])){
      res = false;
      #ifdef DEBUG
      printf("failed >> ref: %s type: %d \n",ref.c_str(),type_arr[i]);
    	std::cout << "ref: " << doc_alarm[ref] << "\n";
      #endif
    }

    i++;
  }

  table = {
    {"p1",5}
  };

  print_colour_text("Test5 - alarm set by defect !","white");

  i = 0;
  while(i<sizeof(type_arr) && type_arr[i] < hex_arr){

    doc_alarm["p1"]["t"] = 0;
    if(!Alarm.check(ref,type_arr[i])){
      res = false;
      #ifdef DEBUG
      printf("failed >> ref: %s type: %d \n",ref.c_str(),type_arr[i]);
      std::cout << "ref: " << doc_alarm[ref] << "\n";
      #endif
    }

    i++;
  }

  doc_alarm = {
    {"p1",
      {
        {"min",-10},
        {"max",-20},
        {"d",0}, // calculate difference between actual value and last value
        {"o",0}, // alarm last value
        {"t",0} // alarm triggered
      }
    }
  };

  table = {
    {"p1",-25} // value to be evaluated
  };

  print_colour_text("Test5 - alarm set by excess !","white");

  i = 0;
  while(i<sizeof(type_arr) && type_arr[i] < hex_arr){
    doc_alarm["p1"]["t"] = 0;
    if(!Alarm.check(ref,type_arr[i])){
      res = false;
      #ifdef DEBUG
      printf("failed >> ref: %s type: %d \n",ref.c_str(),type_arr[i]);
    	std::cout << "ref: " << doc_alarm[ref] << "\n";
      #endif
    }

    i++;
  }

  table = {
    {"p1",-5}
  };

  print_colour_text("Test5 - alarm set by defect !","white");

  i = 0;
  while(i<sizeof(type_arr) && type_arr[i] < hex_arr){

    doc_alarm["p1"]["t"] = 0;
    if(!Alarm.check(ref,type_arr[i])){
      res = false;
      #ifdef DEBUG
      printf("failed >> ref: %s type: %d \n",ref.c_str(),type_arr[i]);
      std::cout << "ref: " << doc_alarm[ref] << "\n";
      #endif
    }

    i++;
  }

  return res;
}

// Testing floating values in alarm
// Negative and positive values
bool alarm_test6(){

  uint8_t i = 0;
  std::string ref = "p1";

  doc_alarm = {
    {"p1",
      {
        {"min",10.2},
        {"max",20.2},
        {"d",0}, // calculate difference between actual value and last value
        {"o",0}, // alarm last value
        {"t",0} // alarm triggered
      }
    }
  };

  table = {
    {"p1",25.3} // value to be evaluated
  };

  print_colour_text("Test6 - alarm set by excess!","white");

  i = 0;
  bool res = true;
  while(i<sizeof(type_arr) && type_arr[i] < hex_arr){

    doc_alarm["p1"]["t"] = 0;
    if(!Alarm.check(ref,type_arr[i])){
      res = false;
      #ifdef DEBUG
      printf("failed >> ref: %s type: %d \n",ref.c_str(),type_arr[i]);
    	std::cout << "ref: " << doc_alarm[ref] << "\n";
      #endif
    }

    i++;
  }

  table = {
    {"p1",5.3}
  };

  print_colour_text("Test6 - alarm set by defect!","white");

  i = 0;
  while(i<sizeof(type_arr) && type_arr[i] < hex_arr){
    doc_alarm["p1"]["t"] = 0;
    if(!Alarm.check(ref,type_arr[i])){
      res = false;
      #ifdef DEBUG
      printf("failed >> ref: %s type: %d \n",ref.c_str(),type_arr[i]);
    	std::cout << "ref: " << doc_alarm[ref] << "\n";
      #endif
    }

    i++;
  }

  doc_alarm = {
    {"p1",
      {
        {"min",-10.2},
        {"max",-20.2},
        {"d",0}, // calculate difference between actual value and last value
        {"o",0}, // alarm last value
        {"t",0} // alarm triggered
      }
    }
  };

  table = {
    {"p1",-25.3} // value to be evaluated
  };

  print_colour_text("Test6 - alarm set by defect!","white");

  i = 0;
  while(i<sizeof(type_arr) && type_arr[i] < hex_arr){
    doc_alarm["p1"]["t"] = 0;
    if(!Alarm.check(ref,type_arr[i])){
      res = false;
      #ifdef DEBUG
      printf("failed >> ref: %s type: %d \n",ref.c_str(),type_arr[i]);
    	std::cout << "ref: " << doc_alarm[ref] << "\n";
      #endif
    }

    i++;
  }

  table = {
    {"p1",-5.3} // value to be evaluated
  };

  print_colour_text("Test6 - alarm set by excess!","white");

  i = 0;
  while(i<sizeof(type_arr) && type_arr[i] < hex_arr){
    doc_alarm["p1"]["t"] = 0;
    if(!Alarm.check(ref,type_arr[i])){
      res = false;
      #ifdef DEBUG
      printf("failed >> ref: %s type: %d \n",ref.c_str(),type_arr[i]);
    	std::cout << "ref: " << doc_alarm[ref] << "\n";
      #endif
    }

    i++;
  }

  return res;
}

// Testing difference between values, no alarm, last value != 0.
// Negative and positive values
bool alarm_test7(){

  uint8_t i = 0;
  std::string ref = "p1";

  doc_alarm = {
    {"p1",
      {
        {"min",10},
        {"max",20},
        {"d",1}, // calculate difference between actual value and last value
        {"o",12}, // alarm last value
        {"t",0} // alarm triggered
      }
    }
  };

  table = {
    {"p1",25} // value to be evaluated
  };

  print_colour_text("Test7 - no alarm!","white");

  i = 0;
  bool res = true;
  while(i<sizeof(type_arr) && type_arr[i] < hex_arr){
    doc_alarm["p1"]["t"] = 0;
    if(Alarm.check(ref,type_arr[i])){
      res = false;
      #ifdef DEBUG
      printf("failed >> ref: %s type: %d \n",ref.c_str(),type_arr[i]);
    	std::cout << "ref: " << doc_alarm[ref] << "\n";
      std::cout << "value: " << table[ref] << "\n";
      #endif
    }

    i++;
  }

  doc_alarm = {
    {"p1",
      {
        {"max",-10},
        {"min",-20},
        {"d",1}, // calculate difference between actual value and last value
        {"o",-12}, // alarm last value
        {"t",0} // alarm triggered
      }
    }
  };

  table = {
    {"p1",-25} // value to be evaluated
  };

  print_colour_text("Test7 - no alarm!","white");

  i = 0;
  while(i<sizeof(type_arr) && type_arr[i] < hex_arr){
    doc_alarm["p1"]["t"] = 0;
    if(Alarm.check(ref,type_arr[i])){
      res = false;
      #ifdef DEBUG
      printf("failed >> ref: %s type: %d \n",ref.c_str(),type_arr[i]);
    	std::cout << "ref: " << doc_alarm[ref] << "\n";
    	std::cout << "value: " << table[ref] << "\n";
      #endif
    }

    i++;
  }

  return res;
}

// Testing difference between floating values, no alarm, last value != 0.
// Negative and positive values
bool alarm_test8(){

  uint8_t i = 0;
  std::string ref = "p1";

  doc_alarm = {
    {"p1",
      {
        {"min",10.2},
        {"max",20.2},
        {"d",1}, // calculate difference between actual value and last value
        {"o",12.8}, // alarm last value
        {"t",0} // alarm triggered
      }
    }
  };

  table = {
    {"p1",25.3} // value to be evaluated
  };

  print_colour_text("Test8 - no alarm !","white");

  i = 0;
  bool res = true;
  while(i<sizeof(type_arr) && type_arr[i] < hex_arr){
    doc_alarm["p1"]["t"] = 0;
    if(Alarm.check(ref,type_arr[i])){
      res = false;
      #ifdef DEBUG
      printf("failed >> ref: %s type: %d \n",ref.c_str(),type_arr[i]);
    	std::cout << "ref: " << doc_alarm[ref] << "\n";
    	std::cout << "value: " << table[ref] << "\n";
      #endif
    }

    i++;
  }

  doc_alarm = {
    {"p1",
      {
        {"max",-10.2},
        {"min",-20.2},
        {"d",1}, // calculate difference between actual value and last value
        {"o",-12.8}, // alarm last value
        {"t",0} // alarm triggered
      }
    }
  };
  table = {
    {"p1",-25.3} // value to be evaluated
  };

  print_colour_text("Test8 - no alarm !","white");

  i = 0;
  while(i<sizeof(type_arr) && type_arr[i] < hex_arr){
    doc_alarm["p1"]["t"] = 0;
    if(Alarm.check(ref,type_arr[i])){
      res = false;
      #ifdef DEBUG
      printf("failed >> ref: %s type: %d \n",ref.c_str(),type_arr[i]);
    	std::cout << "ref: " << doc_alarm[ref] << "\n";
      std::cout << "value: " << table[ref] << "\n";
      #endif
    }

    i++;
  }

  return res;
}

// Testing difference between values, in alarm, last value != 0.
// Negative and positive values
bool alarm_test9(){

  uint8_t i = 0;
  std::string ref = "p1";

  doc_alarm = {
    {"p1",
      {
        {"min",10},
        {"max",20},
        {"d",1}, // calculate difference between actual value and last value
        {"o",12}, // alarm last value
        {"t",0} // alarm triggered
      }
    }
  };

  table = {
    {"p1",45} // value to be evaluated
  };

  print_colour_text("Test9 - alarm set by excess!","white");

  i = 0;
  bool res = true;
  while(i<sizeof(type_arr) && type_arr[i] < hex_arr){

    doc_alarm["p1"]["t"] = 0;
    if(!Alarm.check(ref,type_arr[i])){
      res = false;
      #ifdef DEBUG
      printf("failed >> ref: %s type: %d \n",ref.c_str(),type_arr[i]);
    	std::cout << "ref: " << doc_alarm[ref] << "\n";
      #endif
    }

    i++;
  }

  table = {
    {"p1",5} // value to be evaluated
  };

  print_colour_text("Test9 - alarm set by defect!","white");

  i = 0;

  while(i<sizeof(type_arr) && type_arr[i] < hex_arr){

    doc_alarm["p1"]["t"] = 0;
    if(!Alarm.check(ref,type_arr[i])){
      res = false;
      #ifdef DEBUG
      printf("failed >> ref: %s type: %d \n",ref.c_str(),type_arr[i]);
    	std::cout << "ref: " << doc_alarm[ref] << "\n";
      #endif
    }

    i++;
  }

  return res;
}

// Testing difference between floating values, in alarm, last value != 0.
// Negative and positive values
bool alarm_test10(){

  uint8_t i = 0;
  std::string ref = "p1";

  doc_alarm = {
    {"p1",
      {
        {"min",10.2},
        {"max",20.2},
        {"d",1}, // calculate difference between actual value and last value
        {"o",12.8}, // alarm last value
        {"t",0} // alarm triggered
      }
    }
  };

  table = { // old value
    {"p1",45.3} // value to be evaluated
  };

  print_colour_text("Test10 - alarm set by excess!","white");

  i = 0;
  bool res = true;
  while(i<sizeof(type_arr) && type_arr[i] < hex_arr){

    doc_alarm["p1"]["t"] = 0;
    if(!Alarm.check(ref,type_arr[i])){
      res = false;
      #ifdef DEBUG
      printf("ref: %s type: %d \n",ref.c_str(),type_arr[i]);
      std::cout << "doc_alarm:" << doc_alarm[ref];
      std::cout << "last_value: " << table[ref] << "\n";
      #endif
    }

    i++;
  }

  table = { // old value
    {"p1",5.3} // value to be evaluated
  };

  print_colour_text("Test10 - alarm set by defect!","white");

  i = 0;

  while(i<sizeof(type_arr) && type_arr[i] < hex_arr){

    doc_alarm["p1"]["t"] = 0;
    if(!Alarm.check(ref,type_arr[i])){
      res = false;
      #ifdef DEBUG
      printf("ref: %s type: %d \n",ref.c_str(),type_arr[i]);
      std::cout << "doc_alarm:" << doc_alarm[ref];
      std::cout << "last_value: " << table[ref] << "\n";
      #endif
    }

    i++;
  }

  return res;
}

bool calledInAlarm(String ref){
  std::cout << "[callback] " << ref << " : " << table[ref] << std::endl;
  return true;
}

bool alarm_test11(){

  print_colour_text("Test1 - testing callback!","white");

  std::string ref = "p1";

  doc_alarm = {
    {"p1",
      {
        {"min",10},
        {"max",20},
        {"d",1}, // calculate difference between actual value and last value
        {"o",12}, // alarm last value
        {"t",0} // alarm triggered
      }
    }
  };

  table = {
    {"p1",45} // value to be evaluated
  };

  bool (*callback)(String);
  callback = &calledInAlarm;
  return Alarm.check("p1",type_arr[0],callback);

}

typedef bool (*func_test_type)(void);
func_test_type call_test[] = {
  &alarm_test1,
  &alarm_test2,
  &alarm_test3,
  &alarm_test4,
  &alarm_test5,
  &alarm_test6,
  &alarm_test7,
  &alarm_test8,
  &alarm_test9,
  &alarm_test10,
  &alarm_test11
};

int main() {
    #ifndef UNITTEST
    print_colour_text("Hello World!","red");
    #else
    print_colour_text("","white");
    print_colour_text("--- --- ---","blue");
    print_colour_text("Hello Unit Test!","blue");
    try{
      uint8_t i = 0;
      while(i<sizeof(test)){
        if(test[i]){
          if(call_test[i]())
            print_colour_text(" Test "+std::to_string(i+1)+" has passed","green");
          else
            print_colour_text(" Test "+std::to_string(i+1)+" has failed","red");
        }
        i++;
      }
      printf("\ncheck function called: %d times \n",Alarm.check_counter());
    }catch(std::invalid_argument& e){
      std::cerr << e.what() << std::endl;
    }catch(...){
      print_colour_text("!! Exception Ocurred !! - terminating process ","red");
      return -1;
    }
    print_colour_text("Test terminated","blue");
    #endif
    return 0;
}
