/*


          ██████╗    ██╗    ██████╗    ██╗   ████████╗    █████╗    ██╗
          ██╔══██╗   ██║   ██╔════╝    ██║   ╚══██╔══╝   ██╔══██╗   ██║
          ██║  ██║   ██║   ██║  ███╗   ██║      ██║      ███████║   ██║
          ██║  ██║   ██║   ██║   ██║   ██║      ██║      ██╔══██║   ██║
          ██████╔╝   ██║   ╚██████╔╝   ██║      ██║      ██║  ██║   ███████╗
          ╚═════╝    ╚═╝    ╚═════╝    ╚═╝      ╚═╝      ╚═╝  ╚═╝   ╚══════╝

   ██████╗    ██████╗    ██████╗    ███████╗   ███████╗   ██╗    ██████╗    ███╗   ██╗
  ██╔════╝   ██╔═══██╗   ██╔══██╗   ██╔════╝   ██╔════╝   ██║   ██╔════╝    ████╗  ██║
  ██║        ██║   ██║   ██║  ██║   █████╗     ███████╗   ██║   ██║  ███╗   ██╔██╗ ██║
  ██║        ██║   ██║   ██║  ██║   ██╔══╝     ╚════██║   ██║   ██║   ██║   ██║╚██╗██║
  ╚██████╗   ╚██████╔╝   ██████╔╝   ███████╗   ███████║   ██║   ╚██████╔╝   ██║ ╚████║
   ╚═════╝    ╚═════╝    ╚═════╝    ╚══════╝   ╚══════╝   ╚═╝    ╚═════╝    ╚═╝  ╚═══╝


   @author Digital Codesign
   @version 1.1.0
   @date Fecha de creación: Septiembre de 2024
   @date Fecha de versión: Mayo de 2026
   @see Repositorio: https://github.com/DigitalCodesign/MentorBit-MQ
   * @brief Descripción:
      Esta librería está específicamente diseñada para ser utilizada junto con
      la familia de módulos de sensor de gas MQ de MentorBit. Ha sido optimizada 
      utilizando herencia orientada a objetos ("Bare Metal") para eliminar dependencias 
      de terceros, reduciendo drásticamente el consumo de memoria y mejorando la legibilidad.
   * @details Clases disponibles:
      - MentorBitMQ135 -> Clase para utilizar el sensor MQ135 (Calidad del aire)
      - MentorBitMQ2   -> Clase para utilizar el sensor MQ2 (Gases combustibles)
      - MentorBitMQ3   -> Clase para utilizar el sensor MQ3 (Alcohol)
      - MentorBitMQ4   -> Clase para utilizar el sensor MQ4 (Metano / Gas Natural)
      - MentorBitMQ5   -> Clase para utilizar el sensor MQ5 (GLP / Gas Natural)
      - MentorBitMQ6   -> Clase para utilizar el sensor MQ6 (GLP / Butano)
      - MentorBitMQ7   -> Clase para utilizar el sensor MQ7 (Monóxido de Carbono)
      - MentorBitMQ8   -> Clase para utilizar el sensor MQ8 (Hidrógeno)
      - MentorBitMQ9   -> Clase para utilizar el sensor MQ9 (CO y Gases Combustibles)
   * Métodos principales (Heredados de MentorBitMQBase):
      - MentorBitMQx        -> Constructor de la subclase correspondiente.
      - obtenerLectura      -> Devuelve la concentración del gas estimado en ppm.
      - cambiarDeteccionGas -> Ajusta los parámetros (A y B) según el gas objetivo seleccionado.
      - calibrar            -> Calcula el valor R0 asumiendo que el sensor está en aire limpio.
   * @note Atributos de Gas (enum):
      Cada subclase contiene su propio enumerador `Gas` con las etiquetas válidas 
      (ej. CO, CO2, ALCOHOL, CH4, GLP, etc.) para facilitar la programación al usuario.

*/

#include <MentorBitMQ.h>

/******************
 * CLASE PADRE    *
 *****************/

/**
 * @brief Configura el puerto de hardware asociado al módulo.
 * Asegura que el pin asignado para leer el voltaje analógico del sensor 
 * esté correctamente configurado como entrada (INPUT).
 * @param port Estructura constante por referencia con la configuración del puerto.
 */
void MentorBitMQBase::configPort(const Port &port) {

   _port.type = port.type;
   _port.location = port.location;
   _port.gpios[0] = port.gpios[0];
   _port.gpios[1] = port.gpios[1];

   pinMode(_port.gpios[0], INPUT);

}

/**
 * @brief Calibra el sensor tomando lecturas de referencia en aire limpio.
 * Toma 10 muestras con un intervalo de 200ms para estabilizar la lectura y 
 * calcula la resistencia base (R0) del sensor. Debe ejecutarse en un entorno 
 * sin presencia de los gases objetivo.
 */
void MentorBitMQBase::calibrar() {

   float rs_sum = 0;
   for (int i = 0 ; i < 10 ; i++) {
      rs_sum += _calcularRs();
      delay(200);
   }
   _r0 = (rs_sum / 10.0) / _clean_air_ratio;

}

/**
 * @brief Obtiene la concentración del gas objetivo en partes por millón (ppm).
 * Aplica la fórmula de regresión potencial utilizando los coeficientes A y B 
 * correspondientes al gas seleccionado y la resistencia actual del sensor.
 * @return Valor de concentración en ppm. Si hay error en las lecturas, devuelve 0.
 */
float MentorBitMQBase::obtenerLectura() const {

   float rs = _calcularRs();
   if (_r0 == 0 || rs == 0) return 0;
   return _a * pow(rs / _r0, _b);

}

/**
 * @brief Constructor protegido de la clase base.
 * @param mq_pin Pin analógico conectado al sensor.
 * @param rl Valor de la resistencia de carga de la placa en kOhm.
 * @param clean_air_ratio Ratio Rs/R0 esperado en condiciones de aire limpio.
 */
MentorBitMQBase::MentorBitMQBase(uint8_t mq_pin, float rl, float clean_air_ratio)
   : _r0(1.0), _rl(rl), _clean_air_ratio(clean_air_ratio) {

   _port.gpios[0] = mq_pin;
   if (mq_pin > 0) pinMode(_port.gpios[0], INPUT);

}

/**
 * @brief Calcula la resistencia actual del sensor (Rs).
 * Lee el conversor analógico a digital (ADC) y aplica la ley de Ohm utilizando 
 * el divisor de tensión físico formado junto a la resistencia de carga (RL).
 * @return Resistencia actual del sensor en kOhm.
 */
float MentorBitMQBase::_calcularRs() const
{

   int valor_adc = analogRead(_port.gpios[0]);
   if (valor_adc == 0) return 0;

   float voltaje = valor_adc * (5.0 / 1023.0);
   return _rl * ((5.0 - voltaje) / voltaje);

}

/******************
 * CLASES HIJA    *
 *****************/

/************************************  Sensor MQ135  ***********************************/

/**
 * @brief Constructor de la clase MentorBitMQ135.
 * Inicializa el sensor aplicando las características físicas correspondientes 
 * y establece el gas objetivo por defecto.
 * @param gas_detection Tipo de gas objetivo a medir (mediante enumerador Gas).
 * @param mq_pin Pin analógico donde se conectará el módulo (por defecto 0).
 */
MentorBitMQ135::MentorBitMQ135(uint8_t gas_detection, uint8_t mq_pin)
   : MentorBitMQBase(mq_pin, 10.0, 3.6) {

   cambiarDeteccionGas(gas_detection);

}

/**
 * @brief Cambia el tipo de gas objetivo que el sensor va a calcular.
 * Actualiza internamente los coeficientes matemáticos A y B de la curva de 
 * regresión específicos para este modelo de sensor y el gas elegido.
 * @param gas_detection Valor numérico o enumerador de gas correspondiente a esta clase.
 */
void MentorBitMQ135::cambiarDeteccionGas(Gas gas_detection) {

   switch (gas_detection) {
      case CO:      _a = 605.18; _b = -3.937; break;
      case ALCOHOL: _a = 77.255; _b = -3.180; break;
      case CO2:     _a = 110.47; _b = -2.862; break;
      case TOLUENO: _a = 44.947; _b = -3.445; break;
      case NH4:     _a = 102.20; _b = -2.473; break;
      case ACETONA: _a = 34.668; _b = -3.369; break;
   }

}

/************************************  Sensor MQ2  *************************************/

/**
 * @brief Constructor de la clase MentorBitMQ2.
 * Inicializa el sensor aplicando las características físicas correspondientes 
 * y establece el gas objetivo por defecto.
 * @param gas_detection Tipo de gas objetivo a medir (mediante enumerador Gas).
 * @param mq_pin Pin analógico donde se conectará el módulo (por defecto 0).
 */
MentorBitMQ2::MentorBitMQ2(uint8_t gas_detection, uint8_t mq_pin)
   : MentorBitMQBase(mq_pin, 10.0, 9.83) {

   cambiarDeteccionGas(gas_detection);

}

/**
 * @brief Cambia el tipo de gas objetivo que el sensor va a calcular.
 * Actualiza internamente los coeficientes matemáticos A y B de la curva de 
 * regresión específicos para este modelo de sensor y el gas elegido.
 * @param gas_detection Valor numérico o enumerador de gas correspondiente a esta clase.
 */
void MentorBitMQ2::cambiarDeteccionGas(Gas gas_detection) {

   switch (gas_detection) {
      case H2:      _a = 987.99; _b = -2.162; break;
      case GLP:     _a = 574.25; _b = -2.222; break;
      case CO:      _a = 36974;  _b = -3.109; break;
      case ALCOHOL: _a = 3616.1; _b = -2.675; break;
      case PROPANO: _a = 658.71; _b = -2.168; break;
   }

}

/************************************  Sensor MQ3  *************************************/

/**
 * @brief Constructor de la clase MentorBitMQ3.
 * Inicializa el sensor aplicando las características físicas correspondientes 
 * y establece el gas objetivo por defecto.
 * @param gas_detection Tipo de gas objetivo a medir (mediante enumerador Gas).
 * @param mq_pin Pin analógico donde se conectará el módulo (por defecto 0).
 */
MentorBitMQ3::MentorBitMQ3(uint8_t gas_detection, uint8_t mq_pin)
   : MentorBitMQBase(mq_pin, 10.0, 60) {

   cambiarDeteccionGas(gas_detection);

}

/**
 * @brief Cambia el tipo de gas objetivo que el sensor va a calcular.
 * Actualiza internamente los coeficientes matemáticos A y B de la curva de 
 * regresión específicos para este modelo de sensor y el gas elegido.
 * @param gas_detection Valor numérico o enumerador de gas correspondiente a esta clase.
 */
void MentorBitMQ3::cambiarDeteccionGas(Gas gas_detection) {

   switch (gas_detection) {
      case GLP:     _a = 44771;  _b = -3.245; break;
      case CH4:     _a = 2.0e14; _b = -19.01; break;
      case CO:      _a = 521853; _b = -3.821; break;
      case ALCOHOL: _a = 0.3934; _b = -1.504; break;
      case BENCENO: _a = 4.8387; _b = -2.68;  break;
      case HEXANO:  _a = 7585.3; _b = -2.849; break;
   }

}

/************************************  Sensor MQ4  *************************************/

/**
 * @brief Constructor de la clase MentorBitMQ4.
 * Inicializa el sensor aplicando las características físicas correspondientes 
 * y establece el gas objetivo por defecto.
 * @param gas_detection Tipo de gas objetivo a medir (mediante enumerador Gas).
 * @param mq_pin Pin analógico donde se conectará el módulo (por defecto 0).
 */
MentorBitMQ4::MentorBitMQ4(uint8_t gas_detection, uint8_t mq_pin)
   : MentorBitMQBase(mq_pin, 10.0, 4.4) {

   cambiarDeteccionGas(gas_detection);

}

/**
 * @brief Cambia el tipo de gas objetivo que el sensor va a calcular.
 * Actualiza internamente los coeficientes matemáticos A y B de la curva de 
 * regresión específicos para este modelo de sensor y el gas elegido.
 * @param gas_detection Valor numérico o enumerador de gas correspondiente a esta clase.
 */
void MentorBitMQ4::cambiarDeteccionGas(Gas gas_detection) {

   switch (gas_detection) {
      case GLP:     _a = 3811.9; _b = -3.113; break;
      case CH4:     _a = 1012.7; _b = -2.786; break;
      case CO:      _a = 2.0e14; _b = -19.05; break;
      case ALCOHOL: _a = 6.0e10; _b = -14.01; break;
      case HUMO:    _a = 3.0e7;  _b = -8.308; break;
   }

}

/************************************  Sensor MQ5  *************************************/

/**
 * @brief Constructor de la clase MentorBitMQ5.
 * Inicializa el sensor aplicando las características físicas correspondientes 
 * y establece el gas objetivo por defecto.
 * @param gas_detection Tipo de gas objetivo a medir (mediante enumerador Gas).
 * @param mq_pin Pin analógico donde se conectará el módulo (por defecto 0).
 */
MentorBitMQ5::MentorBitMQ5(uint8_t gas_detection, uint8_t mq_pin)
   : MentorBitMQBase(mq_pin, 10.0, 6.5) {

   cambiarDeteccionGas(gas_detection);

}

/**
 * @brief Cambia el tipo de gas objetivo que el sensor va a calcular.
 * Actualiza internamente los coeficientes matemáticos A y B de la curva de 
 * regresión específicos para este modelo de sensor y el gas elegido.
 * @param gas_detection Valor numérico o enumerador de gas correspondiente a esta clase.
 */
void MentorBitMQ5::cambiarDeteccionGas(Gas gas_detection) {

   switch (gas_detection) {
      case H2:      _a = 1163.8; _b = -3.874; break;
      case GLP:     _a = 80.897; _b = -2.431; break;
      case CH4:     _a = 177.65; _b = -2.56;  break;
      case CO:      _a = 491204; _b = -5.826; break;
      case ALCOHOL: _a = 97124;  _b = -4.918; break;
   }

}

/************************************  Sensor MQ6  *************************************/

/**
 * @brief Constructor de la clase MentorBitMQ6.
 * Inicializa el sensor aplicando las características físicas correspondientes 
 * y establece el gas objetivo por defecto.
 * @param gas_detection Tipo de gas objetivo a medir (mediante enumerador Gas).
 * @param mq_pin Pin analógico donde se conectará el módulo (por defecto 0).
 */
MentorBitMQ6::MentorBitMQ6(uint8_t gas_detection, uint8_t mq_pin)
   : MentorBitMQBase(mq_pin, 10.0, 10.0) {

   cambiarDeteccionGas(gas_detection);

}

/**
 * @brief Cambia el tipo de gas objetivo que el sensor va a calcular.
 * Actualiza internamente los coeficientes matemáticos A y B de la curva de 
 * regresión específicos para este modelo de sensor y el gas elegido.
 * @param gas_detection Valor numérico o enumerador de gas correspondiente a esta clase.
 */
void MentorBitMQ6::cambiarDeteccionGas(Gas gas_detection) {

   switch (gas_detection) {
      case H2:      _a = 88158;  _b = -3.597; break;
      case GLP:     _a = 1009.2; _b = -2.35;  break;
      case CH4:     _a = 2127.2; _b = -2.526; break;
      case CO:      _a = 1.0e15; _b = -13.5;  break;
      case ALCOHOL: _a = 5.0e7;  _b = -6.017; break;
   }

}

/************************************  Sensor MQ7  *************************************/

/**
 * @brief Constructor de la clase MentorBitMQ7.
 * Inicializa el sensor aplicando las características físicas correspondientes 
 * y establece el gas objetivo por defecto.
 * @param gas_detection Tipo de gas objetivo a medir (mediante enumerador Gas).
 * @param mq_pin Pin analógico donde se conectará el módulo (por defecto 0).
 */
MentorBitMQ7::MentorBitMQ7(uint8_t gas_detection, uint8_t mq_pin)
   : MentorBitMQBase(mq_pin, 10.0, 27.5) {

   cambiarDeteccionGas(gas_detection);

}


/**
 * @brief Cambia el tipo de gas objetivo que el sensor va a calcular.
 * Actualiza internamente los coeficientes matemáticos A y B de la curva de 
 * regresión específicos para este modelo de sensor y el gas elegido.
 * @param gas_detection Valor numérico o enumerador de gas correspondiente a esta clase.
 */
void MentorBitMQ7::cambiarDeteccionGas(Gas gas_detection) {

   switch (gas_detection) {
      case H2:      _a = 69.014; _b = -1.374; break;
      case GLP:     _a = 7.0e8;  _b = -7.703; break;
      case CH4:     _a = 6.0e13; _b = -10.54; break;
      case CO:      _a = 99.042; _b = -1.518; break;
      case ALCOHOL: _a = 4.0e16; _b = -12.35; break;
   }

}

/************************************  Sensor MQ8  *************************************/

/**
 * @brief Constructor de la clase MentorBitMQ8.
 * Inicializa el sensor aplicando las características físicas correspondientes 
 * y establece el gas objetivo por defecto.
 * @param gas_detection Tipo de gas objetivo a medir (mediante enumerador Gas).
 * @param mq_pin Pin analógico donde se conectará el módulo (por defecto 0).
 */
MentorBitMQ8::MentorBitMQ8(uint8_t gas_detection, uint8_t mq_pin)
   : MentorBitMQBase(mq_pin, 10.0, 70.0) {

   cambiarDeteccionGas(gas_detection);

}

/**
 * @brief Cambia el tipo de gas objetivo que el sensor va a calcular.
 * Actualiza internamente los coeficientes matemáticos A y B de la curva de 
 * regresión específicos para este modelo de sensor y el gas elegido.
 * @param gas_detection Valor numérico o enumerador de gas correspondiente a esta clase.
 */
void MentorBitMQ8::cambiarDeteccionGas(Gas gas_detection) {

   switch (gas_detection) {
      case H2:      _a = 976.97; _b = -0.688; break;
      case GLP:     _a = 1.0e7;  _b = -3.123; break;
      case CH4:     _a = 8.0e13; _b = -6.666; break;
      case CO:      _a = 2.0e18; _b = -8.074; break;
      case ALCOHOL: _a = 76101;  _b = -1.86;  break;
   }

}

/************************************  Sensor MQ9  *************************************/

/**
 * @brief Constructor de la clase MentorBitMQ9.
 * Inicializa el sensor aplicando las características físicas correspondientes 
 * y establece el gas objetivo por defecto.
 * @param gas_detection Tipo de gas objetivo a medir (mediante enumerador Gas).
 * @param mq_pin Pin analógico donde se conectará el módulo (por defecto 0).
 */
MentorBitMQ9::MentorBitMQ9(uint8_t gas_detection, uint8_t mq_pin) 
   : MentorBitMQBase(mq_pin, 10.0, 9.6) {

   cambiarDeteccionGas(gas_detection);

}

/**
 * @brief Cambia el tipo de gas objetivo que el sensor va a calcular.
 * Actualiza internamente los coeficientes matemáticos A y B de la curva de 
 * regresión específicos para este modelo de sensor y el gas elegido.
 * @param gas_detection Valor numérico o enumerador de gas correspondiente a esta clase.
 */
void MentorBitMQ9::cambiarDeteccionGas(Gas gas_detection) {

   switch (gas_detection) {
      case GLP: _a = 1000.5; _b = -2.186; break;
      case CH4: _a = 4269.6; _b = -2.648; break;
      case CO:  _a = 599.65; _b = -2.244; break;
   }

}
