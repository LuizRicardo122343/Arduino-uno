#include <Arduino.h>

int ledPin = 10;

void setup() {
  // executa uma vez quando o sketch inicia
  Serial.begin(9600); // inicia o monitor serial
// define o pino como saida
  pinMode(ledPin, OUTPUT);

}
//executa repeitdas vezes
void loop() {
   for(int x=0; x<3; x++){
    digitalWrite(ledPin,HIGH);//acendeo Led
    delay(150);//espera 150ms
    digitalWrite(ledPin,LOW);//apagao led
    delay(100);//espera 100ms

}
//espera 100 msparamarcarointervaloentreasletras
    delay(100);
    //3 traços
    for(int x=0; x<3; x++){
      digitalWrite(ledPin,HIGH);//acendeo led
      delay(400);//espera400ms
      digitalWrite(ledPin,LOW);//apagaoled
      delay(100);//espera100ms
}

//espera100msparamarcarointervaloentreasletras
    delay(100);//3pontos
    for(int x=0; x<3; x++){
      digitalWrite(ledPin,HIGH);//acendeo led
      delay(150);//espera400ms
      digitalWrite(ledPin,LOW);//apagao led
      delay(100);//espera100ms
      }
      //espera5segundosantesderepetiroSOS
      delay(5000);
}
