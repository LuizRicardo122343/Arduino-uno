#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// Configuração do OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_I2C_ADDRESS 0x3C // Endereço I2C do OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pino do sensor PIR
#define PIR_PIN 7

void setup() {
  // Inicializa o monitor serial
  Serial.begin(9600);
  Serial.println("Sistema iniciado!");

  // Configura o pino do PIR como entrada
  pinMode(PIR_PIN, INPUT);

  // Inicializa o display OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
    Serial.println("Falha ao inicializar o OLED.");
    while (true); // Para o programa em caso de erro
  } else {
    Serial.println(("ssd1306 oled display e funcionando."));
  }
  // Inicializa o PIR
  if (digitalRead(PIR_PIN)) {
    Serial.println(("HC-SR501 não encontrado!"));
    while (1); // Parar o programa
  } else {
    Serial.println(("HC-SR501 detectado e funcionando."));
  }
  // Limpa o display e exibe mensagem inicial
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("PIR Iniciado");
  display.display();
}

void loop() {
  // Lê o estado do sensor PIR
  int pirState = digitalRead(PIR_PIN);

  if (pirState == HIGH) {
    // Movimento detectado
    Serial.println("Movimento detectado!");

    // Exibe mensagem no OLED
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Movimento:");
    display.println("Detectado!");
    display.display();
  } else {
    // Sem movimento
    Serial.println("Sem movimento.");

    // Exibe mensagem no OLED
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Movimento:");
    display.println("Nao detectado.");
    display.display();
  }
  delay(500); // Aguarda 500ms antes de verificar novamente
}
