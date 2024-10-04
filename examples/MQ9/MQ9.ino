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
      Este sketch es un ejemplo de como medir el valor de GLP en ppm usando un
      sensor MQ para mentorBit. 
*/

// Se incluye la libreria MentorBitMQ.h
#include <MentorBitMQ.h>

// Se define el pin al cual se va a conectar el sensor MQ
#define MQ_PIN A4 

// Se crea el objeto mq9
/*
    El sensor MQ puede medir otros tipos de gases diferentes. A continuacion se muestra la sentencia:

    mq9.glp -> mide las ppm de glp
    mq9.ch4 -> mide las ppm de ch4
    mq9.co -> mide las ppm de co

    El sensor es sensible a todos los tipos de gases mostrados arriba. Si la concentracion de uno de ellos
    cambia producirá un cambio en la medida, que falsificará, en mayor o menor medida (dependiendo de la cantidad
    y gas presente) la medida de ppm del gas deseado
    

*/
MentorBitMQ9 mq9(MQ_PIN, mq9.glp);


void setup(){
    // Se inicializa el monitor serial para mostrar los valores del sensor
    Serial.begin(9600);
    // Se calibra el sensor para obtener una medida fiable
    mq9.calibrar();
}

void loop(){
    // Se muestra por pantalla el valor de ppm obtenido del sensor
    Serial.println("GLP:   " + String(mq9.obtenerLecturaMQ()) + " ppm");
    // Pequeño delay para no llenar el monitor serial
    delay(1000);
}

