/* Change TWSR and TWPS in TWIPrimitives.h if your clock differs from 4 MHz. */

#define F_CPU 4000000UL 

#include <avr/io.h>
#include <util/delay.h>

#include "DS1307.h"

int main(void) {
	DDRD = 0xFF; // 8 LEDs
	TWIInit();

	/* You have to start the oscillator atleast once */
	DS1307StartOsc();

	/* Set time to 15:50:00 Monday 22.7.2013 */
	DS1307SetTimeAndDate(15,50,0,1,22,7,2013);	
	
	while(1) {
		unsigned int sec;
		sec = DS1307GetSeconds();
		PORTD = sec;
 	}
}
