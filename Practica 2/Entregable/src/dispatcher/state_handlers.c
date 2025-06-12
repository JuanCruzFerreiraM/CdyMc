#include "../../include/state_handlers.h"

#define NUM_ELEMENTOS(arr) (sizeof(arr) / sizeof((arr)[0]))

uint8_t key_value;
uint8_t welcome_title[] = "Bienvenido a PasswordFinder";
uint8_t welcome_description[] = "Pulse * para comenzar";
uint8_t error_description[] = "Error, vuelva a intentarlo";
uint8_t timer = 0;
uint8_t password_value[6] = {0};
uint8_t dictionary[5][6] = {"palab", "clave", "valor", "texto", "prueba"};
uint8_t game_start;
uint8_t lose_title[] = "Derrota";
uint8_t win_title[] = "Victoria";

void main_screen()
{
    LCDclr();
    LCDhome();
    LCDstring(welcome_title, 27);
    LCDGoToXY(0, 1);
    LCDstring(welcome_description, 21);
    LCDcursorOFF();
    if (KEYPAD_scan(&key_value))
    {
        if (key_value == '*')
        {
            state = 1;
        }
        else
        {
            LCDstring(&error_description, 26);
        }
    }
}

void password()
{
    if (timer == 0)
    {
        LCDclr();
        LCDhome();
        srand((unsigned int)TCNT0);
        memcpy(password_value, dictionary[rand() % NUM_ELEMENTOS(dictionary)], 6);
        LCDstring(password_value, 5);
        game_start = cont_mef;
    }
    if (++timer == 40)
    {
        LCDclr();
        LCDhome();
        state = 2;
        timer = 0;
    }
}
/**
 * @brief This function manage the input of the user
 *
 * It uses the function KEYPAD_scan to read the value from the keypad and checks if it is a valid value, then change the state of the mef
 */
void wait_input()
{ // check if there is valid key press
    if (KEYPAD_scan(&key_value))
    { // check if the key press is different from *
        if (key_value != 0x2A)
        {
            state = 3;
        }
    }
}

/**
 * @brief This function handles the verification of the input values
 *
 * Prints the input value into the LCD and checks if this value is correct, also handles the logic to determins if the player win or lose
 *
 *
 */
void check()
{
    static uint8_t errors = 0;
    static uint8_t password_index = 0;
    static char buffer[4] = {0};
    static uint8_t buffer_index = 0;
    if (key_value == 0x23)
    {
        buffer[buffer_index] = '\0'; // Terminador nulo
        uint8_t buffer_value = atoi(buffer);
        if (buffer_value == password_value[password_index])
        {
            LCDGotoXY(password_index, 0);
            LCDsendChar(buffer_value);
            // check if the size of the input equals the size of the password
            if ((password_index + 1) == 5)
            {
                state = 4;
            }
            else
            {
                // clr the buffer and the buffer line
                LCDGotoXY(0, 1);
                buffer_index = 0;
                for (int i = 0; i < 3; i++)
                {
                    buffer[i] = 0;
                    LCDsendChar(' ');
                }
                password_index++;
                state = 2;
            }
        }
        else
        {
            if (++errors == 3)
            {
                state = 5;
            }
            else
            {
                LCDGotoXY(0, 1);
                buffer_index = 0;
                // clr the buffer and the buffer line
                for (int i = 0; i < 3; i++)
                {
                    buffer[i] = 0;
                    LCDsendChar(' ');
                }
                state = 2;
            }
        }
    }
    else
    { // This should't happen
        if (buffer_index >= 3)
        {
            // If it happens, the program would let you rewrite the input.
            buffer_index = 0;
        }
        LCDGotoXY(buffer_index, 1);
        buffer[buffer_index] = key_value;
        LCDsendChar(key_value);
        buffer_index++;
        state = 2;
    }
}

void win()
{
    if (timer == 0)
    {
        LCDclr();
        LCDhome();
        LCDstring(&win_title, 8);
        LCDGoToXY(0, 1);

        // Mostrar el tiempo transcurrido en segundos
        uint8_t time_msg[] = "Tiempo: ";
        LCDstring(time_msg, 8);

        // Obtener el tiempo en segundos y mostrarlo
        int seconds = (cont_mef - game_start) * 10 / 1000; // Convertir a segundos
        LCDescribeDato(seconds, -1);

        uint8_t seconds_unit[] = " segundos";
        LCDstring(seconds_unit, 9);

        LCDcursorOFF();
    }

    // The scheduler triggers this function every 50ms
    // So counting to 100 gives us 5 seconds
    if (++timer == 100)
    {
        timer = 0;
        state = 0; // Return to main screen
    }
}

void lose()
{

    if (timer == 0)
    {
        LCDclr();
        LCDhome();
        LCDstring(&lose_title, 7);
        LCDcursorOFF();
    }

    // The scheduler triggers this function every 50ms
    // So counting to 100 gives us 5 seconds
    if (++timer == 100)
    {
        timer = 0;
        state = 0; // Return to main screen
    }
}