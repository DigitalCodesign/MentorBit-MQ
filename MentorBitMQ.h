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

#ifndef MentorBitMQ_h
#define MentorBitMQ_h

#include <Arduino.h>
#include <MentorPort.h>

/******************
 * CLASE PADRE    *
 *****************/

class MentorBitMQBase : public MentorPot {

    public:

        void configPort(const Port& port) override;
        void calibrar();
        float obtenerLectura() const;

    protected:

        MentorBitMQBase(uint8_t mq_pin, float rl, float clean_air_ratio);

        Port _port;

        float _a;
        float _b;
        float _r0;
        float _rl;
        float _clean_air_ratio;

        float _calcularRs() const;

};

/******************
 * CLASES HIJA    *
 *****************/

class MentorBitMQ135 : public MentorPort
{

    public:

        enum Gas { CO, ALCOHOL, CO2, TOLUENO, NH4, ACETONA };

        MentorBitMQ135(uint8_t gas_detection, uint8_t mq_pin = 0);
        void cambiarDeteccionGas(Gas gas_detection);

};

/************************************  Sensor MQ2  ************************************/

class MentorBitMQ2 : public MentorPort
{

    public:

        enum Gas { H2, GLP, CO, ALCOHOL, PROPANO };

        MentorBitMQ2(uint8_t gas_detection, uint8_t mq_pin = 0);
        void cambiarDeteccionGas(Gas gas_detection);

};

/************************************  Sensor MQ3  ************************************/

class MentorBitMQ3 : public MentorPort
{

    public:

        enum Gas { GLP, CH4, CO, ALCOHOL, BENCENO, HEXANO };

        MentorBitMQ3(uint8_t gas_detection, uint8_t mq_pin = 0);
        void cambiarDeteccionGas(Gas gas_detection);

};

/************************************  Sensor MQ4  ************************************/

class MentorBitMQ4 : public MentorPort
{

    public:

        enum Gas { GLP, CH4, CO, ALCOHOL, HUMO };

        MentorBitMQ4(uint8_t gas_detection, uint8_t mq_pin = 0);
        void cambiarDeteccionGas(Gas gas_detection);

};

/************************************  Sensor MQ5  ************************************/

class MentorBitMQ5 : public MentorPort
{

    public:

        enum Gas { H2, GLP, CH4, CO, ALCOHOL };

        MentorBitMQ5(uint8_t gas_detection, uint8_t mq_pin = 0);
        void cambiarDeteccionGas(Gas gas_detection);

};

/************************************  Sensor MQ6  ************************************/

class MentorBitMQ6 : public MentorPort
{

    public:

        enum Gas { H2, GLP, CH4, CO, ALCOHOL };

        MentorBitMQ6(uint8_t gas_detection, uint8_t mq_pin = 0);
        void cambiarDeteccionGas(Gas gas_detection);

};

/************************************  Sensor MQ7  ************************************/

class MentorBitMQ7 : public MentorPort
{

    public:

        enum Gas { H2, GLP, CH4, CO, ALCOHOL };

        MentorBitMQ7(uint8_t gas_detection, uint8_t mq_pin = 0);
        void cambiarDeteccionGas(Gas gas_detection);

};

/************************************  Sensor MQ8  ************************************/

class MentorBitMQ8 : public MentorPort
{

    public:

        enum Gas { H2, GLP, CH4, CO, ALCOHOL };

        MentorBitMQ8(uint8_t gas_detection, uint8_t mq_pin = 0);
        void cambiarDeteccionGas(Gas gas_detection);

};

/************************************  Sensor MQ9  ************************************/

class MentorBitMQ9 : public MentorPort
{

    public:

        enum Gas { GLP, CH4, CO };

        MentorBitMQ9(uint8_t gas_detection, uint8_t mq_pin = 0);
        void cambiarDeteccionGas(Gas gas_detection);

};

#endif