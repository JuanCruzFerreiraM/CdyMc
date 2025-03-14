#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <stdlib.h>

#define N 4

void swap(int8_t*, int8_t*);
void reverseArray(int8_t*, uint16_t); // Dado que 2^16 ~= 65.000, con el tipo de datos usado podemos tener un vector de hasta ~65 mil valores

int main(void) {
    int8_t array[N];
    int16_t byteSize = sizeof(int8_t) * N;
    for (int i = 0; i < N; i++) {
        array[i] = rand() % 256;
        printf("El valor en la posición %d es: %" PRId8 "\n", i, array[i]);
    }
    reverseArray(array, byteSize);
    for (int i = 0; i < N; i++) {
        printf("El valor en la posición %d es: %" PRId8 "\n", i, array[i]);
    }
    return 0;
}

/**
 * Intercambia los valores de dos variables de tipo int8_t.
 *
 * @param a Puntero al primer valor.
 * @param b Puntero al segundo valor.
 */
void swap(int8_t *a, int8_t *b) {
    int8_t temp = *b;
    *b = *a;
    *a = temp;
}

/**
 * Invierte el orden de los elementos en un arreglo de int8_t.
 *
 * @param array Puntero al arreglo de int8_t.
 * @param byteSize Tamaño en bytes del arreglo.
 */
void reverseArray(int8_t *array, uint16_t byteSize) {
    uint16_t length = byteSize / sizeof(int8_t);
    for (int i = 0; i < floor(length / 2); i++) {
        swap(&array[i], &array[length - 1 - i]);
    }
}
