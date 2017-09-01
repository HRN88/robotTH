#include <CCmotor.h>

//Se incluyen las librerias necesarias
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>


//**************Variables para la funcion Goservo*******************
float current_pos;
//Sensibilidad
float easing = 0.05;
//Arreglo con los valores objetivo de cada pocision
float target_pos[5] = {600, 960, 1320, 1680, 2100}   ;
//Guarda la diferencia
float diff;

//******************************************************************

//Constantes para la comunicacion 
#define CE_PIN 9
#define CSN_PIN 10

//Se definen las constantes para cada motor y el pin en donde estan conectados 
#define a1 3
#define a2 4
#define a3 17
#define a4 16

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

//Instancia de servomotor
Servo servo;

void Goservo(int i);
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
   motor.SetParams(4,100,255);
   motor2.SetParams(4,100,255);

   //Se especifica el pin de control para el servomotor
   servo.attach(20);
   Goservo(4);
   delay(100);
}


void loop() {
   //put your main code here, to run repeatedly
   
   //Se recibe el dato por el bufer de la comunicacion inalambrica
   if(receptor.available()){
    receptor.read(dato, sizeof(dato));
    Serial.print("El estado es: ");
    Serial.println(dato[0]);
   }
   else{
    Serial.println("No hay nada");
   }

 //*********************Para el caso de prubeas por cable usb*********************
 //Se recibe el dato del teclado
 
//   if(Serial.available()){
//    input = Serial.read();
//    
//   }
//********************************************************************************

   switch(dato[0]){

    //****************Estados de Giro*****************
      case 'w':
      //Adelante
        motor.Gira('2'); 
        motor2.Gira('2');
      break;
      
      case 's':
      //Atras
        motor.Gira('1'); 
        motor2.Gira('1');
      break;

      case 'a':  
      //Izquierda   
        motor.Gira('2'); 
        motor2.Gira('1');
      break;

      case 'd':
      //Derecha
        motor.Gira('1'); 
        motor2.Gira('2');
      break;
  //******************************************************

  //Estados para el servomotor, los valores dentro
  //De servo.write representan los angulos
    case '1':
      Goservo(4);
    break;
    case '2':
      Goservo(3);    
    break;
    case '3':
      Goservo(2);
    break;
    case '4':
      Goservo(1);
    break;
    case '5':
      Goservo(0);
    break;
    
  //Caso default, el sistema permanece inmovil   
    default:
      motor.parar(); 
      motor2.parar();
      break;
    
    
   }
   
}

void Goservo(int i){
  //Funcion para mover el servomotor a determinada pocision
  diff = target_pos[i] - current_pos;
  if(diff != 0){
    current_pos += diff*easing;
  }
  servo.writeMicroseconds(current_pos);
  Serial.println("se ha movido el servo");
  delay(20);
}
  



