#include <nRF24L01.h>
#include <SPI.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

#define CE_PIN 9
#define CSN_PIN 10

byte direccion[5] = {'f','u','n','k'};

RF24 transmisor(CE_PIN, CSN_PIN);
char datos[3];

void setup() {
  // put your setup code here, to run once:
  transmisor.begin();
  Serial.begin(115200);
  transmisor.openWritingPipe(direccion);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    datos[0] = Serial.read();
  }
  
  
  
  Serial.println(datos[0]);
  bool ok = transmisor.write(datos, sizeof(datos));
  if(ok){
    Serial.println("Dato enviado");
  }
  else{
    Serial.println("No se pudo enviar");
  }
  delay(100);

}
