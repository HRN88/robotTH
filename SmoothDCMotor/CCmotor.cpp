#include "CCmotor.h"
#include <Arduino.h>

CCMotor::CCMotor(int pin1, int pin2){
  ctrla = pin1;
  ctrlb = pin2;
  
}
void CCMotor::SetAcel(int acel){
  aceleracion = acel;
}

void CCMotor::SetVini(int vini){
  velini = vini;
  velact = vini;
}

void CCMotor::SetVmax(int vmax){
  velmax = vmax;
}

void CCMotor::SetParams(int acel, int vini, int vmax){
  aceleracion = acel;
  velini = vini;
  velact = vini;
  velmax = vmax;
}

void CCMotor::GetAllParams(){
  Serial.print("Velocidad actual: ");
  Serial.print(velini);
  Serial.print(" Velocidad maxima: ");
  Serial.print(velmax);
  Serial.print(" Aceleracion: ");
  Serial.print(aceleracion);
  Serial.print(" Pines de conexion: ");
  Serial.print(ctrla);
  Serial.print(" y ");
  Serial.println(ctrlb);
}

void CCMotor::GetVelocidadActual(){
  Serial.println(velini);

}

void CCMotor::acelera(){
  tiempoActual = millis();
  if((tiempoActual - tiempoAnterior) >= 50){
    tiempoAnterior = tiempoActual;
    if(velini <= velmax){
    velini = velini + aceleracion*tiempo;
    tiempo ++;
    }
    Serial.println(velini);
  }

  
  
 
}

void CCMotor::Gira(char direccion){
  anteriorMotor = direccion;
  if(anteriorMotor != actualMotor){
    velini = velact;
    tiempo=0;
  }
  switch(direccion){
    
    case '1':
      actualMotor = '1';
      acelera();
      analogWrite(ctrla, velini);
      analogWrite(ctrlb, 0);
      break;
      
    case '2':
      actualMotor = '2';
      acelera();
      analogWrite(ctrla, 0);
      analogWrite(ctrlb, velini);
      break;
      
    default:
      parar(); 
      parar();
      break;
      
      }
 
}

void CCMotor::parar(){
  tiempo = 0;
  analogWrite(ctrla, 0);
  analogWrite(ctrlb, 0);
}


