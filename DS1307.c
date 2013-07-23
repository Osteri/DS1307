#include "DS1307.h"

/*** DS1307 RTC ***/
#define DS1307_ADDR 0xD0
/*
TWI speed:              100 kHz (only)

00h: bits 7-4 - 10th seconds, bits 3-0 - seconds
01h: bits 7-4 - 10th minutes, bits 3-0 - minutes 
02h: bits 7-4 - 10th hours, bits 3-0 - hours 
03h: day of the week
04h: bits 5-4 - 10th day of the month, bits day of the month
05h: bit 4 - 10th month, bits 3-0 - months
06h: bits 7-4 - 10th year, bits 3-0 year  
*/

void DS1307StartOsc(void) {
	TWIStart();
	if (TWIGetStatus() != 0x08) TWIError();
	
	TWIWrite((uint8_t)(DS1307_ADDR)); // Write operation
	if (TWIGetStatus() != 0x18) TWIError();
	
	TWIWrite((uint8_t)(0x00)); // Seconds register
	if (TWIGetStatus() != 0x28) TWIError();
	
	TWIWrite((uint8_t)(0x00)); // Write CH-bit to "0" (start osc) 
	if (TWIGetStatus() != 0x28) TWIError();
	
	TWIStop();
}

void DS1307SetTimeAndDate(uint8_t h, uint8_t m, uint8_t s,
uint8_t dayOfWeek, uint8_t date, uint8_t month, unsigned int year) {

	year -= 2000; // Register has year value of (0-99)	
	uint8_t ten_h = (h / 10);
	uint8_t ten_m = (m / 10);
	uint8_t ten_s = (s / 10);
	uint8_t ten_date = (date / 10);
	uint8_t ten_month = (month / 10);
	uint8_t ten_year = (year / 10);
	
	h = (h % 10);
	m = (m % 10);
	s = (s % 10);
	date = (date % 10);
	month = (month % 10);
	year = (year % 10);

	/* Adjust values to suit DS1307 memory space */
	ten_s = (ten_s << 4);
	ten_m = (ten_m << 4);
	ten_h = (ten_h << 4);
	ten_date = (ten_date << 4);
	ten_month = (ten_month << 4);
	ten_year = (ten_year << 4);

	s |= ten_s;
	m |= ten_m;
	h |= ten_h;
	date |= ten_date;
	month |= ten_month;
	year |= ten_year;
	
	//h = ((h + AMPM_MODE) << 6); // AMPM_MODE is "1" -> 12 hour mode

	uint8_t values[7] = {s, m, h, dayOfWeek, date, month, year};
	
	TWIStart();
	if (TWIGetStatus() != 0x08) TWIError();
	
	TWIWrite((uint8_t)(DS1307_ADDR)); // Write operation
	if (TWIGetStatus() != 0x18) TWIError();

	TWIWrite((uint8_t)(0x00)); // Start from seconds register (00h)
	if (TWIGetStatus() != 0x28) TWIError();

	uint8_t i = 0;
	for (i; i < 8; i++) { // Write 7 memory bytes (00h->07h)
		TWIWrite((uint8_t)(values[i]));  
		if (TWIGetStatus() != 0x28) TWIError();
	}	
	TWIStop();
}
uint8_t DS1307ReadDataFrom(uint8_t mem) {
	uint8_t u8data;
	TWIStart();
	if (TWIGetStatus() != 0x08) TWIError();
	TWIWrite((uint8_t)(DS1307_ADDR));
	if (TWIGetStatus() != 0x18) TWIError();
	TWIWrite((uint8_t)(mem));
	if (TWIGetStatus() != 0x28) TWIError();
	TWIStart();
	if (TWIGetStatus() != 0x10) TWIError();
	TWIWrite((uint8_t)(DS1307_ADDR + 1));
	if (TWIGetStatus() != 0x40) TWIError();
	u8data = TWIReadNACK();
	if (TWIGetStatus() != 0x58) TWIError();
	TWIStop();
	return u8data;
}

uint8_t DS1307GetSeconds(void) {
	uint8_t u8data;	
	u8data = DS1307ReadDataFrom(0x00);
	u8data &= 0x0F;
	return u8data;
}
uint8_t DS1307GetMinutes(void) {
	uint8_t u8data;	
	u8data = DS1307ReadDataFrom(0x01);
	u8data &= 0x0F;
	return u8data;
}
uint8_t DS1307GetHours(void) {
	uint8_t u8data;	
	u8data = DS1307ReadDataFrom(0x02);
	u8data &= 0x0F;
	return u8data;
}
uint8_t DS1307GetDayOfWeek(void) {
	uint8_t u8data;	
	u8data = DS1307ReadDataFrom(0x03);
	return u8data;
}
uint8_t DS1307GetDate(void) {
	uint8_t u8data;	
	u8data = DS1307ReadDataFrom(0x04);
	u8data &= 0x0F;
	return u8data;
}
uint8_t DS1307GetMonth(void) {
	uint8_t u8data;	
	u8data = DS1307ReadDataFrom(0x05);
	u8data &= 0x0F;
	return u8data;
}
uint8_t DS1307GetYear(void) {
	uint8_t u8data;	
	u8data = DS1307ReadDataFrom(0x06);
	u8data &= 0x0F;
	return u8data;
}
uint8_t DS1307GetTenSeconds(void) {
	uint8_t u8data;	
	u8data = DS1307ReadDataFrom(0x00);
	u8data &= 0x70;
	u8data = (u8data >> 4);
	return u8data;
	
}
uint8_t DS1307GetTenMinutes(void) {
	uint8_t u8data;	
	u8data = DS1307ReadDataFrom(0x01);
	u8data = (u8data >> 4);
	return u8data;
}
uint8_t DS1307GetTenHours(void) {
	uint8_t u8data;	
	u8data = DS1307ReadDataFrom(0x02);
	u8data &= 0x30;
	u8data = (u8data >> 4);
	return u8data;
}
uint8_t DS1307GetTenDate(void) {
	uint8_t u8data;	
	u8data = DS1307ReadDataFrom(0x04);
	u8data &= 0x30;
	u8data = (u8data >> 4);
	return u8data;
}
uint8_t DS1307GetTenMonth(void) {
	uint8_t u8data;	
	u8data = DS1307ReadDataFrom(0x05);
	u8data = (u8data >> 4);
	return u8data;
}
uint8_t DS1307GetTenYear(void) {
	uint8_t u8data;	
	u8data = DS1307ReadDataFrom(0x06);
	u8data = (u8data >> 4);
	return u8data;
}
