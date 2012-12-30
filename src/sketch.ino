#include <Clock.h>
#include <Wire.h>
#include <LiquidCrystal_SR.h>
#include <OneWire.h>
#include <DallasTemperature.h>

Clock* clock;
LiquidCrystal_SR* lcd;
DallasTemperature* sensors;
OneWire* one_wire;

Date date;

#define RED 7
#define GREEN 6
#define WHITE 5

#define HC595_CLOCK 1
#define HC595_DATA 3
#define HC595_ENABLED 4

#define RTC_DS 2

#define DS18B20 8

#define IR_RECEIVER 11

void setup() {
  // inicializar el RTC
  clock = new Clock(2);
  
  // inicializar la pantalla LCD
  setup_lcd();

  // leds de status
  setup_leds();
  
  setup_sensors();
}
 
void loop() {
  clock->getDate(&date);

  lcd->clear();
  
  lcd->setCursor(0, 0);  
  String str = "";
  str += pad(date.getDay()) + "/";
  str += pad(date.getMonth()) + "/";
  str += String(date.getYear()) + " ";
  lcd->print(str);
  
  lcd->setCursor(0, 1);
  str = "";
  str += pad(date.getHour()) + ":";
  str += pad(date.getMinute()) + ":";
  str += pad(date.getSecond());
  lcd->print(str);

  delay(1500);
  
  sensors->requestTemperatures();
  lcd->clear();
  lcd->print(sensors->getTempCByIndex(0));
  lcd->print(" grados");
  
  delay(1500);
}

static void setup_lcd() {
  lcd = new LiquidCrystal_SR (HC595_DATA, HC595_CLOCK, HC595_ENABLED);
  lcd->begin (16,2);
  lcd->home ();
}

static void setup_leds() {
  pinMode(WHITE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  
  digitalWrite(WHITE, HIGH);
  delay(500);
  digitalWrite(GREEN, HIGH);
  delay(500);
  digitalWrite(RED, HIGH);
  delay(500);
  digitalWrite(RED, LOW);
  delay(500);
  digitalWrite(GREEN, LOW);
  delay(500);
  digitalWrite(WHITE, LOW);
}

static void setup_sensors() {
  one_wire = new OneWire(DS18B20);
  sensors = new DallasTemperature(one_wire);
  sensors->begin();
}

static String pad(uint8_t number) {
  return (number < 10 ? "0" : "") + String(number);
}