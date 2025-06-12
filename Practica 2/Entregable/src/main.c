#define F_CPU 16000000UL
#include "../include/scheduler.h"
#include "../include/keypad.h"
#include "../include/lcd.h"

#define true 1
#define false 0

int main()
{
    scheduler_init();
    KEYPAD_Init();
    LCDinit();
    mef_flag = 0;
    sei();
    while (true)
    {
    }
    return 0; //never should reach this
}
