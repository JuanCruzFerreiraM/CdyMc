
#include <stdint.h>
#include <avr/io.h>

#define HIGH 1
#define LOW 1


/**
 * @brief Inicia el KEYPAD
 * Esta función se encarga de iniciar los puertos para el correcto funcionamiento del keypad usado en la 
 * practica, para esto pone en cero los respectivos valores de los pines de salida, y activa las pull-up de 
 * los pines de salida
 */
void KEYPAD_Init();

/**
 * @
 */
uint8_t KEYPAD_scan(uint8_t *key);

