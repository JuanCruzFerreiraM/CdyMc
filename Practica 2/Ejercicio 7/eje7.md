# Planificación Cooperativa de Tareas y Modularización

## a

### Uso de un Temporizador para Generar el "Tick" del Sistema

El corazón de este esquema es una única interrupción periódica de Timer, conocida como RTI (Real Time Interrupt) o simplemente el "tick" del sistema. Un timer en el microcontrolador (como Timer0, Timer1 o Timer2 en el ATmega328p) cuenta pulsos de reloj. Configurando el timer en un modo adecuado (como CTC - Clear Timer on Compare Match - o Normal con desborde) y seleccionando una fuente de reloj y un prescalador, se puede hacer que el timer alcance un valor preestablecido periódicamente. Cuando esto ocurre, se activa un flag de estado de interrupción. Si las interrupciones están habilitadas, el microcontrolador ejecuta una Rutina de Servicio de Interrupción (RSI), que en este esquema es la rutina del planificador.

### El Planificador (Scheduler) en la RSI

La RSI del timer se ejecuta periódicamente, proporcionando la base de tiempo para planificar las tareas. Dentro de esta RSI, el planificador actualiza contadores o flags para determinar qué tareas deben ejecutarse en el "tick" actual o en ticks futuros. Por ejemplo, si una tarea debe ejecutarse cada 200 ms y el tick es de 1 ms, el planificador incrementará un contador en cada tick y activará un flag cuando llegue a 200.

### El Despachador (Dispatcher) en el Bucle Principal (Super-Loop)

El programa principal contiene un Super-Loop infinito que actúa como despachador. En cada iteración, verifica los flags activados por el planificador. Si un flag está activo, el despachador llama a la función correspondiente y luego borra el flag.

### Ejecución Cooperativa de Tareas

En este esquema, las tareas se ejecutan hasta completarse (Run to Completion) y no son interrumpidas por otras tareas. Solo la interrupción del timer está habilitada, asegurando precisión en la temporización. Las tareas deben ser no bloqueantes y rápidas. Si una tarea es larga, debe dividirse en etapas o modelarse como una Máquina de Estados Finitos (MEF) temporizada. Es crucial que el tiempo de ejecución de cualquier tarea sea menor que el intervalo del tick del sistema.

### Ventajas y Características Principales

- **Determinista y Predecible**: La ejecución de tareas está ligada al tick periódico, lo que asegura un comportamiento predecible.
- **Confiable**: Es más fácil verificar su correcto funcionamiento bajo diversas condiciones.
- **Simple**: Requiere poco código y es conceptualmente sencillo.
- **Sin Problemas de Recursos Compartidos**: Solo una tarea se ejecuta a la vez, eliminando la necesidad de mecanismos complejos.
- **Facilita el Diseño con MEF**: Las tareas largas pueden dividirse en múltiples ticks.
- **Ahorro de Energía**: Cuando no hay tareas listas, el microcontrolador puede entrar en modos de bajo consumo.
- **Cálculo de Tiempo de Respuesta**: Es más fácil calcular el tiempo de respuesta de las tareas.

En resumen, este esquema utiliza una interrupción periódica generada por un timer para activar un planificador que indica qué tareas deben ejecutarse en un bucle principal. Las tareas se ejecutan de forma cooperativa, asegurando un comportamiento determinista y confiable, ideal para sistemas embebidos de tiempo real.

## b

El máximo común divisor entre los tres periodos es 5, por lo tanto un tick de 5ms nos permite ejecutar de forma eficiente estos tres periodos, debemos tener cuidado de que las tareas tengan una duración menor a 5ms.

## d

Determinamos previamente que, para las tareas periódicas X (10ms), Y (25ms), y Z (50ms), el Máximo Común Divisor (GCD) de sus periodos es 5ms. Esto sugiere que un tick del sistema (periodo de la interrupción del Timer) de 5ms podría ser una base de tiempo adecuada. Con un tick de 5ms, las tareas se programarían para ejecutarse cada 2 ticks (X), 5 ticks (Y), y 10 ticks (Z).

El problema surge cuando, con un tick de 5ms, varias tareas están programadas para iniciarse en el mismo instante de tiempo (en el mismo "tick"). Por ejemplo, en el tick 0, las tres tareas (X, Y, Z) estarían programadas para iniciar su ejecución. Aunque en un esquema cooperativo la CPU ejecutaría una tarea tras otra en ese tick (el despachador verifica los flags en secuencia), la superposición de tareas programadas para el mismo tick puede evitarse.

Para evitar que múltiples tareas estén programadas para iniciarse en el mismo tick del sistema en este esquema Time-Triggered cooperativo (sEOS), se propone una técnica. La idea principal es subdividir el tick previamente calculado (los 5ms) en un número entero de intervalos de tiempo más pequeños, llamados "slots", obteniendo así un "nuevo tick" de menor duración. Luego, las tareas se planifican utilizando este nuevo tick más pequeño y se les asignan retardos iniciales (initial delays) diferentes para que comiencen en "slots" o ticks distintos.

Siguiendo un ejemplo similar (tareas con periodos 10ms, 30ms, 25ms, con GCD de 5ms), la solución consiste en:

1. Elegir un nuevo periodo para el tick del sistema (nuevo TTICK) que sea un divisor entero del GCD original (5ms) y lo suficientemente pequeño como para proporcionar suficientes "slots" o ticks para separar las tareas. Por ejemplo, un nuevo tick de 1ms (dividiendo los 5ms por 5).

2. Planificar las tareas basándose en el nuevo tick de 1ms:
    - Tarea X (periodo 10ms): se ejecutará cada 10ms / 1ms = 10 ticks.
    - Tarea Y (periodo 25ms): se ejecutará cada 25ms / 1ms = 25 ticks.
    - Tarea Z (periodo 50ms): se ejecutará cada 50ms / 1ms = 50 ticks.

3. Asignar retardos iniciales diferentes a cada tarea para que no todas intenten iniciar en el tick 0. Por ejemplo, usando el tick de 1ms:

- Tarea X: Inicia en el tick 0 (o slot 0).

      SCH_Add_Task(X, 0, 10);
      
- Tarea Y: Inicia en el tick 1 (o slot 1).

      SCH_Add_Task(Y, 1, 25);

- Tarea Z: Inicia en el tick 2 (o slot 2).

      SCH_Add_Task(Z, 2, 50);

De esta manera, con un tick de 1ms y retardos iniciales de 0, 1 y 2 ms, la tarea X iniciaría en los ticks 0, 10, 20, 30, 40, 50...; la tarea Y en los ticks 1, 26, 51...; y la tarea Z en los ticks 2, 52, 102... La superposición de tareas programadas para iniciar en el mismo tick se evita escalonando sus inicios.

El planificador (en la RSI del Timer, que ahora se ejecuta cada 1ms) se encargaría de llevar la cuenta para cada tarea y activar su flag (`Flag_X`, `Flag_Y`, `Flag_Z`) en el tick correspondiente, considerando el periodo y el retardo inicial. El despachador en el bucle principal seguiría verificando los flags y ejecutando la tarea cuyo flag esté activo.

Es fundamental recordar que, incluso con este nuevo tick más pequeño (1ms en este ejemplo), la condición `WCET_tarea < TTICK` (Peor Tiempo de Ejecución de cualquier tarea individual debe ser menor que el nuevo Tick Interval) sigue siendo necesaria para que el planificador cooperativo funcione correctamente. Además, la suma de los WCETs de las tareas que pueden coincidir en el mismo tick (iniciadas en ticks consecutivos pero ejecutándose en el mismo "intervalo" del viejo tick de 5ms) debe ser menor que ese intervalo.
