#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHT_PIN 2
#define DHT_TYPE DHT22
#define LED_CALENTAR 3
#define LED_ENFRIAR 4

DHT dht(DHT_PIN, DHT_TYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

float tempDeseada = 25.0;
float zonamuerta = 3.0;
float limiteMax, limiteMin;

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
  
  pinMode(LED_CALENTAR, OUTPUT);
  pinMode(LED_ENFRIAR, OUTPUT);
  
  limiteMax = tempDeseada + zonamuerta;
  limiteMin = tempDeseada - zonamuerta;
  
  lcd.setCursor(0, 0);
  lcd.print("Control Temp");
}

void loop() {
  float temperatura = dht.readTemperature();
  
  if (!isnan(temperatura)) {
    TresPosSinHist(temperatura);
    mostrarLCD(temperatura);
  }
  
  delay(500);
}

void TresPosSinHist(float temp) {
  if (temp > limiteMax) {
    // Enfriar
    digitalWrite(LED_ENFRIAR, HIGH);
    digitalWrite(LED_CALENTAR, LOW);
    Serial.println("ENFRIANDO");
  }
  else if (temp < limiteMin) {
    // Calentar
    digitalWrite(LED_CALENTAR, HIGH);
    digitalWrite(LED_ENFRIAR, LOW);
    Serial.println("CALENTANDO");
  }
  else {
    // Zona muerta - No acción
    digitalWrite(LED_CALENTAR, LOW);
    digitalWrite(LED_ENFRIAR, LOW);
    Serial.println("EN RANGO");
  }
}

void mostrarLCD(float temp) {
  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(temp, 1);
  lcd.print("C SP:");
  lcd.print(tempDeseada, 0);
}