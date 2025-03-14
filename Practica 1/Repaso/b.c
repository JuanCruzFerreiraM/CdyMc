#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <stdlib.h>

#define N 4

void swapper(int8_t*, int8_t*);
void orderArray(int8_t*, uint16_t); //dado que 2^16 ~= 65.000 con el tipo de datos usado podemos tener un vector de hasta ~ 65 mil valores


int main(void) {
    int8_t array[N];
    int16_t byteSize = sizeof(int8_t) * N;
    for (int i = 0; i < N; i++) {
        array[i] = rand() % 256;
        printf("El valor en la posicion %d es : %" PRId8 "\n", i, array[i]);
    }
    orderArray(array,byteSize);
    for (int i = 0; i < N; i++) {
     printf("El valor en la posicion %d es : %" PRId8 "\n", i, array[i]);
    }
    return 0;
}

void swapper(int8_t *a, int8_t *b) {
    int8_t temp = *b;
    *b = *a;
    *a = temp;
}

void orderArray(int8_t * array, uint16_t byteSize) {
    uint16_t length = byteSize / sizeof(int8_t);
    for (int i = 0; i < floor(length/2); i++) {
        swapper(&array[i], &array[length - 1 - i]);
    }
}
