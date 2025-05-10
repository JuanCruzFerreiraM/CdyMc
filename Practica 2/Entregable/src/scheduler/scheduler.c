#include "../../include/scheduler.h"

static void SEOS_SCH_Task();

static uint8_t cont_mef = 0;

ISR(Timer_OVF)
{
    SEOS_SCH_Task();
}

static void SEOS_SCH_Task()
{
    if (++cont_mef == 5)
    {
        mef_flag = 1;
        cont_mef = 0;
    }
}

uint8_t scheduler_init()
{
    // configuración del timer.
}
