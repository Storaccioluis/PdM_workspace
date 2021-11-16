#include "stdbool.h"
#include "stdint.h"
#include "main.h"

typedef bool bool_sec;
bool_sec secuencia;
typedef bool bool_t;
typedef enum{
    BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RISING
} debounce_t;

// Variable de estado (global)
debounce_t debounceState;

// Prototipos de funciones
bool_t debounceInit(void );
void debounceUpdate(void);


