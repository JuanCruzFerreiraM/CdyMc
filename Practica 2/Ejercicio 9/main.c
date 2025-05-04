#include "./include/lcd.h"
#include "./include/keypad.h"
#define true 1
#define false 0

int main(int argc, char const *argv[])
{
    uint8_t key;
    uint8_t is_key_press;
    KEYPAD_Init();
    LCD_Init();
    while (true)
    {   
        is_key_press = KEYPAD_scan(&key);
        if (is_key_press) {
            LCDclr();
            LCDhome();
            LCDsendChar(key);
        }
    }
    
    return 0;
}
