
/*******************************************************/
/*************Version con motor a pasos*****************/
/*******************************************************/

//Se incluyen las librerias necesarias
#include <CCmotor.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <AccelStepper.h>
#include <MultiStepper.h>

//Constantes para la comunicacion 
#define CE_PIN 9
#define CSN_PIN 10

//Se definen las constantes para cada motor y el pin en donde estan conectados 
#define a1 3
#define a2 4
#define a3 17
#define a4 16

//************Pines para el control del motor superior***********
#define p1 23
#define p2 22
#define p3 20
#define p4 6


//Se guarda la direccion que se usa para establecer la comunicacione entre ambos
//tranceprores por especificacion de la documentacion se  usa un vector
byte direccion[4] = {'f', 'u', 'n', 'k'};
//Vector para almacenar el caracter que se recibe
char dato[3];
//Variable para recibir entrada de teclado (Solo aplica para pruebas por cable USB)
char input;


//**********Instancia de los objetos***********
//Instancias de motores
CCMotor motor(a1, a2);
CCMotor motor2(a3, a4);

//Instancia de modulo NRF24L01
RF24 receptor(CE_PIN, CSN_PIN);

//Se crea una instancia del motor a pasos, el numero 4, indica que se
//esta trabajando en modo Full4Wire
AccelStepper motorp(4, p4, p2, p3, p1);

void setup() {
  // put your setup code here, to run once:
  //Se inicia la comuicacion con el modulo inalambrico
  receptor.begin();
  receptor.openReadingPipe(1, direccion);
  receptor.startListening();
  
  //Se inicia la comunicacion UART
  Serial.begin(115200);  
  
  /*Se establecen los parametros iniciales para cada par de motores
   * aceleracion, velocidad inicial y velocidad final, respectivamente
   */
   motor.SetParams(4,90,255);
   motor2.SetParams(4,90,255);  
   
  //Establece la velocidad maxima del motor a pasos
   motorp.setMaxSpeed(200);
  //Establece la velocidad inicial
   motorp.setSpeed(20);
  //Establece la aceleracion
   motorp.setAcceleration(80);
}

//Funcion para mover el motor a pasos
void buclemotor();

void loop() {
   //put your main code here, to run repeatedly
   
   //Se recibe el dato por el bufer de la comunicacion inalambrica
//   if(receptor.available()){
//    receptor.read(dato, sizeof(dato));
//    Serial.print("El estado es: ");
//    Serial.println(dato[0]);
//   }
//   else{
//    Serial.println("No hay nada");
//   }

 //*********************Para el caso de prubeas por cable usb*********************
 //Se recibe el dato del teclado
 
   if(Serial.available()){
    input = Serial.read();
    
   }
//********************************************************************************

   switch(input){

    //****************Estados de Giro*****************
      case 'w':
      //Adelante
        motor.Gira('1'); 
        motor2.Gira('1');
      break;
      
      case 's':
      //Atras
        motor.Gira('2'); 
        motor2.Gira('2');
      break;

      case 'a':  
      //Izquierda   
        motor.Gira('1'); 
        motor2.Gira('2');
      break;

      case 'd':
      //Derecha
        motor.Gira('2'); 
        motor2.Gira('1');
      break;
  //******************************************************

      case '1':
      motorp.move(100);
      buclemotor();
      break;

      case '2':
      motorp.move(-100);
      buclemotor();
      break;
      

       
        
    
  //Caso default, el sistema permanece inmovil   
    default:
      motor.parar(); 
      motor2.parar();
      break;   
    
   }
   
}

void buclemotor(){
  do{
      motorp.run();
  }while(motorp.distanceToGo() != 0);
      motorp.stop();
      motorp.setCurrentPosition(0);
}
  



