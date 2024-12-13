# MentorBit-SensoresMQ
Esta librería está construida por Digital Codesign para utilizar los módulos de sensores MQ, principalmente diseñados para el kit educacional "MentorBit".

Puedes encontrar nuestro MentorBit y mucho más material de electrónica y robótica en nuestra tienda oficial: [https://digitalcodesign.com/shop](https://digitalcodesign.com/shop)

# Modo de empleo

Una vez tengamos la librería instalada desde el Arduino IDE, tenemos que incluir la librería con la siguiente línea:

```cpp
#include <MentorBitMQ.h>
```

### Constructor

Una vez incluida la librería, usamos el constructor para crear el objeto de cada sensor MQ y definimos el pin al que está conectado el sensor y el tipo de gas a detectar:

```cpp
MentorBitMQ3 sensorMQ3(PIN_SENSOR, TIPO_GAS);
MentorBitMQ4 sensorMQ4(PIN_SENSOR, TIPO_GAS);
MentorBitMQ5 sensorMQ5(PIN_SENSOR, TIPO_GAS);
MentorBitMQ6 sensorMQ6(PIN_SENSOR, TIPO_GAS);
MentorBitMQ7 sensorMQ7(PIN_SENSOR, TIPO_GAS);
MentorBitMQ8 sensorMQ8(PIN_SENSOR, TIPO_GAS);
MentorBitMQ9 sensorMQ9(PIN_SENSOR, TIPO_GAS);
MentorBitMQ135 sensorMQ135(PIN_SENSOR, TIPO_GAS);
```

Siendo `PIN_SENSOR` el pin al que está conectado el sensor y `TIPO_GAS` el gas que se desea medir (0-4, dependiendo del tipo de gas como alcohol, metano, CO, etc.).

### Uso

Con el objeto del sensor definido, podemos obtener la lectura del sensor utilizando la función `obtenerLecturaMQ()`, que devuelve el valor de la medición en ppm:

```cpp
float lectura = sensorMQ3.obtenerLecturaMQ();
```

El valor devuelto es el valor en partes por millón (ppm) correspondiente al gas detectado.

### Calibración

Es recomendable calibrar el sensor antes de leer los valores. Se utiliza la función `calibrar()` para realizar la calibración del sensor:

```cpp
sensorMQ3.calibrar();
```

### Cambio de Gas a Detectar

Puedes cambiar el tipo de gas que el sensor detecta utilizando la función `cambiarDeteccionGas()`. Solo necesitas indicar el nuevo tipo de gas como parámetro:

```cpp
sensorMQ3.cambiarDeteccionGas(MentorBitMQ3.co);
```

# Atributos

Los sensores MQ de MentorBit cuentan con diferentes atributos para detectar diversos gases. Estos son los atributos que puedes encontrar en cada clase de sensor.

### Atributos Comunes para Todos los Sensores MQ

#### `uint8_t mq_pin`
- **Descripción**: Pin del microcontrolador al que está conectado el sensor MQ.

#### `uint8_t gas_detection`
- **Descripción**: Gas que se desea detectar/medir con mayor precisión.

### Atributos Específicos por Sensor

Cada sensor tiene diferentes gases que puede detectar. Los atributos son constantes que definen el tipo de gas a detectar y ajustan el sensor para obtener mejores lecturas:

#### Sensor MQ135

- `MentorBitMQ135.co`: Dióxido de carbono (CO)
- `MentorBitMQ135.alcohol`: Alcohol (Etanol)
- `MentorBitMQ135.co2`: Dióxido de carbono (CO2)
- `MentorBitMQ135.tolueno`: Tolueno
- `MentorBitMQ135.nh4`: Amoníaco (NH4)
- `MentorBitMQ135.acetona`: Acetona

#### Sensor MQ2

- `MentorBitMQ2.h2`: Hidrógeno (H2)
- `MentorBitMQ2.glp`: Gas Licuado de Petróleo (GLP)
- `MentorBitMQ2.co`: Monóxido de carbono (CO)
- `MentorBitMQ2.alcohol`: Alcohol (Etanol)
- `MentorBitMQ2.propano`: Propano

#### Sensor MQ3

- `MentorBitMQ3.glp`: Gas Licuado de Petróleo (GLP)
- `MentorBitMQ3.ch4`: Metano (CH4)
- `MentorBitMQ3.co`: Monóxido de carbono (CO)
- `MentorBitMQ3.alcohol`: Alcohol (Etanol)
- `MentorBitMQ3.benceno`: Benceno
- `MentorBitMQ3.hexano`: Hexano

#### Sensor MQ4

- `MentorBitMQ4.glp`: Gas Licuado de Petróleo (GLP)
- `MentorBitMQ4.ch4`: Metano (CH4)
- `MentorBitMQ4.co`: Monóxido de carbono (CO)
- `MentorBitMQ4.alcohol`: Alcohol (Etanol)
- `MentorBitMQ4.humo`: Humo

#### Sensor MQ5

- `MentorBitMQ5.h2`: Hidrógeno (H2)
- `MentorBitMQ5.glp`: Gas Licuado de Petróleo (GLP)
- `MentorBitMQ5.ch4`: Metano (CH4)
- `MentorBitMQ5.co`: Monóxido de carbono (CO)
- `MentorBitMQ5.alcohol`: Alcohol (Etanol)

#### Sensor MQ6

- `MentorBitMQ6.h2`: Hidrógeno (H2)
- `MentorBitMQ6.glp`: Gas Licuado de Petróleo (GLP)
- `MentorBitMQ6.ch4`: Metano (CH4)
- `MentorBitMQ6.co`: Monóxido de carbono (CO)
- `MentorBitMQ6.alcohol`: Alcohol (Etanol)

#### Sensor MQ7

- `MentorBitMQ7.h2`: Hidrógeno (H2)
- `MentorBitMQ7.glp`: Gas Licuado de Petróleo (GLP)
- `MentorBitMQ7.ch4`: Metano (CH4)
- `MentorBitMQ7.co`: Monóxido de carbono (CO)
- `MentorBitMQ7.alcohol`: Alcohol (Etanol)

#### Sensor MQ8

- `MentorBitMQ8.h2`: Hidrógeno (H2)
- `MentorBitMQ8.glp`: Gas Licuado de Petróleo (GLP)
- `MentorBitMQ8.ch4`: Metano (CH4)
- `MentorBitMQ8.co`: Monóxido de carbono (CO)
- `MentorBitMQ8.alcohol`: Alcohol (Etanol)

#### Sensor MQ9

- `MentorBitMQ9.glp`: Gas Licuado de Petróleo (GLP)
- `MentorBitMQ9.ch4`: Metano (CH4)
- `MentorBitMQ9.co`: Monóxido de carbono (CO)

Cada sensor se calibra para detectar los diferentes gases de forma precisa. Los atributos de cada tipo de gas se pueden modificar y ajustar usando las funciones `calibrar()` y `cambiarDeteccionGas()`.

# Métodos principales

### `MentorBitMQx` -> Constructor
El constructor inicializa el sensor MQ y el tipo de gas que se desea detectar.

```cpp
MentorBitMQ3 sensorMQ3(PIN_SENSOR, MentorBitMQ3.co);
```
- **Parámetros**:
  - `PIN_SENSOR`: El pin al que se conecta el sensor.
  - `MentorBitMQ3.co`: El gas que se va a detectar (en este caso, CO).

### `obtenerLecturaMQ` -> Devuelve la lectura obtenida del sensor MQ.
Devuelve un valor flotante que representa la concentración del gas detectado en partes por millón (ppm).

```cpp
float lectura = sensorMQ3.obtenerLecturaMQ();
```

- **Valor devuelto**: Un valor flotante que representa la concentración del gas detectado en ppm.

### `cambiarDeteccionGas` -> Permite al usuario ajustar el valor de ppm devuelto en función del gas a detectar.
Recibe como parámetro un valor que representa el tipo de gas a detectar (por ejemplo, `MentorBitMQ3.co`).

```cpp
sensorMQ3.cambiarDeteccionGas(MentorBitMQ3.co);
```

- **Parámetros**: 
  - `MentorBitMQ3.co`: El gas que se desea detectar (por ejemplo, `MentorBitMQ3.co`, `MentorBitMQ3.alcohol`, etc.).

### `calibrar` -> Calibra el sensor para su posterior uso.
Calibra el sensor para asegurar mediciones precisas.

```cpp
sensorMQ3.calibrar();
```

### `setParameters` -> Ajusta los parámetros para el cálculo de los ppm (interna).
Este método se utiliza internamente para ajustar los parámetros del sensor según el tipo de gas seleccionado.
