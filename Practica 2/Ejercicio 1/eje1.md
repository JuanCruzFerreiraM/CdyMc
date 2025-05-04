# Teclado LCD

## a

### Pines

- VCC y VSS: puertos de alimentación, 5V en Vcc, Vss a tierra.
- Vee: Tension de contraste, valor entre 0 y 5V.
- D0 a D7: Pines de datos, 8 bits.
- R/W: (R/W) = 0 modo write, (R/W) = 1 modo read.
- E: enable, activa el LCD con un flanco de bajada.
- RS: register select, 1 si usamos datos, 0 si usamos comandos.

### Componentes

- DDRAM: Data display, aca se guardan los datos que quieren ser puestos en el display, cada posición de la memoria DDRAM se corresponde
  con una posición del display. (0x80 a 0xFF).

- GCRAM: character generator, en esta se nos permite generar caracteres especiales utilizando los puntos del display. (0x40 0x7F)

- Cursor: es un registro que indica la position del cursor en la DDRAM.

- Registro de datos y registro de comandos, los mencionados antes en el RS.

### Comandos

- 0x01: Limpia el display.
- 0x02: Retorna a home (0x80 en DDRAM)
- 0x10: Mueve el cursor un lugar a la izquierda.
- 0x14: Mueve el cursor un lugar a la derecha.
- 0x18: Mueve el display a la izquierda ?
- 0x1C: Mueve el display a la derecha ?
- 0x80-0xFF: Mueve el cursor a la posición H (0xH con H en el rango [0x80 - 0xFF]) en DDRAM
- 0x40-0x7F: Mueve el cursor a la posición H (0xH con H en el rango [0x40 - 0x7F]) en GCRAM
- 0x08: apaga el cursor y el display.
- 0x0A: apaga el display, prende el cursor.
- 0x0C: prende el display, apaga el cursor.
- 0x0E: prende display y cursor.
- 0x0F: prende display y cursor en modo parpadeo.
- 0x38: Inicia 2 lineas y fuente 5x7.

### Modo 4 bits

El LCD se puede usar en modo 4 bits, enviando primero un nibble y luego otro, permitiendo asi usar menos puertos del MCU, implica dos accesos de escritura. Tiene una secuencia de inicio especifica 3,3,3,2 y 28. Poniendo modo 4 bits y matriz 5x7. Se utilizan los puertos D4-D7 del LCD.

## d

Funciones de la biblioteca lcd.h

### LCDsendChar

Permite enviar un carácter (8 bits) al LCD, chequea primero en que modo estamos, luego envía los nibbles haciendo uso de la función LCD_DATAWR. Se encarga sola de dar los comandos a RS, RW y E.

### LCDsendCommand

Igual al caso anterior pero seteando el LCD para mandar comandos y no datos.

### LCDinit

Realiza la secuencia de inicio del LCD, tanto para el modo 4 bits como para el 8 bits, chequeando si esta definida la macro LCD_4bit,
que por defecto viene iniciada.

### LCDclr

Envía el comando para limpiar el display.

### LCDhome

Envía el comando para llevar el cursor a home.

### LCDstring

Hace uso de la función LCDsendChar para enviar una cadena de caracteres. (Podría devolver un código de error, para saber si el puntero enviado no es valido, en principio esta configurada para solo retornar).

### LCDGotoXY

Permite enviar el cursor a un cierto punto x,y en la memoria DDRAM.
Internamente mapea y con una linea del LCD y x es agregado al valor inicial de memoria de dicha linea.

### CopyStringtoLCD

Esta función no la entendí muy bien, pero creo que permite copiar un valor almacenado en la flash a el LCD.

### LCDdefineChar

Nos permite definir un carácter en la CGRAM

### LCDshiftLeft

Mueve los caracteres n valores a la derecha ?

### LCDshiftRight

Mueve los caracteres N posiciones a la izquierda ?

### LCDcursorOn

Enciende el cursor

### LCDcursorOnBlink

Pone el cursor en modo parpadeo

### LCDcursorOff

Apaga el cursor

### LCDblank

Apaga el LCD.

### LCDvisible

Enciende el LCD

### LCDcursorLeft

Mueve el cursor n posiciones a la izquierda

### LCDcursorRight

Mueve el cursor n posiciones a la derecha

### LCDdescribeDato

Permite escribir un valor entero en el LCD. Recibe el valor y una longitud de campo, lugares que se necesitan para escribirlo.

### LCDprogressBar

Permite usar una barra de progreso.
