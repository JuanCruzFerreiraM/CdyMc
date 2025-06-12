#include "../../include/keypad.h"
#define MPORTB 0b00011001
#define MPORTD 0b10000000

/*
    La configuración del keypad es
    Salidas del micro (rows):
    A -> PB4
    B -> PB3
    C -> PB0
    D -> PD7
    Entradas del micro (columns):
    1 -> PD3
    2 -> PD5
    3 -> PD4
    4 -> PD2
*/

void KEYPAD_Init()
{
    DDRD &= ~(0b00111100);
    PORTD |= 0b00111100;

    DDRD |= MPORTD;
    DDRB |= MPORTB;

    PORTD |= MPORTD;
    PORTB |= MPORTB;
}

/**
 * @brief Updates the state of the keypad by scanning for key presses.
 *
 * This function performs a scan of the keypad to detect any key presses.
 * It updates the internal state of the keypad, including which key is
 * currently pressed or if no key is pressed. The function is typically
 * called periodically to ensure the keypad state remains up-to-date.
 *
 * @note Ensure that the keypad hardware is properly initialized before
 *       calling this function.
 *
 * @return uint8_t A value between 0 and 15 representing the pressed key, or 0xFF if no key is pressed.
 */
static uint8_t KEYPAD_update()
{
    uint8_t rowPins[] = {PB4, PB3, PB0, PD7};
    uint8_t colPins[] = {PD3, PD5, PD4, PD2};
    uint8_t row, col;

    for (row = 0; row < 4; row ++) {
        PORTD |= MPORTD;
        PORTB |= MPORTB;
        if (row == 3) {
            PORTD &= ~(1 << rowPins[row]);
        } else {
            PORTB &= ~(1 << rowPins[row]);
        }
        
        for (col = 0; col < 4; col++) {
            if (!(PIND & (1 << colPins[col]))) {
                return (row*4 + col);
            }
        }
    }
    return 0xFF;
 }

/**
 * Converts a given key code to its corresponding character representation.
 *
 * @param key_code The integer value representing the key code to be converted.
 * @return The character corresponding to the provided key code.
 *         If the key code does not map to a valid character, the function
 *         may return a default or undefined value.
 */
 static uint8_t key_to_char (uint8_t key) {
    switch (key)
    {
    case 0:
        return 0x31;
        break;
    case 1:
        return 0x32
        break;
    case 2:
        return 0x33;
        break;
    case 3:
        return 0x41;
        break;
    case 4:
        return 0x34;
        break;
    case 5:
        return 0x35;
        break;
    case 6:
        return 0x36;
        break;
    case 7:
        return 0x42;
        break;
    case 8:
        return 0x37;
        break;
    case 9:
        return 0x38;
        break;
    case 10:
        return 0x39;
        break;
    case 11:
        return 0x43;
        break;
    case 12:
        return 0x30;
        break;
    case 13:
        return 0x2A;
        break;
    case 14:
        return 0x23;
        break;
    case 15:
        return 0x44;
        break;
    
    default:
        return 0xFF;
        break;
    }
 }

/**
 * @brief Scans the keypad to detect which key is pressed.
 *
 * This function performs a scan of the keypad matrix by activating rows
 * and reading columns to determine the pressed key. It returns the 
 * corresponding key value or an indication if no key is pressed.
 *
 * @return int The value of the pressed key, or a specific value indicating
 *             no key press (e.g., -1 if no key is pressed).
 *
 * @note Ensure the keypad is properly initialized before calling this function.
 *       The function assumes a specific hardware configuration for the keypad.
 */

 uint8_t KEYPAD_scan (uint8_t *key) {
     static uint8_t Old_key, Last_valid_key = 0xFF; // no hay tecla presionada;
     uint8_t Key,
         Key = KEYPAD_update();
     if (Key == 0xFF)
     {

         Old_key = 0xFF; // no hay tecla presionada
         Last_valid_key = 0xFF;
         return 0;
     }

     if (Key == Old_key)
     { // Esta comprobación evita el efecto de debouncing

         if (Key != Last_valid_key)
         { // evita multiple detección 

             *key = key_to_char(key);
             Last_valid_key = Key;
             return 1;
         }
     }
     Old_key = Key; // Guardamos la tecla presionada por primera vez
     return 0;
 }

