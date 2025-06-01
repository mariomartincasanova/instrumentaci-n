#define DATA_PIN 2    // Pin de datos
#define LATCH_PIN 3   // Pin de latch
#define CLOCK_PIN 4   // Pin de reloj

void setup() {
  Serial.begin(9600);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  
  Serial.println("Control 8 LEDs con 74HC595");
}

void loop() {
  // Encender LEDs secuencialmente
  for (int i = 0; i < 8; i++) {
    byte patron = 1 << i; // Desplazar bit
    enviarDatos(patron);
    delay(200);
  }
  
  // Apagar LEDs secuencialmente
  for (int i = 7; i >= 0; i--) {
    byte patron = 1 << i;
    enviarDatos(patron);
    delay(200);
  }
  
  // Patrón especial
  enviarDatos(B10101010); // LEDs alternos
  delay(500);
  enviarDatos(B01010101); // LEDs alternos opuestos
  delay(500);
}

void enviarDatos(byte datos) {
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, datos);
  digitalWrite(LATCH_PIN, HIGH);
}