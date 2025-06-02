#include <LiquidCrystal.h>
#include <dht.h>
#include <math.h>
#include <Servo.h>
#include <Stepper.h>

// === Pines ===
int tempPin = 3;          // Pin del sensor DHT22
const int LDR = A0;       // Pin del LDR
const int POT = A1;       // Pin del potenciómetro (velocidad del viento)
const int LED = 8;        // LED de aviso

// LCD Pins
int RS = 13;
int EN = 12;
int D4 = 11;
int D5 = 10;
int D6 = 6;
int D7 = 5;

// === ELEMENTRO ELECTRONICOS
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
dht DHT; // Objeto del sensor DHT
Servo servoPanel;
const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11); // Orden específico

// === Variables ===
int tension;        // Valor analógico leído del LDR
float valorLDR;     // Resistencia del LDR
float lux;          // Intensidad de luz en lux
const float R = 10; // Resistencia fija en KOhmios
const int servoPin = 9;// Define the signal pin of the servo pin
const int MQ135 = A2; // Pin analógico simulado con potenciómetro
int calidadAire = 0;


float windSpeed = 0; // Velocidad del viento en km/h

void setup() {

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  lcd.begin(16, 2);

  lcd.setCursor(3, 0);
  lcd.print("PRACTICA DE");
  lcd.setCursor(2, 1);
  lcd.print("INSTRUMENTACION");
  delay(1500);
  lcd.clear();

  servoPanel.attach(servoPin);
  myStepper.setSpeed(10); // RPM del motor
}

void controlarPanelSolar(float lux) {
  int angulo = map(lux, 0, 1000, 0, 90);  // Panel se mueve de 0° a 90°
  angulo = constrain(angulo, 0, 90);      // Seguridad
  servoPanel.write(angulo);
}

void loop() {
  // === Leer datos del DHT ===
  DHT.read22(tempPin);
  float TEMP = DHT.temperature;
  float HUMI = DHT.humidity;

  // === Leer datos del LDR y calcular lux ===
  tension = analogRead(LDR);

  if (tension == 0) {
    lux = 0; // Para evitar división por 0
  } else {
    valorLDR = ((1023.0 * R) / tension) - R;
    lux = 800.69 * pow(valorLDR, -1.283);
  }
  

// === TEMPERATURA
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TEMP: ");
  lcd.print(TEMP);
  lcd.print(" C");

  if (TEMP >= 30) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
  delay(1000);


// === HUMEDAD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("HUMI: ");
  lcd.print(HUMI);
  lcd.print(" %");

  if (HUMI >= 50) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
  delay(1000);
  
// === LUZ
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LUZ: ");
  lcd.print((int)lux);
  lcd.print(" lx");

  lcd.setCursor(0, 1);
  if (lux < 100) {
    lcd.print("Nivel: BAJO ");
    digitalWrite(LED, LOW);
  } else if (lux < 500) {
    lcd.print("Nivel: MEDIO");
    digitalWrite(LED, LOW);
  } else {
    lcd.print("Nivel: ALTO ");
    digitalWrite(LED, HIGH);
  }
  controlarPanelSolar(lux);
  delay(1000);


// === VIENTO
  int potValue = analogRead(POT);
  windSpeed = map(potValue, 0, 1023, 0, 100);  // 0-100 km/h

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("VIENTO: ");
  lcd.print(windSpeed);
  lcd.print(" km/h");

  lcd.setCursor(0, 1);
  if (windSpeed < 20) {
    lcd.print("Viento suave");
  } else if (windSpeed < 60) {
    lcd.print("Viento medio");
  } else {
    lcd.print("Viento fuerte");
  }
  delay(1000);

// === calidad del aire
  calidadAire = analogRead(MQ135);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("AIRE: ");
  lcd.print(calidadAire);

  lcd.setCursor(0, 1);
  if (calidadAire < 200) {
    lcd.print("Buena calidad");
    digitalWrite(LED, LOW);
  } else if (calidadAire < 400) {
    lcd.print("Aceptable");
    digitalWrite(LED, LOW);
  } else {
    lcd.print("Mala calidad");
    digitalWrite(LED, HIGH); // Enciende LED por alerta
  }
  delay(1000);


//controlVentilador(TEMP, HUMI, calidadAire);


}

/*
void controlVentilador(float TEMP, float HUMI, int calidadAire) {
  lcd.clear();
  lcd.setCursor(0, 0);

  if (TEMP > 35 || calidadAire > 600) {
    lcd.print("VENTILADOR ALTO");
    myStepper.setSpeed(15);
    myStepper.step(2048 / 2); // 1/2 vuelta
  } 
  else if ((TEMP >= 30 && TEMP <= 35) || (calidadAire >= 400 && calidadAire <= 600)) {
    lcd.print("VENTILADOR MEDIO");
    myStepper.setSpeed(10);
    myStepper.step(2048 / 4); // 1/4 vuelta
  }
  else if ((TEMP >= 25 && TEMP < 30) || (calidadAire >= 200 && calidadAire < 400) || HUMI > 60) {
    lcd.print("VENTILADOR BAJO");
    myStepper.setSpeed(5);
    myStepper.step(2048 / 8); // 1/8 vuelta
  }
  else {
    lcd.print("VENTILADOR OFF");
    delay(1000);
  }

  delay(1000); // Tiempo para ver el mensaje
}
*/

