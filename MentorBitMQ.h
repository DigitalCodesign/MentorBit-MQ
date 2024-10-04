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


   Autor: Digital Codesign
   Version: 1.0.0
   Fecha de creación: Septiembre de 2024
   Fecha de version: Septiembre de 2024
   Repositorio: https://github.com/DigitalCodesign/MentorBit-MQ
   Descripcion:
      Esta libreria esta especificamente diseñada para ser utilizada junto con
      el modulo de sensor MQ de MentorBit
   clases:
      MentorBitMQ135 -> Clase para utilizar el sensor MQ135
      MentorBitMQ2 -> Clase para utilizar el sensor MQ2
      MentorBitMQ3 -> Clase para utilizar el sensor MQ3
      MentorBitMQ4 -> Clase para utilizar el sensor MQ4
      MentorBitMQ5 -> Clase para utilizar el sensor MQ5
      MentorBitMQ6 -> Clase para utilizar el sensor MQ6
      MentorBitMQ7 -> Clase para utilizar el sensor MQ7
      MentorBitMQ8 -> Clase para utilizar el sensor MQ8
      MentorBitMQ9 -> Clase para utilizar el sensor MQ9
   Metodos principales:
      MentorBitMQx -> Constructor
      obtenerLectura -> devuelve la lectura obtenida del sensor MQ
      cambiarDeteccionGas -> permite al usuario ajustar el valor de ppm devuelto en
                              en funcion del gas a detectar
      calibrar -> Calibra el sensor para su posterior uso
      setParameters -> Ajusta los parametros para el calculo de los ppm (interna)
   Atributos:
      h2 -> asigna los parametros necesarios para una mejor deteccion del h2
      glp -> asigna los parametros necesarios para una mejor deteccion del glp
      ch4 -> asigna los parametros necesarios para una mejor deteccion del ch4
      co -> asigna los parametros necesarios para una mejor deteccion del co
      co2 -> asigna los parametros necesarios para una mejor deteccion del co2
      tolueno -> asigna los parametros necesarios para una mejor deteccion del tolueno
      alcohol -> asigna los parametros necesarios para una mejor deteccion del alcohol
      humo -> asigna los parametros necesarios para una mejor deteccion del humo
      hexano -> asigna los parametros necesarios para una mejor deteccion del hexano
      benceno -> asigna los parametros necesarios para una mejor deteccion del benceno
      propano -> asigna los parametros necesarios para una mejor deteccion del propano
      acetona -> asigna los parametros necesarios para una mejor deteccion del acetona
*/

#ifndef MentorBitMQ_h
#define MentorBitMQ_h

#include <arduino.h>
#include <MQUnifiedsensor.h>

/***********************************  Sensor MQ135  ***********************************/

class MentorBitMQ135
{

    public:

        MentorBitMQ135(uint8_t mq_pin, uint8_t gas_detection);
        float obtenerLecturaMQ();
        void cambiarDeteccionGas(uint8_t gas_detection);
        void calibrar();

        const uint8_t co = 0;
        const uint8_t alcohol = 1;
        const uint8_t co2 = 2;
        const uint8_t tolueno = 3;
        const uint8_t nh4 = 4;
        const uint8_t acetona = 5;

    private:

        void setParameters(uint8_t gas_detection);

        uint8_t _mq_pin;
        uint8_t _gas_detection;

        MQUnifiedsensor MQ;

};

/************************************  Sensor MQ2  ************************************/

class MentorBitMQ2
{

    public:

        MentorBitMQ2(uint8_t mq_pin, uint8_t gas_detection);
        float obtenerLecturaMQ();
        void cambiarDeteccionGas(uint8_t gas_detection);
        void calibrar();

        const uint8_t h2 = 0;
        const uint8_t glp = 1;
        const uint8_t co = 2;
        const uint8_t alcohol = 3;
        const uint8_t propano = 4;

    private:

        void setParameters(uint8_t gas_detection);

        uint8_t _mq_pin;
        uint8_t _gas_detection;

        MQUnifiedsensor MQ;

};

/************************************  Sensor MQ3  ************************************/

class MentorBitMQ3
{

    public:

        MentorBitMQ3(uint8_t mq_pin, uint8_t gas_detection);
        float obtenerLecturaMQ();
        void cambiarDeteccionGas(uint8_t gas_detection);
        void calibrar();

        const uint8_t glp = 0;
        const uint8_t ch4 = 1;
        const uint8_t co = 2;
        const uint8_t alcohol = 3;
        const uint8_t benceno = 4;
        const uint8_t hexano = 5;

    private:

        void setParameters(uint8_t gas_detection);

        uint8_t _mq_pin;
        uint8_t _gas_detection;

        MQUnifiedsensor MQ;

};

/************************************  Sensor MQ4  ************************************/

class MentorBitMQ4
{

    public:

        MentorBitMQ4(uint8_t mq_pin, uint8_t gas_detection);
        float obtenerLecturaMQ();
        void cambiarDeteccionGas(uint8_t gas_detection);
        void calibrar();

        const uint8_t glp = 0;
        const uint8_t ch4 = 1;
        const uint8_t co = 2;
        const uint8_t alcohol = 3;
        const uint8_t humo = 4;

    private:

        void setParameters(uint8_t gas_detection);

        uint8_t _mq_pin;
        uint8_t _gas_detection;

        MQUnifiedsensor MQ;

};

/************************************  Sensor MQ5  ************************************/

class MentorBitMQ5
{

    public:

        MentorBitMQ5(uint8_t mq_pin, uint8_t gas_detection);
        float obtenerLecturaMQ();
        void cambiarDeteccionGas(uint8_t gas_detection);
        void calibrar();

        const uint8_t h2 = 0;
        const uint8_t glp = 1;
        const uint8_t ch4 = 2;
        const uint8_t co = 3;
        const uint8_t alcohol = 4;

    private:

        void setParameters(uint8_t gas_detection);

        uint8_t _mq_pin;
        uint8_t _gas_detection;

        MQUnifiedsensor MQ;

};

/************************************  Sensor MQ6  ************************************/

class MentorBitMQ6
{

    public:

        MentorBitMQ6(uint8_t mq_pin, uint8_t gas_detection);
        float obtenerLecturaMQ();
        void cambiarDeteccionGas(uint8_t gas_detection);
        void calibrar();

        const uint8_t h2 = 0;
        const uint8_t glp = 1;
        const uint8_t ch4 = 2;
        const uint8_t co = 3;
        const uint8_t alcohol = 4;

    private:

        void setParameters(uint8_t gas_detection);

        uint8_t _mq_pin;
        uint8_t _gas_detection;

        MQUnifiedsensor MQ;

};

/************************************  Sensor MQ7  ************************************/

class MentorBitMQ7
{

    public:

        MentorBitMQ7(uint8_t mq_pin, uint8_t gas_detection);
        float obtenerLecturaMQ();
        void cambiarDeteccionGas(uint8_t gas_detection);
        void calibrar();

        const uint8_t h2 = 0;
        const uint8_t glp = 1;
        const uint8_t ch4 = 2;
        const uint8_t co = 3;
        const uint8_t alcohol = 4;

    private:

        void setParameters(uint8_t gas_detection);

        uint8_t _mq_pin;
        uint8_t _gas_detection;

        MQUnifiedsensor MQ;

};

/************************************  Sensor MQ8  ************************************/

class MentorBitMQ8
{

    public:

        MentorBitMQ8(uint8_t mq_pin, uint8_t gas_detection);
        float obtenerLecturaMQ();
        void cambiarDeteccionGas(uint8_t gas_detection);
        void calibrar();

        const uint8_t h2 = 0;
        const uint8_t glp = 1;
        const uint8_t ch4 = 2;
        const uint8_t co = 3;
        const uint8_t alcohol = 4;

    private:

        void setParameters(uint8_t gas_detection);

        uint8_t _mq_pin;
        uint8_t _gas_detection;

        MQUnifiedsensor MQ;

};

/************************************  Sensor MQ9  ************************************/

class MentorBitMQ9
{

    public:

        MentorBitMQ9(uint8_t mq_pin, uint8_t gas_detection);
        float obtenerLecturaMQ();
        void cambiarDeteccionGas(uint8_t gas_detection);
        void calibrar();

        const uint8_t glp = 0;
        const uint8_t ch4 = 1;
        const uint8_t co = 2;

    private:

        void setParameters(uint8_t gas_detection);

        uint8_t _mq_pin;
        uint8_t _gas_detection;

        MQUnifiedsensor MQ;

};

#endif