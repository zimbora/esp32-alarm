
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

  StaticJsonDocument<64> doc_object;

  doc_object["ref"] = "sensor1";
  doc_object["min_value"] = 2;
  doc_object["max_value"] = 12;
  doc_object["diff"] = 0;

  JsonObject obj = doc_object.as<JsonObject>();

  if(!Alarm.add(obj)){
    Serial.println("!! alarm not added");
    serializeJson(obj, Serial);
  }

  if(!Alarm.add("sensor2",12,20,0)){
    Serial.println("!! Error adding sensor2 alarm");
  }

  Alarm.list();
}

void loop() {
  // put your main code here, to run repeatedly:

  uint8_t rand = (uint8_t)random(0,20);
  //uint8_t rand = 20;
  Serial.printf("value: %d \n",rand);
  table[ref] = rand;
  table["sensor2"] = rand;
  JsonObject data = table.as<JsonObject>();

  callback = &calledInAlarm;

  if(Alarm.check(ref,int32be_type,data,callback))
    Serial.println(ref+" is in alarm\n");

  if(Alarm.check("sensor2",int32be_type,data,callback))
    Serial.println("!! sensor2 is in alarm\n");

  delay(3000);
}
