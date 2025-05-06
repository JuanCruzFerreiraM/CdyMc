# Interrupciones

## a

1. La cpu termina de ejecutar la instrucción actual.
2. Se almacena en la pila el contador de programa.
3. Se pone el cero el bit `I` del registro ``SREG`` para inhabilitar las interrupciones.
4. Se busca la RSI en la tabla de vectores de Interrupción. Y se salta a ejecutar la misma.
5. Se ejecuta la RSI, primero se guarda el contexto de la CPU (estado actual de los flags y los registros). En caso de que no se haga automáticamente se debe borrar el flag de pedido de interrupción del disp. para permitirle que pueda interrumpir.
6. Se ejecuta la instruccion RETI, que sirve para salir de la RSI, se restaura el estado de la CPU, el PC y se reactiva el flag ``I`` del ``SREG``.

## b

El flag `I` del registro `SREG` permite habilitar las interrupciones. El valor por defecto luego de un reset es cero. Para habilitar y deshabilitar las interrupciones se usan las instrucciones

```asm
SEI ;habilita Set Interrupt Enable
CEI ;deshabilita Clear Interrupt Enable
```

O las macros en C:

```c
sei();
cli();
```

## c

Un reset es un evento que permite iniciar el sistema en un estado conocido por defecto. Es una señal que puede interpretarse como una interrupción, pero esta a diferencia de las otras no puede enmascararse. En el ATmega328p hay cuatro fuentes de reset:

- Power On: genera un reset al encender el sistema.
- External reset: se realiza a través de un pin dedicado, el 9, y es activo en bajo. Al poner un nivel bajo en el pin, se genera un reset.
- Watchdog: Temporizador interno que funciona como contador,si no es reiniciado mediante wrd, llega al valor de timeout y manda un pulso reset, sirve para evitar bucles infinitos no deseados y otro tipo de errores.
- Brown-out Reset: genera un reset cundo la tension de alimentación cae por debajo de los niveles seguros. Se configura mediante bits de fusible.

MCU status register o SREG es un registro de 8 bits que indica las condiciones luego de la ejecución de una instrucción.

- **C (Carry flag):** Bandera de arrastre. Se activa cuando hay un arrastre (carry) saliendo del bit D7 después de una operación de suma o resta de 8 bits.
- **Z (Zero flag):** Bandera de cero. Refleja el resultado de una operación. Si el resultado es cero, Z se activa (Z=1); si el resultado no es cero, Z se desactiva (Z=0).
- **N (Negative flag):** Bandera de negativo. Indica si el resultado es negativo.
- **V (Overflow flag):** Bandera de desbordamiento. Indica si ha ocurrido un desbordamiento en complemento a 2.
- **S (Sign flag):** Bandera de signo. Este bit se deriva de otras banderas y se utiliza para indicar el signo del resultado, especialmente en operaciones con números con signo.
- **H (Half carry):** Semi-arrastre. Indica un arrastre entre el bit D3 y D4. Es útil en operaciones BCD (Decimal Codificado en Binario).
- **T (Bit copy storage):** Almacenamiento temporal de bit. Utilizado para almacenar un bit individual copiado desde un registro antes de ser manipulado.
- **I (Global Interrupt Enable):** Habilitación global de interrupciones. Este bit es responsable de habilitar o deshabilitar globalmente todas las interrupciones en el microcontrolador.

## d

La latencia de una interrupción es el tiempo que pasa desde que la esta fue detectada hasta que la CPU comienza a ejecutar su instrucción. El tiempo usual es de 4 ciclos de reloj, pero puede variar dependiendo de varios factores, como por ejemplo si la instrucción que se esta ejecutando en este momento dura mas de un ciclo de reloj como por ejemplo ``mul``.
RETI también demora 4 ciclos de reloj.

## e

Las interrupciones anidadas, se dan cuando una ISR es interrumpida por otra interrupción. Por defecto esto se encuentra deshabilitado ya que al entrar en una interrupción, el bit I del SREG se pone en cero, pero puede habilitarse desde la ISR, se anidaran solo si se recibe una interrupción de mayor prioridad que la actual. Esta metodología no es recomendable.

## f

Las interrupciones externas son generadas por dispositivos conectados a pines específicos del MCU, en el caso del ATmega328p INT0 (PD2) e INT1 (PD3). Cada una de estas tiene su dirección respectiva en el vector de interrupciones.
Para habilitarlas debemos configurar el bit especifico del EIMSK. Encontramos dos modos principales:

- Por flanco: Se activo por flanco de bajada o de subida, el cual queda registrado en un latch.
- Por nivel: Se activa cuando la entrada se encuentra en un nivel especifico, suele ser bajo.

Ambos se configuran mediante el registro EICRA.

La diferencia principal recae en que la activation por flanco se guarda en un latch, permitiendo asi que se interrumpa cuando las interrupciones estén habilitadas. En cambio por nivel, el nivel debe ser bajo (en caso de que ese sea el estado para interrumpir) cuando están habilitadas las interrupciones, en caso contrario no queda registrada dicha solicitud. En modo flanco ademas el bit se borra de forma automática. En modo por nivel, si el nivel se mantiene al ejecutar RETI, se volverá a ejecutar la ISR.

## g


### Terminales I/O que pueden generar interrupciones por cambio de estado

- Las interrupciones por cambio de pin están asociadas con los terminales (pines) de Entrada/Salida de los puertos del microcontrolador.
- En el diagrama de un ATmega328p de 28 pines, se muestran varios pines designados con etiquetas `PCINTx`. Esto incluye:
  - Pines de `PORTB` (ej. `PB6 PCINT6`, `PB7 PCINT7`).
  - Pines de `PORTC` (ej. `PC6 PCINT14/RESET`).
  - Pines de `PORTD` (ej. `PD0 PCINT16`, `PD1 PCINT17`, `PD2 PCINT18`, `PD3 PCINT19`, `PD4 PCINT20`, `PD5 PCINT21`, `PD6 PCINT22`, `PD7 PCINT23`).
- A diferencia de las interrupciones externas dedicadas `INT0`, `INT1`, `INT2` que están en pines específicos (`PD2`, `PD3`, `PB2` respectivamente en el ATmega32/328p), los `PCINTs` pueden ocurrir en muchos pines de E/S.

#### Configuración de estas interrupciones en los puertos de Entrada/Salida

Para que una interrupción por cambio de pin sea atendida, se requieren varios pasos de configuración:

1. **Habilitación Global**:  
     La máscara global de interrupciones (bit `I` del registro `SREG`) debe estar en `1`. Esto se logra con la instrucción `SEI` en Assembly o la macro `sei()` en C. Si `I=0`, la CPU no aceptará ninguna interrupción, aunque la solicitud quede pendiente.

2. **Habilitación del Grupo de Pin Change**:  
     Los pines de `PCINT` están organizados en grupos (ej. `PCINT0-7`, `PCINT8-15`, `PCINT16-23`) asociados a diferentes puertos. Para habilitar las interrupciones por cambio de pin para un grupo, se debe configurar el bit correspondiente en el registro `PCICRx` (donde `x` denota el grupo o puerto, como `PCICR` para `PORTD`).

3. **Habilitación del Pin Específico**:  
     Dentro de un grupo habilitado por `PCICRx`, se debe especificar qué pines específicos dentro de ese grupo pueden generar una interrupción. Esto se hace configurando los bits correspondientes en los registros `PCMSKx`.

4. **Tipo de Activación**:  
     Una característica distintiva de las interrupciones por cambio de pin es que siempre se activan con cualquier flanco (rising o falling edge) de la señal de entrada en el terminal. No se configuran por nivel como una opción por defecto, a diferencia de `INT0/INT1`.

5. **Configuración de los Pines de E/S**:  
     Los pines de E/S configurados para `PCINTx` deben estar configurados como entrada (limpiando el bit correspondiente en el registro `DDRx`).

#### Vectores de interrupción asociados y sus prioridades relativas

- Cada grupo de interrupciones por cambio de pin tiene asociado un Vector de Interrupción específico en la Tabla de Vectores de Interrupción.
- En el contexto del ATmega328p, los vectores de interrupción asociados son:
  - `PCINT0_vect`, con número de vector 3.
  - `PCINT1_vect`, con número de vector 4.
  -`PCINT2_vect`, con número de vector 5.
- La prioridad de las interrupciones en los AVR está determinada por el orden en que aparecen los vectores en la Tabla de Vectores de Interrupción:
  - `INT0_vect` (vector 1) y `INT1_vect` (vector 2) tienen mayor prioridad que `PCINT0_vect` (vector 3), `PCINT1_vect` (vector 4) y `PCINT2_vect` (vector 5).
  - `PCINT2_vect` (vector 5) tiene el mismo número de vector que `INT2_vect` (vector 5), lo que implica que tendrían la misma prioridad o una regla de desempate no especificada.
  - Los vectores de `PCINT` (3, 4, 5) tienen mayor prioridad que los vectores de la mayoría de los Timers (ej. `TIMER0_OVF_vect` es vector 16), SPI (vector 17), USART (vectores 18, 19, 20), ADC (vector 21), etc.

En resumen, las interrupciones por cambio de pin permiten que cualquier cambio de estado en muchos pines de E/S configurados como entrada genere una interrupción. Requieren la habilitación global, la habilitación del grupo `PCINT` y la habilitación del pin específico. Siempre se activan por flanco ("any change"). Tienen vectores dedicados en la tabla de interrupciones, con prioridades relativas menores que `INT0/INT1` pero generalmente mayores que muchas otras fuentes de interrupción según el orden de la tabla en el ATmega328p. La solicitud de interrupción queda registrada en un flag y se borra automáticamente al atender la RSI (o escribiendo un `1` en el flag correspondiente).

