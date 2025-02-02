// Projeto 6 
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
  for (int i = 0; i < 256; i++) { //conta de 0 a 255 
  digitalWrite(latchPin, LOW); //define latchPin como LOW, para permitir o fluxo de dados 
  shiftOut(i); 
  shiftOut(255-i); 
// define latchPin como HIGH, para fechar e enviar os dados 
  digitalWrite(latchPin, HIGH); 
  delay(250); 
} 
}
void shiftOut(byte dataOut) { 
  boolean pinState; // Desloque 8 bits, com o bit menos significativos (LSB) sendo deslocado 
// primeiro, no extremo ascendente do clock 
  digitalWrite(dataPin, LOW); // libera o registrador de deslocamento, deixando-o pronto 
// para enviar dados 
  digitalWrite(clockPin, LOW); 
  for (int i=0; i<=7; i++) { // para cada bit em dataOut, envie um bit 
  digitalWrite(clockPin, LOW); // define clockPin como LOW, antes de enviar o bit 
// se o valor de dataOut e (E lógico) uma máscara de bits forem verdadeiros, defina 
// pinState como 1 (HIGH) 
  if (dataOut & (1<<i)) { 
  pinState = HIGH; 
}
  else { 
  pinState = LOW; 
} 
// define dataPin como HIGH ou LOW, dependendo de pinState 
  digitalWrite(dataPin, pinState); 
  digitalWrite(clockPin, HIGH); // envia o bit no extremo ascendente do clock 
  digitalWrite(dataPin, LOW); 
} 
  digitalWrite(clockPin, LOW); // interrompe o deslocamento 
} 