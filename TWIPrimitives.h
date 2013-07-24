#ifndef TWIPRIMITIVES_H
#define TWIPRIMITIVES_H

#include <util/twi.h>

void TWIInit(void);
void TWIStart(void);
void TWIWrite(uint8_t data);
void TWIStop(void);
void TWIError(void);

uint8_t TWIReadACK(void);
uint8_t TWIReadNACK(void);
uint8_t TWIGetStatus(void);

#endif
