#include <avr/interrupt.h>
#include <stdint.h>

extern  volatile uint8_t mef_flag;
extern  volatile uint8_t cont_mef;

void     scheduler_init();