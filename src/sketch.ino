#include <Clock.h>

Clock* clock;
Date date;

void setup() {
  Serial.begin(9600);
  
  clock = new Clock(2);

  Serial.println("Probando DS1307");

  Serial.println();
}
 
void loop() {
  clock->getDate(&date);
  
  if (date.getHour() < 10) {
    Serial.print("0");
    Serial.print(date.getHour(), DEC);
  } else {
    Serial.print(date.getHour(), DEC);
  }

  Serial.print(":");
  if (date.getMinute() < 10) {
    Serial.print("0");
    Serial.print(date.getMinute(), DEC);
  } else {
    Serial.print(date.getMinute(), DEC);
  }
  
  Serial.print(":");
  if (date.getSecond() < 10) {
    Serial.print("0");
    Serial.print(date.getSecond(), DEC);
  } else {
    Serial.print(date.getSecond(), DEC);
  }
  
  Serial.print(" ");
  if (date.getDay() < 10) {
    Serial.print("0");
    Serial.print(date.getDay(), DEC);
  } else {
    Serial.print(date.getDay(), DEC);
  }
  Serial.print("-");
  if (date.getMonth() < 10) {
    Serial.print("0");
    Serial.print(date.getMonth(), DEC);
  } else {
    Serial.print(date.getMonth(), DEC);
  }
  Serial.print("-");
  Serial.print(date.getYear(), DEC);
  Serial.println("");

  delay(1000);
}