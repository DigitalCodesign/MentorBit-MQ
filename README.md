# MentorBitMQ

Librería para el uso de sensores de gas MQ con módulos compatibles con MentorBit.

## Descripción

La librería `MentorBitMQ` facilita la lectura y el uso de sensores de gas MQ en módulos compatibles con MentorBit. Proporciona clases para diferentes modelos de sensores MQ (MQ2, MQ3, MQ4, MQ5, MQ6, MQ7, MQ8, MQ9 y MQ135), permitiendo medir la concentración de diversos gases como monóxido de carbono (CO), dióxido de carbono (CO2), metano (CH4), gas licuado de petróleo (GLP), hidrógeno (H2), humo, alcohol, tolueno, amoníaco (NH4), acetona y benceno.

**Nota:** Esta librería depende de la librería `MQUnifiedsensor`. Asegúrate de que también esté instalada.

## Clases y Métodos

La librería incluye las siguientes clases, cada una para un modelo de sensor MQ:

* `MentorBitMQ2`
* `MentorBitMQ3`
* `MentorBitMQ4`
* `MentorBitMQ5`
* `MentorBitMQ6`
* `MentorBitMQ7`
* `MentorBitMQ8`
* `MentorBitMQ9`
* `MentorBitMQ135`

Cada clase tiene los siguientes métodos públicos:

* `MentorBitMQX(uint8_t mq_pin, uint8_t gas_detection)`: Constructor de la clase.
    * `mq_pin`: Pin analógico al que está conectado el sensor.
    * `gas_detection`: Constante que indica el gas que se quiere detectar con mayor precisión.
* `float obtenerLecturaMQ()`: Obtiene la lectura del sensor en ppm.
* `void cambiarDeteccionGas(uint8_t gas_detection)`: Cambia el gas que se quiere detectar.
* `void calibrar()`: Calibra el sensor.

## Constantes

Cada clase define constantes para los diferentes gases que puede detectar el sensor. Por ejemplo, la clase `MentorBitMQ2` define las siguientes constantes:

* `h2`: Hidrógeno
* `glp`: Gas licuado de petróleo
* `co`: Monóxido de carbono
* `alcohol`: Alcohol
* `propano`: Propano

## Modo de Empleo

1.  **Instalación:**
    * Abre el IDE compatible con MentorBit.
    * Ve a "Herramientas" -> "Gestionar librerías..."
    * Busca "MentorBitMQ" e instálala.
    * **Nota:** Asegúrate de que la librería `MQUnifiedsensor` esté instalada.

2.  **Ejemplo básico (MQ2):**

    ```c++
    #include <MentorBitMQ.h>

    MentorBitMQ2 mq2(A0, MentorBitMQ2::h2); // Sensor MQ2 en pin A0, detectando H2

    void setup() {
      Serial.begin(9600);
      mq2.calibrar(); // Calibra el sensor
    }

    void loop() {
      float ppm = mq2.obtenerLecturaMQ();
      Serial.print("Concentración de H2: ");
      Serial.print(ppm);
      Serial.println(" ppm");
      delay(1000);
    }
    ```
