/*Duda: consultar si es correcto el uso de sleep o se prentedia usar otra funcion*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>

#define LENGTH 8

void printSerial(uint8_t);

int main (void) {
    uint8_t n = 4;
    printSerial(n);
    return 0;
}


void printSerial(uint8_t n) {
    uint8_t mascara = 0x01;
    for (int i = 0; i < LENGTH; i++) {
        uint8_t printValue = n & mascara;
        printf("%"PRIu8,printValue);
        fflush(stdout);
        n = n >> 1;
        sleep(1);    
    }
}