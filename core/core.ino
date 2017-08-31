
#include "CCMotor.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
Servo servo;

#define CE_PIN 9
#define CSN_PIN 10
//Se definen las constantes para cada motor y el pin en donde estan conectados
//#define led 13 
#define a1 3
#define a2 4
#define a3 17
#define a4 16


byte direccion[4] = {'f', 'u', 'n', 'k'};
RF24 receptor(CE_PIN, CSN_PIN);

char dato[3];
char input;
//Instancia de los objetos
CCMotor motor(a1, a2);
CCMotor motor2(a3, a4);

void setup() {
  // put your setup code here, to run once:
  receptor.begin();
  Serial.begin(115200);
  //pinMode(led, OUTPUT);
  //digitalWrite(led, HIGH);
  receptor.openReadingPipe(1, direccion);
  receptor.startListening();
  
  /*Se establecen los parametros iniciales para cada par de motores
   * aceleracion, velocidad inicial y velocidad final, respectivamente
   */
   motor.SetParams(4,100,255);
   motor2.SetParams(4,100,255);
   servo.attach(20);
  
   

}


void loop() {
   //put your main code here, to run repeatedly
   //Se lee la entrada del teclado
   if(receptor.available()){
    receptor.read(dato, sizeof(dato));
    Serial.print("El estado es: ");
    Serial.println(dato[0]);
   }
   else{
    Serial.println("No hay nada");
   }
   
//   if(Serial.available()){
//    input = Serial.read();
//    
//   }

   switch(dato[0]){
    case 'w':
      motor.Gira('2'); 
      motor2.Gira('2');
      break;
      
    case 's':
      motor.Gira('1'); 
      motor2.Gira('1');
      break;

      case 'a':     
      motor.Gira('2'); 
      motor2.Gira('1');
      break;

    case 'd':
      motor.Gira('1'); 
      motor2.Gira('2');
    break;


    case '1':
      servo.write(70);
    break;
    case '2':
      servo.write(90);
    break;
    case '3':
      servo.write(110);
    break;
    case '4':
      servo.write(130);
    break;
    case '5':
      servo.write(150);
    break;
    

        
    default:
      motor.parar(); 
      motor2.parar();
      break;
    
    
   }
   
}


