# RTC

## a

### Diferencias entre Timer0 y Timer2 en Microcontroladores AVR

1. **Capacidad de Reloj de Tiempo Real (RTC):**
    - El **Timer2** puede funcionar como un Reloj de Tiempo Real (RTC) al sincronizarse de forma asíncrona con un cristal externo de 32.768 kHz conectado a los pines **TOSC1** y **TOSC2** (PB6 y PB7). Esta funcionalidad no está disponible para el **Timer0**.

2. **Fuentes de Reloj Asíncronas:**
    - El **Timer2** puede operar en modo asíncrono utilizando el cristal de 32.768 kHz en **TOSC1/TOSC2**.
    - Los **Timer0** y **Timer1** generalmente utilizan el cristal principal de 16 MHz o el oscilador RC interno como fuente de reloj.

3. **Conteo de Eventos Externos:**
    - Los temporizadores pueden usarse como contadores de eventos externos alimentando pulsos a través de un pin.
    - El prescalador del **Timer0** (y **Timer1**) permite configurar las entradas **T0** y **T1** para el conteo de pulsos externos en el ATmega328p. En el ATmega32/ATmega16, **T0** es una función alternativa del pin **PB0** y **T1** del pin **PB1**.
    - Aunque el **Timer2** también puede contar eventos, se destaca la capacidad del **Timer0** (y **Timer1**) de usar pines dedicados para esta función.

4. **Registros de Control (TCCRn):**
    - Los registros de control (**TCCRn**, como **TCCR0** y **TCCR2**) son diferentes para cada temporizador.
    - Los valores de los bits **CS** (Clock Selector) pueden tener significados distintos para seleccionar el prescalador o la fuente de reloj entre **Timer0** y **Timer2** en el ATmega32. Esto implica que la configuración específica para modos de operación y prescaladores varía entre estos temporizadores.

5. **Pines de Salida Asociados (OCn):**
    - Cada temporizador tiene pines de salida de comparación (**OCn**) asociados para la generación de formas de onda.
    - En el ATmega328p:
      - **Timer0**: **OC0A (PD5)** y **OC0B (PD4)**.
      - **Timer2**: **OC2 (PD7)**.

6. **Tamaño del Contador:**
    - Tanto el **Timer0** como el **Timer2** son temporizadores de 8 bits, lo que significa que el registro **TCNTn** (como **TCNT0** y **TCNT2**) tiene un tamaño de 8 bits.

Aunque **Timer0** y **Timer2** comparten características básicas como ser temporizadores de 8 bits y tener registros de control, conteo y comparación, las diferencias clave en el ATmega328p incluyen:

- La capacidad única del **Timer2** para funcionar como RTC con un cristal externo de baja frecuencia.
- Variaciones en los pines asociados y la configuración del prescalador y la fuente de reloj a través de sus respectivos registros de control.
- La capacidad destacada del **Timer0** (y **Timer1**) para el conteo de eventos externos mediante pines dedicados.

## c

Funcionalidad de un chip RTC externo (basado en la descripción del DS1307):
1.
Provee Hora y Fecha precisas: Un chip RTC como el DS1307 proporciona información precisa de segundos, minutos, horas, día, fecha, mes y año.
2.
Ajuste Automático: Ajusta automáticamente la fecha de fin de mes, incluyendo correcciones para años bisiestos.
3.
Formato de Hora: Puede operar en formato de 24 horas o de 12 horas con indicador AM/PM.
4.
Batería de Respaldo: Muchos chips RTC utilizan una batería interna (como una de litio de 3V conectada al pin Vbat en el DS1307) para mantener la hora y la fecha incluso cuando la alimentación principal está desconectada. El DS1307 tiene un circuito de detección de energía incorporado que cambia automáticamente a la fuente de batería ante fallos de alimentación.
5.
Memoria RAM: El DS1307 tiene un total de 64 bytes de espacio RAM. Los primeros siete bytes (direcciones 00 a 06) están reservados para los valores de tiempo y fecha. El byte en la dirección 07H se usa para el registro de control. Esto deja 56 bytes (de 07H a 3FH) disponibles para almacenamiento de datos de propósito general. Las fuentes indican que los contenidos de la RAM en el DS1307 no son volátiles.
6.
Pin de Salida (SQW/OUT): El pin 7 (SQW/OUT) en el DS1307 es un pin de salida que puede proporcionar frecuencias de 1 kHz, 4 kHz, 8 kHz o 32 kHz si está habilitado. Este pin requiere una resistencia pull-up externa.
Conexión a un MCU (basado en el DS1307):
1.
Interfaz Serial (I2C/TWI): El DS1307 es un RTC serial que utiliza el bus I2C. El I2C es un bus de interfaz que utiliza solo 2 pines para la transferencia de datos.
2.
Pines SCL y SDA: Estos dos pines son SCL (Serial Clock), que sincroniza la transferencia de datos entre chips, y SDA (Serial Data). En las hojas de datos de AVR, el I2C a menudo se denomina Two-Wire Serial Interface (TWI).
3.
Conexión AVR-DS1307: El DS1307 se conecta al AVR (ATmega32 en los diagramas) a través de los pines SCL y SDA. Se necesita un cristal externo de 32.768 kHz conectado a los pines X1 y X2 del DS1307 para proporcionar la fuente de reloj al chip.
Ventajas de su uso (derivadas de las características del DS1307 y el bus I2C/TWI):
1.
Precisión del Tiempo: Permiten tener una fuente de tiempo y fecha precisa, lo cual es crucial para muchas aplicaciones. La precisión del reloj en el DS1307 depende de la calidad del cristal oscilador.
2.
Retención de Datos: La capacidad de mantener la hora y la fecha (y el contenido de la RAM no volátil) incluso cuando la alimentación principal está apagada, gracias a la batería de respaldo, es una gran ventaja.
3.
Libera al MCU: Al ser un chip dedicado, el MCU no necesita gastar recursos (ciclos de CPU, temporizadores internos) en llevar la cuenta del tiempo de manera continua, especialmente durante cortes de energía.
4.
Bajo Conteo de Pines: El uso de un bus serial como I2C/TWI, que solo requiere 2 pines (SDA y SCL), reduce drásticamente el tamaño del encapsulado y el consumo de energía en comparación con buses paralelos. Esto libera otros pines del MCU para diferentes usos de E/S.
5.
Facilidad de Interfaz: El I2C/TWI es un estándar ampliamente adoptado, lo que facilita la interfaz con el MCU.
