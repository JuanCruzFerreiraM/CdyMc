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
        printf("El valor ingresado no es valido");
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