#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Servo.h>

// === CONFIGURACIÓN DE PINES ===
#define DHT_PIN 2
#define DHT_TYPE DHT22
#define LDR_PIN A0
#define POT_VIENTO_PIN A1
#define POT_AIRE_PIN A2
#define LED_ROJO 3          // Calentamiento
#define LED_AZUL 4          // Enfriamiento
#define LED_ALERTA 8        // Alerta general

// Pines para 74HC595
#define DATA_PIN 5
#define LATCH_PIN 6
#define CLOCK_PIN 7
#define SERVO_PIN 9

// === PARÁMETROS DE CONTROL ===
const float TEMP_OBJETIVO = 25.0;
const float TEMP_TOLERANCIA = 3.0;
const float TEMP_MIN = TEMP_OBJETIVO - TEMP_TOLERANCIA;  // 22°C
const float TEMP_MAX = TEMP_OBJETIVO + TEMP_TOLERANCIA;  // 28°C
const int ILUMINACION_OBJETIVO = 80;
const unsigned long INTERVALO_ACTUALIZACION = 1000;

// === OBJETOS ===
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHT_PIN, DHT_TYPE);
Servo servoPanel;

// === VARIABLES GLOBALES ===
unsigned long ultimaActualizacion = 0;
float temperatura = 0;
float humedad = 0;
float lux = 0;
int calidadAire = 0;
float velocidadViento = 0;
int nivelIluminacion = 0;

void setup() {
  Serial.begin(9600);
  
  // Configurar pines
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED_ALERTA, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  
  // Inicializar componentes
  lcd.init();
  lcd.backlight();
  dht.begin();
  servoPanel.attach(SERVO_PIN);
  
  // Mensaje de inicio
  mostrarMensajeInicio();
  delay(2000);
  
  Serial.println("=== SISTEMA DE CONTROL CLIMATICO ===");
  Serial.println("Temp. Objetivo: 25°C ±3°C");
  Serial.println("Iluminación: 80%");
  Serial.println("====================================");
}

void mostrarMensajeInicio() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CONTROL CLIMATICO");
  lcd.setCursor(4, 1);
  lcd.print("ARDUINO");
}

void leerSensores() {
  // Leer temperatura y humedad
  temperatura = dht.readTemperature();
  humedad = dht.readHumidity();
  
  // Verificar errores del DHT
  if (isnan(temperatura) || isnan(humedad)) {
    Serial.println("Error leyendo DHT22!");
    temperatura = 25.0; // Valor por defecto
    humedad = 50.0;
  }
  
  // Leer LDR y calcular lux
  int tension = analogRead(LDR_PIN);
  if (tension == 0) {
    lux = 0;
  } else {
    float R = 10.0; // Resistencia en kΩ
    float valorLDR = ((1023.0 * R) / tension) - R;
    if (valorLDR > 0) {
      lux = 800.69 * pow(valorLDR, -1.283);
    } else {
      lux = 1000; // Valor máximo si hay mucha luz
    }
  }
  
  // Limitar rango de lux
  lux = constrain(lux, 0, 1000);
  
  // Leer velocidad del viento (simulada)
  int potValue = analogRead(POT_VIENTO_PIN);
  velocidadViento = map(potValue, 0, 1023, 0, 100);
  
  // Leer calidad del aire (simulada)
  calidadAire = analogRead(POT_AIRE_PIN);
}

void controlTemperatura() {
  // Apagar ambos LEDs primero
  digitalWrite(LED_ROJO, LOW);
  digitalWrite(LED_AZUL, LOW);
  
  if (temperatura < TEMP_MIN) {
    // Activar calentamiento
    digitalWrite(LED_ROJO, HIGH);
  } 
  else if (temperatura > TEMP_MAX) {
    // Activar enfriamiento
    digitalWrite(LED_AZUL, HIGH);
  }
  // Zona muerta: 22°C - 28°C (sin acción)
}

void controlIluminacion() {
  // Calcular porcentaje de luz actual (0-100%)
  int porcentajeLuz = map(lux, 0, 1000, 0, 100);
  porcentajeLuz = constrain(porcentajeLuz, 0, 100);
  
  // Calcular cuántos LEDs encender para llegar al 80%
  int luzNecesaria = ILUMINACION_OBJETIVO - porcentajeLuz;
  if (luzNecesaria < 0) luzNecesaria = 0;
  
  // Mapear a 8 LEDs (0-8)
  nivelIluminacion = map(luzNecesaria, 0, 80, 0, 8);
  nivelIluminacion = constrain(nivelIluminacion, 0, 8);
  
  // Crear patrón de LEDs
  byte patronLEDs = 0;
  for (int i = 0; i < nivelIluminacion; i++) {
    patronLEDs |= (1 << i);
  }
  
  // Enviar datos al 74HC595
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, patronLEDs);
  digitalWrite(LATCH_PIN, HIGH);
}

void controlarPanelSolar() {
  int angulo = map(lux, 0, 1000, 0, 90);
  angulo = constrain(angulo, 0, 90);
  servoPanel.write(angulo);
}

void controlAlertas() {
  bool alerta = false;
  
  // Condiciones de alerta
  if (temperatura > 35 || temperatura < 10) alerta = true;
  if (humedad > 80) alerta = true;
  if (calidadAire > 600) alerta = true;
  if (velocidadViento > 80) alerta = true;
  
  digitalWrite(LED_ALERTA, alerta ? HIGH : LOW);
}

void mostrarEnLCD() {
  static int pantalla = 0;
  static unsigned long ultimoCambio = 0;
  
  // Cambiar pantalla cada 3 segundos
  if (millis() - ultimoCambio > 3000) {
    pantalla = (pantalla + 1) % 4;
    ultimoCambio = millis();
  }
  
  lcd.clear();
  
  switch (pantalla) {
    case 0: // Temperatura y Control
      lcd.setCursor(0, 0);
      lcd.print("T:");
      lcd.print(temperatura, 1);
      lcd.print("C H:");
      lcd.print(humedad, 0);
      lcd.print("%");
      
      lcd.setCursor(0, 1);
      if (temperatura < TEMP_MIN) {
        lcd.print("CALENTANDO");
      } else if (temperatura > TEMP_MAX) {
        lcd.print("ENFRIANDO");
      } else {
        lcd.print("TEMP OK (25±3C)");
      }
      break;
      
    case 1: // Iluminación
      lcd.setCursor(0, 0);
      lcd.print("LUZ:");
      lcd.print((int)lux);
      lcd.print(" lx");
      
      lcd.setCursor(0, 1);
      int porcentaje = map(lux, 0, 1000, 0, 100);
      lcd.print("Nivel:");
      lcd.print(porcentaje);
      lcd.print("% LEDs:");
      lcd.print(nivelIluminacion);
      break;
      
    case 2: // Ambiente
      lcd.setCursor(0, 0);
      lcd.print("VIENTO:");
      lcd.print(velocidadViento, 0);
      lcd.print("km/h");
      
      lcd.setCursor(0, 1);
      lcd.print("AIRE:");
      lcd.print(calidadeAire);
      if (calidadAire > 600) {
        lcd.print(" MALO");
      } else if (calidadAire > 400) {
        lcd.print(" REG");
      } else {
        lcd.print(" BUENO");
      }
      break;
      
    case 3: // Sistema
      lcd.setCursor(0, 0);
      lcd.print("SISTEMA ACTIVO");
      lcd.setCursor(0, 1);
      lcd.print("Panel:");
      lcd.print(map(lux, 0, 1000, 0, 90));
      lcd.print("° IL:80%");
      break;
  }
}

void imprimirEstadoSerie() {
  Serial.println("=== ESTADO SISTEMA ===");
  Serial.print("Temp: ");
  Serial.print(temperatura);
  Serial.print("°C ");
  
  if (temperatura < TEMP_MIN) {
    Serial.println("-> CALENTANDO");
  } else if (temperatura > TEMP_MAX) {
    Serial.println("-> ENFRIANDO");
  } else {
    Serial.println("-> OK");
  }
  
  Serial.print("Humedad: ");
  Serial.print(humedad);
  Serial.println("%");
  
  Serial.print("Luz: ");
  Serial.print(lux);
  Serial.print(" lx -> LEDs: ");
  Serial.print(nivelIluminacion);
  Serial.println("/8");
  
  Serial.print("Panel Solar: ");
  Serial.print(map(lux, 0, 1000, 0, 90));
  Serial.println("°");
  
  Serial.print("Viento: ");
  Serial.print(velocidadViento);
  Serial.println(" km/h");
  
  Serial.print("Aire: ");
  Serial.println(calidadeAire);
  Serial.println("=====================");
}

void loop() {
  unsigned long tiempoActual = millis();
  
  if (tiempoActual - ultimaActualizacion >= INTERVALO_ACTUALIZACION) {
    // Leer sensores
    leerSensores();
    
    // Ejecutar controles
    controlTemperatura();
    controlIluminacion();
    controlarPanelSolar();
    controlAlertas();
    
    // Actualizar display
    mostrarEnLCD();
    
    // Debug cada 5 segundos
    static unsigned long ultimoDebug = 0;
    if (tiempoActual - ultimoDebug > 5000) {
      imprimirEstadoSerie();
      ultimoDebug = tiempoActual;
    }
    
    ultimaActualizacion = tiempoActual;
  }
}