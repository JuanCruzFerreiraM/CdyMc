#include "../../include/state_handlers.h"

static uint8_t welcome_title[] = "Bienvenido a PasswordFinder";
static uint8_t welcome_description[] = "Pulse * para comenzar";


void main_screen()
{
    LCDstring(&welcome_title, 27);
    LCDGoToXY(0, 1);
    LCDstring(&welcome_description, 21);
    LCDcursorOFF();
}