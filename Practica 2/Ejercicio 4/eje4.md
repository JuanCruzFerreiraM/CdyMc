# Temporizadores

## El Timer0 en Microcontroladores AVR

El **Timer0** es uno de los temporizadores/contadores disponibles en los microcontroladores AVR como el ATmega328p. En el ATmega32, hay tres temporizadores: **Timer0**, **Timer1** y **Timer2**. El Timer0 es un temporizador de 8 bits que puede ser utilizado para generar retardos de tiempo o como contador para eventos externos.

### Módulos y Registros del Timer0

1. **Registro TCNT0 (Timer/Counter Register):**
    - Registro central de conteo de 8 bits.
    - Se incrementa con cada pulso de reloj.
    - Puede ser leído o cargado con un valor inicial.
    - En modo Normal, cuenta hasta 0xFF y luego "desborda" (rollover) a 0x00.

2. **Registro TCCR0 (Timer/Counter Control Register):**
    - Registro de control de 8 bits para configurar el Timer0.
    - Bits **CS02:CS00** seleccionan la fuente de reloj (Prescaler).
    - Bits **WGM01:00** seleccionan el modo de operación (Normal, CTC, PWM).
    - Bits **COM01:00** configuran el modo de salida del comparador.

3. **Registro OCR0 (Output Compare Register):**
    - Contiene un valor que se compara continuamente con el registro TCNT0.
    - Al coincidir, activa la bandera **OCF0**.
    - Usado en modos CTC y PWM.

4. **Generador de Forma de Onda (Waveform Generator):**
    - Modifica el estado del pin de salida (OC0) en coincidencias de comparación.
    - En ATmega328p, los pines asociados son **PD5 (OC0A)** y **PD4 (OC0B)**.
    - Configuración controlada por los bits **COM01:00** en TCCR0.

5. **Prescaler:**
    - Divide la señal de reloj principal para proporcionar una señal más lenta al contador.
    - Configurado mediante los bits **CS02:CS00** en TCCR0.
    - Permite operar como temporizador (oscilador interno) o contador (fuente externa).

6. **Banderas de Interrupción (Interrupt Flags):**
    - **TOV0**: Se activa al desbordar TCNT0 de 0xFF a 0x00.
    - **OCF0x**: Se activa al coincidir TCNT0 con OCR0x.
    - Ubicadas en el registro **TIFR** y monitoreadas por polling o interrupciones.

7. **Bits de Habilitación de Interrupción (Interrupt Enable Bits):**
    - Ubicados en el registro **TIMSK**.
    - **TOIE0**: Habilita interrupción por desbordamiento.
    - **OCIE0A/OCIE0B**: Habilitan interrupción por coincidencia de comparación.

### Modos de Operación del Timer0

1. **Modo Normal (WGM01:00 = 00):**
    - TCNT0 cuenta de 0x00 a 0xFF y desborda a 0x00.
    - Bandera **TOV0** se activa al desbordar.
    - Usado para generar retardos de tiempo.

2. **Modo CTC (Clear Timer on Compare Match) (WGM01:00 = 10):**
    - TCNT0 se reinicia a 0x00 al coincidir con OCR0.
    - Bandera **OCF0** se activa en coincidencias.
    - Útil para generar interrupciones o señales periódicas.

3. **Modos PWM (Pulse Width Modulation):**
    - **Fast PWM (WGM01:00 = 11)** y **Phase Correct PWM (WGM01:00 = 01)**.
    - Generan señales con ancho de pulso variable.
    - Usados para controlar motores DC o el brillo de LEDs.

### Resumen

El Timer0 es un recurso versátil que, mediante sus registros de control (**TCCR0**), conteo (**TCNT0**) y comparación (**OCR0**), junto con el generador de onda y el prescaler, permite operar en modos como:

- **Normal**: Para retardos simples.
- **CTC**: Para eventos periódicos precisos.
- **PWM**: Para señales de ancho de pulso variable.

Sus capacidades de interrupción, habilitadas vía **TIMSK** y señalizadas en **TIFR**, permiten operar en segundo plano sin intervención constante de la CPU.

## b

### Funcionamiento del Prescaler (Prescaler)

El prescalador es un circuito divisor de frecuencia cuya función principal es reducir la velocidad de la señal de reloj que llega al registro contador del Timer (**TCNTn**). Esto permite que el Timer pueda medir o generar retardos de tiempo o contar eventos que duran más que un solo ciclo del reloj principal del microcontrolador.

El prescalador toma la señal de reloj principal, que puede ser la frecuencia del oscilador interno del microcontrolador (**CLKio** o **Fosc**) o una señal de reloj externa proporcionada a través de un pin dedicado (**T0** para Timer0, **T1** para Timer1). La división de frecuencia se realiza por un factor **N**, donde **N** es un valor específico que puede ser seleccionado. Los posibles valores de **N** están definidos por los bits de selección de reloj (**CSn2:CSn0**) en el registro de control del Timer (**TCCRn**, como **TCCR0** para Timer0).

Para el Timer0, las opciones de división de frecuencia (valores de **N**) son:

- 1 (sin prescaler)
- 8
- 64
- 256
- 1024 (cuando se usa el reloj interno).

También se puede seleccionar una fuente de reloj externa en el pin **T0**, con conteo en el flanco de bajada o de subida.

### Frecuencia de Reloj del Contador (**f_clkTn**)

La frecuencia con la que el registro contador (**TCNTn**) se incrementa (o decrementa en algunos modos) se llama la frecuencia de reloj del Timer o del contador (**f_clkTn**). Esta frecuencia es el resultado de dividir la fuente de reloj principal (generalmente la frecuencia del oscilador **Fosc** o **fclkIO**) por el factor de prescalado **N**.

La expresión para calcular la frecuencia de reloj del contador es:

```latex
f_clkTn = Fosc / N
```

Donde:

- **Fosc** es la frecuencia del oscilador principal del microcontrolador (por ejemplo, 8 MHz, 1 MHz, 10 MHz, 16 MHz).
- **N** es el factor de división seleccionado por los bits **CSn2:CSn0** en el registro **TCCRn**.

**Ejemplo:**
Si **Fosc = 8 MHz** y el prescalador es **64 (N=64)**:

- La frecuencia de reloj del Timer0 sería:  
    `f_clkTn = 8 MHz / 64 = 125 kHz`.  
- La resolución de temporización sería el período de esta frecuencia:  
    `T = 1 / 125 kHz = 8 µs`.

### Frecuencia de Desborde (**f_OVF**)

La frecuencia de desborde (**f_OVF**) se refiere a la velocidad con la que el registro contador (**TCNTn**) alcanza su valor máximo (**TOP**) y luego se reinicia a cero (o a **BOTTOM**). Para un contador de 8 bits como Timer0 (en modo Normal), el valor máximo es **0xFF (255)** y el valor inicial es **0x00**. El contador pasa por **256 estados** (de 0 a 255) antes de desbordar.

La frecuencia de desborde se calcula dividiendo la frecuencia de reloj del contador (**f_clkTn**) por el número total de estados que cuenta antes de desbordar o reiniciarse. En modo Normal, este número de estados es **(TOP + 1)**. Para un contador de 8 bits como Timer0 en modo Normal, **TOP = 255**, por lo tanto, el número de estados es **256**.

La expresión para calcular la frecuencia de desborde en modo Normal para un Timer de 8 bits es:

```latex
f_OVF = f_clkTn / 256
```

Sustituyendo la fórmula de **f_clkTn**, obtenemos:

```latex
f_OVF = (Fosc / N) / 256 = Fosc / (N * 256)
```

**Ejemplo:**
Si **Fosc = 8 MHz** y **N = 64**:

- `f_clkTn = 125 kHz`.  
- La frecuencia de desborde sería:  
    `f_OVF = 125 kHz / 256 ≈ 488.28 Hz`.  
- El período de desborde sería:  
    `T_OVF = 1 / 488.28 Hz ≈ 2.048 ms`.

Si **N = 1024**:

- `f_clkTn = 8 MHz / 1024 = 7812.5 Hz`.  
- La frecuencia de desborde sería:  
    `f_OVF = 7812.5 Hz / 256 ≈ 30.517 Hz`.  
- El período de desborde sería:  
    `T_OVF = 1 / 30.517 Hz ≈ 32.768 ms`.

En modo **CTC**, la frecuencia del evento de comparación (**OCF**) se basa en el valor de **OCR0**, y el contador se reinicia a 0 en cada coincidencia. La frecuencia de "desborde" o reinicio del contador en **CTC**, basada en **OCR0**, es:

```latex
f_OCnx = f_clkTn / (OCRn + 1)
```

### Borrado de la Bandera de Desborde (**TOVn**)

La bandera de desborde (**TOVn**, por ejemplo **TOV0** para Timer0) se encuentra en el registro **TIFRn** (Timer/Counter Interrupt Flag Register). Esta bandera se activa (se pone a '1') cuando el contador (**TCNTn**) pasa de su valor máximo (**0xFF** para 8 bits en modo Normal) a **0x00**.

Existen dos mecanismos principales para borrar esta bandera:

1. **Automáticamente por la Rutina de Servicio de Interrupción (RSI):**
     - Si la interrupción por desbordamiento está habilitada (mediante el bit **TOIEn** en el registro **TIMSKn**) y ocurre un desbordamiento, la CPU salta a la RSI asociada a ese vector de interrupción. La bandera **TOVn** se borra automáticamente al entrar a la RSI.

2. **Manualmente por Software (en modo Polling):**
     - Si no se utilizan interrupciones y el programador monitorea la bandera **TOVn** mediante polling (leyendo el registro **TIFRn**), debe borrar la bandera manualmente después de detectarla. Para borrar la bandera **TOVn**, se debe escribir un logic '1' en el bit correspondiente del registro **TIFRn**. Este mecanismo de escribir un '1' para borrar la bandera es común en los periféricos AVR.

> **Nota:** El registro **TIFR** en ATmega32 puede tener un nombre ligeramente diferente o ser parte de **TIFR0** en otros modelos como ATmega328p, pero el principio de escribir '1' para borrar el bit correspondiente es el mismo.
