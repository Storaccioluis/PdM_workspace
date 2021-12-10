/*
 * API_menu.h
 *
 *  Created on: 5 dic. 2021
 *      Author: luis
 */

#ifndef API_MENU_H_
#define API_MENU_H_

#include "stdbool.h"
#include "stdint.h"
#include "main.h"

typedef bool bool_sec;
bool_sec secuencia;
typedef bool bool_t;
typedef enum{
    READ_FIRST_C,
	READ_NUMBER_STEP,
    VALIDATE_STEP,
	TURN_SERVO,
	STATUS_TURN,
	STATUS_CHARACTER_INCORRECT,
} menu_t;

// Variable de estado (global)
menu_t menuState;

// Prototipos de funciones
bool_t menuInit(void );
void menuUpdate(uint16_t *dirP);
static uint16_t CharToInt(uint8_t *data);



#endif /* API_MENU_H_ */
