# MentorBit-SensorMQ

Esta librería está diseñada para detectar la presencia de un gas, el cual cambiará en función del módulo MQ utilizado. Para ello unicamente se debe usar el **módulo de sensor de gases MQ** seleccionado y la placa MentorBit.

Si estás empezando en el mundo de la electrónica, ¡no te preocupes! MentorBit está pensado para que aprender sea fácil y divertido. Esta placa ya incluye un montón de componentes (LEDs, pulsadores, pantallas, etc.) y utiliza conectores especiales (JST) para que puedas añadir nuevos sensores y módulos sin tener que pelearte con un montón de cables. Pásate por nuestra web para saber más de MentorBit y nuestros productos [pinchando aquí](https://digitalcodesign.com/).

![Render del Módulo MentorBit Sensor de Gases MQ.](https://github.com/DigitalCodesign/MentorBit-MQ/blob/main/assets/MQ135.png)

Con esta librería, podrás saber la presencia de un determinado gas y su concentración aproximada en tus proyectos.

---

## Descripción

### ¿Qué es un sensor de gases MQ?

Un sensor de gases MQ tiene un calentador interno y un sensor sensible al gas. El calentador eleva la temperatura del sensor hasta llegar al punto ideal de operación. En este punto, en función de un determinado gas, la reistencia del sensor va a cambiar. Es gracias a este cambio que podemos saber lel gas presente y la concentración de este.

Este tipo de sensor es ideal para proyectos de automatización, protección de dispositivos o monitoreo ambiental.

---

### ¿Qué hace esta librería?

La librería **MentorBit-MQ** facilita la lectura del sensor y te proporciona una función sencilla para saber la concentración de un determinado gas.

Así puedes centrarte en el desarrollo de tu idea sin preocuparte por el tratamiento de señales o configuraciones complejas.

---

### ¿Qué puedes construir con este módulo?

- Una detector de calidad del aire.
- alarmas para niveles peligrosos de gases.
- dispositivos inteligentes de detección de gases.

---

## Modelos compatibles

A continuación se pueden ver todos los módulos MentorBit MQ junto con los gases a los que son sensibles.


||||
|:-----:|:------:|:-----:|
|MQ-135|MQ-2|MQ-3|
|<img src="https://github.com/DigitalCodesign/MentorBit-MQ/blob/main/assets/MQ135.png" width="300"/>|<img src="https://github.com/DigitalCodesign/MentorBit-MQ/blob/main/assets/MQ2.png" width="300"/>|<img src="https://github.com/DigitalCodesign/MentorBit-MQ/blob/main/assets/MQ3.png" width="300"/>|
|<b>- Amoniaco</b><br>- Alcohol<br>- Benceno<br>- Humo<br>- CO2|<b> - GLP</b> <br>-  H2<br> - Alcohol<br> - CO<br> - Propano |- GLP<br> -CH4<br> -CO<br><b> - Alcohol</b><br>- Benceno<br>- Hexano|
|MQ-4|MQ-5|MQ-6|
|<img src="https://github.com/DigitalCodesign/MentorBit-MQ/blob/main/assets/MQ4.png" width="300"/>|<img src="https://github.com/DigitalCodesign/MentorBit-MQ/blob/main/assets/MQ5.png" width="300"/>|<img src="https://github.com/DigitalCodesign/MentorBit-MQ/blob/main/assets/MQ6.png" width="300"/>|
|-GLP<br><b>- CH4</b><br> - CO<br> - Alcohol<br> - Humo|- H2<br><b> - GLP</b><br> - CH4<br> - CO<br> - Alcohol| - H2<br><b> - GLP<br> - CH4</b><br> - CO<br> - Alcohol|
|MQ-7|MQ-8|MQ-9|
|<img src="https://github.com/DigitalCodesign/MentorBit-MQ/blob/main/assets/MQ7.png" width="300"/>|<img src="https://github.com/DigitalCodesign/MentorBit-MQ/blob/main/assets/MQ8.png" width="300"/>|<img src="https://github.com/DigitalCodesign/MentorBit-MQ/blob/main/assets/MQ9.png" width="300"/>|
|-H2<br>- GLP<br> - CH4<br><b> - CO</b><br> - ALcohol|<b>- H2</b><br> - GLP<br> - CH4<br> - CO<br> - Alcohol|- <b>GLP<br> - CH4<br> - CO</b>|


## Cómo empezar

### 1. **Conexión del Módulo**

Conecta el módulo sensor de gases MQ a uno de los puertos analógico-digital con conector JST de 4 pines que estan en la sección "Puertos para Módulos" de la placa MentorBit. En este caso se va a utilizar el pin analógico para obtener la información del sensor.

### 2. **Instalación de la Librería**

- Abre tu entorno de programación IDE de Arduino.
- Ve al menú *Programa -> Incluir Librería -> Administrar Librerías...*
- En el buscador, escribe ***MentorBit-SensorMQ*** y haz clic en "Instalar".

![Ejemplo de búsqueda en el gestor de librerías del IDE de Arduino.](https://github.com/DigitalCodesign/MentorBit-MQ/blob/main/assets/library_instalation_example.png)

---

## Ejemplo Básico: Detectar gas detectado

Este ejemplo utiliza el sensor MQ para medir la concentracion de acetona.

```cpp
#include <MentorBitSensorMQ.h>

// Definimos los pines a los que se va a conectar el modulo
#define MQ_PIN A4

// Creamos el objeto del sensor
MentorBitMQ135  mq135(MQ_PIN, mq135.acetona);

void setup() {
    // Inicializamos el monitor Serial a una velocidad de 9600 baudios
    Serial.begin(9600);
    // Se calibra el sensor para obtener una medida fiable
    mq135.calibrar();
}

void loop() {
    // Se muestra por pantalla el valor de ppm obtenido del sensor
    Serial.println("Acetona:   " + String(mq135.obtenerLecturaMQ()) + " ppm");
    // Pequeño delay para no llenar el monitor serial
    delay(1000);
}
```

---

## Funciones Principales

- `float obtenerLecturaMQ();`  
  Devuelve el valor en ppm medido por el sensor en el ambiente para el gas indicado.

- `void cambiarDeteccionGas(uint8_t gas_detection);`  
  Cambia los parametros del sensor para medir la concentración de otro tipo de gas.

- `void calibrar();`  
  Calibra el sensor para obtener una medida más precisa.

---


## Atributos por sensor

###   MQ 135 (clase mq135)

| Atributo | Descripción |
| -------- | ----------- |
| `mq135.co` | Configura el sensor para medir la cantidad de ppm de CO |
| `mq135.alcohol` | Configura el sensor para medir la cantidad de ppm de alcohol |
| `mq135.co2` | Configura el sensor para medir la cantidad de ppm de CO2 |
| `mq135.tolueno` | Configura el sensor para medir la cantidad de ppm de tolueno |
| `mq135.nh4` | Configura el sensor para medir la cantidad de ppm de amonio |
| `mq135.acetona` | Configura el sensor para medir la cantidad de ppm de acetona |

###   MQ 2 (clase mq2)

| Atributo | Descripción |
| -------- | ----------- |
| `mq2.co` | Configura el sensor para medir la cantidad de ppm de CO |
| `mq2.alcohol` | Configura el sensor para medir la cantidad de ppm de alcohol |
| `mq2.h2` | Configura el sensor para medir la cantidad de ppm de hidrogeno |
| `mq2.glp` | Configura el sensor para medir la cantidad de ppm de glp |
| `mq2.propano` | Configura el sensor para medir la cantidad de ppm de propano |

###   MQ 3 (clase mq3)

| Atributo | Descripción |
| -------- | ----------- |
| `mq3.co` | Configura el sensor para medir la cantidad de ppm de CO |
| `mq3.alcohol` | Configura el sensor para medir la cantidad de ppm de alcohol |
| `mq3.glp` | Configura el sensor para medir la cantidad de ppm de glp |
| `mq3.ch4` | Configura el sensor para medir la cantidad de ppm de metano |
| `mq3.benceno` | Configura el sensor para medir la cantidad de ppm de benceno |
| `mq3.hexano` | Configura el sensor para medir la cantidad de ppm de hexano |

###   MQ 4 (clase mq4)

| Atributo | Descripción |
| -------- | ----------- |
| `mq4.co` | Configura el sensor para medir la cantidad de ppm de CO |
| `mq4.alcohol` | Configura el sensor para medir la cantidad de ppm de alcohol |
| `mq4.glp` | Configura el sensor para medir la cantidad de ppm de glp |
| `mq4.ch4` | Configura el sensor para medir la cantidad de ppm de metano |
| `mq135.humo` | Configura el sensor para medir la cantidad de ppm de humo |

###   MQ 5 (clase mq5)

| Atributo | Descripción |
| -------- | ----------- |
| `mq5.co` | Configura el sensor para medir la cantidad de ppm de CO |
| `mq5.alcohol` | Configura el sensor para medir la cantidad de ppm de alcohol |
| `mq5.h2` | Configura el sensor para medir la cantidad de ppm de hidrogeno |
| `mq5.glp` | Configura el sensor para medir la cantidad de ppm de glp |
| `mq5.ch4` | Configura el sensor para medir la cantidad de ppm de metano |

### MQ 6 (clase mq6)

| Atributo | Descripción |
| -------- | ----------- |
| `mq6.co` | Configura el sensor para medir la cantidad de ppm de CO |
| `mq6.alcohol` | Configura el sensor para medir la cantidad de ppm de alcohol |
| `mq6.h2` | Configura el sensor para medir la cantidad de ppm de hidrogeno |
| `mq6.glp` | Configura el sensor para medir la cantidad de ppm de glp |
| `mq6.ch4` | Configura el sensor para medir la cantidad de ppm de metano |

### MQ 7 (clase mq7)

| Atributo | Descripción |
| -------- | ----------- |
| `mq7.co` | Configura el sensor para medir la cantidad de ppm de CO |
| `mq7.alcohol` | Configura el sensor para medir la cantidad de ppm de alcohol |
| `mq7.h2` | Configura el sensor para medir la cantidad de ppm de hidrogeno |
| `mq7.glp` | Configura el sensor para medir la cantidad de ppm de glp |
| `mq7.ch4` | Configura el sensor para medir la cantidad de ppm de metano |

### MQ 8 (clase mq8)

| Atributo | Descripción |
| -------- | ----------- |
| `mq8.co` | Configura el sensor para medir la cantidad de ppm de CO |
| `mq8.alcohol` | Configura el sensor para medir la cantidad de ppm de alcohol |
| `mq8.h2` | Configura el sensor para medir la cantidad de ppm de hidrogeno |
| `mq8.glp` | Configura el sensor para medir la cantidad de ppm de glp |
| `mq8.ch4` | Configura el sensor para medir la cantidad de ppm de metano |

### MQ 9 (clase mq9)

| Atributo | Descripción |
| -------- | ----------- |
| `mq9.co` | Configura el sensor para medir la cantidad de ppm de CO |
| `mq9.glp` | Configura el sensor para medir la cantidad de ppm de glp |
| `mq9.ch4` | Configura el sensor para medir la cantidad de ppm de metano |

---


## Recursos Adicionales

- [Web del fabricante](https://digitalcodesign.com/)
- [Tienda Online de Canarias](https://canarias.digitalcodesign.com/shop)
- [Tienda Online de Península](https://digitalcodesign.com/shop)
- [Web Oficial de MentorBit](https://digitalcodesign.com/mentorbit)
- [Web Oficial del Módulo de Gas Detectado](https://digitalcodesign.com/shop/mentorbit-modulo-de-sensor-mq-8147#attr=91)
- [Manual de usuario del Módulo](https://drive.google.com/file/d/1QrtqhS7Hp8bIin3XZIuWA6utWsu4fHat/view?usp=drive_link)
- [Modelo 3D del Módulo en formato .STEP](https://drive.google.com/file/d/1x98k-mTPjL0OpKV29PBwvK_WGO9_Rzva/view?usp=drive_link)
