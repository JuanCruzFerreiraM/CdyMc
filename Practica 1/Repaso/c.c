/* Duda sobre un porcentaje en la salida, es por la shell, el código en principio parece correcto */
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>
#include <stdlib.h>

#define N 3 // Dado que es un valor de 8 bits entre 0-255 a lo sumo tenemos 3 valores en el array
/**
 * Convierte un valor numérico sin signo de 8 bits a un array de caracteres compuesto por los dígitos
 * @param number: número entre 0-255
 * @param string: array final con los dígitos como caracteres
 */
void convertor(uint8_t, uint8_t*);
void print(uint8_t*);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error 1. El número de argumentos es incorrecto");
        return 1;
    }
    uint8_t number = atoi(argv[1]);
    if (number > 255) {
        printf("Error 2. El valor numérico debe ser de 8 bits sin signo (0-255)");
        return 2;
    } 

    uint8_t string[N];
    convertor(number, string);
    print(string);
    return 0;
}

void convertor(uint8_t number, uint8_t *string) {
    for (int i = N-1; i >= 0; i--) {
        printf("%d", number);
        string[i] = number % 10 + '0';
        number /= 10;
    }
}   

void print(uint8_t *string) {
    for (int i = 0; i < 3; i++) {
        printf("%c", string[i]);
        if (i < 2) {
            printf(" -");
        }
    }
}
