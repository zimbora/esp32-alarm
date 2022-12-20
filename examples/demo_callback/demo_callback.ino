
#include "alarm.hpp"

DynamicJsonDocument table(220); // store values to be analyzed

ALARM Alarm(&Serial);

String ref = "sensor1";

bool (*callback)(String);
bool calledInAlarm(String ref){
  Serial.println("alarm was changed");
  return true;
}


void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  StaticJsonDocument<120> doc_object;

  doc_object["ref"] = "sensor1";
  doc_object["min_value"] = 2;
  doc_object["max_value"] = 12;
  doc_object["diff"] = 0;
  doc_object["period"] = 15;

  JsonObject obj = doc_object.as<JsonObject>();

  if(!Alarm.add(obj)){
    Serial.println("!! alarm not added");
    serializeJson(obj, Serial);
  }

  if(!Alarm.add("sensor2",30,12,20,0)){
    Serial.println("!! Error adding sensor2 alarm");
  }

  Alarm.list();
}

void loop() {
  // put your main code here, to run repeatedly:

  if(Alarm.timedOut(ref)){
    uint8_t rand = (uint8_t)random(0,20);
    //uint8_t rand = 20;
    Serial.printf("value: %d \n",rand);
    table[ref] = rand;
    table["sensor2"] = rand;
    JsonObject data = table.as<JsonObject>();

    if(Alarm.check(ref,int32be_type,data,calledInAlarm))
      Serial.println(ref+" is in alarm\n");
  }

  if(Alarm.timedOut("sensor2")){

    uint8_t rand = (uint8_t)random(0,20);
    //uint8_t rand = 20;
    Serial.printf("value: %d \n",rand);
    table["sensor2"] = rand;
    JsonObject data = table.as<JsonObject>();

    if(Alarm.check("sensor2",int32be_type,data,calledInAlarm))
      Serial.println("!! sensor2 is in alarm\n");
  }

}
