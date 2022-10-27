# esp32-alarm

## Description
package to detect values outside of a defined range

## Implementation
Alarms are stored in a JsonDocument with the following structure
```
  doc_alarm = {[
    ref : {
       "min" : min_value,
       "max" : max_value,
       "d" : bool, // use differencial values (actual value oldest value),
       "t" : bool, // alarm triggered
       "o" : last_value
     }]
  }
```
## Methods
[bool ALARM::add(String ref, long min, long max, int8_t diff = 0)](#Add-object-1)

[bool ALARM::add(JsonObject obj)](#Add-object-2)

[bool check(String ref, uint8_t type, JsonObject value)](#Check-Alarm-1)

[bool check(String ref, uint8_t type, bool(*callback)(String))](#Check-Alarm-2)

### Add object 1
return true if has succeed

bool ALARM::add(String ref, long min, long max, int8_t diff = 0)

#### Example
```
  if(!Alarm.add("sensor2",12,20,0)){
    Serial.println("!! Error adding sensor2 alarm");
  }
```
### Add object 2
return true if has succeed

bool ALARM::add(JsonObject obj)
```
  obj = {
    "ref"       : <string>,
    "min_value" : <number>,
    "max_value" : <number>,
    "diff"      : <number>
 }
 ```
*diff - 1 to use the difference between current and last value, 0 - otherwise

#### Example

```
  StaticJsonDocument<64> doc_object;

  doc_object["ref"] = "sensor1";
  doc_object["min_value"] = 2;
  doc_object["max_value"] = 12;
  doc_object["diff"] = 0;

  JsonObject obj = doc_object.as<JsonObject>();

  Alarm.add(obj);
```

### Check Alarm 1
return true if is in alarm

bool ALARM::check(String ref, uint8_t type, JsonObject value)

#### Example
```
  DynamicJsonDocument table(220);
  String ref = "sensor1"
  table[ref] = rand;
  JsonObject data = table.as<JsonObject>();

  Alarm.check(ref,int32be_type,data);
```

### Check Alarm 2
return true if is in alarm

call callback function if alarm goes out of range limite or returns to the range limit

bool ALARM::check(String ref, uint8_t type, bool(*callback)(String))

#### Example
```
DynamicJsonDocument table(220);
String ref = "sensor1"
table[ref] = rand;
JsonObject data = table.as<JsonObject>();

Alarm.check(ref,int32be_type,data);
```
