#include "../../include/scheduler.h"

static void SEOS_SCH_Task();

ISR(TIMER0_COMPA_vect)
{
    SEOS_SCH_Task();
}

static void SEOS_SCH_Task()
{
    if ((++cont_mef % 5) == 0)
    {
        mef_flag = 1;
    }
}

void scheduler_init()
{
    OCROA = 157;

    // Modo CTC: WGM02:0 = 0b010 (WGM01 = 1, WGM00 = 0)
    TCCR0A |= (1 << WGM01);
    TCCR0A &= ~(1 << WGM00);
    TCCR0B &= ~(1 << WGM02);

    // Prescaler 1024: CS02:0 = 0b101
    TCCR0B |= (1 << CS02) | (1 << CS00);
    TCCR0B &= ~(1 << CS01);

    // Habilitar interrupción por comparación con OCR0A
    TIMSK0 |= (1 << OCIE0A);
}
