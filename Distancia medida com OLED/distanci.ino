#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// Configuração do display OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_I2C_ADDRESS 0x3C // Endereço I2C do OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pinos do HC-SR04
#define TRIG_PIN 9
#define ECHO_PIN 8

void setup() {
  // Inicializa o monitor serial
  Serial.begin(9600);
  Serial.println("Sistema iniciado!");

  // Configura os pinos do HC-SR04
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Inicializa o display OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
    Serial.println("Falha ao inicializar o OLED.");
    while (true); // Para o programa em caso de erro
   } else {
    Serial.println(("ssd1306 oled display e funcionando."));
  }

  if (digitalRead(ECHO_PIN)) {
    Serial.println(("HC-SR04 não encontrado!"));
    while (1); // Parar o programa
  } else {
    Serial.println(("HC-SR04 Distancia e funcionando."));
  }

  // Limpa e exibe mensagem inicial no OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("HC-SR04 Iniciado");
  display.display();
}

void loop() {
  // Gera o pulso TRIG
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Lê o pulso ECHO
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calcula a distância em cm
  float distance = duration * 0.034 / 2;

  // Exibe a distância no monitor serial
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Exibe a distância no OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("HC-SR04:");
  display.print("Distancia: ");
  display.print(distance);
  display.println(" cm");
  display.display();

  // Aguarda 500ms antes da próxima leitura
  delay(500);
}
