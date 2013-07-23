#ifndef DS1307_H
#define DS1307_H

#include "TWIPrimitives.h"

void DS1307StartOsc(void);
void DS1307SetTimeAndDate(uint8_t h, uint8_t m, uint8_t s
, uint8_t dayOfWeek, uint8_t date, uint8_t month, unsigned int year);
uint8_t ReadDataFrom(uint8_t mem);

uint8_t DS1307GetSeconds(void);
uint8_t DS1307GetMinutes(void);
uint8_t DS1307GetHours(void);
uint8_t DS1307GetDayOfWeek(void);
uint8_t DS1307GetDate(void);
uint8_t DS1307GetMonth(void);
uint8_t DS1307GetYear(void);

uint8_t DS1307GetTenSeconds(void);
uint8_t DS1307GetTenMinutes(void);
uint8_t DS1307GetTenHours(void);
uint8_t DS1307GetTenDate(void);
uint8_t DS1307GetTenMonth(void);
uint8_t DS1307GetTenYear(void);

#endif
