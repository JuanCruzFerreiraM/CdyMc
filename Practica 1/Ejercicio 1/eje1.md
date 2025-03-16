# Ejercicio 1

## a

- *Static* :  Una variable local declarada como static posee una dirección fija de memoria RAM
que se conserva durante toda la ejecución del programa. De esta manera su valor se
mantiene entre las sucesivas llamadas a la función.
Una variable global declarada como static se convierte en una variable “privada” y su
alcance se limita solo al archivo .c donde está definida.
Una función declarada como static se convierte en una función “privada” y su
alcance se limita solo al archivo .c donde está definida.

- *Volatile* : Una variable local declarada como static posee una dirección fija de memoria RAM
que se conserva durante toda la ejecución del programa. De esta manera su valor se
mantiene entre las sucesivas llamadas a la función.
Una variable global declarada como static se convierte en una variable “privada” y su
alcance se limita solo al archivo .c donde está definida.
Una función declarada como static se convierte en una función “privada” y su
alcance se limita solo al archivo .c donde está definida.

- *Register* : Sugiere al compilador que la variable local sea colocada en algún registro CPU para
optimizar su tiempo de acceso.

- *Const* : Indica al compilador que la variable es READ_ONLY y por lo tanto no puede
modificarse en otra parte del programa (evita errores de escritura indeseados).
El compilador puede almacenar este tipo de variables en ROM, optimizando el uso de la memoria RAM (uso de PROGMEM).

---
Los tipos de datos en C son los siguientes:

![tipos de datos en C](public/image.png)

Podemos utilizar las declaraciones de tipos de <stdint.h> para mejorar su compatibilidad

![alt text](public/image-1.png)
