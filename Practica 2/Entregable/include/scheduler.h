#include <avr/interrupt.h>
#include <stdint.h>

volatile uint8_t mef_flag = 0;

uint8_t scheduler_init();