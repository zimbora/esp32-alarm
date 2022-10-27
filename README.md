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
## Public Methods
[bool add(String ref, long min, long max, int8_t diff = 0)](#Add-object-1)

[bool add(JsonObject obj)](#Add-object-2)

[bool check(String ref, uint8_t type, JsonObject value)](#Check-Alarm-1)

[bool check(String ref, uint8_t type, bool(*callback)(String))](#Check-Alarm-2)

[void list()](#List)

[JsonObject get(String ref)](#Get)

## Examples
  Run programs inside examples folder to check how it works
### demo
  Add alarms and then check it forever
### demo_callback
  Add alarms and then check it forever. If alarm state was changed call registered callback
### test_limits
  Check how many alarms can be handled with actual parameters

## Unit Test with clang
  >> chmod u+x make.sh

  >> ./make.sh

  If needed uncomment DEBUG FLAGS in Makefile

## Public Methods - Extension

### Add object 1
return true if has succeed
```
bool ALARM::add(String ref, long min, long max, int8_t diff = 0)
```
#### Example
```
  if(!Alarm.add("sensor2",12,20,0)){
    Serial.println("!! Error adding sensor2 alarm");
  }
```
### Add object 2
return true if has succeed
```
bool ALARM::add(JsonObject obj)
```
```
  obj = {
    "ref"       : <string>,
    "min_value" : <number>,
    "max_value" : <number>,
    "diff"      : <number> // 1 to use the difference between current and last value, 0 - otherwise
 }
 ```

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
```
bool ALARM::check(String ref, uint8_t type, JsonObject value)
```
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

call callback function if alarm goes out of the range limit or returns to the range limit
```
bool ALARM::check(String ref, uint8_t type, bool(*callback)(String))
```
#### Example
```
bool (*callback)(String);
bool calledInAlarm(String ref){
  Serial.println("alarm was changed");
  return true;
}

DynamicJsonDocument table(220);
String ref = "sensor1"
table[ref] = rand;
JsonObject data = table.as<JsonObject>();

callback = &calledInAlarm;
Alarm.check(ref,int32be_type,data,callback);
```

### List

```
void ALARM::list()
```
#### Example
```
  Alarm.list();
```

### Get

```
JsonObject ALARM::get(String ref)
```
#### Example
```
  JsonObject object = Alarm.get("sensor1");
```
