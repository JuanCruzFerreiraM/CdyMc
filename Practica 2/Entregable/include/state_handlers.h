#include <stdint.h>
#include "include/keypad.h"
#include "include/lcd.h"
#include "include/mef.h"
#include "include/scheduler.h"
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
//include lcd

void main_screen();
void password();
void wait_input();
void check();
void win();
void lose();