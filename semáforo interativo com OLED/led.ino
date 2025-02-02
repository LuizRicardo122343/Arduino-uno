#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // Largura do display OLED
#define SCREEN_HEIGHT 64  // Altura do display OLED
#define OLED_RESET    -1  // Reset do display

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Definições dos pinos
int carRed = 12;       // LED vermelho para carros
int carYellow = 11;    // LED amarelo para carros
int carGreen = 10;     // LED verde para carros
int pedRed = 9;        // LED vermelho para pedestres
int pedGreen = 8;      // LED verde para pedestres
int button = 2;        // Botão para solicitar travessia de pedestres

bool pedButtonPressed = false;
unsigned long lastButtonPress = 0;  // Armazena o tempo do último pressionamento do botão
unsigned long debounceDelay = 200;  // Tempo de debounce (200ms)

void setup() {
  // Configura os pinos dos LEDs como saída
  pinMode(carRed, OUTPUT);
  pinMode(carYellow, OUTPUT);
  pinMode(carGreen, OUTPUT);
  pinMode(pedRed, OUTPUT);
  pinMode(pedGreen, OUTPUT);

  // Configura o botão como entrada com pull-up interno
  pinMode(button, INPUT_PULLUP);

  // Inicializa o Serial Monitor
  Serial.begin(9600);

  // Inicializa o display OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Falha ao iniciar o display OLED"));
    while(true);  // Fica em loop se o display não for encontrado
  }

  // Inicia o semáforo em estado padrão: carro verde e pedestre vermelho
  digitalWrite(carGreen, HIGH);
  digitalWrite(pedRed, HIGH);

  // Inicializa o display com uma mensagem de boas-vindas
  display.display();
  delay(2000); // Espera 2 segundos para o usuário ver o display
  display.clearDisplay();
}

void loop() {
  // Verifica o tempo passado desde o último pressionamento do botão
  unsigned long currentMillis = millis();

  // Verifica se o botão foi pressionado e se o tempo de debounce já passou
  if (digitalRead(button) == LOW && currentMillis - lastButtonPress > debounceDelay) {
    pedButtonPressed = true;  // Sinaliza pedido de travessia
    lastButtonPress = currentMillis;  // Atualiza o tempo do último pressionamento
  }

  if (pedButtonPressed) {
    // Sinaliza para os carros pararem e permite a passagem dos pedestres
    Serial.println("Pedido de travessia recebido. Mudando semáforo...");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.println("Pedido de travessia");
    display.println("recebido. Mudando");
    display.println("semáforo...");
    display.display();

    // 1. Carros amarelo, pedestres vermelho
    digitalWrite(carGreen, LOW);
    digitalWrite(carYellow, HIGH);
    delay(2000);
    
    // 2. Carros vermelho, pedestres vermelho
    digitalWrite(carYellow, LOW);
    digitalWrite(carRed, HIGH);
    delay(1000);

    // 3. Pedestres verde, carros vermelho
    digitalWrite(pedRed, LOW);
    digitalWrite(pedGreen, HIGH);
    Serial.println("Pedestres: VERDE - Travessia permitida");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Pedestres: VERDE");
    display.println("Travessia permitida");
    display.display();
    delay(5000); // Tempo de travessia para pedestres
    
    // 4. Carros vermelho, pedestres vermelho
    digitalWrite(pedGreen, LOW);
    digitalWrite(pedRed, HIGH);
    Serial.println("Pedestres: VERMELHO - Travessia encerrada");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Pedestres: VERMELHO");
    display.println("Travessia encerrada");
    display.display();
    delay(1000);

    // 5. Carros amarelo piscando
    digitalWrite(carRed, LOW);
    digitalWrite(carYellow, HIGH);
    delay(2000);

    // 6. Carros verde, pedestres vermelho
    digitalWrite(carYellow, LOW);
    digitalWrite(carGreen, HIGH);
    Serial.println("Carros: VERDE - Siga");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Carros: VERDE");
    display.println("Siga");
    display.display();
    
    // Reseta o botão
    pedButtonPressed = false;
  }
  
  delay(100); // Delay para estabilidade do botão
}
