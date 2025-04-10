/**
 * TP 1
 * Autores: Cid de la Paz, Alejo-Ferreira Monteiro, Juan Cruz-Garmendia Marotz, Joaquin.
 * Materia: Circuitos Digitales y Microcontroladores
 */
#define F_CPU 16000000UL
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#define TRUE 1
#define FALSE 0

/**
 * @brief Alterna entre encender los pines pares o impares del puerto D.
 *
 * Esta función enciende los pines pares (0, 2, 4, 6) o impares (1, 3, 5, 7) del puerto D
 * dependiendo del valor de la variable `parity`. Si `parity` es TRUE, enciende los pares;
 * si es FALSE, enciende los impares. Además, alterna el valor de `parity` para la próxima llamada.
 *
 * @param parity Puntero a una variable que indica si encender los pines pares (TRUE) o impares (FALSE).
 */
void on_by_parity(uint8_t *);

/**
 * @brief Enciende un pin específico del puerto D en secuencia ascendente.
 *
 * Esta función enciende un pin del puerto D indicado por `act_bit`. Si `act_bit` alcanza el valor 7,
 * se reinicia a 0 para comenzar nuevamente desde el primer pin.
 *
 * @param act_bit Puntero a una variable que indica el pin actual a encender (0-7).
 */
void on_led_s1(uint8_t *);

/**
 * @brief Enciende un pin específico del puerto D en secuencia ascendente o descendente.
 *
 * Esta función enciende un pin del puerto D indicado por `act_bit`, siguiendo un sentido
 * determinado por `direction`. Si `direction` es 0, los pines se encienden en secuencia ascendente
 * (de 0 a 7). Si `direction` es 1, los pines se encienden en secuencia descendente (de 7 a 0).
 * Cuando se alcanza el extremo (0 o 7), el sentido cambia automáticamente.
 *
 * @param act_bit Puntero a una variable que indica el pin actual a encender (0-7).
 * @param direction Puntero a una variable que indica el sentido de la secuencia:
 *                  0 para ascendente (LSB a MSB), 1 para descendente (MSB a LSB).
 */
void on_led_s2(uint8_t *, uint8_t *);

int main()
{
    DDRD = 0xFF;  // Configuramos todos los pines del puerto D como salidas
    DDRC  |= (0 << PC0); // Configuramos el pin 0  del puerto C como entrada
	DDRC  |= (0 << PC1); // Configuramos el pin 1 del puerto C como entrada
    PORTC = 0x03; // Activamos la resistencia pull up interna de los pines 0 y 1 del puerto C
    DDRB = 0x18;  // Configuramos los pines 3 y 4 del puerto B como salidas.
    uint8_t sequence = 1;
    uint8_t parity = TRUE;
    uint8_t act_bit = 0;
    uint8_t direction = 0; // Si direction es 0 va del LSB al MSB si es 1 va del MSB al LSB
    while (TRUE)
    {
        if ((PINC & (1 << PC0)) == 0)
        // Comprobamos si el pulsador de cambio de secuencia esta activo.
        {
			while ((PINC & (1 << PC0)) == 0) {
				_delay_ms(1);
			}
			sequence = (sequence % 3) + 1;
            PORTD = 0x00;
            act_bit = 0;
            direction = 0;
        }

        if ((PINC & (1 << PC1)) == 0)
        { // Comprobamos si el pulsador de ver secuencia esta activo;
            PORTB = (sequence << PB3);
        }

        if ((PINC & (1 << PC1)) != 0)
        { // Comprobamos si el pulsador de ver secuencia esta inactivo;
            PORTB = 0x00;
        }

        switch (sequence)
        {
        case 1:
            on_by_parity(&parity);
            _delay_ms(100);
            break;
        case 2:
            on_led_s1(&act_bit);
            _delay_ms(100);
            break;
        case 3:
            on_led_s2(&act_bit, &direction);
            _delay_ms(100);
            break;
        }
    }
    return 0;
}

void on_by_parity(uint8_t *parity)
{
    if (*parity)
    {
        PORTD = 0b01010101;
        *parity = FALSE;
    }
    else
    {
        PORTD = 0b10101010;
        *parity = TRUE;
    }
}

void on_led_s1(uint8_t *act_bit)
{
    if (*act_bit <= 7)
    {
        PORTD = 0x00;
        PORTD |= (1 << *act_bit);
        if (*act_bit == 7)
        {
            *act_bit = 0;
        }
        else
        {
            (*act_bit)++;
        }
    }
}

// Pensar si hay alguna forma de hacerlo sin direction
void on_led_s2(uint8_t *act_bit, uint8_t *direction)
{
    if (!*direction)
    {
        PORTD = 0x00;
        PORTD |= (1 << *act_bit);
        if (*act_bit == 7)
        {
            *direction = 1;
            (*act_bit)--;
        }
        else
        {
            (*act_bit)++;
        }
    }
    else
    {
		PORTD = 0x00;
        PORTD |= (1 << *act_bit);
        if (*act_bit == 0)
        {
            *direction = 0;
            (*act_bit)++;
        }
        else
        {
            (*act_bit)--;
        }
    }
}