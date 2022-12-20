
#include "alarm.hpp"

DynamicJsonDocument table(220);

ALARM Alarm(&Serial);

String ref = "sensor1";

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

  Alarm.list();
}

void loop() {
  // put your main code here, to run repeatedly:

  if(Alarm.timedOut(ref)){
    //uint8_t rand = (uint8_t)random(0,20);
    uint8_t rand = 20;
    Serial.printf("value: %d \n",rand);
    table[ref] = rand;
    JsonObject data = table.as<JsonObject>();
    if(Alarm.check(ref,int32be_type,data))
      Serial.println(ref+" is in alarm\n");
  }

}
