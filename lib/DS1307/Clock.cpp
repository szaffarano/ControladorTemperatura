#include <Clock.h>

Date::Date() {
}

Date::Date(uint16_t y, uint8_t m, uint8_t d) {
  Date(y, m, d, 0, 0, 0);
}

Date::Date(uint16_t y, uint8_t m, uint8_t d, uint8_t h, uint8_t mm, uint8_t s) {
  this->year = y;
  this->month = m;
  this->day = d;
  this->hour = h;
  this->minute = mm;
  this->second = s;
}
  
uint16_t Date::getYear() {
  return this->year;
}

uint8_t Date::getMonth() {
  return this->month;
}

uint8_t Date::getDay() {
  return this->day;
}

uint8_t Date::getHour() {
  return this->hour;
}

uint8_t Date::getMinute() {
  return this->minute;
}

uint8_t Date::getSecond() {
  return this->second;
}

void Date::setYear(uint16_t y) {
  this->year = y;
}

void Date::setMonth(uint8_t m) {
  this->month = m;
}

void Date::setDay(uint8_t d) {
  this->day = d;
}

void Date::setHour(uint8_t h) {
  this->hour = h;
}

void Date::setMinute(uint8_t m) {
  this->minute = m;
}

void Date::setSecond(uint8_t s) {
  this->second = s;
}

Clock::Clock(uint8_t sqw) { 
  pinMode(sqw, INPUT);
  digitalWrite(sqw, HIGH);
 
  RTC.setRAM(0, (uint8_t *)&startAddr, sizeof(uint16_t));
  
  /*
   Control Register for SQW pin which can be used as an interrupt.
  */
  RTC.ctrl = 0x00;                      // 0x00=disable SQW pin, 0x10=1Hz,
                                        // 0x11=4096Hz, 0x12=8192Hz, 0x13=32768Hz
  RTC.setCTRL();
}

void Clock::setDate(Date date) {
  RTC.stopClock();
         
  RTC.fillByYMD(date.getYear(),date.getMonth(), date.getDay());
  RTC.fillByHMS(date.getHour(), date.getMinute(), date.getSecond());
     
  RTC.setTime();
  
  RTC.startClock();
}

Date Clock::getDate() {
  RTC.getTime();
  return Date(RTC.year, RTC.month, RTC.day, RTC.hour, RTC.minute, RTC.second);
}

void Clock::getDate(Date* date) {
  RTC.getTime();
  date->setYear(RTC.year);
  date->setMonth(RTC.month);
  date->setDay(RTC.day);
  date->setHour(RTC.hour);
  date->setMinute(RTC.minute);
  date->setSecond(RTC.second);
}