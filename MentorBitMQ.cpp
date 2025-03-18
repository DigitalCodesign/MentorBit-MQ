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

#include <MentorBitMQ.h>

/***********************************  Sensor MQ135  ***********************************/

/*
   Constructor para el uso de la clase MentorBitMQ135. Se deben indicar los siguientes 
   parametros:
      - Pin del microcontrolador al que esta conectado el sensor MQ135
      - Gas que se desea detectar/medir con mayor precision
*/
MentorBitMQ135::MentorBitMQ135(uint8_t gas_detection, uint8_t mq_pin = 0): MQ("nc", 5, 10, mq_pin, "nc"){
   _port.gpios[0] = mq_pin;
   _gas_detection = gas_detection;
   MQ.setRegressionMethod(1);
   //MQ.update();
   
   setParameters(_gas_detection);
   
   
}

/*
   Funcion que devuelve el valor de la lectura del sensor MQ en ppm
*/
float MentorBitMQ135::obtenerLecturaMQ(){
   MQ.update();
   float value;
   value = MQ.readSensor();
   return value;
}

/*
   Funcion que permite calibrar el sensor MQ. Se debe utilizar antes de leer el valor
   del sensor MQ ya que si no el valor leido no es real.
*/
void MentorBitMQ135::calibrar(){
   float calcR0 = 0;
   for(int i = 1; i<=10; i ++)
   {
    MQ.update(); // Update data, the arduino will read the voltage from the analog pin
    calcR0 += MQ.calibrate(3.6);
   }
   MQ.setR0(calcR0/10);
}

/*
   Esta función permite cambiar el tipo de gas a detectar (cambiando los valores necesarios)
   para los calculos de las ppm. Tener en cuenta que la presencia de mas de un gas a los que
   el sensor es sensible puede ocasionar que el valor medido no se corresponda con el valor exacto.
*/
void MentorBitMQ135::cambiarDeteccionGas(uint8_t gas_detection){
   _gas_detection = gas_detection;
   setParameters(_gas_detection);
}

/*
   Esta funcion es interna y es utilizada para ajustar los parametros del modelo matematico
   empleado para calcular las pppm
*/
void MentorBitMQ135::setParameters(uint8_t gas_detection){
switch(gas_detection){
   case 0:
      MQ.setA(605.18);
      MQ.setB(-3.937 );
      break;
   case 1:
      MQ.setA(77.255);
      MQ.setB(-3.18);
      break;
   case 2:
      MQ.setA(110.47);
      MQ.setB(-2.862);
      break;
   case 3:
      MQ.setA(44.947);
      MQ.setB(-3.445);
      break;
   case 4:
      MQ.setA(102.2);
      MQ.setB(-2.473);
      break;
   case 5:
      MQ.setA(34.668);
      MQ.setB(-3.369);
      break;
   }
}

void MentorBitMQ135::configPort(const Port& port) {

   _port.type = port.type;
   _port.location = port.location;
   _port.gpios[0] = port.gpios[0];
   _port.gpios[1] = port.gpios[1];

   MQUnifiedsensor temp_mq("nc", 5, 10, _port.gpios[0], "nc");
   temp_mq.setRegressionMethod(1);
   MQ = temp_mq;

}

/************************************  Sensor MQ2  ************************************/

/*
   Constructor para el uso de la clase MentorBitMQ2. Se deben indicar los siguientes 
   parametros:
      - Pin del microcontrolador al que esta conectado el sensor MQ2
      - Gas que se desea detectar/medir con mayor precision
*/
MentorBitMQ2::MentorBitMQ2(uint8_t gas_detection, uint8_t mq_pin = 0): MQ("nc", 5, 10, mq_pin, "nc"){
   _port.gpios[0] = mq_pin;
   _gas_detection = gas_detection;
   MQ.setRegressionMethod(1);
   setParameters(_gas_detection);
}

/*
   Funcion que devuelve el valor de la lectura del sensor MQ en ppm
*/
float MentorBitMQ2::obtenerLecturaMQ(){
      MQ.update();
      float value;
      value = MQ.readSensor();
      return value;

}

/*
   Funcion que permite calibrar el sensor MQ. Se debe utilizar antes de leer el valor
   del sensor MQ ya que si no el valor leido no es real.
*/
void MentorBitMQ2::calibrar(){
   float calcR0 = 0;
   for(int i = 1; i<=10; i ++)
   {
    MQ.update(); // Update data, the arduino will read the voltage from the analog pin
    calcR0 += MQ.calibrate(9.83);
   }
   MQ.setR0(calcR0/10);
}

/*
   Esta función permite cambiar el tipo de gas a detectar (cambiando los valores necesarios)
   para los calculos de las ppm. Tener en cuenta que la presencia de mas de un gas a los que
   el sensor es sensible puede ocasionar que el valor medido no se corresponda con el valor exacto.
*/
void MentorBitMQ2::cambiarDeteccionGas(uint8_t gas_detection){
   _gas_detection = gas_detection;
   setParameters(_gas_detection);
}

/*
   Esta funcion es interna y es utilizada para ajustar los parametros del modelo matematico
   empleado para calcular las pppm
*/
void MentorBitMQ2::setParameters(uint8_t gas_detection){
switch(gas_detection){
   case 0:
      MQ.setA(987.99);
      MQ.setB(-2.162 );
      break;
   case 1:
      MQ.setA(574.25);
      MQ.setB(-2.222);
      break;
   case 2:
      MQ.setA(36974);
      MQ.setB(-3.109);
      break;
   case 3:
      MQ.setA(3616.1);
      MQ.setB(-2.675);
      break;
   case 4:
      MQ.setA(658.71);
      MQ.setB(-2.168);
      break;
   }
}

void MentorBitMQ2::configPort(const Port& port) {

   _port.type = port.type;
   _port.location = port.location;
   _port.gpios[0] = port.gpios[0];
   _port.gpios[1] = port.gpios[1];

   MQUnifiedsensor temp_mq("nc", 5, 10, _port.gpios[0], "nc");
   temp_mq.setRegressionMethod(1);
   MQ = temp_mq;

}

/************************************  Sensor MQ3  ************************************/

/*
   Constructor para el uso de la clase MentorBitMQ3. Se deben indicar los siguientes 
   parametros:
      - Pin del microcontrolador al que esta conectado el sensor MQ3
      - Gas que se desea detectar/medir con mayor precision
*/
MentorBitMQ3::MentorBitMQ3(uint8_t gas_detection, uint8_t mq_pin = 0): MQ("nc", 5, 10, mq_pin, "nc"){
   _port.gpios[0] = mq_pin;
   _gas_detection = gas_detection;
   MQ.setRegressionMethod(1);
   setParameters(_gas_detection);
}

/*
   Funcion que devuelve el valor de la lectura del sensor MQ en ppm
*/
float MentorBitMQ3::obtenerLecturaMQ(){
      MQ.update();
      float value;
      value = MQ.readSensor();
      return value;

}

/*
   Funcion que permite calibrar el sensor MQ. Se debe utilizar antes de leer el valor
   del sensor MQ ya que si no el valor leido no es real.
*/
void MentorBitMQ3::calibrar(){
   float calcR0 = 0;
   for(int i = 1; i<=10; i ++)
   {
    MQ.update(); // Update data, the arduino will read the voltage from the analog pin
    calcR0 += MQ.calibrate(60);
   }
   MQ.setR0(calcR0/10);
}

/*
   Esta función permite cambiar el tipo de gas a detectar (cambiando los valores necesarios)
   para los calculos de las ppm. Tener en cuenta que la presencia de mas de un gas a los que
   el sensor es sensible puede ocasionar que el valor medido no se corresponda con el valor exacto.
*/
void MentorBitMQ3::cambiarDeteccionGas(uint8_t gas_detection){
   _gas_detection = gas_detection;
   setParameters(_gas_detection);
}

/*
   Esta funcion es interna y es utilizada para ajustar los parametros del modelo matematico
   empleado para calcular las pppm
*/
void MentorBitMQ3::setParameters(uint8_t gas_detection){
switch(gas_detection){
   case 0:
      MQ.setA(44771);
      MQ.setB(-3.245);
      break;
   case 1:
      MQ.setA(2*10000000000000000000000000000000);
      MQ.setB(19.01);
      break;
   case 2:
      MQ.setA(521853);
      MQ.setB(-3.821);
      break;
   case 3:
      MQ.setA(0.3934);
      MQ.setB(-1.504);
      break;
   case 4:
      MQ.setA(4.8387);
      MQ.setB(-2.68);
      break;
   case 5:
      MQ.setA(7585.3);
      MQ.setB(-2.849);
      break;
   }
}

void MentorBitMQ3::configPort(const Port& port) {

   _port.type = port.type;
   _port.location = port.location;
   _port.gpios[0] = port.gpios[0];
   _port.gpios[1] = port.gpios[1];

   MQUnifiedsensor temp_mq("nc", 5, 10, _port.gpios[0], "nc");
   temp_mq.setRegressionMethod(1);
   MQ = temp_mq;

}

/************************************  Sensor MQ4  ************************************/

/*
   Constructor para el uso de la clase MentorBitMQ4. Se deben indicar los siguientes 
   parametros:
      - Pin del microcontrolador al que esta conectado el sensor MQ4
      - Gas que se desea detectar/medir con mayor precision
*/
MentorBitMQ4::MentorBitMQ4(uint8_t gas_detection, uint8_t mq_pin = 0): MQ("nc", 5, 10, mq_pin, "nc"){
   _port.gpios[0] = mq_pin;
   _gas_detection = gas_detection;
   MQ.setRegressionMethod(1);
   setParameters(_gas_detection);
}

/*
   Funcion que devuelve el valor de la lectura del sensor MQ en ppm
*/
float MentorBitMQ4::obtenerLecturaMQ(){
      MQ.update();
      float value;
      value = MQ.readSensor();
      return value;

}

/*
   Funcion que permite calibrar el sensor MQ. Se debe utilizar antes de leer el valor
   del sensor MQ ya que si no el valor leido no es real.
*/
void MentorBitMQ4::calibrar(){
   float calcR0 = 0;
   for(int i = 1; i<=10; i ++)
   {
    MQ.update(); // Update data, the arduino will read the voltage from the analog pin
    calcR0 += MQ.calibrate(4.4);
   }
   MQ.setR0(calcR0/10);
}

/*
   Esta función permite cambiar el tipo de gas a detectar (cambiando los valores necesarios)
   para los calculos de las ppm. Tener en cuenta que la presencia de mas de un gas a los que
   el sensor es sensible puede ocasionar que el valor medido no se corresponda con el valor exacto.
*/
void MentorBitMQ4::cambiarDeteccionGas(uint8_t gas_detection){
   _gas_detection = gas_detection;
   setParameters(_gas_detection);
}

/*
   Esta funcion es interna y es utilizada para ajustar los parametros del modelo matematico
   empleado para calcular las pppm
*/
void MentorBitMQ4::setParameters(uint8_t gas_detection){
switch(gas_detection){
   case 0:
      MQ.setA(3811.9);
      MQ.setB(-3.113);
      break;
   case 1:
      MQ.setA(1012.7);
      MQ.setB(-2.786);
      break;
   case 2:
      MQ.setA(200000000000000);
      MQ.setB(-19.05);
      break;
   case 3:
      MQ.setA(60000000000);
      MQ.setB(-14.01);
      break;
   case 4:
      MQ.setA(30000000);
      MQ.setB(-8.308);
      break;
   }
}

void MentorBitMQ4::configPort(const Port& port) {

   _port.type = port.type;
   _port.location = port.location;
   _port.gpios[0] = port.gpios[0];
   _port.gpios[1] = port.gpios[1];

   MQUnifiedsensor temp_mq("nc", 5, 10, _port.gpios[0], "nc");
   temp_mq.setRegressionMethod(1);
   MQ = temp_mq;

}

/************************************  Sensor MQ5  ************************************/

/*
   Constructor para el uso de la clase MentorBitMQ5. Se deben indicar los siguientes 
   parametros:
      - Pin del microcontrolador al que esta conectado el sensor MQ5
      - Gas que se desea detectar/medir con mayor precision
*/
MentorBitMQ5::MentorBitMQ5(uint8_t gas_detection, uint8_t mq_pin = 0): MQ("nc", 5, 10, mq_pin, "nc"){
   _port.gpios[0] = mq_pin;
   _gas_detection = gas_detection;
   MQ.setRegressionMethod(1);
   setParameters(_gas_detection);
}

/*
   Funcion que devuelve el valor de la lectura del sensor MQ en ppm
*/
float MentorBitMQ5::obtenerLecturaMQ(){
      MQ.update();
      float value;
      value = MQ.readSensor();
      return value;

}

/*
   Funcion que permite calibrar el sensor MQ. Se debe utilizar antes de leer el valor
   del sensor MQ ya que si no el valor leido no es real.
*/
void MentorBitMQ5::calibrar(){
   float calcR0 = 0;
   for(int i = 1; i<=10; i ++)
   {
    MQ.update(); // Update data, the arduino will read the voltage from the analog pin
    calcR0 += MQ.calibrate(6.5);
   }
   MQ.setR0(calcR0/10);
}

/*
   Esta función permite cambiar el tipo de gas a detectar (cambiando los valores necesarios)
   para los calculos de las ppm. Tener en cuenta que la presencia de mas de un gas a los que
   el sensor es sensible puede ocasionar que el valor medido no se corresponda con el valor exacto.
*/
void MentorBitMQ5::cambiarDeteccionGas(uint8_t gas_detection){
   _gas_detection = gas_detection;
   setParameters(_gas_detection);
}

/*
   Esta funcion es interna y es utilizada para ajustar los parametros del modelo matematico
   empleado para calcular las pppm
*/
void MentorBitMQ5::setParameters(uint8_t gas_detection){
switch(gas_detection){
   case 0:
      MQ.setA(1163.8);
      MQ.setB(-3.874);
      break;
   case 1:
      MQ.setA(80.897);
      MQ.setB(-2.431);
      break;
   case 2:
      MQ.setA(177.65);
      MQ.setB(-2.56);
      break;
   case 3:
      MQ.setA(491204);
      MQ.setB(-5.826);
      break;
   case 4:
      MQ.setA(97124);
      MQ.setB(-4.918);
      break;
   }
}

void MentorBitMQ5::configPort(const Port& port) {

   _port.type = port.type;
   _port.location = port.location;
   _port.gpios[0] = port.gpios[0];
   _port.gpios[1] = port.gpios[1];

   MQUnifiedsensor temp_mq("nc", 5, 10, _port.gpios[0], "nc");
   temp_mq.setRegressionMethod(1);
   MQ = temp_mq;

}

/************************************  Sensor MQ6  ************************************/

/*
   Constructor para el uso de la clase MentorBitMQ6. Se deben indicar los siguientes 
   parametros:
      - Pin del microcontrolador al que esta conectado el sensor MQ6
      - Gas que se desea detectar/medir con mayor precision
*/
MentorBitMQ6::MentorBitMQ6(uint8_t gas_detection, uint8_t mq_pin = 0): MQ("nc", 5, 10, mq_pin, "nc"){
   _port.gpios[0] = mq_pin;
   _gas_detection = gas_detection;
   MQ.setRegressionMethod(1);
   setParameters(_gas_detection);
}

/*
   Funcion que devuelve el valor de la lectura del sensor MQ en ppm
*/
float MentorBitMQ6::obtenerLecturaMQ(){
      MQ.update();
      float value;
      value = MQ.readSensor();
      return value;

}

/*
   Funcion que permite calibrar el sensor MQ. Se debe utilizar antes de leer el valor
   del sensor MQ ya que si no el valor leido no es real.
*/
void MentorBitMQ6::calibrar(){
   float calcR0 = 0;
   for(int i = 1; i<=10; i ++)
   {
    MQ.update(); // Update data, the arduino will read the voltage from the analog pin
    calcR0 += MQ.calibrate(10);
   }
   MQ.setR0(calcR0/10);
}

/*
   Esta función permite cambiar el tipo de gas a detectar (cambiando los valores necesarios)
   para los calculos de las ppm. Tener en cuenta que la presencia de mas de un gas a los que
   el sensor es sensible puede ocasionar que el valor medido no se corresponda con el valor exacto.
*/
void MentorBitMQ6::cambiarDeteccionGas(uint8_t gas_detection){
   _gas_detection = gas_detection;
   setParameters(_gas_detection);
}

/*
   Esta funcion es interna y es utilizada para ajustar los parametros del modelo matematico
   empleado para calcular las pppm
*/
void MentorBitMQ6::setParameters(uint8_t gas_detection){
switch(gas_detection){
   case 0:
      MQ.setA(88158);
      MQ.setB(-3.597);
      break;
   case 1:
      MQ.setA(1009.2);
      MQ.setB(-2.35);
      break;
   case 2:
      MQ.setA(2127.2);
      MQ.setB(-2.526);
      break;
   case 3:
      MQ.setA(1000000000000000);
      MQ.setB(-13.5);
      break;
   case 4:
      MQ.setA(50000000);
      MQ.setB(-6.017);
      break;
   }
}

void MentorBitMQ6::configPort(const Port& port) {

   _port.type = port.type;
   _port.location = port.location;
   _port.gpios[0] = port.gpios[0];
   _port.gpios[1] = port.gpios[1];

   MQUnifiedsensor temp_mq("nc", 5, 10, _port.gpios[0], "nc");
   temp_mq.setRegressionMethod(1);
   MQ = temp_mq;

}

/************************************  Sensor MQ7  ************************************/

/*
   Constructor para el uso de la clase MentorBitMQ7. Se deben indicar los siguientes 
   parametros:
      - Pin del microcontrolador al que esta conectado el sensor MQ7
      - Gas que se desea detectar/medir con mayor precision
*/
MentorBitMQ7::MentorBitMQ7(uint8_t gas_detection, uint8_t mq_pin = 0): MQ("nc", 5, 10, mq_pin, "nc"){
   _port.gpios[0] = mq_pin;
   _gas_detection = gas_detection;
   MQ.setRegressionMethod(1);
   setParameters(_gas_detection);
}

/*
   Funcion que devuelve el valor de la lectura del sensor MQ en ppm
*/
float MentorBitMQ7::obtenerLecturaMQ(){
      MQ.update();
      float value;
      value = MQ.readSensor();
      return value;

}

/*
   Funcion que permite calibrar el sensor MQ. Se debe utilizar antes de leer el valor
   del sensor MQ ya que si no el valor leido no es real.
*/
void MentorBitMQ7::calibrar(){
   float calcR0 = 0;
   for(int i = 1; i<=10; i ++)
   {
    MQ.update(); // Update data, the arduino will read the voltage from the analog pin
    calcR0 += MQ.calibrate(27.5);
   }
   MQ.setR0(calcR0/10);
}

/*
   Esta función permite cambiar el tipo de gas a detectar (cambiando los valores necesarios)
   para los calculos de las ppm. Tener en cuenta que la presencia de mas de un gas a los que
   el sensor es sensible puede ocasionar que el valor medido no se corresponda con el valor exacto.
*/
void MentorBitMQ7::cambiarDeteccionGas(uint8_t gas_detection){
   _gas_detection = gas_detection;
   setParameters(_gas_detection);
}

/*
   Esta funcion es interna y es utilizada para ajustar los parametros del modelo matematico
   empleado para calcular las pppm
*/
void MentorBitMQ7::setParameters(uint8_t gas_detection){
switch(gas_detection){
   case 0:
      MQ.setA(69.014);
      MQ.setB(-1.374);
      break;
   case 1:
      MQ.setA(700000000);
      MQ.setB(-7.703);
      break;
   case 2:
      MQ.setA(60000000000000);
      MQ.setB(-10.54);
      break;
   case 3:
      MQ.setA(99.042);
      MQ.setB(-1.518);
      break;
   case 4:
      MQ.setA(40000000000000000);
      MQ.setB(-12.35);
      break;
   }
}

void MentorBitMQ7::configPort(const Port& port) {

   _port.type = port.type;
   _port.location = port.location;
   _port.gpios[0] = port.gpios[0];
   _port.gpios[1] = port.gpios[1];

   MQUnifiedsensor temp_mq("nc", 5, 10, _port.gpios[0], "nc");
   temp_mq.setRegressionMethod(1);
   MQ = temp_mq;

}

/************************************  Sensor MQ8  ************************************/

/*
   Constructor para el uso de la clase MentorBitMQ8. Se deben indicar los siguientes 
   parametros:
      - Pin del microcontrolador al que esta conectado el sensor MQ8
      - Gas que se desea detectar/medir con mayor precision
*/
MentorBitMQ8::MentorBitMQ8(uint8_t gas_detection, uint8_t mq_pin = 0): MQ("nc", 5, 10, mq_pin, "nc"){
   _port.gpios[0] = mq_pin;
   _gas_detection = gas_detection;
   MQ.setRegressionMethod(1);
   setParameters(_gas_detection);
}

/*
   Funcion que devuelve el valor de la lectura del sensor MQ en ppm
*/
float MentorBitMQ8::obtenerLecturaMQ(){
      MQ.update();
      float value;
      value = MQ.readSensor();
      return value;

}

/*
   Funcion que permite calibrar el sensor MQ. Se debe utilizar antes de leer el valor
   del sensor MQ ya que si no el valor leido no es real.
*/
void MentorBitMQ8::calibrar(){
   float calcR0 = 0;
   for(int i = 1; i<=10; i ++)
   {
    MQ.update(); // Update data, the arduino will read the voltage from the analog pin
    calcR0 += MQ.calibrate(70);
   }
   MQ.setR0(calcR0/10);
}

/*
   Esta función permite cambiar el tipo de gas a detectar (cambiando los valores necesarios)
   para los calculos de las ppm. Tener en cuenta que la presencia de mas de un gas a los que
   el sensor es sensible puede ocasionar que el valor medido no se corresponda con el valor exacto.
*/
void MentorBitMQ8::cambiarDeteccionGas(uint8_t gas_detection){
   _gas_detection = gas_detection;
   setParameters(_gas_detection);
}

/*
   Esta funcion es interna y es utilizada para ajustar los parametros del modelo matematico
   empleado para calcular las pppm
*/
void MentorBitMQ8::setParameters(uint8_t gas_detection){
switch(gas_detection){
   case 0:
      MQ.setA(976.97);
      MQ.setB(-0.688);
      break;
   case 1:
      MQ.setA(10000000);
      MQ.setB(-3.123);
      break;
   case 2:
      MQ.setA(80000000000000);
      MQ.setB(-6.666);
      break;
   case 3:
      MQ.setA(2000000000000000000);
      MQ.setB(-8.074);
      break;
   case 4:
      MQ.setA(76101);
      MQ.setB(-1.86);
      break;
   }
}

void MentorBitMQ8::configPort(const Port& port) {

   _port.type = port.type;
   _port.location = port.location;
   _port.gpios[0] = port.gpios[0];
   _port.gpios[1] = port.gpios[1];

   MQUnifiedsensor temp_mq("nc", 5, 10, _port.gpios[0], "nc");
   temp_mq.setRegressionMethod(1);
   MQ = temp_mq;

}

/************************************  Sensor MQ9  ************************************/

/*
   Constructor para el uso de la clase MentorBitMQ9. Se deben indicar los siguientes 
   parametros:
      - Pin del microcontrolador al que esta conectado el sensor MQ9
      - Gas que se desea detectar/medir con mayor precision
*/
MentorBitMQ9::MentorBitMQ9(uint8_t gas_detection, uint8_t mq_pin = 0): MQ("nc", 5, 10, mq_pin, "nc"){
   _port.gpios[0] = mq_pin;
   _gas_detection = gas_detection;
   MQ.setRegressionMethod(1);
   setParameters(_gas_detection);
}

/*
   Funcion que devuelve el valor de la lectura del sensor MQ en ppm
*/
float MentorBitMQ9::obtenerLecturaMQ(){
      MQ.update();
      float value;
      value = MQ.readSensor();
      return value;

}

/*
   Funcion que permite calibrar el sensor MQ. Se debe utilizar antes de leer el valor
   del sensor MQ ya que si no el valor leido no es real.
*/
void MentorBitMQ9::calibrar(){

   float calcR0 = 0;
   for(int i = 1; i<=10; i ++)
   {
    MQ.update(); // Update data, the arduino will read the voltage from the analog pin
    calcR0 += MQ.calibrate(9.6);
   }
   MQ.setR0(calcR0/10);
}

/*
   Esta función permite cambiar el tipo de gas a detectar (cambiando los valores necesarios)
   para los calculos de las ppm. Tener en cuenta que la presencia de mas de un gas a los que
   el sensor es sensible puede ocasionar que el valor medido no se corresponda con el valor exacto.
*/
void MentorBitMQ9::cambiarDeteccionGas(uint8_t gas_detection){
   _gas_detection = gas_detection;
   setParameters(_gas_detection);
}

/*
   Esta funcion es interna y es utilizada para ajustar los parametros del modelo matematico
   empleado para calcular las pppm
*/
void MentorBitMQ9::setParameters(uint8_t gas_detection){
switch(gas_detection){
   case 0:
      MQ.setA(1000.5);
      MQ.setB(-2.186);
      break;
   case 1:
      MQ.setA(4269.6);
      MQ.setB(-2.648);
      break;
   case 2:
      MQ.setA(599.65);
      MQ.setB(-2.244);
      break;
   }
}

void MentorBitMQ9::configPort(const Port& port) {

   _port.type = port.type;
   _port.location = port.location;
   _port.gpios[0] = port.gpios[0];
   _port.gpios[1] = port.gpios[1];

   MQUnifiedsensor temp_mq("nc", 5, 10, _port.gpios[0], "nc");
   temp_mq.setRegressionMethod(1);
   MQ = temp_mq;

}
