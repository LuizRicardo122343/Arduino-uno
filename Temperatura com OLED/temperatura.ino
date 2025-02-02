#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <DHT.h>

// Configuração do OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_I2C_ADDRESS 0x3C // Endereço I2C do OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Configuração do DHT22
#define DHTPIN 2     // Pino onde o DHT22 está conectado
#define DHTTYPE DHT22 // Define o tipo do sensor como DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Inicializa o monitor serial
  Serial.begin(9600);
  Serial.println("Inicializando...");

  // Inicializa o display OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
    Serial.println("Falha ao inicializar o OLED.");
    while (true); // Para o programa em caso de erro
  } else {
    Serial.println(("ssd1306 oled display e funcionando."));
  }
  // Inicializa o PIR
  if (digitalRead(DHTTYPE)) {
    Serial.println(("dht22 não encontrado!"));
    while (1); // Parar o programa
  } else {
    Serial.println(("dht22 temperatura e Umidade e funcionando."));
  }

  // Limpa o display e exibe uma mensagem inicial
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Inicializando...");
  display.display();

  // Inicializa o sensor DHT
  dht.begin();

  // Aguardar estabilização
  delay(2000);
  display.clearDisplay();
  display.println("Sistema Pronto!");
  display.display();
  Serial.println("Sistema pronto!");
}

void loop() {
  // Lê a temperatura e a umidade
  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();

  // Verifica se os valores são válidos
  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println("Erro ao ler o sensor!");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Erro ao ler");
    display.println("o sensor DHT!");
    display.display();
    delay(2000);
    return;
  }

  // Exibe os valores no monitor serial
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");
  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.println(" %");

  // Exibe os valores no OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Leitura do DHT22:");
  display.print("Temperatura: ");
  display.print(temperatura);
  display.println(" C");
  display.print("Umidade: ");
  display.print(umidade);
  display.println(" %");
  display.display();

  // Aguarda 2 segundos antes da próxima leitura
  delay(2000);
}
