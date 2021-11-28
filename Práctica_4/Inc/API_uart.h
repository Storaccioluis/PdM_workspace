/*
 * API_uart.h
 *
 *  Created on: 22 nov. 2021
 *      Author: luis
 */
#include "main.h"
#include "stdbool.h"
#include "stdint.h"
typedef bool bool_t;

bool_t uartInit();

void uartSendString(uint8_t *pstring,uint16_t size);

