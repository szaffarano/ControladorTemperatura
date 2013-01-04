#include <Clock.h>
#include <Wire.h>
#include <LiquidCrystal_SR.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <IRremote.h>
#include "YK001.h"

Clock* clock;
LiquidCrystal_SR* lcd;
DallasTemperature* sensors;
OneWire* one_wire;
IRrecv* receiver;
decode_results* results;

Date date;

void (*screens[])() = {
  print_temp,
  print_date
};
uint8_t screens_count;
uint8_t current_screen;

#define RED 7
#define GREEN 6
#define WHITE 5

#define HC595_CLOCK 1
#define HC595_DATA 3
#define HC595_LATCH 4

#define RTC_DS 2

#define DS18B20 8

#define RECEIVER 11

void setup() {
  // inicializar el RTC
  clock = new Clock(2);
  
  // inicializar la pantalla LCD
  setup_lcd();

  // leds de status
  setup_leds();
  
  // sensor de temperatura
  setup_sensors();
  
  // control remoto
  setup_receiver();

  screens_count = sizeof(screens)/sizeof(void*);
  current_screen = 0;
}
 
void loop() {
  if (receiver->decode(results)) {
    if (results->value == NEXT) {
      current_screen = current_screen < screens_count-1 ? current_screen+1 : 0;
    } else if (results->value == PREV) {
      current_screen = current_screen > 0 ? current_screen-1 : screens_count-1;
    }
    receiver->resume();
  }
  screens[current_screen]();
  delay(1000);
}

static void setup_lcd() {
  lcd = new LiquidCrystal_SR (HC595_DATA, HC595_CLOCK, HC595_LATCH);
  lcd->begin (16,2);
  lcd->noBacklight();
  lcd->home ();
}

static void setup_leds() {
  
  pinMode(WHITE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  
  pinMode(HC595_LATCH, OUTPUT);
  pinMode(HC595_CLOCK, OUTPUT);
  pinMode(HC595_DATA, OUTPUT);
  
  digitalWrite(HC595_LATCH, LOW);  
  shiftOut(HC595_DATA, HC595_CLOCK, LSBFIRST, 0);
  digitalWrite(HC595_LATCH, HIGH);  
  
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

static void setup_receiver() {
  receiver = new IRrecv(RECEIVER);
  receiver->enableIRIn();
}

static String pad(uint8_t number) {
  return (number < 10 ? "0" : "") + String(number);
}

static void print_date() {
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
}

static void print_temp() {
  sensors->requestTemperatures();
  lcd->clear();
  lcd->print(sensors->getTempCByIndex(0));
  lcd->print(" grados");
}
