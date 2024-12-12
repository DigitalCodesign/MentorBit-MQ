
# MentorBit-SensoresMQ
Esta librería está construida por Digital Codesign para utilizar los módulos de sensores MQ (2, 3, 4, 5, 6, 7, 8 y 9), principalmente diseñada para el kit educacional "MentorBit".

Puedes encontrar nuestro MentorBit y mucho más material de electrónica y robótica en nuestra tienda oficial:  [https://digitalcodesign.com/shop](https://digitalcodesign.com/shop)

# Modo de empleo

Una vez tengamos la librería instalada desde el Arduino IDE, tenemos que incluir la librería con la siguiente línea:

```
#include <MentorBitSensoresMQ.h>
```

### Constructor

Una vez incluida la librería, usamos el constructor para crear el objeto del sensor MQ deseado, y definir el pin al que está conectado el sensor y el gas que deseamos detectar. El gas es identificado por un número, que varía dependiendo del modelo de sensor y gas a detectar.

```
MentorBitMQ2 sensorMQ2(PIN_SENSOR, GAS_DETECCION);
```

Donde `PIN_SENSOR` es el pin al que está conectado el sensor y `GAS_DETECCION` es el tipo de gas que se desea detectar (un número que se elige de acuerdo a los gases que puede detectar el sensor).

### Uso

Con el objeto `sensorMQ2` definido, podemos obtener la lectura del sensor utilizando la función `obtenerLecturaMQ()`, que devuelve el valor analógico leído del gas en el sensor MQ:

```
float lectura = sensorMQ2.obtenerLecturaMQ();
```

El valor devuelto es un número que representa la concentración del gas en partes por millón (ppm).

### Calibración del Sensor

Es importante calibrar el sensor antes de obtener lecturas precisas. Utilizamos la función `calibrar()` para calibrar el sensor:

```
sensorMQ2.calibrar();
```

### Cambiar el tipo de gas a detectar

Si deseas cambiar el gas que el sensor está detectando, puedes usar la función `cambiarDeteccionGas()` y pasarle el número correspondiente al gas que deseas medir:

```
sensorMQ2.cambiarDeteccionGas(NUEVO_GAS_DETECCION);
```

### Atributos

- `PIN_SENSOR`: Define el pin donde se conecta el sensor.
- `GAS_DETECCION`: Especifica el gas que el sensor debe detectar, con valores correspondientes a gases como metano, CO2, monóxido de carbono, entre otros.
