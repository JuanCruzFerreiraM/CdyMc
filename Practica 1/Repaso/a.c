/**
 * @brief Calculates the sum of all integers from 1 to N.
 *
 * This function takes an 8-bit unsigned integer N as input and calculates
 * the sum of all integers from 1 to N. The result is returned as a 16-bit
 * unsigned integer.
 *
 * @param N The upper limit of the range to sum, must be in the range 0-255.
 * @return The sum of all integers from 1 to N.
 */
uint16_t sumCalc(uint8_t N);
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

uint16_t sumCalc(uint8_t); 

int main(void) {
    uint8_t N;
    uint16_t sum;
    printf("Ingrese un valor en el rango 0-255 \n");
    if (scanf("%" SCNu8, &N) != 1) {
          printf("El valor ingresado no es válido");
          return 1;
    }
    sum = sumCalc(N);
    printf("La suma de los valores es: %" PRIu16 "\n", sum);
}

uint16_t sumCalc(uint8_t N) {
     uint16_t total = 0;
     for (uint8_t i = 1; i <= N; i++) {
          total += i;
     }
     return total;
}