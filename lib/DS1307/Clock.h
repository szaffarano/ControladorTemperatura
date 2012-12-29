#ifndef _CLOCK_H_
#define _CLOCK_H_

#include <Wire.h>
#include <DS1307new.h>

class Date {
  uint16_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
public:
  Date();
  Date(uint16_t y, uint8_t m, uint8_t d);
  Date(uint16_t y, uint8_t m, uint8_t d, uint8_t h, uint8_t mm, uint8_t s);
  
  uint16_t getYear();
  uint8_t getMonth();
  uint8_t getDay();
  uint8_t getHour();
  uint8_t getMinute();
  uint8_t getSecond();
  void setYear(uint16_t y);
  void setMonth(uint8_t m);
  void setDay(uint8_t d);
  void setHour(uint8_t h);
  void setMinute(uint8_t m);
  void setSecond(uint8_t s);
};

class Clock {
    /**
    * Dirección inicial para almacenar en la memoria RAM
    */
    uint16_t startAddr = 0x0000;
    
    /**
    * Dirección en donde se lee de la RAM
    */
    uint16_t lastAddr;
public:
  Clock(uint8_t sqw);
  void setDate(Date date);
  Date getDate();
  void getDate(Date* date);
};

#endif