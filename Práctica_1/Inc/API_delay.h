/*
 * API_delay.h
 *
 *  Created on: 5 nov. 2021
 *      Author: luis
 */


#ifndef API_DELAY_H_
#define API_DELAY_H_

#include "stdbool.h"
#include "stdint.h"
#include "main.h"

typedef uint32_t tick_t; // Qué biblioteca se debe incluir para que esto compile
typedef bool bool_t;      // Qué biblioteca se debe incluir para que esto compile

typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;

void delayInit( delay_t * delay, tick_t duration );
bool_t delayRead( delay_t * delay );
void delayWrite( delay_t * delay, tick_t duration );



#endif /* API_DELAY_H_ */
