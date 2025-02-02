int latchPin = 8; // Pino conectado ao pino 12 do 74HC595 (Latch) 
int clockPin = 12; // Pino conectado ao pino 11 do 74HC595 (Clock) 
int dataPin = 11; // Pino conectado ao pino 14 do 74HC595 (Data) 

void setup() { 
// define os pinos como saída 
  pinMode(latchPin, OUTPUT); 
  pinMode(clockPin, OUTPUT); 
  pinMode(dataPin, OUTPUT); 
} 
void loop() { 
// conta de 0 a 255 
  for (int i = 0; i < 256; i++) { 
// define latchPin como LOW, para permitir o fluxo de dados 
  digitalWrite(latchPin, LOW); 
  shiftOut(i); 
// define latchPin como HIGH, para fechar e enviar os dados 
  digitalWrite(latchPin, HIGH); 
  delay(1000); 
  } 
} 
void shiftOut(byte dataOut) { 
// Desloca 8 bits, com o bit menos significativo (LSB) sendo deslocado primeiro, no extremo 
// ascendente do clock 
boolean pinState; 
  digitalWrite(dataPin, LOW); // deixa o registrador de deslocamento pronto para enviar dados 
  digitalWrite(clockPin, LOW); 
  for (int i=0; i<=7; i++) { // para cada bit em dataOut, envie um bit 
  digitalWrite(clockPin, LOW); // define clockPin como LOW antes de enviar o bit 
  // se o valor de DataOut e (E lógico) de uma máscara de bits 
  // forem verdadeiros, defina pinState como 1 (HIGH) 
  if (dataOut & (1<<i)) { 
  pinState = HIGH; 
} else { 
  pinState = LOW; 
}
// define dataPin como HIGH ou LOW, dependendo de pinState
  digitalWrite(dataPin, pinState); // envia o bit no extremo ascendente do clock
  digitalWrite(clockPin, HIGH);
}
  digitalWrite(clockPin, LOW); // interrompe o deslocamento de dados
}